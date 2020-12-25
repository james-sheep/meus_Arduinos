// bibliotecas

#include <VarSpeedServo.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h> 
 
// criação de objetos

VarSpeedServo motor1;
VarSpeedServo motor2;
VarSpeedServo motor3;
VarSpeedServo motor4;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
Serial.begin(9600);
lcd.init();
motor1.attach(3);
motor2.attach(5);
motor3.attach(9);
motor4.attach(11);
}

void loop() {

int angulo1 = analogRead(0);
int angulo2 = analogRead(1);
int angulo3 = analogRead(3);
int angulo4 = analogRead(4);

angulo1 = map(angulo1, 0, 1023, 0, 180);
angulo2 = map(angulo2, 0, 1023, 0, 180);
angulo3 = map(angulo3, 0, 1023, 0, 180);
angulo4 = map(angulo4, 0, 1023, 0, 180);

lcd.setBacklight(HIGH);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Oi Samuel :-)");
lcd.setCursor(0,1);
lcd.print("Sou o Guincho:-)");

motor1.slowmove(angulo1,30);

motor2.slowmove(angulo2,30);

motor3.slowmove(angulo3,30);

motor4.slowmove(angulo4,30);
  }
  
