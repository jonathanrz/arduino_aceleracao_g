#include <SoftwareSerial.h>

const int pinoLDR1 = A3;
const int pinoLDR2 = A2;
const int pinoRX = 11;
const int pinoTX = 10;
 //se o sensor mostrar menos de 600, sabemos que não está mais chegando luz do led nele
const int THRESHOLD_PARA_DETECTAR_QUE_A_BOLINHA_PASSOU = 300;

const float DISTANCIA_ENTRE_SENSORES_EM_M = 0.46;

SoftwareSerial bluetooth(pinoRX, pinoTX);

unsigned long tempoQueABolinhaPassouNoLDR1 = 0;
unsigned long tempoQueABolinhaPassouNoLDR2 = 0;

void setup(){
  Serial.begin(115200);
  bluetooth.begin(9600);

  pinMode(pinoLDR1, INPUT);
  pinMode(pinoLDR2, INPUT);
}

void imprime(char* mensagem) {
  Serial.println(mensagem);
  bluetooth.print(mensagem);
}

void loop(){
  const int valorLDR1 = analogRead(pinoLDR1);
  const int valorLDR2 = analogRead(pinoLDR2);

  // bolinha passou pelo sensor 1
  if(tempoQueABolinhaPassouNoLDR1 == 0 && valorLDR1 > THRESHOLD_PARA_DETECTAR_QUE_A_BOLINHA_PASSOU) {
    tempoQueABolinhaPassouNoLDR1 = millis();
    char buffer[40];
    sprintf(buffer, "Tempo no sensor 1: %d\n", tempoQueABolinhaPassouNoLDR1);
    imprime(buffer);
  }

  // bolinha passou pelo sensor 2
  if(tempoQueABolinhaPassouNoLDR1 != 0 && tempoQueABolinhaPassouNoLDR2 == 0 && valorLDR2 > THRESHOLD_PARA_DETECTAR_QUE_A_BOLINHA_PASSOU) {
    tempoQueABolinhaPassouNoLDR2 = millis();
    char buffer[40];
    sprintf(buffer, "Tempo no sensor 2: %d\n", tempoQueABolinhaPassouNoLDR2);
    imprime(buffer);
  }

  if(tempoQueABolinhaPassouNoLDR1 != 0 && tempoQueABolinhaPassouNoLDR2 != 0) {
    float tempoEntreSensoresEmSegundos = (tempoQueABolinhaPassouNoLDR2 - tempoQueABolinhaPassouNoLDR1) / 1000.0;
    float velocidade = tempoEntreSensoresEmSegundos / DISTANCIA_ENTRE_SENSORES_EM_M;

    char bufferTempo[10];
    dtostrf(tempoEntreSensoresEmSegundos, 1, 2, bufferTempo);
    char bufferVelocidade[10];
    dtostrf(velocidade, 1, 2, bufferVelocidade);

    char buffer[100];
    sprintf(buffer, "Velocidade: %s m/s - Tempo: %s s\n", bufferVelocidade, bufferTempo);
    imprime(buffer);

    tempoQueABolinhaPassouNoLDR1 = 0;
    tempoQueABolinhaPassouNoLDR2 = 0;
  }
}

// Cabos
// Vermelho vai na de 3.3v
// Azul e preto vão na GND
// Marrom vai na 5v
// Verde vai na A2
// Amarelo vai na A3
// Branco vai na 10
// Cinza vai na 11
