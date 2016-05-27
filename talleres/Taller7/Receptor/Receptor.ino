
int ent;
//entrada

void desplazar(){
//proceso  
  while(bitRead(PINC,7) == LOW){
    bitSet(PORTA,0);
  }
  bitClear(PORTA,0);
}

void setup(){
  
  Serial1.begin(9600);
  Serial.begin(9600);
  DDRA = B11111111;          //habilitación puertos
}


void loop(){

  if (Serial1.available()>0)
  {
    ent=Serial1.read();
    if(ent=='0')
    {
      Serial1.println("Moviendo");
      desplazar();
      Serial1.println("Paro");   
    }
  }
  //fin
}





