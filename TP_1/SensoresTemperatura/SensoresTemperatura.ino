
// Teste sensor temperatura

// bibliotecas
#include <OneWire.h> //  usada para ler valor do ds18b20 
#include "DHT.h" //  usada para o DHT11



OneWire ds(33);  // A fio de dados está ligado no pin digital 33
DHT dht(37, DHT11); // Pin que esta ligado a comunicação e o tipo de sensor


// variaveis
float temperaturaAgua;
int humidade;
int temperaturaAmbiente;

void setup() 
{
   Serial.begin(9600);

   dht.begin();

}

void loop() 
{
  temperaturaAgua = getTemperaturaAgua();

  humidade = (int)dht.readHumidity();

  temperaturaAmbiente = (int)dht.readTemperature();

  Serial.print("Humidade ambiente: ");
  Serial.print(humidade);
  Serial.print("%\t");
  Serial.print("Temperatura ambiente: ");
  Serial.print(temperaturaAmbiente);
  Serial.print("ºC\t");
  Serial.print("Temperatura água: ");
  Serial.print(temperaturaAgua); 
  Serial.println("ºC");

  

  delay(1000); 
}


// Método que le informação do ds18b20 (sparkfun)
float getTemperaturaAgua()
{

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }

  ds.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;

  return TemperatureSum;
} 
