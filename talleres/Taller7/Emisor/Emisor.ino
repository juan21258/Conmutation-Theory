
int ent;
char grabar;
boolean parar = false;

void setup()

{
  
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("Presione 0 para empezar");
}
void loop()

{
  if (Serial.available() > 0)
  {
    ent = Serial.read();
    if (ent == '0')
    {
      parar = true;
      Serial.println("Moviendo a 1");
      Serial1.println('1');
    }
  }
  if(Serial1.available() > 0)
  {
    grabar = Serial1.read();
    Serial.print(grabar);
  }
  
}
