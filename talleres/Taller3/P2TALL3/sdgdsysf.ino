#define S1 PINC,0
#define S2 PINC,1
#define PA PINC,2
#define PAB PINC,3
#define AP PORTA,0
#define CP PORTA,1
#define LR PORTA,2
#define LV PORTA,3
#define salida PINC,4

int capacidad = 9;


byte display[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};

void setup() {
  DDRA=B00001111;
  DDRC=B00000000;
  DDRL=B11111111; 
}

void loop() {
  PORTL=(display[capacidad]);
  delay(1000);
  if(bitRead(PINC,S1)==HIGH){
    while(bitRead(PINC,S2)==LOW){
    bitClear(PORTA,CP);
    bitSet(PORTA,AP);
    bitClear(PORTA,LV);
    bitSet(PORTA,LR);
    }  
    if(bitRead(PINC,S2)==HIGH){
      bitSet(PORTA,LR);  
      bitClear(PORTA,PA);
      bitSet(PORTA,LR);
      bitSet(PORTA,CP);
      capacidad--;
    }
  } 
  
  else { // sino mantiene la pumilla abajo y no deja pasar
    bitClear(PORTA,AP); 
    bitClear(PORTA,LR);
    bitSet(PORTA,CP);
    bitSet(PORTA,LV);
  } 
  
  if(bitRead(PINC,salida)==HIGH){
    if(bitRead(PINC,S2)==HIGH){
       PORTL=(display[capacidad]);
       delay(1000);
       while(bitRead(PINC,S1)==LOW){
        bitClear(PORTA,CP); 
        bitClear(PORTA,LV);
        bitSet(PORTA,AP);
        bitSet(PORTA,LR);
       }
       if(bitRead(PINC,S1)==HIGH){
        bitClear(PORTA,AP); 
        bitClear(PORTA,LR);
        bitSet(PORTA,CP);
        bitSet(PORTA,LV);
         if(capacidad==9){
          capacidad=9;
         }
         else{
          capacidad++;
          PORTL=(display[capacidad]);
          delay(1000);
         }
       }
     }
  }
  /* if(bitRead(PINC,S2)==HIGH){
      bitClear(PORTA,CP); 
      bitClear(PORTA,LV);
      bitSet(PORTA,AP);
      bitSet(PORTA,LR);
      if(bitRead(PINC,S1)==HIGH){
       if(capacidad==9){
         capacidad=9;
       }
       else{
       capacidad++;
       }
     }
     */
  
  if(capacidad==0){
    PORTL = (display[capacidad]); 
    delay(1000);
    while(bitRead(PINC,S2)==LOW){
     bitClear(PORTA,AP); 
     bitClear(PORTA,LV);
     bitSet(PORTA,CP);
     bitSet(PORTA,LR);
    }  
    if(bitRead(PINC,S2)==HIGH){
      while(bitRead(PINC,S1)==LOW){
       bitClear(PORTA,CP); 
       bitClear(PORTA,LV);
       bitSet(PORTA,AP);
       bitSet(PORTA,LR);
      }
       if(bitRead(PINC,S1)==HIGH){
        bitClear(PORTA,AP); 
        bitClear(PORTA,LV);
        bitSet(PORTA,CP);
        bitSet(PORTA,LR);
         if(capacidad==9){
         capacidad=9;
         }
         else{
          capacidad++;
          delay(1000);
         }
       }
     }

   }

  }
         
