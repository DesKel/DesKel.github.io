#define LED 3
#define button 7

void setup()
{
  pinMode(LED,OUTPUT);
  pinMode(button,INPUT);   // Set button as Input
}

void loop()
{
  boolean ButtonState = digitalRead(button); // read button

  if (ButtonState == 0) digitalWrite(LED,HIGH);
  else if (ButtonState == 1) digitalWrite(LED,LOW);

}
