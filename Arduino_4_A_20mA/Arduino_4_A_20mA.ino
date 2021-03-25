float valor;
String valor1;
const  int  Switch  =  2 ;      // o número do seletror 
#define pinBotao1 8
#define pinBotao2 9
int numero = 5;
boolean botaoAtu = false;
boolean botaoAnt = false;

int count_value =0;
int prestate =0;
int Retorna_Valor = 0;
int PWM = 3;
int Pin01 =4;
float tensao;
float ValorEnmA;
float x1,x,x2,y1,y,y2;

#include <OLED_I2C.h>
OLED  myOLED(SDA, SCL); // Remember to add the RESET pin if your display requires it...

extern uint8_t SmallFont[];
extern uint8_t TinyFont[];
extern uint8_t MediumNumbers[];
void setup() {
  Serial.begin(9600);
  pinMode(pinBotao1, INPUT);
  pinMode(pinBotao2, INPUT);
  pinMode(Switch, INPUT);
  pinMode(PWM, OUTPUT);
  pinMode(Pin01, OUTPUT);
  pinMode(A0, INPUT);
  if(!myOLED.begin(SSD1306_128X32))
    while(1);   // In case the library failed to allocate enough RAM for the display buffer...
}

void loop() {
  int leitura1 = digitalRead(Switch);
  if (leitura1 == HIGH){
    
  digitalWrite(Pin01,HIGH);
  float leitura = analogRead(A0); //Armazena a leitura do pino A0 na variavel leitura
  tensao = leitura * 5.0 / 1023; 
  //////////Interpolação Linear //////////
 float x = tensao ;
 x1= 5.0;
 x2= 0.0;
 
 
 float y = ValorEnmA ;
 y1 = 20.0;
 y2 = 4.0;

  y = y1+((x-x1)/(x2-x1)*(y2-y1)) ;
///////////////////Fim  da interpolação linear///////////////////////
  
  float pwm = map(leitura,0,1023,0,255);
  analogWrite(PWM, pwm);
  Serial.println(pwm);
  float mA;
  mA = map(pwm,0,255,4,20);
  Serial.println("Valor do PWM em mA:");
  Serial.println(mA);
  
  
  valor = y;
  myOLED.clrScr();
  myOLED.setFont(SmallFont);
  myOLED.print("mA", CENTER, 3);
  myOLED.setFont(MediumNumbers);
  myOLED.printNumF(valor,1, CENTER, 12);
  myOLED.update();
  delay (100);
   myOLED.clrScr();
  }
  else if (leitura1 == LOW){
   botaoAtu = digitalRead(pinBotao1);
     if (botaoAtu && !botaoAnt) {
     numero++;
     Serial.print("O numero é:");
      Serial.println(numero);
     if (numero > 5) {
        numero = 5; 
        
     }
     }
      botaoAtu = digitalRead(pinBotao2);
      if (botaoAtu && !botaoAnt) {
       numero--;
     Serial.print("O numero é:");
      Serial.println(numero);
     if (numero <1) {
        numero = 1; 
        
     }
     
  }
  botaoAnt = botaoAtu;
 valor1 = numero;
if (numero ==1){
  int step1 = 0;
  analogWrite(PWM, step1);
  myOLED.clrScr();
  myOLED.setFont(SmallFont);
  myOLED.print("Step 1", CENTER, 3);
  myOLED.print("0%", CENTER, 15);
  myOLED.update();
  delay (100);
   myOLED.clrScr();
}
else if (numero ==2){
  int step2 = 68;
  analogWrite(PWM, step2);
  myOLED.clrScr();
  myOLED.setFont(SmallFont);
  myOLED.print("Step 2", CENTER, 3);
  myOLED.print("25%", CENTER, 15);
  myOLED.update();
  delay (100);
   myOLED.clrScr();
}
else if (numero ==3){
   int step3 = 130;
  analogWrite(PWM, step3);
  myOLED.clrScr();
  myOLED.setFont(SmallFont);
  myOLED.print("Step 3", CENTER, 3);
  myOLED.print("50%", CENTER, 15);
  myOLED.update();
  delay (100);
   myOLED.clrScr();
}
else if (numero ==4){
   int step4 = 190;
  analogWrite(PWM, step4);
  myOLED.clrScr();
  myOLED.setFont(SmallFont);
  myOLED.print("Step 4", CENTER, 3);
  myOLED.print("75%", CENTER, 15);
  myOLED.update();
  delay (100);
   myOLED.clrScr();
 delay(100);
}
else if (numero ==5){
  
  int step5 = 255;
  analogWrite(PWM, step5);
  myOLED.clrScr();
  myOLED.setFont(SmallFont);
  myOLED.print("Step 5", CENTER, 3);
  myOLED.print("100%", CENTER, 15);
  myOLED.update();
  delay (100);
   myOLED.clrScr();
}
 
 /*  valor1 = numero;
   switch (valor1) {
      case 1: 
          Serial.println("Caso 1");
          
        break; 

      case 2: 
       Serial.println("Caso 2");
      
        break; 
  }
  */
}

}
