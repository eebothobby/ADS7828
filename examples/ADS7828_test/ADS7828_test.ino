#include <ADS7828.h>

ADS7828 adc;

void setup()
{
  // Initialize I2C communication as MASTER
  Wire.begin();
  Wire.setClock(400000L);
  adc.begin(0);
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
