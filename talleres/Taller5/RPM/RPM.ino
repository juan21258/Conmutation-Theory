#include <TimerOne.h>   		//incluye la librería del rimer1
//RPM Meter
#include <LiquidCrystal.h>              		//Agrega la librería del LCD
LiquidCrystal lcd(48,49,45,44,43,42); 	//Inicializa la librería y define los pines digitales LCD

#define stopper PINC,1
#define pause PINC,2

long int seg;

int mint=0,s=0,ms=0;

void RPM()             			
{
  seg++;
}

void pausa(){
  
  ms = seg%100;
  s = seg/100;
  
  lcd.setCursor(3, 0); 
  lcd.print("Pausa");
  lcd.setCursor(5,1);
  
  if(mint<10){
    lcd.print("0");
    lcd.setCursor(6,1);
    lcd.print(mint);
  }
  else{
    lcd.print(mint);
  }
  lcd.setCursor(7,1);
  lcd.print(":");
  
  if(s<10){
    lcd.setCursor(8,1);
    lcd.print("0");
    lcd.setCursor(9,1);
    lcd.print(s);
  }
  else{
    lcd.setCursor(8,1);
    lcd.print(s);
  } 
  lcd.setCursor(10,1);
  lcd.print(":");
  lcd.setCursor(11, 1); 
  lcd.print(ms);
  lcd.setCursor(13, 1);
}

void detener(){
  s = 0;
  ms = seg%100;
  s = seg/100;
  if(s==60){
    seg=0;
    mint = mint+1;
  }
  lcd.setCursor(3, 0); 
  lcd.print("RPM");
  lcd.setCursor(5,1);
  if(mint<10){
    lcd.print("0");
    lcd.setCursor(6,1);
    lcd.print(mint);
  }
  else{
    lcd.print(mint);
  }
  lcd.setCursor(7,1);
  lcd.print(":");
  if(s<10){
    lcd.setCursor(8,1);
    lcd.print("0");
    lcd.setCursor(9,1);
    lcd.print(s);
  }
  else{
    lcd.setCursor(8,1);
    lcd.print(s);
  } 
  lcd.setCursor(10,1);
  lcd.print(":");
  lcd.setCursor(11, 1); 
  lcd.print(ms);
  lcd.setCursor(13, 1);
}

void setup()

{
  DDRC=0B0000000;
  pinMode(47,OUTPUT);
  digitalWrite(47,0);
  lcd.begin(16,2);                     		
  seg=0;  
  Timer1.initialize(10000);
  Timer1.attachInterrupt(RPM); 		
  lcd.clear();
  
}

void loop()
{

  ms = seg%100;
  s = seg/100;
  if(s==60){
    seg=0;
    mint = mint+1;
  }
  lcd.setCursor(3, 0); 
  lcd.print("RPM");
  lcd.setCursor(5,1);
  if(mint<10){
    lcd.print("0");
    lcd.setCursor(6,1);
    lcd.print(mint);
  }
  else{
    lcd.print(mint);
  }
  lcd.setCursor(7,1);
  lcd.print(":");
  if(s<10){
    lcd.setCursor(8,1);
    lcd.print("0");
    lcd.setCursor(9,1);
    lcd.print(s);
  }
  else{
    lcd.setCursor(8,1);
    lcd.print(s);
  } 
  lcd.setCursor(10,1);
  lcd.print(":");
  lcd.setCursor(11, 1); 
  lcd.print(ms);
  lcd.setCursor(13, 1);

}





