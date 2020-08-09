# define LED 3

void setup()
{
  Serial.begin(9600);
  Serial.println("Input bightness 0~255 ");
  pinMode(LED,OUTPUT);
}

void loop()
{
  if (Serial.available()>0)
  {
     String brightness = Serial.readString();
     int bright = brightness.toInt();      //convert to int
     analogWrite(LED,bright);
     Serial.println(bright);
  }
}
