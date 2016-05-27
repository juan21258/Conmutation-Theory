
#include <Keypad.h>                      
#include <LiquidCrystal.h>              



LiquidCrystal lcd(48,49,45,44,43,42);  
const byte filas = 4;                    
const byte columnas = 3;
unsigned int act,ant;


#define S1 PINC,7
#define S2 PINC,6
#define S3 PINC,5
#define S4 PINC,4
#define BD PORTA,0
#define BI PORTA,1


char teclas[filas][columnas] =       
{
  {
    '1','2','3'                                  }
  ,
  {
    '4','5','6'                                  }
  ,
  {
    '7','8','9'                                  }
  ,
  {
    '*','0','#'                                  }
};

byte pinesfilas[filas] = {
  21,20,19,18};    //defines los pines digitales de las cuatro fila
byte pinescolumnas[columnas] = {
  17,16,15}; //defines los pines digitales de las tres columnas
Keypad teclado = Keypad( makeKeymap(teclas), pinesfilas,  pinescolumnas, filas,columnas ); //lectura del teclado
//


//vars

int in1,in2,in3,in4;
int clave,tiempo,tiempo1,tiempo2;
int PB,UB;

char k;
int c1,c2,c3,c4;


//metodo para esperar
void espera(int x){
  act = millis();
  ant = millis();
  while(act-ant < x){
    act = millis();
    int val = teclado.getKey();
    if(val == '*') loop();
  }
}

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

  //Banda Derecha S1
  //Banda Izquierda S4
  /*
  Para moverse hacia la derecha se utiliza el pin A,0 BD
  Para moverse hacia la izquierda se utiliza el pin A,1 BI
  */
  
  //Indica hacia donde se mueve la banda


void setup(){

  pinMode(47,OUTPUT);
  digitalWrite(47,0);
  lcd.begin(16,2); 
  DDRA=B11111111;
  DDRC=B00000000;

}
void tiempodeseado(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tiempo?");
  lcd.setCursor(0,1);
  lcd.print(":");
  lcd.setCursor(8,1);
  lcd.print("s");
  lcd.setCursor(6,1);
  in1 = teclados();
  tiempo1 = in1;
  lcd.print(tiempo1);
  lcd.setCursor(7,1);
  in2 = teclados();
  tiempo2 = in2;
  lcd.print(tiempo2); 
  while(k != '#'){
    k=teclado.getKey(); 
  }
  tiempo = (tiempo1*10) + tiempo2;
  tiempo = tiempo*1000;
  lcd.clear();
}

void movera(){
  lcd.clear();
  lcd.setCursor(7,1);
  lcd.print("-");
  lcd.setCursor(0,0);
  lcd.print("Bandas:");
  lcd.setCursor(0,1);
  lcd.print("Entre:");
  lcd.setCursor(6,1);
  in1 = teclados();

  PB = in1;
  lcd.print(PB);
  lcd.setCursor(8,1);
  in2 = teclados();
  UB = in2;
  lcd.print(UB);
  while(k != '#'){
    k=teclado.getKey(); 
  }
  if(k == '#'){
    tiempodeseado();
  }
  else if(k == '*') {
    PORTA = 0;
    loop();
  }
  lcd.clear();
}

void lugar4(){
  while(bitRead(PINC,4)==LOW){
    lcd.setCursor(0,0);
    lcd.print("Banda Izquierda");  //Indica hacia donde se mueve la banda
    bitSet(PORTA, 1);
    int val = teclado.getKey();
    if(val == '*'){
      PORTA = 0;
      loop();
    }
  }
  bitClear(PORTA,1);
  lcd.clear();
}
void lugar1(){
  while(bitRead(PINC,7)==LOW){
    lcd.setCursor(0,0);
    lcd.print("Banda Derecha");   //Indica hacia donde se mueve la banda
    bitSet(PORTA, 0);
    int val = teclado.getKey();
    if(val == '*'){
      PORTA = 0;
      loop();
    }
  }
  bitClear(PORTA,0);
  lcd.clear();
}

