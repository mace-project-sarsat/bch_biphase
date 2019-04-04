//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////  bch generation  //////////////////////
//////////////////////////////////////////////////////////////////////////////

bool emg_msg[ 144 ] ;
bool biphase_msg[ 288 ];
uint8_t msgLength_1 = 82 ;
uint8_t genLength_1 = 22 ;
uint8_t emgLength_1 = 61 ;
uint8_t msg_offset_1 = 24 ;

uint8_t msgLength_2 = 38 ;
uint8_t genLength_2 = 13 ;
uint8_t emgLength_2 = 26 ;
uint8_t msg_offset_2 = 106 ;


///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////    function declarations   //////////////////
///////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////  void setup    /////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void setup(){
  
  Serial.begin(9800);
  
}

////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////    void loop   //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

void loop(){
  
  message_assign( emg_msg );
  
  //bch_gen( emg_msg, msgLength_2, genLength_2 , emgLength_2  , msg_offset_2  );


  for( int i = 0; i < 144 ; i++)
  {
      Serial.print( emg_msg[ i ] );
  }
  Serial.println(" ");
  
  bch_gen( msgLength_1, genLength_1 , emgLength_1  , msg_offset_1  );
  bch_gen( msgLength_2, genLength_2 , emgLength_2  , msg_offset_2  );

  for( int i = 0; i < 144 ; i++)
  {
      Serial.print( emg_msg[ i ] );
  }
  Serial.println(" ");
  delay(1000); 
  
}

/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////     function definitions    /////////////////////
////////////////////////////////////////////////////////////////////////////////////

void bch_gen( uint8_t msgLength, uint8_t genLength , uint8_t emgLength , uint8_t msg_offset  )
{

    Serial.println("Entering bch_gen");
    
    Serial.println(msgLength);
    Serial.println(genLength);
    
    Serial.println(emgLength);
    Serial.println(msg_offset);
    
    bool msgPolynomial [ msgLength ];   
    bool genPolynomial [ genLength ];


    for( int k = 0; k < emgLength  ; k++ )
    {
      msgPolynomial[ k ] = emg_msg[ msg_offset + k ];
    }


    for( int k = emgLength ; k < msgLength ; k++)
    {
      msgPolynomial[k]= false ;
    }


    if( genLength == genLength_1 )
    {
      bch21_Generator( genPolynomial);
    }

    else
    {
      bch12_Generator( genPolynomial);
    }

    for (int i = 0; i < (msgLength - genLength +1) ; i++ )
    {
        if ( msgPolynomial[ i ] == true )
        {
          int temp = i;

          for (int k = temp ; k < ( genLength + temp ) ; k++ )
          {
            
            msgPolynomial[ k ] = ( ( msgPolynomial[ k ] ) ^ ( genPolynomial[ k - temp ] ) );

          }
          
        }
    }


    for( int k = 0; k < genLength ; k++ )
    {
      emg_msg[  k + emgLength + msg_offset  ] = msgPolynomial[ k + emgLength - 1 ];
    }

    for( int k = 0; k < genLength ; k++ )
    {
      Serial.print( msgPolynomial[ k + emgLength - 1]);
    } 
    Serial.println(" ");
}


///////////////////////////////////////////////////////////////////////
void bch21_Generator(bool* genPolynomial)
{
  Serial.println("Entering bch_21");
  genPolynomial[ 0 ] = true ;
  genPolynomial[ 1 ] = false ;
  genPolynomial[ 2 ] = false ;
  genPolynomial[ 3 ] = true ;

  genPolynomial[ 4 ] = true ;
  genPolynomial[ 5 ] = false ;
  genPolynomial[ 6 ] = true ;
  genPolynomial[ 7 ] = true ;

  genPolynomial[ 8 ] = false ;
  genPolynomial[ 9 ] = true ;
  genPolynomial[ 10 ] = true ;
  genPolynomial[ 11 ] = false ;

  genPolynomial[ 12 ] = false ;
  genPolynomial[ 13 ] = true ;
  genPolynomial[ 14 ] = true ;
  genPolynomial[ 15 ] = true ;

  genPolynomial[ 16 ] = true ;
  genPolynomial[ 17 ] = false ;
  genPolynomial[ 18 ] = false ;
  genPolynomial[ 19 ] = false ;

  genPolynomial[ 20 ] = true ;
  genPolynomial[ 21 ] = true ;
}

