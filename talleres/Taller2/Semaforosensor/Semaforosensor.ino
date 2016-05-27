#define LVC1 PORTA,0            
#define LAC1 PORTA,1            
#define LRC1 PORTA,2
#define LVC2 PORTA,3
#define LAC2 PORTA,4
#define LRC2 PORTA,5
#define S PINC,7          //Definición del sensor
unsigned int TAC = 0;     // Asignación de valor 
unsigned int TAN = 0;

void Retardo2()             //Define el retardo de paso del color Amarillo 
{                            
  TAN = millis();
  TAC=millis();
  while(TAC-TAN<3000&&bitRead(PINC,S)==LOW)
  {    
    TAC=millis();
  } 
}

void Retardo15()             //Define el retardo de paso entre el color rojo y verde del semaforo
{                    
  TAN = millis();
  TAC=millis();
  while(TAC-TAN<15000&&bitRead(PINC,S)==LOW)
  {    
    TAC=millis();
  } 
}

void setup() {
  DDRA=B00111111;  //Definir PORTA como salida
  DDRC=B00000000;  //Definir PORTC como entrada
}

void loop() {
  while(bitRead(PINC,S)==HIGH){  //Punto de verificación de que este de noche
    bitClear(PORTA,LVC1);             //Se apagan los semaforos y se enciende el led amarillo 
    bitClear(PORTA,LAC1);             //del semáforo uno y la luz roja del semáforo dos.
    bitClear(PORTA,LRC1);
    bitClear(PORTA,LVC2);
    bitClear(PORTA,LAC2);
    bitClear(PORTA,LRC2);
    delay(500);
    bitSet(PORTA,LAC1);
    bitSet(PORTA,LRC2);
    delay(500);
  }
  bitSet(PORTA,LRC2);            //Funcionamiento normal de los semáforos
  bitSet(PORTA,LVC1);
  Retardo15();
  for(int i=0;i<8;i++)
  {
    bitSet(PORTA,LVC1);
    delay(500);
    bitClear(PORTA,LVC1);
    delay(500);
  }
  bitClear(PORTA,LVC1);
  bitSet(PORTA,LAC1);
  Retardo2();
  bitClear(PORTA,LAC1);
  bitClear(PORTA,LRC2);
  bitSet(PORTA,LRC1);
  bitSet(PORTA,LVC2);
  Retardo15();
  for(int i=0;i<8;i++)
  {
    bitSet(PORTA,LVC2);
    delay(500);
    bitClear(PORTA,LVC2);
    delay(500);
  }
  bitClear(PORTA,LVC2);
  bitSet(PORTA,LAC2);
  Retardo2();
  bitClear(PORTA,LAC2);
  bitClear(PORTA,LRC1);
}



