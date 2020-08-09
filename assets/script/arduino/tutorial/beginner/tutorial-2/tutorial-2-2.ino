void setup() 
{
  Serial.begin(9600);
  Serial.println("What is your name?");             
}

void loop() 
{
   String Name="";           //Declare a variable to store your name

   while(Serial.available()>0)   //Check the input
   {
      Name = Serial.readString(); 
      Serial.print("Hi, ");
      Serial.print(Name);    //print your name  
   }
}