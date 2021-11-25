#include <TimerOne.h>    //Biblioeca para o temporizador
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


String comando;

String dia="00-00:00";

struct DadosSensor{
  int Numsensor;
  float humid;
  float temperatura;
  String hora[8];     //01-00:00
  };
 
 //funcoes e variais para timmer
 void contahora();
 int segundos=0;
 int minutos=0;
 int horas=0;

 
void setup() { 
    // portabluetooth.begin(9600);
    //SERIAL.println("Teste!");
    Serial.begin(9600);
    dht.begin();
    dht1.begin();
    dht2.begin();
    dht3.begin();
    Serial.println(EEPROM.length());//tamanho da eeprom
    Serial.println("OK");

    //Inicio Timer
    Timer1.initialize(1000000); // 100 segundos  | 1 segundo(1000000)
    Timer1.attachInterrupt(contahora);
    }
 
void loop() {
  float temp_hum_val[2] = {0};
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    
    if(Serial.available()>0){
      comando = Serial.parseInt();
      if (comando ==999){
       Serial.print ("alo");
       escreveString(3,"123456789");
       Serial.println(" String Armazenada: "+leString(3));
     if(!dht.readTempAndHumidity(temp_hum_val)){
        
        DadosSensor sensor1 = {
          1,
          temp_hum_val[0],
          temp_hum_val[1],
          dia
          };
        
        Serial.print(sensor1.humid); 
    }
    else{
       Serial.println("Falha ao ler sensor 01");
    }
        
        } 
      }
   
 
   delay(5000);

}

void contahora(){
  segundos++;
  if(segundos==60){
    minutos++;
    segundos=0;
    }
    if(minutos==60){
      horas++;
      minutos=0;
      }
   Serial.print(horas+":"+minutos);
   Serial.print(":" +segundos);
  }

void escreveString(int enderecoBase, String mensagem){ // Salva a string nos endereços de forma sequencial
  if (mensagem.length()>EEPROM.length() || (enderecoBase+mensagem.length()) >EEPROM.length() ){ // verificamos se a string cabe na memória a partir do endereço desejado
    Serial.println ("A sua String não cabe na EEPROM"); // Caso não caiba mensagem de erro é mostrada
  }
  else{ // Caso seja possível armazenar 
    for (int i = 0; i<mensagem.length(); i++){ 
       EEPROM.write(enderecoBase,mensagem[i]); // Escrevemos cada byte da string de forma sequencial na memória
       enderecoBase++; // Deslocamos endereço base em uma posição a cada byte salvo
    }
    EEPROM.write(enderecoBase,'\0'); // Salvamos marcador de fim da string 
  }
}
String leString(int enderecoBase){
  String mensagem="";
  if (enderecoBase>EEPROM.length()){ // Se o endereço base for maior que o espaço de endereçamento da EEPROM retornamos uma string vazia
    return mensagem;
  }
  else { // Caso contrário, lemos byte a byte de cada endereço e montamos uma nova String
    char pos;
    do{
      pos = EEPROM.read(enderecoBase); // Leitura do byte com base na posição atual
      enderecoBase++; // A cada leitura incrementamos a posição a ser lida
      mensagem = mensagem + pos; // Montamos string de saídaa
    }
    while (pos != '\0'); // Fazemos isso até encontrar o marcador de fim de string
  }
  return mensagem; // Retorno da mensagem
}
