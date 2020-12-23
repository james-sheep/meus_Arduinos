

#include <HTTPClient.h>
#include <WiFi.h>      //ESP32 Core WiFi Library    
#include <WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h> 
WiFiManager wifiManager; //declaração do objeto wifiManager


void setup() {

Serial.begin(115200); 
Serial.println();


wifiManager.setAPCallback(configModeCallback);  //callback para quando entra em modo de configuração AP
   
wifiManager.setSaveConfigCallback(saveConfigCallback);  //callback para quando se conecta em uma rede, ou seja, quando passa a trabalhar em modo estação

wifiManager.autoConnect("ESP_AP", "12345678");  //cria uma rede de nome ESP_AP com senha 12345678

Serial.print("Connected to ");

Serial.print("IP address: ");
Serial.println(WiFi.localIP());
  
 
}

void loop() {



}

// SEÇAO DE CALLBACK 

      // que indica que o ESP entrou no modo AP

void configModeCallback (WiFiManager *myWiFiManager) {  
  Serial.println("Entrou no modo de configuração");
  Serial.println(WiFi.softAPIP()); //imprime o IP do AP
  Serial.println(myWiFiManager->getConfigPortalSSID()); //imprime o SSID criado da rede

}

// Informa que foi salva a configuraçao de rede;

void saveConfigCallback () {
  Serial.println("Configuração salva");
}
