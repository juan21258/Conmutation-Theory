#define start PINC,0
#define Pa    PINC,1
#define Pe    PINC,2
#define Pi    PINC,3
#define Po    PINC,4
#define Pu    PINC,5

char a = B01110111;
char e = B01111001;
char i = B00000110;
char o = B00111111;
char u = B00111110;
//chars de estado de ganar o perder
char G=B01111101;
char P=B01110011;

char display[5]={a,e,i,o,u};
int numero;

void setup() {
  DDRC=B00000000;
  DDRL=B11111111;
   
}

int Aleatorio() {
    randomSeed(millis());    // genera una semilla para aleatorio a partir de la función millis()
    numero = random(0,5);    // genera número aleatorio entre 0 y 4 
    return numero;
} 

void loop() {
  if(bitRead(PINC,start)==HIGH){
    Aleatorio();
    if(numero == 0){
      PORTL=(display[a]);
      delay(2000);
    }
    if(numero == 1){
      PORTL=(display[e]);
      delay(2000);
    }
    if(numero == 2){
      PORTL=(display[i]);
      delay(2000);
    }
    if(numero == 3){
      PORTL=(display[o]);
      delay(2000);
    }
    if(numero == 4){
      PORTL=(display[u]);
      delay(2000);
    }
    
    if(bitRead(PINC,Pa)==HIGH && numero==0){
      PORTL=(display[G]);
      delay(500);
      PORTL=(display[G]);
      delay(500);
      PORTL=(display[G]);
      delay(500);
    }
    if(bitRead(PINC,Pa)==HIGH && numero==1){
      PORTL=(display[G]);
      delay(500);
      PORTL=(display[G]);
      delay(500);
      PORTL=(display[G]);
      delay(500);
    }
    if(bitRead(PINC,Pa)==HIGH && numero==2){
      PORTL=(display[G]);
      delay(500);
      PORTL=(display[G]);
      delay(500);
      PORTL=(display[G]);
      delay(500);
    }
    if(bitRead(PINC,Pa)==HIGH && numero==3){
      PORTL=(display[G]);
      delay(500);
      PORTL=(display[G]);
      delay(500);
      PORTL=(display[G]);
      delay(500);
    }
    if(bitRead(PINC,Pa)==HIGH && numero==4){
      PORTL=(display[G]);
      delay(500);
      PORTL=(display[G]);
      delay(500);
      PORTL=(display[G]);
      delay(500);
    }
    else{
      PORTL=(display[P]);
      delay(500);
      PORTL=(display[P]);
      delay(500);
      PORTL=(display[P]);
      delay(500);
      delay(10000)
    }
  }
}
