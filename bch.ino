//////////////////////////////////////////////////////////////////////////////// emergency message
////////////////////////////////////////////////////////////////////////////////////////////////////
bool emg_msg[144];
bool biphase_msg[288];
//////////////////////////////////////////////////////////////////////////// function declarations
void bch_gen82( bool*);
void message_assign(bool*);
void emgto_biphase();
///////////////////////////////////////////////////////////////////////////// void setup
////////////////////////////////////////////////////////////////////////////////////////////
void setup(){
    Serial.begin(9600);
    message_assign(emg_msg);
    
}
///////////////////////////////////////////////////////////////////////////// void loop
void loop(){

/////////////////////////////// bch generation
    bch_gen82(emg_msg);
//////////////////////////////  emg msg display    
    for(int i=0;i<144;i++){
      Serial.print(emg_msg[i]);
    }
    Serial.println();
//////////////////////////////// biphase transmission  
     emgto_biphase();
}
/////////////////////////////////////////////////////// function definitions
void bch_gen82( bool emg_message[]){
  ///////////////////////////////////////////////////////////////////////     bch variables declaration and initialisation

    bool temp_word;
    bool temp_shift;
    int k;

///////////////////////////////////////////////////////////////////////     1st emg to data and code  

    bool data_word_1[61] ;
    bool code_word_1[21]; 

    for(k=0; k<61;k++)
    {
        data_word_1[k]= emg_msg[24+k];
    }

    for(k=0; k<21;k++)
    {
        code_word_1[k]= emg_msg[85+k];
    }
//////////////////////////////////////////////////////////////////////////    2nd emg to data and code

    bool data_word_2[26] ;
    bool code_word_2[12]; 

    for(k=0; k<26;k++)
    {
        data_word_2[k]= emg_msg[106+k];
    }

    for(k=0; k<12;k++)
    {
        code_word_2[k]= emg_msg[132+k];
    }

///////////////////////////////////////////////////////////////////////////// BCH1 generation
////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////// step_1////////// rotate code word

    temp_word = data_word_1[60];
    for(k=60;k>0;k--)
    {
        data_word_1[k]=data_word_1[k-1];
    }
    data_word_1[0]=false;

///////////////////////////////  step_2 /////////// d60 xor c20

    data_word_1[60] = (data_word_1[60]^code_word_1[20]);

////////////////////////////// step_3  ////////////////shift code word

    temp_shift = code_word_1[20];
    for(k=20;k>0;k--)
    {
        code_word_1[k]=code_word_1[k-1];
    }
    code_word_1[0]=temp_shift;
    
///////////////////////////////// step_4 //////////////// xor with generator


    temp_word = (temp_word^(true));
    code_word_1[0] = (code_word_1[0]^(true));
    code_word_1[4] = (code_word_1[4]^(true));
    code_word_1[5] = (code_word_1[5]^(true));
    code_word_1[6] = (code_word_1[6]^(true));
    code_word_1[7] = (code_word_1[7]^(true));
    code_word_1[10] = (code_word_1[10]^(true));
    code_word_1[11] = (code_word_1[11]^(true));
    code_word_1[13] = (code_word_1[13]^(true));
    code_word_1[14] = (code_word_1[14]^(true));
    code_word_1[16] = (code_word_1[16]^(true));
    code_word_1[17] = (code_word_1[17]^(true));
    code_word_1[20] = (code_word_1[20]^(true));

///////////////////////////////// step_1////////// rotate code word

    temp_word = data_word_1[60];
    for(k=60;k>0;k--)
    {
        data_word_1[k]=data_word_1[k-1];
    }
    data_word_1[0]=false;

///////////////////////////////  step_2 /////////// d60 xor c20

    data_word_1[60] = (data_word_1[60]^code_word_1[20]);

////////////////////////////// step_3  ////////////////shift code word

    temp_shift = code_word_1[20];
    for(k=20;k>0;k--)
    {
        code_word_1[k]=code_word_1[k-1];
    }
    code_word_1[0]=temp_shift;

///////////////////////////////// step_1////////// rotate code word

    temp_word = data_word_1[60];
    for(k=60;k>0;k--)
    {
        data_word_1[k]=data_word_1[k-1];
    }
    data_word_1[0]=false;

///////////////////////////////  step_2 /////////// d60 xor c20

    data_word_1[60] = (data_word_1[60]^code_word_1[20]);

////////////////////////////// step_3  ////////////////shift code word

    temp_shift = code_word_1[20];
    for(k=20;k>0;k--)
    {
        code_word_1[k]=code_word_1[k-1];
    }
    code_word_1[0]=temp_shift;

///////////////////////////////// step_4 //////////////// xor with generator


    temp_word = (temp_word^(true));
    code_word_1[0] = (code_word_1[0]^(true));
    code_word_1[4] = (code_word_1[4]^(true));
    code_word_1[5] = (code_word_1[5]^(true));
    code_word_1[6] = (code_word_1[6]^(true));
    code_word_1[7] = (code_word_1[7]^(true));
    code_word_1[10] = (code_word_1[10]^(true));
    code_word_1[11] = (code_word_1[11]^(true));
    code_word_1[13] = (code_word_1[13]^(true));
    code_word_1[14] = (code_word_1[14]^(true));
    code_word_1[16] = (code_word_1[16]^(true));
    code_word_1[17] = (code_word_1[17]^(true));
    code_word_1[20] = (code_word_1[20]^(true));

///////////////////////////////////////////////////////////// 1st bch code to emg 

for(k=0; k<21;k++)
    {
         emg_msg[85+k]= code_word_1[k];
    }


///////////////////////////////////////////////////////////////////////////// BCH2 generation
////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////// step_1////////// rotate code word

    temp_word = data_word_1[25];
    for(k=25;k>0;k--)
    {
        data_word_1[k]=data_word_1[k-1];
    }
    data_word_1[0]=false;

///////////////////////////////  step_2 /////////// d60 xor c20

    data_word_1[25] = (data_word_1[25]^code_word_1[11]);

////////////////////////////// step_3  ////////////////shift code word

    temp_shift = code_word_1[11];
    for(k=11;k>0;k--)
    {
        code_word_1[k]=code_word_1[k-1];
    }
    code_word_1[0]=temp_shift;
    
///////////////////////////////// step_4 //////////////// xor with generator


    temp_word = (temp_word^(true));
    code_word_1[0] = (code_word_1[0]^(true));
    code_word_1[4] = (code_word_1[4]^(true));
    code_word_1[5] = (code_word_1[5]^(true));
    code_word_1[6] = (code_word_1[6]^(true));
    code_word_1[7] = (code_word_1[7]^(true));
    code_word_1[10] = (code_word_1[10]^(true));
    code_word_1[11] = (code_word_1[11]^(true));

///////////////////////////////// step_1////////// rotate code word

    temp_word = data_word_1[25];
    for(k=25;k>0;k--)
    {
        data_word_1[k]=data_word_1[k-1];
    }
    data_word_1[0]=false;

///////////////////////////////  step_2 /////////// d60 xor c20

    data_word_1[25] = (data_word_1[25]^code_word_1[11]);

////////////////////////////// step_3  ////////////////shift code word

    temp_shift = code_word_1[11];
    for(k=11;k>0;k--)
    {
        code_word_1[k]=code_word_1[k-1];
    }
    code_word_1[0]=temp_shift;

///////////////////////////////// step_1////////// rotate code word

    temp_word = data_word_1[25];
    for(k=25;k>0;k--)
    {
        data_word_1[k]=data_word_1[k-1];
    }
    data_word_1[0]=false;

///////////////////////////////  step_2 /////////// d60 xor c20

    data_word_1[25] = (data_word_1[25]^code_word_1[11]);

////////////////////////////// step_3  ////////////////shift code word

    temp_shift = code_word_1[11];
    for(k=11;k>0;k--)
    {
        code_word_1[k]=code_word_1[k-1];
    }
    code_word_1[0]=temp_shift;

///////////////////////////////// step_4 //////////////// xor with generator


    temp_word = (temp_word^(true));
    code_word_1[0] = (code_word_1[0]^(true));
    code_word_1[4] = (code_word_1[4]^(true));
    code_word_1[5] = (code_word_1[5]^(true));
    code_word_1[6] = (code_word_1[6]^(true));
    code_word_1[7] = (code_word_1[7]^(true));
    code_word_1[10] = (code_word_1[10]^(true));
    code_word_1[11] = (code_word_1[11]^(true)); 

///////////////////////////////////////////////////////////// 2st bch code to emg 

for(k=0; k<12;k++)
    {
         emg_msg[106+k]= code_word_1[k];
    }
///////////////////////////////////////////////////////////////////end

}

