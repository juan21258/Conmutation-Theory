#define Start PINC,0                //Variables de juego
#define Pa PINC,1                  
#define Pe PINC,2
#define Pi PINC,3
#define Po PINC,4
#define Pu PINC,5
int v; //Equivalente a vocal
unsigned int TimeAc = 0;
unsigned int TimeAn = 0;

int Iniazar() //Genara Número al azar por medio de la función random 
{   
  randomSeed(millis());
  v = random(0,4);
  return v;
}

void gano() //Muestra letra G si se gana 
{
  for(int i=0;i<3;i++){
    PORTL = B01111101;
    delay(500);
    PORTL = B00000000;
    delay(500);  
  }
}

void perdio() //Muestra letra P si se pierde
{
  for(int i=0;i<3;i++){
    PORTL = B01110011;
    delay(500);
    PORTL = B00000000;
    delay(500);     
  }
}

void Espera10s()             //Función de espera 10 segundos 
{                           
  TimeAn = millis();
  TimeAc=millis();
  while(TimeAc-TimeAn<10000 &&(bitRead(PINC,Pa)==LOW && 
    bitRead(PINC,Pe)==LOW && bitRead(PINC,Pi)==LOW && bitRead(PINC,Po)==LOW 
    && bitRead(PINC,Pu)==LOW))
  {    
    TimeAc=millis();
  } 
}

void setup()
{
  DDRC = B00000000;
  DDRL = B01111111;
}

void loop(){
  if(bitRead(PINC,Start)==HIGH){             //Verifica que inicio el juego
    v = Iniazar();               
    if(v==0){                           
      PORTL = B01110111;
      delay(2000);
      PORTL = B00000000;
      Espera10s();                            //Tiempo para responder
      if bitRead(PINC,Pa==HIGH){        //Si respondió bien
        gano();
      }
      else{        //Si perdió 
        perdio();
      }
    }
    else if(v==1){                                  
      PORTL = B01111001;
      delay(2000);
      PORTL = B00000000;  
      Espera10s();                          
      if (bitRead(PINC,Pe)==HIGH){          
        gano();
      }
      else {                                  
        perdio();
      }  
    }
    else if(v==2){
      PORTL = B00000110;
      delay(2000);
      PORTL = B00000000;
      Espera10s();                                
      if (bitRead(PINC,Pi)==HIGH){                
        gano();
      }
      else {                                      
        perdio();
      }  
    }
    else if (v==3){
      PORTL = B00111111;
      delay(2000);
      PORTL = B00000000;
      Espera10s();                                  
      if (bitRead(PINC,Po)==HIGH){                  
        gano();
      }
      else {                                      
        perdio();
      }  
    }
    else if (v==4){
      PORTL = B00111110;
      delay(2000);
      PORTL = B00000000;
      Espera10s;                                          
      if (bitRead(PINC,Pu)==HIGH){                       
        gano();
      }
      else {                                            
        perdio();
      }  
    }
  }
}












