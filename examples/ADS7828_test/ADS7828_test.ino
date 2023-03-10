#include <ADS7828.h>

// If using an I2C bus that is different from default Wire,
// for example SDA2 = PB3, SCL2 = PB10 on STM32F411-based "black pill"
// TwoWire Wire2(PB3, PB10);

ADS7828 adc;

void setup()
{
  // Initialize I2C communication as MASTER
  Wire.begin();
  Wire.setClock(400000L);
  
  // If using Wire2
  // Wire2.begin();
  // Wire2.setClock(400000L);
  
  adc.begin(0);
  
  // If using Wire2
  // adc.begin(0, &Wire2);

  Serial.begin(115200);
  delay(300);
}

void loop()
{
    int adcData[8];
    for (int channel = 0; channel < 8; channel++) {
      adcData[channel] = adc.read(channel);
      Serial.print(adcData[channel]); Serial.print(" ");
    }
    Serial.println();
}
