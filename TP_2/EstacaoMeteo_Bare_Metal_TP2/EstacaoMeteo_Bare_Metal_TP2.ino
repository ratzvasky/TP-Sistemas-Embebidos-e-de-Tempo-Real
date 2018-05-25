/*
    Estação metereologica
    UC - Sistemas Embebidos e de Tempo Real (ESI)

    Rúben Guimarães nº11156
    Kyrylo Yavorenko nº10355

    Implementação em BareMetal
*/


// Bibliotecas usadas
#include <OneWire.h> //  usada para ler valor do ds18b20 
#include "DHT.h" //  usada para o DHT11
#include <Wire.h>
#include <Adafruit_BMP085.h> // usada para o BMP180
#include <LiquidCrystal_I2C.h> // usada para o lcd


#define Sensor_Temp 37 // DHT11
#define Sensor_Temp_2 33 // DS18B20
#define Sensor_Agua 41
#define Buzzer 45
#define IR A0
#define LDR1 A1
#define LDR2 A2
#define LDR3 A3


// Declaração de objectos
OneWire ds(Sensor_Temp_2);
DHT dht(Sensor_Temp, DHT11);
Adafruit_BMP085 bmp180;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Inicializa o display no endereco 0x27


// Declaração de variaveis globais
uint8_t humidade;
uint8_t temperaturaAmbiente;
float temperaturaAgua;
float temperaturaAmbienteBMP;
uint16_t  pressaoAtmosferica;
int  altitude;
uint8_t velocidadeVento;
boolean valorSensorAgua;
int ldrValue1;
int ldrValue2;
int ldrValue3;
int tempoDelay = 1000;



// Inicializa objectos e define pin's de entrada/saida
void setup()
{
  Serial.begin(9600);

  dht.begin();
  bmp180.begin();
  lcd.begin (16, 2);

  pinMode(Sensor_Agua, INPUT);
  pinMode(Buzzer, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print(F("A ler Sensores.."));
}


// Ciclo que vai correr o programa
void loop()
{

  getSensorValues();


  printDataString();


  showValuesLCD();


  delay(tempoDelay);
}


// Método que vai mostar no LCD os valores lidos pelos sensores
void showValuesLCD()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Temp. Amb."));
  lcd.setCursor(0, 1);
  lcd.print(String(temperaturaAmbiente) + String((char)223) + String(F(" C")));


  delay(tempoDelay);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Humidade Ambi."));
  lcd.setCursor(0, 1);
  lcd.print(String(humidade) + String(F(" %")));

  delay(tempoDelay);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Temp. Ambi. 2"));
  lcd.setCursor(0, 1);
  lcd.print(String(temperaturaAmbienteBMP) + String((char)223) + String(" C"));


  delay(tempoDelay);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Temp. agua"));
  lcd.setCursor(0, 1);
  lcd.print(String(temperaturaAgua) + String((char)223) + String(" C"));

  delay(tempoDelay);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("P. Atmosferica"));
  lcd.setCursor(0, 1);
  lcd.print(String(pressaoAtmosferica) + String(" Pa"));

  delay(tempoDelay);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Altitude"));
  lcd.setCursor(0, 1);
  lcd.print(altitude);
  lcd.print(" m");

  delay(tempoDelay);


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Agua no sensor?"));
  lcd.setCursor(0, 1);

  if ( valorSensorAgua == LOW)
    lcd.print(F("Nao!"));
  else  // Se detectar agua
    lcd.print(F("Sim!"));

  delay(tempoDelay);


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Velocidade vento"));
  lcd.setCursor(0, 1);
  lcd.print(String(velocidadeVento) + String(" RPM"));


  delay(tempoDelay);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Posicao sol"));
  lcd.setCursor(0, 1);

  if  ( ldrValue1 < ldrValue2 && ldrValue1 < ldrValue3)
    lcd.print(F("Este"));

  if ( ldrValue2 < ldrValue1 && ldrValue2 < ldrValue3)
    lcd.print(F("Sul"));

  if ( ldrValue3 < ldrValue1 && ldrValue3 < ldrValue2)
    lcd.print(F("Oeste"));
}



