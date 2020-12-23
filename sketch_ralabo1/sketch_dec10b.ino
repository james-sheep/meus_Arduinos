


float armazenavalor;
int distancia = 0;
int counter;
float armazena_valor;

  
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

void setup()
{
  Serial.begin(9600);
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
    digitalWrite(13, HIGH);
  if (distancia >= 60) {
    digitalWrite(13, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
  }
  
  if (distancia < 60) {
    digitalWrite(2,HIGH);
    delay(500);
    digitalWrite(2,LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(13, LOW);
    tone(7, 60, 100); // play tone 40 (E3 = 165 Hz);
    delay(500);
    digitalWrite(7,LOW);
  }
}

    
