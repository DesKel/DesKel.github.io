#define Red 11
#define Green 10
#define Blue 9

void setup()
{
  pinMode(Red,OUTPUT);
  pinMode(Green,OUTPUT);
  pinMode(Blue,OUTPUT);

  RGB(255,255,255);  //calling the RGB function
}

void loop()
{
}

void RGB(int red, int green, int blue)
{
  analogWrite(Red,red);
  analogWrite(Green,green);
  analogWrite(Blue,blue);
}
