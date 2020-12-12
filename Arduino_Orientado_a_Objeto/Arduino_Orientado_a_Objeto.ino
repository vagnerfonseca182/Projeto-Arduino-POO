#include <Servo.h>
class Piscar
{
  // Atributos da Class " variaveis "

  int ledPin;      // o número do pino do LED // o número do pino do LED 
  long OnTime;     // milissegundos de sobre - tempo 
  long OffTime;    // // milissegundos de fora - tempo 

  // These maintain the current state
  int ledState;                 // // ledState usado para definir o LED 
  unsigned long previousMillis;   // armazenará a última vez que o LED foi atualizado 

  // O Constructor é criado   
  // e inicia as variaveis e seus estados 
  public:
  Piscar(int pin, long on, long off)
  {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);     
    
  OnTime = on;
  OffTime = off;
  
  ledState = LOW; 
  previousMillis = 0;
  }

  void Update()
  {
    //verificacão  para mudar o estado do LED 
    unsigned long currentMillis = millis();
     
    if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      ledState = LOW;  // Turn it off
      previousMillis = currentMillis;  // tempo anterior 
      digitalWrite(ledPin, ledState);  // atualiza o LED
    }
    else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = HIGH;  // turn it on
      previousMillis = currentMillis;   // tempo anterior 
      digitalWrite(ledPin, ledState);   // atualiza o LED
    }
  }
};

class Sweeper
{
  Servo servo;              //  servo
  int pos;              // posição atual do servo  
  int increment;        // incrementação
  int  updateInterval;      // intervalo entre atualizações 
  unsigned long lastUpdate; // última atualização de posição 

public: 
  Sweeper(int interval)
  {
    updateInterval = interval;
    increment = 1;
  }
  
  void Attach(int pin)
  {
    servo.attach(pin);
  }
  
  void Detach()
  {
    servo.detach();
  }
  
  void Update()
  {
    if((millis() - lastUpdate) > updateInterval)  // atualizar
    {
      lastUpdate = millis();
      pos += increment;
      servo.write(pos);
      Serial.println(pos);
      if ((pos >= 180) || (pos <= 0)) // fim da varredura
      {
        // reverse direction
        increment = -increment;
      }
    }
  }
};
 
 
Piscar led1(2, 123, 300);
Piscar led2(3, 500, 1000);
Piscar led3(4, 100, 122);

Sweeper sweeper1(15);
Sweeper sweeper2(25);
 
void setup() 
{ 
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP); 
  sweeper1.Attach(9);
  sweeper2.Attach(10);
} 
 
 
void loop() 
{ 
  sweeper1.Update();
  
  if(digitalRead(11) == HIGH)
  {
     sweeper2.Update();
     led1.Update();
  }
  
  led2.Update();
  led3.Update();
}
