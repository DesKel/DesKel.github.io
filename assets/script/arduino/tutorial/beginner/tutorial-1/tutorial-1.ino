#define LED 3      //Declare LED pin

void setup() 
{
  pinMode(LED,OUTPUT);  //Set LED pin as output
}

void loop() 
{
  digitalWrite(LED, HIGH);   //LED high
  delay(1000);               //delay 1000ms or 1s        
  digitalWrite(LED, LOW);    //LED low
  delay(1000);               //delay 1000ms or 1s        
}