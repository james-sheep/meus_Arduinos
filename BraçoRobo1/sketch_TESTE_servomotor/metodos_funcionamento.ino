void direita (){

lcd.clear();
delay(1000);
lcd.setCursor(0,0);
lcd.print("---->");

motor1.slowmove(0,30);

  }

void esquerda() {
   
lcd.clear();
delay(1000);
lcd.setCursor(0,0);
lcd.print("<----");
motor1.slowmove(160,30);
  
  }

void sobe(){
   
lcd.clear();
delay(1000);
lcd.setCursor(0,0);
lcd.print(" subindo !!!");
motor2.slowmove(160,30);
motor3.slowmove(20,30);
  
  }

void desce(){ 
 
lcd.clear();
delay(1000);
lcd.setCursor(0,0);
lcd.print("Descendooooo!");
motor2.slowmove(120,30);
motor3.slowmove(90,30);
  }

void abre(){
  
lcd.clear();
delay(1000);
lcd.setCursor(0,0);
lcd.print("Bocão AHHHH");

motor4.slowmove(0,30);
  }

void fecha(){

 
lcd.clear();
delay(1000);
lcd.setCursor(0,0);
lcd.print("Mordendo !!!");
lcd.setCursor(0,1);
lcd.print("Vou pegar :-D");
  
  motor4.slowmove(163,30);
}


void pega_direita(){
  
 
lcd.clear();
delay(1000);
lcd.setCursor(0,0);
lcd.print("Encomenda -->");
lcd.setCursor(0,1);
lcd.print("Vou pegar :-D");
  
 // pegar algo
  motor4.slowmove(0,30);
  delay(2000);
  motor1.slowmove(0,30);
  delay(2000);
  motor2.slowmove(120,30);
  motor3.slowmove(90,30);
  delay(2000);
  motor4.slowmove(163,30);
  delay(2500);
  motor2.slowmove(160,30);
  motor3.slowmove(20,30);
  delay(2500);
  motor1.slowmove(60,30);
  delay(2000);
  motor2.slowmove(120,30);
  motor3.slowmove(90,30);
  delay(2000);
  motor4.slowmove(0,30);
  delay(2500);
  motor2.slowmove(160,30);
  motor3.slowmove(20,30);

}
void pega_esquerda(){

   
lcd.clear();
delay(1000);
lcd.setCursor(0,0);
lcd.print("Encomenda -->");
lcd.setCursor(0,1);
lcd.print("Vou pegar :-D");
  
 // pegar algo
  motor4.slowmove(0,30);
  delay(2000);
  motor1.slowmove(160,30);
  delay(2000);
  motor2.slowmove(120,30);
  motor3.slowmove(90,30);
  delay(2000);
  motor4.slowmove(163,30);
  delay(2500);
  motor2.slowmove(160,30);
  motor3.slowmove(20,30);
  delay(2500);
  motor1.slowmove(60,30);
  delay(2000);
  motor2.slowmove(120,30);
  motor3.slowmove(90,30);
  delay(2000);
  motor4.slowmove(0,30);
  delay(2500);
  motor2.slowmove(160,30);
  motor3.slowmove(20,30);

}
