#define LED 3

void setup() 
{
  Serial.begin(9600);
  Serial.println("ON or OFF LED?");  
  pinMode(LED,OUTPUT);
}

void loop() 
{
   String LEDStatus="";          

   while(Serial.available()>0)   
   {
      LEDStatus = Serial.readString();          
      int LengthLED = LEDStatus.length();         //remove newline and null
      LEDStatus.remove(LengthLED-2,LengthLED-1);
     
      if (LEDStatus == "ON")                      //ON condition
      {
         Serial.println("LED ON");
         digitalWrite(LED,HIGH);
      }

      else if (LEDStatus == "OFF")                //OFF condition
      {
         Serial.println("LED OFF");
         digitalWrite(LED,LOW);
      }
   }
}