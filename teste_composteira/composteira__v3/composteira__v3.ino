#include "DHT.h" //biblioteca do sensor de humidade e temperatura
#include <SoftwareSerial.h> //Emulador de porta TX e RX para portas digitais
#include <EEPROM.h>       //memoria

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


int comando;

int dia=1;

struct DadosSensor{
  int Numsensor;
  float humid;
  float temperatura;
  };
 //funcoes e variais para timmer
 void contahora();
 int segundos=0;
 int minutos=0;
 int horas=0;

// Variavel inteira (2 bytes - 16bits) para definir a posição inicial
      int posicao = 2;
 
void setup() { 
    // portabluetooth.begin(9600);
    //SERIAL.println("Teste!");
    Serial.begin(9600);
    dht.begin();
    dht1.begin();
    dht2.begin();
    dht3.begin();
    Serial.println("ok-1");


     // Grava no endereço 0 e 1, pois a variavel int ocupa 2 bytes
     EEPROM.put(0, posicao);
   // Serial.print("Read float from EEPROM: ");

     //float f = 0.00f;   //Variable to store data read from EEPROM.

    //  int eeAddress = 3; //EEPROM address to start reading from
     // EEPROM.get(eeAddress, f);
    // Serial.println(f, 3); 
    }
 
void loop() {
 if (dia<03){
  //cronometro
  segundos++;
  if(segundos==60){
    minutos++;
    segundos=0;
    }
    if(minutos==60){
      horas++;
      minutos=0;
      }
      if(minutos==1){
        sensores();
        }
        if (horas==25){
          horas=0;
          dia++;
          }
      //chama sensores
      if(minutos==1){
      sensores();
      }
      
      //comandos serial
      if(Serial.available()>0){
      comando = Serial.parseInt();
      if (comando ==1){
        sensores();
        }
        if ( comando==2){
          tempo();
          }
      }
delay(1000);  
 }
 
 if (dia>03){
  Serial.print("Memoria lotada");
  delay(2000);
  }
 /*  for(int i=0;i<EEPROM.length();i++){
      Serial.print(i);
      Serial.print("=");
      Serial.println(EEPROM.read(i));
      delay(500);
      }
      */


}

void tempo(){
  if(horas<10){
    Serial.print("0");
    Serial.print(horas);
    }else{
      Serial.print(horas);
      }
   Serial.print(":");
   if (minutos<10){
    Serial.print("0");
    Serial.print(minutos);
    }else{
      Serial.print(minutos);
      }
   Serial.print(":");
    if (segundos<10){
    Serial.print("0");
    Serial.print(segundos);
    }else{
      Serial.print(segundos);
      }
   }
  
void sensores(){
  float temp_hum_val[2] = {0};
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
     Serial.println ("chamada sensores");
     
     if(!dht.readTempAndHumidity(temp_hum_val)){   
        DadosSensor sensor1 = {
          1,
          temp_hum_val[0],
          temp_hum_val[1]
          };
        sensor1.humid = map(sensor1.humid, 0, 1023, 0, 255);
     //humidade
          posicaoa();
          tempo();
          Serial.print(" |Dia: ");
          Serial.print(dia);
          Serial.print(" ||Sensor: ");
          Serial.print(sensor1.Numsensor);
          sensor1.humid = map(sensor1.humid, 0, 1023, 0, 255);
          Serial.print(" |H% ");
          EEPROM.update(posicao, sensor1.humid); 
          Serial.print(EEPROM.read(posicao));
          Serial.print(".");
          Serial.print(EEPROM.read(posicao+1));
          //temperatura
          posicaoa();
          sensor1.humid = map(sensor1.temperatura, 0, 1023, 0, 255);
          Serial.print(" |Cº ");
          EEPROM.update(posicao, sensor1.temperatura); 
          Serial.print(EEPROM.read(posicao));
          Serial.print(".");
          Serial.print(EEPROM.read(posicao+1));
    }
    else{
       Serial.println("Falha ao ler sensor 01");
    }
    //sensor 2
    if(!dht1.readTempAndHumidity(temp_hum_val)){   
        DadosSensor sensor2 = {
          2,
          temp_hum_val[0],
          temp_hum_val[1]
          };
          Serial.print(" ||Sensor: ");
          Serial.print(sensor2.Numsensor);
          sensor2.humid = map(sensor2.humid, 0, 1023, 0, 255);
          Serial.print(" |H% ");
          EEPROM.update(posicao, sensor2.humid); 
          Serial.print(EEPROM.read(posicao));
          Serial.print(".");
          Serial.print(EEPROM.read(posicao+1));
          //temperatura
          posicaoa();
          sensor2.humid = map(sensor2.temperatura, 0, 1023, 0, 255);
          Serial.print(" |Cº ");
          EEPROM.update(posicao, sensor2.temperatura); 
          Serial.print(EEPROM.read(posicao));
          Serial.print(".");
          Serial.print(EEPROM.read(posicao+1));
    }
    else{
       Serial.println("Falha ao ler sensor 02");
    }
    //sensor 3
    if(!dht2.readTempAndHumidity(temp_hum_val)){   
        DadosSensor sensor3 = {
          3,
          temp_hum_val[0],
          temp_hum_val[1]
          };
          Serial.print(" ||Sensor: ");
          Serial.print(sensor3.Numsensor);
          sensor3.humid = map(sensor3.humid, 0, 1023, 0, 255);
          Serial.print(" |H% ");
          EEPROM.update(posicao, sensor3.humid); 
          Serial.print(EEPROM.read(posicao));
          Serial.print(".");
          Serial.print(EEPROM.read(posicao+1));
          //temperatura
          posicaoa();
          sensor3.humid = map(sensor3.temperatura, 0, 1023, 0, 255);
          Serial.print(" |Cº ");
          EEPROM.update(posicao, sensor3.temperatura); 
          Serial.print(EEPROM.read(posicao));
          Serial.print(".");
          Serial.print(EEPROM.read(posicao+1));
    }
    else{
       Serial.println("Falha ao ler sensor 03");
    }
    //sensor 4
    if(!dht3.readTempAndHumidity(temp_hum_val)){   
        DadosSensor sensor4 = {
          4,
          temp_hum_val[0],
          temp_hum_val[1]
          };
          Serial.print(" ||Sensor: ");
          Serial.print(sensor4.Numsensor);
          sensor4.humid = map(sensor4.humid, 0, 1023, 0, 255);
          Serial.print(" |H% ");
          EEPROM.update(posicao, sensor4.humid); 
          Serial.print(EEPROM.read(posicao));
          Serial.print(".");
          Serial.print(EEPROM.read(posicao+1));
          //temperatura
          posicaoa();
          sensor4.humid = map(sensor4.temperatura, 0, 1023, 0, 255);
          Serial.print(" |Cº ");
          EEPROM.update(posicao, sensor4.temperatura); 
          Serial.print(EEPROM.read(posicao));
          Serial.print(".");
          Serial.print(EEPROM.read(posicao+1));
          
    }
    else{
       Serial.println("Falha ao ler sensor 04");
        
    }
         // noInterrupts();
         // interrupts();
      for (int x = 0; x==0;) {
        break;
      }
      
        }

void posicaoa(){
          posicao++;
          posicao++;
          if (posicao<255){
             posicao++;
            }else{
              posicao=1;
              }

              return posicao;
          }

         
