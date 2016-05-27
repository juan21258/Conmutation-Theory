#include <LiquidCrystal.h>
#include <Keypad.h>                      //Agrega la libreria del teclado
LiquidCrystal lcd(48,49,45,44,43,42);
const byte filas = 4;                    //Define las 4 filas del teclado 
const byte columnas = 3;                 //Define las 3 columnas del teclado
String estado = "Apagado";
int Minimo= 0;                           //Valor de temperatura mínima
int Maximo = 0;                          //Valor de temperatura maxima
char k;
char teclas[filas][columnas] =           //Define las teclas a usar
{
  {
    '1','2','3'    }
  ,
  {
    '4','5','6'    }
  ,
  {
    '7','8','9'    }
  ,
  {
    '*','0','#'    }
};

byte pinesfilas[filas] = {
  21,20,19,18};    //Define los pines digitales de las cuatro filas
byte pinescolumnas[columnas] = {
  17,16,15}; //Define los pines digitales de las tres columnas
Keypad teclado = Keypad( makeKeymap(teclas), pinesfilas,  pinescolumnas, filas,columnas ); //Define el teclado
float temp = 0;

void setup()                               //Configuracion de puertos              
{ 
  pinMode(47,OUTPUT);
  digitalWrite(47,0);
  DDRA=B11111111;  //Define PORTA como salida
  Serial.begin(9600);
  lcd.begin(16,2);
}

int tecla()                            //Funcion de control del teclado
{
  int valor;  
  k=teclado.getKey(); 	                 //Llama la función del teclado para ver si se digito
  //algun número y almacenarlo en k. 
  while((k=='\0')||(k=='#')||(k=='*'))	                  
  {
    k=teclado.getKey();                    
  }
  valor=k-48;                                
  return valor;
}

int valtemp(int val1, int val2){  //Retorna el valor de temperatura digitada.
  int res = val1*10;
  res= res + val2;
  return res;
}

void loop()                                
{
  lcd.setCursor(9,1);
  lcd.print(estado);
  lcd.setCursor(0,0);
  lcd.print("Temp Minima:");
  Minimo = valtemp(tecla(),tecla());
  lcd.setCursor(0,0);
  lcd.print("Temp Maxima:");
  Maximo = valtemp(tecla(),tecla());
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Empezar con #");
  while(teclado.getKey()!=(int)'#'){
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperatura:");
  lcd.setCursor(7,1);
  estado = "Encendido";
  lcd.print(estado);
  int temp = analogRead(0)/12;
  lcd.setCursor(0,1);
  while(temp<=Maximo&&temp>=Minimo){
    lcd.print("    ");
    lcd.setCursor(0,1);
    lcd.print(temp);
    temp = analogRead(0)/12;
  }
  estado = "Apagado";
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(estado);
  delay(2000);
}

