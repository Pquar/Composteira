
#include "DHT.h" //biblioteca do sensor de humidade e temperatura
#include <SoftwareSerial.h> //Emulador de porta TX e RX para portas digitais

//definindo os pinos digitais para RX,TX
SoftwareSerial portabluetooth(8,9);
//String command = "";
//pinos que estao sendo usados
#define DHTPIN  2
#define DHTPIN1 3
#define DHTPIN2 4
#define DHTPIN3 5

#define DHTTYPE DHT22
#define DHTTYPE1 DHT22
#define DHTTYPE2 DHT22
#define DHTTYPE3 DHT22

DHT dht(DHTPIN, DHTTYPE);
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
DHT dht3(DHTPIN3, DHTTYPE);


#if defined(ARDUINO_ARCH_AVR)
#define SERIAL  Serial

#elif defined(ARDUINO_ARCH_SAMD) ||  defined(ARDUINO_ARCH_SAM)
#define SERIAL  SerialUSB
#else
#define SERIAL  Serial
#endif

void setup() {
  SERIAL.begin(9600); 
  portabluetooth.begin(9600);
    SERIAL.println("Teste!");
    
    dht.begin();
    dht1.begin();
    dht2.begin();
    dht3.begin();
}

void loop() {
  float temp_hum_val[2] = {0};
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    
    //Primeiro sensor
    if(!dht.readTempAndHumidity(temp_hum_val)){
        SERIAL.print("Sensor: 01 ");
        SERIAL.print("Humidade: "); 
        SERIAL.print(temp_hum_val[0]);
        SERIAL.print(" %\t");
        SERIAL.print("Temperatura: "); 
        SERIAL.print(temp_hum_val[1]);
        SERIAL.println(" *C");
    }
    else{
       SERIAL.println("Falha ao ler sensor 01");
    }
    //Segundo sensor
    if(!dht1.readTempAndHumidity(temp_hum_val)){
        SERIAL.print("Sensor02 ");
        SERIAL.print("Humidade: "); 
        SERIAL.print(temp_hum_val[0]);
        SERIAL.print(" %\t");
        SERIAL.print("Temperatura: "); 
        SERIAL.print(temp_hum_val[1]);
        SERIAL.println(" *C");
    }
    else{
       SERIAL.println("Falha ao ler sensor 02");
    }
    //Terceiro sensor
    if(!dht2.readTempAndHumidity(temp_hum_val)){
        SERIAL.print("Sensor03 ");
        SERIAL.print("Humidade: "); 
        SERIAL.print(temp_hum_val[0]);
        SERIAL.print(" %\t");
        SERIAL.print("Temperatura: "); 
        SERIAL.print(temp_hum_val[1]);
        SERIAL.println(" *C");
    }
    else{
       SERIAL.println("Falha ao ler sensor 03");
    }
    //Quarto sensor
    if(!dht3.readTempAndHumidity(temp_hum_val)){
        SERIAL.print("Sensor04 ");
        SERIAL.print("Humidade: "); 
        SERIAL.print(temp_hum_val[0]);
        SERIAL.print(" %\t");
        SERIAL.print("Temperatura: "); 
        SERIAL.print(temp_hum_val[1]);
        SERIAL.println(" *C");
    }
    else{
       SERIAL.println("Falha ao ler sensor 04");
    }

   delay(5000);

}
