// bibliotecas

#include <VarSpeedServo.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h> 
 
// tipagem das variavéis e métodos particulares
int  armazenavalor = 0;
int  RECV_PIN = 13;  


// criação de objetos

VarSpeedServo motor1;
VarSpeedServo motor2;
VarSpeedServo motor3;
VarSpeedServo motor4;
LiquidCrystal_I2C lcd(0x27,16,2);
IRrecv irrecv(RECV_PIN);  
decode_results results;  

// metodos principais arduino:

void setup() {
Serial.begin(9600);
lcd.init();

motor1.attach(3);
motor2.attach(5);
motor3.attach(9);
motor4.attach(11);
irrecv.enableIRIn();
}

void loop() {

  
///Definindo estado inicial

lcd.setBacklight(HIGH);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Oi Samuel");
lcd.setCursor(0,1);
lcd.print("Sou o Guincho:-)");

motor1.slowmove(60,30);
delay(1000);
motor2.slowmove(160,30);
 delay(1000);
motor3.slowmove(20,30);
delay(1000);
motor4.slowmove(175,30);


  
///// FUNCIONAMENTO//////

if (irrecv.decode(&results)) {  
Serial.print("Valor lido : ");  
Serial.println(results.value, HEX);  
armazenavalor = (results.value);
irrecv.resume();

if (armazenavalor == 0xFFA25D) {
  
  pega_esquerda();  
  }

if (armazenavalor == 0xFF629D) {
  
  pega_direita();
  }

if (armazenavalor == 0xFF10EF ) {
  
  esquerda(); 
  }
  
if (armazenavalor == 0xFF5AA5) {
  
  direita(); 
  }

if (armazenavalor == 0xFF18E7) {
  
  sobe();
  }

if (armazenavalor == 0xFF4AB5) {
  
  desce();
  }

if (armazenavalor == 0xFF6897) {
  
  abre(); 
  }

if (armazenavalor == 0xFFB04F) {
  
  fecha(); 
  }




  }

}
