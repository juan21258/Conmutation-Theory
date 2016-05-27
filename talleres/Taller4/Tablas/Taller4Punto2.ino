#include <LiquidCrystal.h>
#include <Keypad.h>
int resultado;
int numero;
int multi;
int dec,uni,usuario;
char s;

LiquidCrystal lcd(48, 49, 45, 44, 43, 42); //Inicializa la libreria y Define los pines digitales para el LCD
const byte filas = 4;                    //define las 4 filas del teclado
const byte columnas = 3;                 //define las 3 columnas del teclado
char teclas[filas][columnas] =           //inicializa filas y columnas
{
  {
    '1', '2', '3'
  }
  ,
  {
    '4', '5', '6'
  }
  ,
  {
    '7', '8', '9'
  }
  ,
  {
    '*', '0', '#'
  }
};

byte pinesfilas[filas] = {
  21, 20, 19, 18
};    //defines los pines digitales de las cuatro fila

byte pinescolumnas[columnas] = {
  17, 16, 15
}; //defines los pines digitales de las tres columnas

Keypad teclado = Keypad( makeKeymap(teclas), pinesfilas,  pinescolumnas, filas, columnas ); //lectura del teclado

#define led PORTA,0                        //Define led a PORTA,0

char k;                                    //Define k como caracter

int teclados()                            //Funcion teclados
{
  int val;
  k = teclado.getKey(); 	                 /*Llamar la función del teclado y almacenar el valor
   	                                     digitado en una variable (k) tipo caracter. Si no se oprime
   	                                     ninguna tecla el teclado retornara el carácter nulo.*/

  while ((k == '\0') )	                //Si no se oprime ninguna tecla
  {
    k = teclado.getKey();                   //Sigue llamando al teclado
  }

  val = k - 48;                           //Poner el valor de k menos 48 a val
  return val;
}


int aleatorio()
{
  randomSeed(millis()); 
  multi = random(0, 10);
  return multi;
}

int operacion(){
    resultado = numero * multi; 
    return resultado;

};


void setup() {
  pinMode(47, OUTPUT);
  digitalWrite(47, 0);
  lcd.begin(16, 2);                   //Define el LCD a utilizar que en este caso es de 16 filas y 2 columnas
  DDRA = B11111111;

}


void loop() {
  
  s = '#';
  lcd.setCursor(1, 0);
  lcd.print("¿Que tabla");
  lcd.setCursor(0, 1);
  lcd.print("va a practicar?");
   //ejecución
  
  numero = teclados();
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Vas a practicar:");
  lcd.setCursor(1, 1);
  lcd.print("Tabla");
  lcd.setCursor(6, 1);
  lcd.print(" del ");
  lcd.setCursor(11, 1);
  lcd.print(numero);
  int res = operacion();
  delay(1000);
  lcd.clear(); 
  while(s != '*'){
   lcd.clear(); 
   lcd.setCursor(0,0);
   lcd.print(numero);
   lcd.setCursor(1,0);
   lcd.print("X");
   lcd.setCursor(2,0);
   lcd.print(aleatorio());
   lcd.print("=?");
   lcd.setCursor(5,0);
   dec=teclados();                             //Llamar funcion teclados
   lcd.setCursor(2,1);                      //Columna 3, fila 1 de la pantalla
   lcd.print(dec);
   uni=teclados();                           //Llamar funcion teclados
   lcd.setCursor(3,1);                      //Columna 3, fila 1 de la pantalla
   lcd.print(uni);
   usuario = (dec*10)+uni;
   //resultado de la multiplicación
  if(usuario==operacion()){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Correcto!");
    delay(2000);
  }else {
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Incorrecto!");
   delay(2000);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("desea probar");
  lcd.setCursor(0,1);
  lcd.print("otra tabla?");
  delay(1500);
  lcd.clear(); 
   s = teclado.getKey(); 	                 /*Llamar la función del teclado y almacenar el valor
   	                                     digitado en una variable (k) tipo caracter. Si no se oprime
   	                                     ninguna tecla el teclado retornara el carácter nulo.*/

  while (s != '*') 	                //Si no se oprime ninguna tecla
  {
    s = teclado.getKey();                   //Sigue llamando al teclado
  }
  lcd.setCursor(0,1);
  lcd.print(s);
  delay(1000);
  if(s=='*'){
   s= '*';
  }
 }
}
