#include <genieArduino.h> //Importamos la librería
#define RESETLINE 4  //El 4 es el índice o pin de PWM en el cual se realiza la conexión o comunicación serial
Genie genie; //Variable para manejar las funciones de la libreria Genie
int state; // Variable para identificar los eventos de los botones
#define SP1	PINC,4  //Sensor del punto uno de la grúa.   
#define SP2     PINC,5  //Sensor del punto dos de la grúa.   
#define SP3	PINC,6  //Sensor del punto tres de la grúa.   
#define SUP	PINC,7  //Sensor que indica si la grua está arriba.   
#define SDOWN   PINA,7  //Sensor que indica si la grua está arriba.      
#define BAJAR 	PORTA,0 //Envía orden y/o señal a la grúa para bajar.
#define SUBIR 	PORTA,1 //Envía orden y/o señal a la grúa para subir.
#define SOL   	PORTA,2 //Envía orden y/o señal a la grúa para activar o desactivar el imán.
#define IZQ	PORTA,3 //Envía orden y/o señal a la grúa para mover hacia la izquierda.
#define DER   	PORTA,4 //Envía orden y/o señal a la grúa para mover hacia la derecha.

void setup()
{
  DDRA = B01111111;  //Se pone el puerto A como salida
  state = 0; // Variable que utilizamos para identificar los botones presionados.
  Serial.begin(9600); //Se iniciliza el serial en 9600, el cual indica el flujo de datos. 
  Serial1.begin(9600); // Se utiliza un serial diferente para realizar la comunicación serial.   
  genie.Begin(Serial1); //Serial se comunica con la libreria begin.
  genie.AttachEventHandler(myGenieEventHandler); //AttachEventHandler es el objeto como tal de genie para manejar los eventos,
                                                 //se le pasa como atributo la función que se hace para detectar y manipular
                                                 //los eventos para proceder a ejecutar la acción que deseemos. 
  pinMode(RESETLINE, OUTPUT); //Pone el pin como salida. 
  digitalWrite(RESETLINE, 0); //Resetea la pantalla.
  delay(100); //Retardo de 100 milisegundos.
  digitalWrite(RESETLINE, 1); //Desactiva la reseteada.
  delay (3500); //Tiempo mientras inicia después del reinicio.
  genie.WriteContrast(1); //Se enciende la pantalla. 
}

void Bajar() //Procede a bajar la grúa.
{
  while(bitRead(PINA,SDOWN)==LOW){ //Ciclo para proceder con el moviemiento.
    bitSet(PORTA,BAJAR);  
  }
  bitClear(PORTA,BAJAR);
}

void Subir() //Sube la grúa.
{
  while(bitRead(PINC,SUP)==LOW){ //Cumple, mientras el pin del sensor arriba esté apagado.  
    bitSet(PORTA,SUBIR); //Cambia el estado SUBIR (Prende el led al que esté ligado). 
  }
  bitClear(PORTA,SUBIR); //Apaga el led anteriormente encendido. 
}

void DerechaS2() //Mueve la grúa en dirección derecha, hasta llegar al Punto 2.
{
  while(bitRead(PINC,SP2)==LOW){ 
    bitSet(PORTA,DER);
  }
  bitClear(PORTA,DER);
}


void DerechaS3() //Mueve la grúa en dirección derecha, hasta llegar al Punto 3.
{
  while(bitRead(PINC,SP3)==LOW){
    bitSet(PORTA,DER);
  }
  bitClear(PORTA,DER);
}


void IzquierdaS1() //Mueve la grúa en dirección izquierda, hasta llegar al Punto 1.
{
  while(bitRead(PINC,SP1)==LOW){
    bitSet(PORTA,IZQ);
  }
  bitClear(PORTA,IZQ);
}

void IzquierdaS2() //Mueve la grúa en dirección izquierda, hasta llegar al Punto 1.
{
  while(bitRead(PINC,SP2)==LOW){
    bitSet(PORTA,IZQ);
  }
  bitClear(PORTA,IZQ);
}

void loop() //Función que se ejecuta de manera contínua. 
{
  genie.DoEvents(); //Función que se encarga de detectar eventos de la pantalla. 
  if(state == 1){ //Si el botón presionado fue el que se identificó con estado 1.
    if(bitRead(PINC,SP2)==HIGH)
    {
      IzquierdaS1();
    }
    else if(bitRead(PINC,SP3)==HIGH)
    {
      IzquierdaS1();	
    }
    Bajar();
    bitSet(PORTA,SOL);
    Subir();
    DerechaS2();
    Bajar();
    bitClear(PORTA,SOL);
    Subir();
    state = 0; //Reiniciamos la variable state a su estado normal.
  }
  if(state == 2){
    if(bitRead(PINC,SP2)==HIGH)
    {
      IzquierdaS1();
    }
    else if(bitRead(PINC,SP3)==HIGH)
    {
      IzquierdaS1();	
    }
    Bajar();
    bitSet(PORTA,SOL);
    Subir();
    DerechaS3();
    Bajar();
    bitClear(PORTA,SOL);
    Subir();
    state = 0;
  }
  if(state == 3){
    if(bitRead(PINC,SP1)==HIGH)
    {
      DerechaS2();
    }
    else if(bitRead(PINC,SP3)==HIGH)
    {
      IzquierdaS2();	
    }
    Bajar();
    bitSet(PORTA,SOL);
    Subir();
    IzquierdaS1();
    Bajar();
    bitClear(PORTA,SOL);
    Subir();
    state = 0;
  }
  if(state == 4){
    if(bitRead(PINC,SP1)==LOW){	 
      Bajar();      
      bitSet(PORTA,SOL);
      Subir();
      IzquierdaS1();
      Bajar();
      bitClear(PORTA,SOL);
      Subir();
      state =0;
    }
  }
}
void myGenieEventHandler(void) //Función que creamos para manejar eventos de la pantalla.  
{
  genieFrame Event; //Permite manejar los eventos de BOTONES, genieFrame pertenece a la libreria Genie
  genie.DequeueEvent(&Event); // Se captura y pasa el evento como tal,DequeueEvent pertenece a la libreria Genie
  if (Event.reportObject.cmd == GENIE_REPORT_EVENT) { //Se asegura de que se pasaron datos de evento, reportObject.cmd pertenece a la libreria Genie 
    if(Event.reportObject.index == 0) { //Se pregunta por el index del botón presionado, reportObject.index pertenece a la libreria Genie
      state = 1; //Identificador asignado al botón, con el que se trabajará en el loop.     
    }
  }
  if (Event.reportObject.cmd == GENIE_REPORT_EVENT) {
    if(Event.reportObject.index == 1) {
      state = 2;      
    }
  }
  if (Event.reportObject.cmd == GENIE_REPORT_EVENT) {
    if(Event.reportObject.index == 3) {
      state = 3;      
    }
  }
  if (Event.reportObject.cmd == GENIE_REPORT_EVENT) {
    if(Event.reportObject.index == 2) {
      state = 4;      
    }
  }
}


