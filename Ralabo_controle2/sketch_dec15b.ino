
#include <IRremote.h>  
#include <Ultrasonic.h> 



int RECV_PIN = 4 ;  
int distancia = 0;  
float armazenavalor;
int PinTrigger = 2; // Pino usado para disparar os pulsos do sensor
int PinEcho = 3;
  
IRrecv irrecv(RECV_PIN);  
decode_results results;  


#define pino_trigger 2
#define pino_echo 3
Ultrasonic ultrasonic(pino_trigger, pino_echo);//Inicializa o sensor nos pinos definidos acima


void setup()
{
  
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(2, OUTPUT);
  
}


void loop()  
{  

  //Le as informacoes do sensor, em cm e pol
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  //Exibe informacoes no serial monitor
  //Serial.print("Distancia em cm: ");
  //Serial.print(cmMsec);
  //Serial.print(" - Distancia em polegadas: ");
  //Serial.println(inMsec);
 // delay(1000);


 
    
  
  if (irrecv.decode(&results))  
  {  
    Serial.print("Valor lido : ");  
    Serial.println(results.value, HEX);  
    armazenavalor = (results.value);  
    
    if (armazenavalor == 0xFF38C7)
    {  
     
       digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
    
    }  
    
    
    if (armazenavalor == 0xFF18E7) //- FRENTE
    {  
    
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
   
    }  
    if (armazenavalor == 0xFF4AB5) //-TRÁS
    {  
     
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
    
    }  
    if (armazenavalor == 0xFF10EF) //Verifica se a tecla 3 foi acionada  - esquerda 
    {  
      
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      

    }  
    if (armazenavalor == 0xFF5AA5) //Verifica se a tecla 4 foi acionada  - direita
    {  

    
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);

      
    }  
    
  irrecv.resume(); //Le o próximo valor  
  }  
}
