//Carrega a biblioteca do display de LCD
#include <LiquidCrystal.h>

const int pinoLDR1 = A3;
const int pinoLDR2 = A2;
 //se o sensor mostrar menos de 600, sabemos que não está mais chegando luz do led nele
const int THRESHOLD_PARA_DETECTAR_QUE_A_BOLINHA_PASSOU = 600;

const float DISTANCIA_ENTRE_SENSORES_EM_M = 0.46;

// LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int tempoQueABolinhaPassouNoLDR1 = 0;
int tempoQueABolinhaPassouNoLDR2 = 0;

void setup(){
  Serial.begin(9600);

  pinMode(pinoLDR1, INPUT);
  pinMode(pinoLDR2, INPUT);

  // lcd.begin(16, 2);
}

void loop(){
  const int valorLDR1 = analogRead(pinoLDR1);
  const int valorLDR2 = analogRead(pinoLDR2);

  // bolinha passou pelo sensor 1
  if(tempoQueABolinhaPassouNoLDR1 == 0 && valorLDR1 > THRESHOLD_PARA_DETECTAR_QUE_A_BOLINHA_PASSOU) {
    tempoQueABolinhaPassouNoLDR1 = millis();
  }

  // bolinha passou pelo sensor 2
  if(tempoQueABolinhaPassouNoLDR1 != 0 && tempoQueABolinhaPassouNoLDR2 == 0 && valorLDR2 > THRESHOLD_PARA_DETECTAR_QUE_A_BOLINHA_PASSOU) {
    tempoQueABolinhaPassouNoLDR2 = millis();
  }

  if(tempoQueABolinhaPassouNoLDR1 != 0 && tempoQueABolinhaPassouNoLDR2 != 0) {
    float tempoEntreSensoresEmSegundos = (tempoQueABolinhaPassouNoLDR2 - tempoQueABolinhaPassouNoLDR1) / 1000.0;
    float velocidade = DISTANCIA_ENTRE_SENSORES_EM_M / tempoEntreSensoresEmSegundos;
    Serial.println("PASSOU");
    Serial.println(tempoQueABolinhaPassouNoLDR1);
    Serial.println(tempoQueABolinhaPassouNoLDR2);
    Serial.println(tempoEntreSensoresEmSegundos);
    Serial.println(velocidade);
    Serial.println("-----------------------");

    tempoQueABolinhaPassouNoLDR1 = 0;
    tempoQueABolinhaPassouNoLDR2 = 0;
  }

  // if(tempoQueABolinhaPassouNoLDR1 != 0 && tempoQueABolinhaPassouNoLDR2 != 0) {
  //   const int diff = tempoQueABolinhaPassouNoLDR2 - tempoQueABolinhaPassouNoLDR1;

  //   lcd.clear();
  //   lcd.setCursor(0, 0);
  //   lcd.print("TEMPO (em ms)");
  //   lcd.setCursor(0, 1);
  //   lcd.print(diff);
  //   delay(15000);
  // }
}

// Cabos
// Vermelho vai na de 3.3v
// Azul e preto vão na GND
// Marrom vai na 5v
// Verde vai na A2
// Amarelo vai na A3
