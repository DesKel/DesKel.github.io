#define Pot A0 //Assign potentiometer to A0

void setup()
{
  Serial.begin(9600);
  pinMode(Pot,INPUT);
}

void loop()
{
  int val = analogRead(Pot);    //Read analog input
  float voltage = val * 0.0048828;

  Serial.print("Step size: ");
  Serial.print(val);
  Serial.print("    ");
  Serial.print("Voltage: ");
  Serial.println(voltage);
  delay(500);
}
