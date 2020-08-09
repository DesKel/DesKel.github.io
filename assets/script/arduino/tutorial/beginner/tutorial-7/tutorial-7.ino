#define R 11
#define G 10
#define B 9
#define POT A0
#define button 7

int i = 0;
int LB[11],UB[11];
float j = 0.65;
boolean ButtonState,OldButtonState;
double startTime,endTime,diffTime;

void setup()
{
  Serial.begin(9600);
  pinMode (R,OUTPUT);
  pinMode (G,OUTPUT);
  pinMode (B,OUTPUT);
  pinMode (POT,INPUT);
  pinMode (button,INPUT);
  OldButtonState = digitalRead(button);
  Serial.println("Let's the game begin");
  RGB (255,255,0);

  do
  {
    LB[0] = random(0,1023);
    UB[0] = LB[0] + ((1023-LB[0]) * j);
  }
  while (UB[0] > 1023);
  Serial.println("Press button to start");
  while (digitalRead(button) == 1);
  Serial.println("game start in");
  delay(1000);
  Serial.println("3");
  delay(500);
  Serial.println("2");
  delay(500);
  Serial.println("1");
  delay(500);
  Serial.println("start");
  startTime = millis();
}

void loop()
{
  int potVal = analogRead(POT);
  ButtonState = digitalRead(button);

  if(potVal>LB[i] && potVal<UB[i])
  {
    RGB(0,255,0);
    if(ButtonState != OldButtonState)
    {
      if(ButtonState == 0)
      {
        j = j - 0.05;
        i ++;
        getRandom(i,j);
        Serial.print("Stage ");
        Serial.print(i);
        Serial.println(" Complete");
      }
      delay(50);
    }
    OldButtonState = ButtonState;
  }

  else
  {
    RGB(255,0,0);
    if(ButtonState != OldButtonState)
    {
      if(ButtonState == 0)
      {
        Serial.println("Penalty 2s");
        delay(2000);
      }
    }
    OldButtonState = ButtonState;
  }

  if(i == 10)
  {
    endTime = millis();
    diffTime = (endTime - startTime)/1000;
    RGB(0,0,255);
    Serial.println("All stages Completed");
    Serial.println("============================================================");
    Serial.print("Finished time; ");
    Serial.print(diffTime);
    Serial.println(" s");
    while(1);
  }
}

void RGB(int r, int g, int b)
{
  analogWrite(R,r);
  analogWrite(G,g);
  analogWrite(B,b);
}

void getRandom(int k, float l)
{
  do
  {
    LB[k] = random(0,1023);
    UB[k] = LB[k] + ((1023-LB[k]) * l);
  }
  while(UB[k] > 1023);
}
