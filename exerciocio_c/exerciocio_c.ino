
#include <WiFi.h>
#include <WiFiClient.h>


const char* ssid = "NET_2G60E226";
const char* password = "4F60E226";

WiFiServer server(80); //Shield irá receber as requisições das páginas (o padrão WEB é a porta 80)
WiFiClient  client;

String HTTP_req; 
String URLValue;


String getURLRequest(String *requisicao);
bool mainPageRequest(String *requisicao);

const int servomotor1 = 5;
const int servomotor2 = 6;
const int servomotor3 = 10;
const int servomotor4 = 11;
bool estadoserv1 = digitalRead(servomotor1);
bool estadoserv2 = digitalRead(servomotor2);
bool estadoserv3 = digitalRead(servomotor3);


void conexao() {

//Conexão na rede WiFi
    
    Serial.println();
    Serial.print("Conectando a ");
    Serial.println(ssid);

    WiFi.begin(ssid, password); // INICIA WIFI

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi conectado!");

    // Inicia o servidor WEB
    server.begin();
    Serial.println("Server iniciado");

    // Mostra o endereco IP
    Serial.println(WiFi.localIP());
}

void setup(){         
    
    Serial.begin(115200);
    
    conexao();
  
    //Configura o modo dos pinos
    pinMode(servomotor1, OUTPUT);
    pinMode(servomotor2, OUTPUT);
    pinMode(servomotor3, OUTPUT);
    pinMode(servomotor4, OUTPUT);

}

void loop()
{
                    
           
WiFiClient client = server.available();   
if (client) {
          Serial.println("Novo Cliente.");
          String currentLine = "";    
     while (client.connected()) {
          char c = client.read();
          Serial.write(c);
          if (c == '\n') {
                if (currentLine.length() == 0) {
                client.println("HTTP/1.1 200 OK");
                client.println("Content-type:text/html");
                client.println();
                             
                client.println("<!DOCTYPE html>");
                
                client.println("<html>");
                
                client.println("<head>");
                client.println("<title>Arduino via WEB</title>");
                client.println("<link rel='canonical' href= 'https://getbootstrap.com/docs/4.5/examples/checkout/'>");
                client.println("<link href='static/css/assets/dist/css/bootstrap.min.css' rel='stylesheet>");
                client.println("<link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/bootstrap@4.5.3/dist/css/bootstrap.min.css' integrity=sha384-TX8t27EcRE3e/ihU7zmQxVncDAy5uIKz4rEkgIXeMed4M0jlfIDPvg6uqKI2xXr2' crossorigin='anonymous'>");
                client.println( "<link href='https://fonts.googleapis.com/css2?family=Titillium+Web:wght@30'0&di'splay=swap' rel='stylesheet'>");
                client.println("</head>");
               
                client.println("<body style='background: rgb(161, 161, 159);  font-family: 'Titillium Web', sans-serif;>'");
                client.println("<div style='background-color: rgb(127, 161, 116); margin-left: 10%; margin-right: 10%; margin-top: 5%; padding-left: 30%; padding-top: 5%; padding-bottom: 5%;' class='conteiner'>");
                client.println("<h5>PAINEL DE CONTROLE<h5>");
                client.println("<form action='/' method='GET'>");
                client.println("<button type='button' class='btn btn-danger' name='comando' value='1ON'>Liga</button>");
                client.println("<button type='button' class='btn btn-warning' name=' comando' value='2ON'>Desliga</button>");
                client.println("<button type='button' class='btn btn-success' name='comando' value='3ON'>opcional</button>");              
                client.println("</form>");
                client.println("</div>");
                client.println("</body>");
                client.println("</html>");                    
                client.println();
                break;
      
                } else{ 
                currentLine = "";
                }
                } else if (c != '\r') {
                currentLine += c;
                }
      
                if (currentLine.endsWith("GET /1ON")) {
                digitalWrite(servomotor1, HIGH);
                }
                
                if (currentLine.endsWith("GET /2ON")) {
                digitalWrite(servomotor2, HIGH);
                }
                
                if (currentLine.endsWith("GET /3ON")) {
                digitalWrite(servomotor1, HIGH);
                }
                client.stop();
                Serial.println("Cliente desconectado.");
                }
}
}
