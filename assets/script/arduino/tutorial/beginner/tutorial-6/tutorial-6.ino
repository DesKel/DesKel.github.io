#define buzzer 4
#define LDR A1

void setup()
{
  pinMode(buzzer,OUTPUT);
  pinMode(LDR,INPUT);
}

void loop()
{
  int LDRStatus = analogRead(LDR);
  if (LDRStatus >= 600)    //Detect Intruder at dimmer light
  {
    digitalWrite(buzzer,HIGH);
    delay(3000);
  }

  else
  {
    digitalWrite(buzzer,LOW);
  }
}
