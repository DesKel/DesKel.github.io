#define LED 3
#define button 7

boolean OldButtonState; //define last button state

void setup()
{
  pinMode(LED,OUTPUT);
  pinMode(button,INPUT);   // Set button as Input
}

void loop()
{
  boolean ButtonState = digitalRead(button);

  if(ButtonState != OldButtonState)  //detect change in button state
  {
    if(ButtonState == 0)
    {
      digitalWrite(LED,!digitalRead(LED)); //toggle LED
    }
    delay(50);
  }
 OldButtonState = ButtonState;   //register the old button state
}
