#define S1 PINC,0
#define S2 PINC,1 
#define PABAJO PINC,2
#define PARRIBA PINC,3
#define APLUMILLA PORTA,0
#define CPLUMILLA PORTA,1 //Definir variables
#define LR PORTA,2
#define LV PORTA,3

void setup(){
  DDRA = B11111111;  //Definir PORTA como salida
  DDRC = B00000000;  //Definir PORTC como entrada
}

void loop(){ //Simepre se hace
  if(bitRead(PINC,S1)==HIGH || bitRead(PINC,S2)==HIGH){ //Si alguno de los sensores esta encendido Abre la pumilla y da señal de paso
    bitClear(PORTA,CPLUMILLA);
    bitSet(PORTA,APLUMILLA);
    if(bitRead(PINC,PARRIBA)==HIGH){
      bitClear(PORTA,LR);
      bitSet(PORTA,LV);  
    }
  } 
  else { // sino mantiene la pumilla abajo y no deja pasar
    bitClear(PORTA,APLUMILLA); 
    bitClear(PORTA,LV);
    bitSet(PORTA,CPLUMILLA);
    bitSet(PORTA,LR);
  } 
}

