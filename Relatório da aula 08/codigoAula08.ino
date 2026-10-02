const int trigPin = 27;
const int echoPin = 26;

#define SOUND_SPEED 0.034 // cm/uS

const float DISTANCIA_MAXIMA = 400.0; 

long duracao;
float distanciaCM;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracao = pulseIn(echoPin, HIGH);
  
  distanciaCM = duracao * SOUND_SPEED / 2;

  if (distanciaCM > DISTANCIA_MAXIMA || distanciaCM < 2.0) {
    distanciaCM = 0;
  }

  Serial.print("Distância: ");
  Serial.print(distanciaCM);
  Serial.println(" cm");

  delay(1000);
}
