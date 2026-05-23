#include <AFMotor.h>

// --- Configurare Pini ---
#define PIN_SENSOR A0     
#define SWITCH_PIN_1 22   
#define PIN_BUZZER 32     
#define LED_R 44
#define LED_G 45
#define LED_B 46

AF_DCMotor motorStanga(1);
AF_DCMotor motorDreapta(4);

// Variabile control
bool autonom = true;
unsigned long timpAnterior = 0;
int stadiuVerde = 0;   
int indexCuloare = 0;  

void seteazaCuloare(int r, int g, int b) {
  analogWrite(LED_R, r); analogWrite(LED_G, g); analogWrite(LED_B, b);
}

void setup() {
  Serial.begin(9600);   // USB
  Serial1.begin(9600);  // Bluetooth (Pin 19=RX, 18=TX)
  
  pinMode(SWITCH_PIN_1, INPUT_PULLUP);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(LED_R, OUTPUT); pinMode(LED_G, OUTPUT); pinMode(LED_B, OUTPUT);

  motorStanga.setSpeed(200); 
  motorDreapta.setSpeed(200);
}

void loop() {
  // 1. Verificam Bluetooth (daca primim comenzi)
  if (Serial1.available() > 0) {
    char cmd = Serial1.read();
    autonom = false; // Comanda primita = trecem pe manual
    if (cmd == 'F') { motorStanga.run(FORWARD); motorDreapta.run(FORWARD); }
    else if (cmd == 'B') { motorStanga.run(BACKWARD); motorDreapta.run(BACKWARD); }
    else if (cmd == 'S') { motorStanga.run(RELEASE); motorDreapta.run(RELEASE); }
    else if (cmd == 'A') { autonom = true; } // Comanda revenire autonomie
  }

  // 2. Modul Autonom
  bool estePornit = (digitalRead(SWITCH_PIN_1) == LOW);
  int valSenzor = analogRead(PIN_SENSOR);
  unsigned long timp = millis();

  if (estePornit) {
    if (autonom) {
      if (valSenzor > 300) { // OBSTACOL
        seteazaCuloare(0, 0, 255); tone(PIN_BUZZER, 1500, 200);
        motorStanga.run(RELEASE); motorDreapta.run(RELEASE); delay(200);
        motorStanga.run(BACKWARD); motorDreapta.run(BACKWARD); delay(300);
        motorStanga.run(FORWARD); motorDreapta.run(BACKWARD); delay(600);
      } else { // DRUM LIBER
        motorStanga.run(FORWARD); motorDreapta.run(FORWARD);
        if (timp - timpAnterior >= 100) {
          timpAnterior = timp;
          stadiuVerde = !stadiuVerde;
          seteazaCuloare(0, stadiuVerde ? 255 : 0, 0);
        }
      }
    }
  } else { // MOD STOP
    motorStanga.run(RELEASE); motorDreapta.run(RELEASE);
    noTone(PIN_BUZZER);
    if (timp - timpAnterior >= 200) {
      timpAnterior = timp;
      if (indexCuloare == 0) { seteazaCuloare(255, 0, 0); indexCuloare = 1; }
      else if (indexCuloare == 1) { seteazaCuloare(255, 20, 147); indexCuloare = 2; }
      else { seteazaCuloare(128, 0, 128); indexCuloare = 0; }
    }
  }
}