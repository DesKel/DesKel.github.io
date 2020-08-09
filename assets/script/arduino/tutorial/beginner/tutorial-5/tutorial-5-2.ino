#define LED 3
#define Pot A0

void setup()
{
  pinMode(LED,OUTPUT);
  pinMode(Pot,INPUT);
}

void loop()
{
  int val = analogRead(Pot);
  val = map(val, 0, 1023, 0, 255);
  analogWrite(LED,val);
}
