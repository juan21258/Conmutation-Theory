#define jugador1 PINC,0               //Define el PINC,0 para el pulsador1
#define jugador2 PINC,1               //Define el PINC,1 para el pulsador2
#define jugador3 PINC,2               //Define el PINC,2 para el pulsador3
#define animador PINC,3               //Define el PINC,3 para el pulsador4

//tabla de colores

int pwm1 = 240;
int pwm2 = 255;
int pwm3 = 255;
int i = 0;
int j = 0;

//colores
boolean B = false;
boolean R = false;
boolean G = false;
unsigned int act,ant;

//inicilizacíon
void setup() 
{  
  DDRC=B00000000;                   //Define todo el PUERTOC como entrada
  // start();
}


//delay para titilar

//int def(default)

void titilar(int def){
  ant = millis();
  act = millis();
//condiciónn
  while(act-ant < def){
    
    if(bitRead(PINC,jugador1)==HIGH){
      B=true;
      DDRC = B11111110;
    }
    
    else if(bitRead(PINC,jugador2)==HIGH){
      G = true;
      DDRC = B11111101;
    }
    
    else if(bitRead(PINC,jugador3)==HIGH) {
      R = true;
      DDRC = B11111011;
    }
    
    else if(bitRead(PINC,animador)==HIGH) {
      DDRC = B00000000;
    
      B = false;
      G = false;
      R = false;
    
      analogWrite(2,0);
      analogWrite(3,0);
      analogWrite(4,0);
      delay(1500);
    
      comenzar();
    }

    //enciende luces

    if(B){

      //se enciende el azul
      analogWrite(2,255);
      analogWrite(3,0);
      analogWrite(4,0);
    }
    else if(G){

      //se enciende el verde
      analogWrite(2,0);
      analogWrite(3,255);
      analogWrite(4,0);
    }
    else if(R){

      //se enciende el rojo
      analogWrite(2,0);
      analogWrite(3,0);
      analogWrite(4,255);
    }

    act = millis();
  }
  
}

void comenzar(){

  analogWrite(2,255);
  analogWrite(3,0);
  analogWrite(4,0);
  titilar(200);
  
  analogWrite(2,0);
  analogWrite(3,255);
  analogWrite(4,0);
  titilar(200);
  
  analogWrite(2,0);
  analogWrite(3,0);
  analogWrite(4,255);
  titilar(200);

}

//comienzo con el switch 1
void loop() 
{ 
  //si se enciende
  if(PINC == 0){
    comenzar();
  }
//fin
}


