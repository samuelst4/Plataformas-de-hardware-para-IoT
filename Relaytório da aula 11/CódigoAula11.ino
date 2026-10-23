const int trigPin = 27;
const int echoPin = 25;

#define SOUND_SPEED 0.034 // cm/us

volatile unsigned long tempoInicio = 0;
volatile unsigned long tempoFim = 0;
volatile bool novaLeituraDisponivel = false;


void IRAM_ATTR echoISR() {
  if (digitalRead(echoPin) == HIGH) {
    tempoInicio = micros(); 
  } else {
    tempoFim = micros();   
    novaLeituraDisponivel = true;
  }
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  digitalWrite(trigPin, LOW);
  Serial.begin(115200);

  attachInterrupt(digitalPinToInterrupt(echoPin), echoISR, CHANGE);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long tempoEspera = millis();
  while (!novaLeituraDisponivel && (millis() - tempoEspera < 50)) {
  }

  if (novaLeituraDisponivel) {
    noInterrupts();
    unsigned long duracao = tempoFim - tempoInicio;
    novaLeituraDisponivel = false;
    interrupts();

    float distanciaCM = (duracao * SOUND_SPEED) / 2.0;

    Serial.print("Distância: ");
    Serial.print(distanciaCM);
    Serial.println(" cm");
  } else {
    Serial.println("Distância: Erro de leitura (Timeout)");
  }

  delay(1000); 
}