void bch12_Generator(bool* genPolynomial)
{
  Serial.println("Entering bch12");
  genPolynomial[ 0 ] = true ;
  genPolynomial[ 1 ] = false ;
  genPolynomial[ 2 ] = true ;
  genPolynomial[ 3 ] = false ;

  genPolynomial[ 4 ] = false ;
  genPolynomial[ 5 ] = true ;
  genPolynomial[ 6 ] = true ;
  genPolynomial[ 7 ] = false ;

  genPolynomial[ 8 ] = true ;
  genPolynomial[ 9 ] = true ;
  genPolynomial[ 10 ] = false ;
  genPolynomial[ 11 ] = false ;

  genPolynomial[ 11 ] = false ;
}


void message_assign(bool* message ){

  Serial.println("Entering message_assign");
/////////////////////////////////////////////  bit synchronisation 0 - 14 - all 1s
  int i;
  for(i=0;i<15;i++)
  {
      message[i]= true;  
  }
//////////////////////////////////////////// frame synchro 15- 23
    message[15]= false;
    message[16]= false;
    message[17]= false;
  
    message[18]= true;
    message[19]= false;
    message[20]= true;
  
    message[21]= true;
    message[22]= true;
    message[23]= true;
//////////////////////////////////////////// std location with MMSI
    message[24]= true;      // long message
    message[25]= false;     // location protocol
/////////////////////////////////////////// country code india 419
    message[26]= false;
    message[27]= true;
    message[28]= true;
    message[29]= false;

    message[30]= true;
    message[31]= false;
    message[32]= false;
    message[33]= false;

    message[34]= true;
    message[35]= true;
/////////////////////////////////////////////// std protocol type ; EPIRB-MMSI 0110
    message[36]= false;
    message[37]= true;
    message[38]= true;
    message[39]= false;
//////////////////////////////////////////////// 10 bit cospass sarsat approva certificate no
    for(i=40;i<49;i++)
    {
      message[i]= false;  
    }
////////////////////////////////////////////////  14 bit serial number
    for(i=50;i<63;i++)
    {
      message[i]= false;  
    }
////////////////////////////////////////////////   latitude flag  (N/S :   0/1)
    message[64]= false; 
/////////////////////////////////////////////// latitude in degree (0 - 90 with .25 increment)
    for(i=65;i<72;i++)
    {
      message[i]= false;  
    }
//////////////////////////////////////////////  lattitude in 1/4 increment
    message[72]= true; 
    message[73]= true; 
////////////////////////////////////////////////   logitude flag  (E/W :   0/1)
    message[74]= false; 
/////////////////////////////////////////////// logitude in degree (0 - 180 with .25 increment)
    for(i=75;i<83;i++)
    {
      message[i]= false;  
    }
//////////////////////////////////////////////  logitude in 1/4 increment
    message[83]= true; 
    message[84]= true; 
//////////////////////////////////////////////  BCH_1 - 21 bit
    for(i=85;i<105;i++)
    {
      message[i]= false;  
    }
/////////////////////////////////////////////  fixed bits (1101)
    message[106]= true;
    message[107]= true;
    message[108]= false;
    message[109]= true;
////////////////////////////////////////////  positional data provided by external device (yes/no) ; (0/1)
    message[110]= false;
///////////////////////////////////////////   auxiliary device :121.5 m hz (y/n)  : (1/0)
    message[111]= false;
/////////////////////////////////////////// latitue offset sign (-/+) : (0/1)
    message[112]= false;
/////////////////////////////////////////// latitude off set in min :(0-30 in 1 min increment)
    message[113]= false;
    message[114]= false;
    message[115]= false;
    message[116]= false;
    message[117]= true;
/////////////////////////////////////////// latitude off set in sec : (0-30 in 1 min increment)
    message[118]= false;
    message[119]= false;
    message[120]= false;
    message[121]= true;
  /////////////////////////////////////////// longitude offset sign (-/+) : (0/1)
    message[122]= false;
/////////////////////////////////////////// longitude off set in min : (0-30 in 1 min increment)
    message[123]= true;
    message[124]= false;
    message[125]= false;
    message[126]= false;
    message[127]= false;
/////////////////////////////////////////// longitude off set in sec : (0-30 in 1 min increment)
    message[128]= false;
    message[129]= false;
    message[130]= true;
    message[131]= false;
//////////////////////////////////////////////  BCH_2 - 12 bit
    for(i=132;i<144;i++)
    {
      message[i]= false;  
    }
}
////////////////////////////////////////////////////////////// biphase 
void emgto_biphase(){
  for(int i = 0 ; i<144; i){
    if( emg_msg[i] == true){
        biphase_msg[ (i*2) ] = emg_msg[i];
        biphase_msg[ (i*2) + 1 ] = ~ (emg_msg[i]) ;
    }
  }
}