void lugar2(){
  if(bitRead(PINC,7)==HIGH){
    while(bitRead(PINC,6)==LOW){
      lcd.setCursor(0,0);
      lcd.print("Banda Izquierda");  //Indica hacia donde se mueve la banda
      bitSet(PORTA, 1);
      int val = teclado.getKey();
      if(val == '*') {
        PORTA = 0;
        loop();
      }
    }
  }
  else{
    while(bitRead(PINC,6)==LOW){
      lcd.setCursor(0,0);
      lcd.print("Banda derecha");  //Indica hacia donde se mueve la banda
      bitSet(PORTA, 0);
      int val = teclado.getKey();
      if(val == '*') {
        PORTA = 0;
        loop();
      }
    }
  }
  bitClear(PORTA,1);
  bitClear(PORTA,0);
  lcd.clear();
}

void lugar3(){
  if(bitRead(PINC,4)==HIGH){
    while(bitRead(PINC,5)==LOW){
      lcd.setCursor(0,0);
      lcd.print("Banda derecha");  //Indica hacia donde se mueve la banda
      bitSet(PORTA, 0);
      int val = teclado.getKey();
      if(val == '*'){
        PORTA = 0;
        loop();
      }
    }
  }
  else{
    while(bitRead(PINC,5)==LOW){
      lcd.setCursor(0,0);
      lcd.print("Banda Izquierda");  //Indica hacia donde se mueve la banda
      bitSet(PORTA, 1);
      int val = teclado.getKey();
      if(val == '*'){
        PORTA = 0;
        loop();
      }
    }
  }
  bitClear(PORTA,1);
  bitClear(PORTA,0);
  lcd.clear();
}

void loop(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Clave?");
  lcd.setCursor(0,1);
  lcd.print("Clave: ");
  lcd.setCursor(8,1);
  in1 = teclados();
  c1 = in1;
  lcd.print(c1);
  lcd.setCursor(9,1);
  in2 = teclados();
  c2 = in2;
  lcd.print(c2);
  lcd.setCursor(10,1);
  in3 = teclados();
  c3 = in3;
  lcd.print(c3);
  lcd.setCursor(11,1);
  in4 = teclados();
  c4 = in4;
  lcd.print(c4);
  while(k != '#'){
    k=teclado.getKey();     
  }

  clave = c1*1000 + c2*100 + c3*10 + c4;
  if(clave == 1234){
    lcd.clear();
    delay(1000);

    movera();
    if(PB == 4){
      lugar4();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Espere...");
      espera(tiempo);
      lcd.clear();
      if(UB == 1){
        lugar1();
      }

      if(UB == 2){
        lugar2();
      }

      if(UB == 3){
        lugar3();
      }

      if(UB == 4){
        lugar4();
      }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Espere...");
      espera(tiempo);
      lcd.clear();
    }
    if(PB == 1){
      lugar1();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Espere...");
      espera(tiempo);
      lcd.clear();
      if(UB == 2){
        lugar2();
      }
      if(UB == 3){
        lugar3();
      }
      if(UB == 4){
        lugar4();
      }
      if(UB == 1){
        lugar1();
      }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Espere...");
      espera(tiempo);
      lcd.clear();
    }
    if(PB == 2){
      lugar2();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Espere...");
      espera(tiempo);
      lcd.clear();
      if(UB == 2){
        lugar2();
      }
      if(UB == 3){
        lugar3();
      }
      if(UB == 4){
        lugar4();
      }
      if(UB == 1){
        lugar1();
      }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Espere...");
      espera(tiempo);
      lcd.clear();
    }
    if(PB == 3){
      lugar3();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Espere...");
      espera(tiempo);
      lcd.clear();
      
      if(UB == 2){
        lugar2();
      }
      
      if(UB == 3){
        lugar3();
      }
      
      if(UB == 4){
        lugar4();
      }
      
      if(UB == 1){
        lugar1();
      }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Espere...");
      espera(tiempo);
      lcd.clear();    
    }  

  }
  
  
  
  else{
    
    //llave del funcionamiento de la banda if clave = 1234
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("No es la clave");
    delay(2000); 
    lcd.clear();
    
  }
  
  //fin del programa si la clave digitada no es correcta  
}



