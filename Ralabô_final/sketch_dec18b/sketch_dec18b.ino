
#include <Ultrasonic.h> 


int motor1a = 5;
int motor1b = 6;
int motor2a = 10;
int motor2b = 11;


float armazenavalor;
int PinTrigger = 2; // Pino usado para disparar os pulsos do sensor
int PinEcho = 3;
  



#define pino_trigger 2
#define pino_echo 3
Ultrasonic ultrasonic(pino_trigger, pino_echo);//Inicializa o sensor nos pinos definidos acima


void setup()
{
  
  Serial.begin(9600);
  pinMode(motor1a, OUTPUT);
  pinMode(motor1b, OUTPUT);
  pinMode(motor2a, OUTPUT);
  pinMode(motor2b, OUTPUT);
  pinMode(2, OUTPUT);
  
}


void loop()  
{  
// ajuste pwm de velocidades vai de 0 a 255 
      
      


  //Le as informacoes do sensor, em cm e pol
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  //Exibe informacoes no serial monitor
  Serial.print("Distancia em cm: ");
  Serial.print(cmMsec);
  Serial.print(" - Distancia em polegadas: ");
  Serial.println(inMsec);
  delay(1000);
 
   if (cmMsec < 30)
    {  
     // parar
      analogWrite(motor1a, 255);
      analogWrite(motor1b, 255);
      analogWrite(motor2a, 255);
      analogWrite(motor2b, 255);
      //aguardar
      delay(1000);
     // tras
      analogWrite(motor1a, 160);
      analogWrite(motor1b, LOW);
      analogWrite(motor2a, 160);
      analogWrite(motor2b, LOW);
      //aguardar
      delay (500);
      //girar
      analogWrite(motor1a, 100);
      digitalWrite(motor1b, LOW);
      digitalWrite(motor2a, HIGH);
      digitalWrite(motor2b, HIGH);
      delay(500);
      //parar
      digitalWrite(motor1a, HIGH);
      digitalWrite(motor1b, HIGH);
      digitalWrite(motor2a, HIGH);
      digitalWrite(motor2b, HIGH);
     
              
       
      
    }  
    
    
    if (cmMsec < 90) //- FRENTE
    {  
    
    analogWrite(motor1a, LOW);
    analogWrite(motor1b, 160);
    analogWrite(motor2a, LOW);
    analogWrite(motor2b, 160);
   
    }

    if (cmMsec > 90) //- aguarda
    {  
    
       digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
    }

  }  
