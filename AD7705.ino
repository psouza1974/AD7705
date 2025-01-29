#include <SPI.h>
#include <AD770X.h>

/*
Conexões
Arduino Uno         AD7705
===========         ======
5V ---------------- VCC
GND --------------- GND
D9 ---------------- RST
D10 --------------- CS
D13 --------------- SCK
D11 --------------- DIN
D12 --------------- DOUT
D8 ---------------- DRDY
*/

// Configuração da tensão de referência (5V)
AD770X ad7705(5.0);

void setup() {
  Serial.begin(9600);

  // Reinicia o AD7705
  ad7705.reset();

  // Configura o AD7705 no canal AIN1
  ad7705.init(
    AD770X::CHN_AIN1,     // Canal 1 (AIN1+ e AIN1-)
    AD770X::CLK_DIV_1,    // Divisor de clock
    AD770X::BIPOLAR,      // Modo bipolar (-5V a +5V)
    AD770X::GAIN_1,       // Ganho 1x (sem amplificação)
    AD770X::UPDATE_RATE_50 // Taxa de atualização de 50 Hz para maior precisão
  );

  Serial.println("AD7705 inicializado! Pronto para medir -5V a +5V.");
}

void loop() {
  // Verifica continuamente se os dados estão prontos
  if (ad7705.dataReady(AD770X::CHN_AIN1)) {
    // Lê o valor convertido
    double voltage = ad7705.readADResult(AD770X::CHN_AIN1);

    // Exibe o valor lido
    Serial.print("Tensão lida: ");
    Serial.print(voltage, 6); // Mostra 6 casas decimais
    Serial.println(" V");
  } else {
    Serial.println("Aguardando dados...");
  }

  delay(100); // Pequeno atraso para evitar sobrecarga no monitor serial
}
