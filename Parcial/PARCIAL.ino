
/*
Parcial teoria de la conmutación
Integrantes:
Juan David Pérez Pérez
Sergio Atehortua Ceferino
*/


//definicion entradas
#define S1 PINC,7
#define S2 PINC,6
#define S3 PINC,5
#define S4 PINC,4
//definicion salidas
#define Bder PORTA,0
#define Bizq PORTA,1
//definimos el Keypad y la pantalla lcd
#include <Keypad.h>                      
#include <LiquidCrystal.h>              
LiquidCrystal lcd(48,49,45,44,43,42);  
const byte filas = 4;                    
const byte columnas = 3;
unsigned int act,ant;
char teclas[filas][columnas] =       
{
  {
    '1','2','3'                                                    }
  ,
  {
    '4','5','6'                                                    }
  ,
  {
    '7','8','9'                                                    }
  ,
  {
    '*','0','#'                                                    }
};
byte pinesfilas[filas] = {
  21,20,19,18};    //defines los pines digitales de las cuatro fila
byte pinescolumnas[columnas] = {
  17,16,15}; //defines los pines digitales de las tres columnas
Keypad teclado = Keypad( makeKeymap(teclas), pinesfilas,  pinescolumnas, filas,columnas ); //lectura del teclado
char k;
int destinos,paradas,tiempoesp;
//definimos el metodo tecleado
int teclados()                            //Funcion teclados
{
  int val;  
  k=teclado.getKey(); 	                 /*Llamar la función del teclado y almacenar el valor 
   	                                     digitado en una variable (k) tipo caracter. Si no se oprime 
   	                                     ninguna tecla el teclado retornara el carácter nulo.*/
  while((k=='\0')||(k=='#'))	                           //Si no se oprime ninguna tecla 
  {
    k=teclado.getKey();                     //Sigue llamando al teclado
  }
  if(k == '*') loop();
  val=k-48;                               //Poner el valor de k menos 48 a val 
  return val;
}

int aleatorio(){
  randomSeed(millis());
  paradas = random(1,5);
  return paradas;
}

int tiempo(){
  randomSeed(millis());
  tiempoesp= random(1,6);
  return tiempoesp*1000;
}

void der(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("derecha");
  delay(1000);
}

void S1M(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sensor1");
  delay(1000);
}
void S2M(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sensor2");
  delay(1000);
}
void S3M(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sensor3");
  delay(1000);
}
void t(int v){
  lcd.setCursor(0,1);
  lcd.print(v);
  delay(1000);
} 

void S4M(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sensor4");
  delay(1000);
}

void izq(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("izquierda");
  delay(1000);
}

void contador(int i){
  lcd.setCursor(8,1);
  lcd.print("C:");
  lcd.setCursor(10,1);
  lcd.print(i);
  delay(1500);
}

void setup(){

  pinMode(47,OUTPUT);
  digitalWrite(47,0);
  lcd.begin(16,2); 
  DDRA=B11111111;
  DDRC=B00000000;
}

void loop(){  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("iniciando");
  lcd.setCursor(0,1);
  lcd.print("programa");
  delay(1400);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("# de destinos");
  destinos = teclados();
  lcd.setCursor(0,1);
  lcd.print(destinos);
  delay(1000);
  int ar[destinos];
  for(int i =0;i<destinos;i++){
    delay(i+10);
    ar[i]=aleatorio(); 
  }
  for(int i=0;i<destinos;i++){
    lcd.setCursor(6+i,1);
    lcd.print(ar[i]);
    delay(1000);
  }

  int cont = 1;
  for(int i=0;i<destinos;i++){  
    char c = '#';
    if(ar[i]==1){
      if(bitRead(PINC,S1)==HIGH){
      }
      else{
        while(bitRead(PINC,S1)==LOW){
          bitSet(PORTA,Bder);
          der();
          int tecla = teclado.getKey();
          if(tecla == '*'){
            PORTA = 0;
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("PARO");
            tecla = teclado.getKey();
            while(tecla!='#')tecla = teclado.getKey();
            lcd.clear();
          }
        }
        bitClear(PORTA,Bder);
        S1M();
        tiempo();
        t(tiempo());
        contador(cont);  
      }
    }
    else if(ar[i]==2){
      if(bitRead(PINC,S2)==HIGH){
      }
      else if(bitRead(PINC,S3)==HIGH || bitRead(PINC,S4)==HIGH){
        while(bitRead(PINC,S2)==LOW){
          bitSet(PORTA,Bder);
          der();
          int tecla = teclado.getKey();
          if(tecla == '*'){
            PORTA = 0;
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("PARO");
            tecla = teclado.getKey();
            while(tecla!='#')tecla = teclado.getKey();
            lcd.clear();
          }
        }
        bitClear(PORTA,Bder);
        S2M();
        tiempo();
        t(tiempo()); 
        contador(cont);
      }
      else{
        while(bitRead(PINC,S2)==LOW){
          bitSet(PORTA,Bizq);
          izq();
          int tecla = teclado.getKey();
          if(tecla == '*'){
            PORTA = 0;
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("PARO");
            tecla = teclado.getKey();
            while(tecla!='#')tecla = teclado.getKey();
            lcd.clear();
          }
        }
        bitClear(PORTA,Bizq);
        S2M();
        tiempo();
        t(tiempo());
        contador(cont);

      }
    }
    else if(ar[i]==3){
      if(bitRead(PINC,S3)==HIGH){
      }
      else if(bitRead(PINC,S4)==HIGH){
        while(bitRead(PINC,S3)==LOW){
          bitSet(PORTA,Bder);
          der();
          int tecla = teclado.getKey();
          if(tecla == '*'){
            PORTA = 0;
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("PARO");
            tecla = teclado.getKey();
            while(tecla!='#')tecla = teclado.getKey();
            lcd.clear();
          }
        }
        bitClear(PORTA,Bder);
        S3M();
        tiempo();
        t(tiempo());
        contador(cont);

      }
      else{
        while(bitRead(PINC,S3)==LOW){
          bitSet(PORTA,Bizq);
          izq();
          int tecla = teclado.getKey();
          if(tecla == '*'){
            PORTA = 0;
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("PARO");
            tecla = teclado.getKey();
            while(tecla!='#')tecla = teclado.getKey();
            lcd.clear();
          }
        }
        bitClear(PORTA,Bizq);
        S3M();
        tiempo();
        t(tiempo());
        contador(cont);

      }
    }
    else if(ar[i]==4){
      if(bitRead(PINC,S4)==HIGH){
      }
      else{
        while(bitRead(PINC,S4)==LOW){
          bitSet(PORTA,Bizq);
          izq();
          int tecla = teclado.getKey();
          if(tecla == '*'){
            PORTA = 0;
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("PARO");
            tecla = teclado.getKey();
            while(tecla!='#')tecla = teclado.getKey();
            lcd.clear();
          }
        }
        bitClear(PORTA,Bizq);
        S4M();
        tiempo();
        t(tiempo());
        contador(cont);

      }
    }
    cont = cont +1;   
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("fin del");
  lcd.setCursor(0,1);
  lcd.print("programa");
  delay(2000);
}











