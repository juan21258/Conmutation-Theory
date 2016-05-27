//definicion entradas 
#define sw1 PINC,0
#define sw2 PINC,1
#define sw3 PINC,2
#define sw4 PINC,3
#define sep PINC,4
//definicion salidas
#define motA PORTA,0
#define motB PORTA,1
#define motC PORTA,2
#define motD PORTA,3
//definimos el Keypad y la pantalla lcd
#include <Keypad.h>                      
#include <LiquidCrystal.h>              
LiquidCrystal lcd(48,49,45,44,43,42);  
const byte filas = 4;                    
const byte columnas = 3;               
char teclas[filas][columnas] =       
{
  {
    '1','2','3'        }
  ,
  {
    '4','5','6'        }
  ,
  {
    '7','8','9'        }
  ,
  {
    '*','0','#'        }
};
byte pinesfilas[filas] = {
  21,20,19,18};    //defines los pines digitales de las cuatro fila
byte pinescolumnas[columnas] = {
  17,16,15}; //defines los pines digitales de las tres columnas
Keypad teclado = Keypad( makeKeymap(teclas), pinesfilas,  pinescolumnas, filas,columnas ); //lectura del teclado
int num1;
int num2;
int num3;
int num4;
int valor;
char k;

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
  val=k-48;                               //Poner el valor de k menos 48 a val 
  return val;
}




void setup(){

  pinMode(47,OUTPUT);
  digitalWrite(47,0);
  lcd.begin(16,2); 
  DDRA=B11111111;
  DDRC=B00000000;

}

void entregarP1(){
  while(bitRead(PINC, 4)==LOW){  
  bitSet(PORTA, 0);
  }
  bitClear(PORTA, 0);
  lcd.clear();
}
void entregarP2(){
  while(bitRead(PINC, 4)==LOW){  
  bitSet(PORTA, 1);
  }
  bitClear(PORTA, 1);
  lcd.clear();
}
void entregarP3(){
  while(bitRead(PINC, 4)==LOW){  
  bitSet(PORTA, 2);
  }
  bitClear(PORTA, 2);
  lcd.clear();
}
void entregarP4(){
  while(bitRead(PINC, 4)==LOW){  
  bitSet(PORTA, 3);
  }
  bitClear(PORTA, 3);
  lcd.clear();
}

void loop(){
  lcd.setCursor(0,0);
  lcd.print("1: $200");
  lcd.setCursor(8,0);
  lcd.print("2: $400");
  lcd.setCursor(0,1);
  lcd.print("3: $600");
  lcd.setCursor(8,1);
  lcd.print("4: $1000");
  
  
  if(bitRead(PINC, 0)==HIGH){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Goma: $200");
    lcd.setCursor(0,1);
    lcd.print("Valor: $");
    lcd.setCursor(8,1);
    num1 = teclados();
    lcd.print(num1);
    lcd.setCursor(9,1);
    num2 = teclados();
    lcd.print(num2);
    lcd.setCursor(10,1);
    num3 = teclados();
    lcd.print(num3);
    while(k != '#'){
       k=teclado.getKey();     
    }
    valor = num1*100 + num2*10 + num3;
    if(valor == 200){
      entregarP1();
    }else{
     lcd.clear();
     loop(); 
    }
    
  }
  
  if(bitRead(PINC, 1)==HIGH){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Galleta: $400");
    lcd.setCursor(0,1);
    lcd.print("Valor: $");
    lcd.setCursor(8,1);
    num1 = teclados();
    lcd.print(num1);
    lcd.setCursor(9,1);
    num2 = teclados();
    lcd.print(num2);
    lcd.setCursor(10,1);
    num3 = teclados();
    lcd.print(num3);
     while(k != '#'){
       k=teclado.getKey();     
    }
    valor = num1*100 + num2*10 + num3;
    if(valor == 400){
      entregarP2();
    }else{
   lcd.clear();
   loop();
    }   
  }
  
  if(bitRead(PINC, 2)==HIGH){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Dulce : $600");
    lcd.setCursor(0,1);
    lcd.print("Valor: $");
    lcd.setCursor(8,1);
    num1 = teclados();
    lcd.print(num1);
    lcd.setCursor(9,1);
    num2 = teclados();
    lcd.print(num2);
    lcd.setCursor(10,1);
    num3 = teclados();
    lcd.print(num3);
     while(k != '#'){
       k=teclado.getKey();     
    }
    valor = num1*100 + num2*10 + num3;
    if(valor == 600){
      entregarP3();
    }else{
      lcd.clear();
      loop(); 
    }
  }
  
  if(bitRead(PINC, 3)==HIGH){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Chocolate: $1000");
    lcd.setCursor(0,1);
    lcd.print("Valor: $");
    lcd.setCursor(8,1);
    num1 = teclados();
    lcd.print(num1);
    lcd.setCursor(9,1);
    num2 = teclados();
    lcd.print(num2);
    lcd.setCursor(10,1);
    num3 = teclados();
    lcd.print(num3);
    lcd.setCursor(11,1);
    num4 = teclados();
    lcd.print(num4);
     while(k != '#'){
       k=teclado.getKey();     
    }
    valor = num1*1000 + num2*100 + num3*10 + num4;
    if(valor == 1000){
      entregarP4();
    }else{
     lcd.clear();
     loop();
    } 
    
    
  }
 
  
}





