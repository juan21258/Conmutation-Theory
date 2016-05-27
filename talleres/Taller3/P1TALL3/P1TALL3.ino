#define SP1	PINC,4
#define SP2     PINC,5 
#define SP3	PINC,6
#define PP1     PINC,0
#define PP2     PINC,1
#define PP3	PINC,2
#define STOP    PINC,3
#define SUP	PINC,7
#define SDOWN   PINA,7
#define BAJAR 	PORTA,0
#define SUBIR 	PORTA,1
#define SOL   	PORTA,2
#define IZQ	PORTA,3
#define DER   	PORTA,4


void setup()
{
  DDRA = B01111111;
  DDRC = B00000000;
  DDRL = B11111111;
}

void Bajar()
{
  while(bitRead(PINA,SDOWN)==LOW){
	bitSet(PORTA,BAJAR);
	PORTL = B11111100;  
  }
	bitClear(PORTA,BAJAR);
	PORTL = B00000000;
}

void Subir()
{
	while(bitRead(PINC,SUP)==LOW){
     	bitSet(PORTA,SUBIR);
     PORTL = B1101101;
    	}
    	bitClear(PORTA,SUBIR);
    	PORTL = B00000000;
}

void DerechaS2()
{
	while(bitRead(PINC,SP2)==LOW){
     	bitSet(PORTA,DER);
     	PORTL = B01011110;
    	}
    	bitClear(PORTA,DER);
    	PORTL = B00000000;
}


void DerechaS3()
{
	while(bitRead(PINC,SP3)==LOW){
     	bitSet(PORTA,DER);
     	PORTL = B01011110;
    	}
    	bitClear(PORTA,DER);
    	PORTL = B00000000;
}


void IzquierdaS1()
{
	while(bitRead(PINC,SP1)==LOW){
     		bitSet(PORTA,IZQ);
     		PORTL = B00000110;
    	}
    	bitClear(PORTA,IZQ);
    	PORTL = B00000000;
}

void IzquierdaS2()
{
	while(bitRead(PINC,SP2)==LOW){
     		bitSet(PORTA,IZQ);
     		PORTL = B00000110;
    	}
    	bitClear(PORTA,IZQ);
    	PORTL = B00000000;
}

void loop()
{
  if(bitRead(PINC,PP1)==HIGH)
  { 	
	if(bitRead(PINC,SP2)==HIGH)
	{
	   IzquierdaS1();
	}else if(bitRead(PINC,SP3)==HIGH)
	{
	   IzquierdaS1();	
	}
    	Bajar();
    	bitSet(PORTA,SOL);
    	Subir();
    	DerechaS2();
	Bajar();
	bitClear(PORTA,SOL);
	Subir();
  }
  if(bitRead(PINC,PP2)==HIGH)
  {
	if(bitRead(PINC,SP2)==HIGH)
	{
	   IzquierdaS1();
	}else if(bitRead(PINC,SP3)==HIGH)
	{
	   IzquierdaS1();	
	}
    	Bajar();
	bitSet(PORTA,SOL);
	Subir();
	DerechaS3();
	Bajar();
	bitClear(PORTA,SOL);
        Subir();
  }
  if(bitRead(PINC,PP3)==HIGH){
	if(bitRead(PINC,SP1)==HIGH)
	{
	   DerechaS2();
	}else if(bitRead(PINC,SP3)==HIGH)
	{
	   IzquierdaS2();	
	}
	Bajar();
	bitSet(PORTA,SOL);
	Subir();
	IzquierdaS1();
	Bajar();
	bitClear(PORTA,SOL);
	Subir();
  }
  if(bitRead(PINC,STOP)==HIGH){
    if(bitRead(PINC,SP1)==LOW){	 
	Bajar();      
     	bitSet(PORTA,SOL);
	Subir();
	IzquierdaS1();
	Bajar();
     	bitClear(PORTA,SOL);
	Subir();
    }  
  }
}


