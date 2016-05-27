#define encender PINC,0
#define encender2 PINC,1
#define bombillo0 PORTA,0
#define bombillo1 PORTA,1
#define bombillo2 PORTA,2
#define bombillo3 PORTA,3
#define bombillo4 PORTA,4  //Definicion de variables
#define bombillo5 PORTA,5
#define bombillo6 PORTA,6
#define bombillo7 PORTA,7  

void setup() {
 DDRA=B11111111;    //Se define el PORTA como salida
 DDRC=B00000000;    //Se define el PORTC como entrada
}

void loop() { //Hacer por siempre
  
  if(bitRead(PINC,encender)==HIGH){ //Si el primer suiche está encendido, se prenden los
                                    // leds del 0 al 7 cada medio segundo.  
    bitSet(PORTA,bombillo0);        //Enciende led 0
    delay(500);                      //Intervalo de medio segundo
    bitSet(PORTA,bombillo1);
    delay(500);
    bitSet(PORTA,bombillo2);
    delay(500);
    bitSet(PORTA,bombillo3);
    delay(500);
    bitSet(PORTA,bombillo4);
    delay(500);
    bitSet(PORTA,bombillo5);
    delay(500);
    bitSet(PORTA,bombillo6);
    delay(500);
    bitSet(PORTA,bombillo7);
    delay(9999);
  }
  
  if(bitRead(PINC,encender2)==HIGH){ // Si el segundo sucihe está prendido
      for(int i=0;i<3;i++){ //Prende y apaga tres veces el led 0
      bitSet(PORTA,bombillo0);
      delay(500);
      bitClear(PORTA,bombillo0);
      delay(500);
      }
      bitSet(PORTA,bombillo0); // Deja encendido el led 0
      for(int i=0;i<3;i++){
      bitSet(PORTA,bombillo1);
      delay(500);
      bitClear(PORTA,bombillo1);
      delay(500);
      }
      bitSet(PORTA,bombillo1);
      for(int i=0;i<3;i++){
      bitSet(PORTA,bombillo2);
      delay(500);
      bitClear(PORTA,bombillo2);
      delay(500);
      }
      bitSet(PORTA,bombillo2);
      for(int i=0;i<3;i++){
      bitSet(PORTA,bombillo3);
      delay(500);
      bitClear(PORTA,bombillo3);
      delay(500);
      }
      bitSet(PORTA,bombillo3);
      for(int i=0;i<3;i++){
      bitSet(PORTA,bombillo4);
      delay(500);
      bitClear(PORTA,bombillo4);
      delay(500);
      }
      bitSet(PORTA,bombillo4);
      for(int i=0;i<3;i++){
      bitSet(PORTA,bombillo5);
      delay(500);
      bitClear(PORTA,bombillo5);
      delay(500);
      }
      bitSet(PORTA,bombillo5);
      for(int i=0;i<3;i++){
      bitSet(PORTA,bombillo6);
      delay(500);
      bitClear(PORTA,bombillo6);
      delay(500);
      }
      bitSet(PORTA,bombillo6);
      for(int i=0;i<3;i++){
      bitSet(PORTA,bombillo7);
      delay(500);
      bitClear(PORTA,bombillo7);
      delay(500);
      }
      bitSet(PORTA,bombillo7);
      
      if(bitRead(PORTA,bombillo7)==HIGH){ //En caso de tener todos los leds encendidos
      delay(1000); // Espera 1 segundo y empieza a apagar todos los leds 
      bitClear(PORTA,bombillo0);  //Apaga led 0
      bitClear(PORTA,bombillo1);
      bitClear(PORTA,bombillo2);
      bitClear(PORTA,bombillo3);
      bitClear(PORTA,bombillo4);
      bitClear(PORTA,bombillo5);
      bitClear(PORTA,bombillo6);
      bitClear(PORTA,bombillo7);
      }
  }
}
