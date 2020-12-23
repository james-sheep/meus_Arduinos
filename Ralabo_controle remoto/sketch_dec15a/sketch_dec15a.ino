
  
#include <IRremote.h>  
  
int RECV_PIN = 8;  
float armazenavalor;  
int distancia = 0;  

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}


IRrecv irrecv(RECV_PIN);  
decode_results results;  
  
void setup()
{
  
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(7, OUTPUT);
  
}
   
void loop()
{

    distancia = 0.01723 * readUltrasonicDistance(12, 9);
    Serial.print(distancia);
    Serial.println("cm");
 
  if (distancia <15) {
   
    digitalWrite(13, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
  
  }

if (irrecv.decode(&results)) {  
    Serial.print("Valor lido : ");  
    Serial.println(results.value, HEX);  
    armazenavalor = (results.value); 
    
    if (armazenavalor == 0xFF30CF) //Verifica se a tecla 1 foi acionada  {  
       tone(7, 60, 100); // play tone 40 (E3 = 165 Hz);
    }  
    
    if (armazenavalor == 0xFF18E7) //Verifica se a tecla 2 foi acionada  
    {  
       
      digitalWrite(2,LOW);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(13, LOW);
      
    }  
    
if (armazenavalor == 0xFF10EF) //Verifica se a tecla 3 foi acionada  
    {  
      digitalWrite(2,HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(13, HIGH);
    } 
     
  irrecv.resume(); //Le o próximo valor 
} 
