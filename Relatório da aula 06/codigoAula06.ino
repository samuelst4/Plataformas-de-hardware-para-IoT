const int PIN_POT = 32;   
const int PIN_LDR = 34;   
const int PIN_BOTAO = 26;  
const int PIN_LED1 = 18;  
const int PIN_LED2 = 19;  

const int ADC_MAX = 4095; 

bool modoAuto = false;          
bool estadoBotaoAnterior = HIGH; 

unsigned long ultimoTempoDebounce = 0;
const unsigned long tempoDebounce = 50; 

unsigned long tempoAnteriorPisca = 0;
bool estadoLed2 = LOW;

void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_POT, INPUT);
  pinMode(PIN_LDR, INPUT);
  
  pinMode(PIN_BOTAO, INPUT_PULLUP);
  
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
}

void loop() {
  unsigned long tempoAtual = millis();

  bool leituraBotao = digitalRead(PIN_BOTAO);
  
  if (leituraBotao != estadoBotaoAnterior) {
    ultimoTempoDebounce = tempoAtual;
  }
  
  if ((tempoAtual - ultimoTempoDebounce) > tempoDebounce) {
    if (leituraBotao == LOW) {
      modoAuto = !modoAuto; 
      
      if(modoAuto) {
        Serial.println("Modo: AUTOMATICO (LDR)");
      } else {
        Serial.println("Modo: MANUAL (Potenciometro)");
      }
      
      while(digitalRead(PIN_BOTAO) == LOW) { delay(10); } 
    }
  }
  estadoBotaoAnterior = leituraBotao;

  int valorADC = 0;
  if (modoAuto) {
    valorADC = analogRead(PIN_LDR);
  } else {
    valorADC = analogRead(PIN_POT);
  }

  int valorPWM = map(valorADC, 0, ADC_MAX, 0, 255); 
  
  int intervaloPisca = map(valorADC, 0, ADC_MAX, 100, 1000);

  analogWrite(PIN_LED1, valorPWM);

  if (tempoAtual - tempoAnteriorPisca >= intervaloPisca) {
    tempoAnteriorPisca = tempoAtual;       
    estadoLed2 = !estadoLed2;              
    digitalWrite(PIN_LED2, estadoLed2);    
  }
}