// Método que vai receber informaçãor dos diferentes sensores
void getSensorValues()
{
  temperaturaAgua = getTemperaturaAgua();

  humidade = (int)dht.readHumidity();

  temperaturaAmbiente = (int)dht.readTemperature();

  temperaturaAmbienteBMP = bmp180.readTemperature();

  pressaoAtmosferica = bmp180.readPressure();

  //altitude = bmp180.readAltitude(100600); // 100600 pressao atmosferica media ao nivel do mar no porto (para efeitos de calibração)
  altitude = bmp180.readAltitude();

  valorSensorAgua = digitalRead(Sensor_Agua);

  velocidadeVento = ((getWindSpeed() * 60) / 5); // Recebe uma contagem e efetua uma regra de 3 simples para calcular uma estimativa das RPM's do vento

  ldrValue1 = analogRead(LDR1);
  ldrValue2 = analogRead(LDR2);
  ldrValue3 = analogRead(LDR3);
}


/*
  // Método que imprime os valores enviados para a porta de comunicação na consola
  void printValuesOnConsole()
  {
  Serial.println(F(" *** Valores Lidos ***"));

  Serial.print(F("Humidade ambiente: "));
  Serial.print(humidade);
  Serial.println(F("%\t"));

  Serial.print(F("Temperatura ambiente: "));
  Serial.print(temperaturaAmbiente);
  Serial.println(F("ºC\t"));

  Serial.print(F("Temperatura água: "));
  Serial.print(temperaturaAgua);
  Serial.println(F("ºC\t"));

  Serial.print(F("Temperatura BMP: "));
  Serial.print(temperaturaAmbienteBMP);
  Serial.println(F("ºC\t"));

  Serial.print(F("Pressão atmosferica: "));
  Serial.print(pressaoAtmosferica);
  Serial.println(F("Pa\t"));

  Serial.print(F("Altitude: "));
  Serial.print(altitude);
  Serial.println(F("m"));

  Serial.print(F("Água no sensor ? "));
  if ( valorSensorAgua == LOW)
    Serial.println(F(" Não!"));

  else  // Se detectar agua
  {
    Serial.println(F("Sim!"));
    beep();
  }

  Serial.print(F("Velocidade vento: "));
  Serial.print(velocidadeVento);
  Serial.println(F(" RPM"));


  Serial.print(F("Posição do sol: "));
  if  ( ldrValue1 < ldrValue2 && ldrValue1 < ldrValue3)
    Serial.println(F("Este"));

  if ( ldrValue2 < ldrValue1 && ldrValue2 < ldrValue3)
    Serial.println(F("Sul"));

  if ( ldrValue3 < ldrValue1 && ldrValue3 < ldrValue2)
    Serial.println(F("Oeste"));

  }

*/

// Método que vai imprimir na consola uma string com os dados dos sensores para ler lido pelo qt
void printDataString()
{
  String trama;
  String posicaoSol;

  if  ( ldrValue1 < ldrValue2 && ldrValue1 < ldrValue3)
    posicaoSol = "Este";

  if ( ldrValue2 < ldrValue1 && ldrValue2 < ldrValue3)
    posicaoSol = "Sul";

  if ( ldrValue3 < ldrValue1 && ldrValue3 < ldrValue2)
    posicaoSol = "Oeste";

  // Constroi a string com os dados
  trama = String(humidade) + ";" + String(temperaturaAmbiente)  + ";" + String(temperaturaAgua)  + ";" + String(temperaturaAmbienteBMP)  + ";" + String(pressaoAtmosferica)
          + ";" + String(altitude)  + ";" + String(valorSensorAgua)  + ";" + String(velocidadeVento)  + ";" + posicaoSol + ";";

  Serial.println(trama);
}



// Método que vai fazer com que o buzzer ligado a porta emita um beep
void beep()
{
  digitalWrite(45, HIGH);
  delay(50);
  digitalWrite(45, LOW);
}


// Método que vai ler a velocidade do vento durante 5 segundos
uint8_t getWindSpeed()
{
  uint8_t contador = 0;
  uint8_t aux;

  int valorSensor;

  long starttime = millis();
  long endtime = starttime;

  while ((endtime - starttime) <= 5000)
  {
    valorSensor = analogRead(IR);

    if (valorSensor > 800) // usada para evitar a mesma leitura
      aux = 0;

    if (valorSensor < 800 && aux == 0) // Se a flag tiver sido limpa e o valor do sensor for inferior ao threshold
    {
      contador++;
      aux = 1;
    }

    delay(50);
    endtime = millis();
  }

  return contador;
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
  ds.write(0x44, 1); // start conversion, with parasite power on at the end

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