void message_assign(bool message[] ){
/////////////////////////////////////////////  bit synchronisation 0 - 14 - all 1s
int i;
for(i=0;i<15;i++){
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
  for(i=40;i<49;i++){
      message[i]= false;  
  }
////////////////////////////////////////////////  14 bit serial number
  for(i=50;i<63;i++){
      message[i]= false;  
  }
////////////////////////////////////////////////   latitude flag  (N/S :   0/1)
  message[64]= false; 
/////////////////////////////////////////////// latitude in degree (0 - 90 with .25 increment)
  for(i=65;i<72;i++){
      message[i]= false;  
  }
//////////////////////////////////////////////  lattitude in 1/4 increment
   message[72]= true; 
   message[73]= true; 
////////////////////////////////////////////////   logitude flag  (E/W :   0/1)
  message[74]= false; 
/////////////////////////////////////////////// logitude in degree (0 - 180 with .25 increment)
  for(i=75;i<83;i++){
      message[i]= false;  
  }
//////////////////////////////////////////////  logitude in 1/4 increment
   message[83]= true; 
   message[84]= true; 
//////////////////////////////////////////////  BCH_1 - 21 bit
   for(i=85;i<105;i++){
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
   for(i=132;i<144;i++){
      message[i]= false;  
  }
}
/////////////////////////////////////////////////////////////////
void emgto_biphase(){
  for(int i = 0 ; i<144; i){
    if( emg_msg[i] == true){
        biphase_msg[ (i*2) ] = emg_msg[i];
        biphase_msg[ (i*2) + 1 ] = ~ (emg_msg[i]) ;
    }
  }
}
