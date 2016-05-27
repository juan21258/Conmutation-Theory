#define LVC PORTA,0
#define LAC PORTA,1
#define LRC PORTA,2
#define LVP PORTA,3
#define LRP PORTA,4  //Definicion de variables
#define PIN1 PINC,6
#define PIN2 PINC,7
unsigned int TAC = 0;
unsigned int TAN = 0;  //Asignacion de valor a la variable

void Retardo15()             //Funcion de 15 segundos de retardo
{ 
  TAN = millis();
  TAC = millis();
  while (TAC - TAN < 15000 && ((bitRead(PINC,PIN1)==LOW || bitRead(PINC,PIN2)==LOW)))
  {
    TAC = millis();
  }
}

void setup()
{
  DDRA = B11111111; //Se define PORTA como salida
  DDRC = B00000000; //Se define PORTC como entrada
}

void loop()
{
  bitSet(PORTA, LVC);  //Enciende led verde del carro
  bitSet(PORTA, LRP);  //Enciende led rojo del peaton
  Retardo15();
  if((bitRead(PINC,PIN1)==HIGH || bitRead(PINC,PIN2)==HIGH)) // Si se pulso algun botón de los semaforos
  {
    if((bitRead(PINA,LVC)==HIGH)&& bitRead(PINA,LRP)==HIGH) // Si se está en led verde del carro y led rojo de peaton
    {
      bitClear(PORTA,LVC); //Apaga led verde del carro
      bitClear(PORTA,LRP); 
      bitSet(PORTA,LRC);
      for(int i=0;i<16;i++) // Pone a titilar el led verde del peaton durante 8 segundos
      {
        bitSet(PORTA,LVP); 
        delay(500);
        bitClear(PORTA,LVP);
        delay(500);
      }
      bitClear(PORTA,LRC); //Apaga led rojo del carro
      bitClear(PORTA,LVP);
    }
  }else { // En caso no estar presionado nungún suiche
    for(int i=0;i<3;i++) //Pone a titilar 3 veces casa medio segundo el led verde del carro 
    {
      bitSet(PORTA,LVC);
      delay(500);
      bitClear(PORTA,LVC);
      delay(500);
    }
    bitClear(PORTA, LVC);
    bitSet(PORTA, LAC); // Enciende led Amarillo del carro 
    delay(2000);
    bitClear(PORTA,LAC);
    bitClear(PORTA,LRP);
    bitSet(PORTA,LRC);
    bitSet(PORTA,LVP);
    delay(15000); 
    bitClear(PORTA,LRC);
    bitClear(PORTA,LVP);  
  } 
}






