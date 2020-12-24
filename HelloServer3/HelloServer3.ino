#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* ssid = "NET_2G60E226";
const char* password = "4F60E226";

WiFiServer server(80); //Shield irá receber as requisições das páginas (o padrão WEB é a porta 80)

String HTTP_req; 
String URLValue;

   
String getURLRequest(String *requisicao);
bool mainPageRequest(String *requisicao);

const byte qtdePinosDigitais = 8;
byte pinosDigitais[qtdePinosDigitais] = {2    , 3      , 4     , 5     ,   12     , 13     , 14     , 15     };
byte modoPinos[qtdePinosDigitais]     = {OUTPUT, OUTPUT ,OUTPUT, OUTPUT,   OUTPUT, OUTPUT, OUTPUT, OUTPUT};

const byte qtdePinosAnalogicos = 1;
byte pinosAnalogicos[qtdePinosAnalogicos] = {A0};

void setup()
{         
    Serial.begin(115200);

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

    //Configura o modo dos pinos
    for (int nP=0; nP < qtdePinosDigitais; nP++) {
        pinMode(pinosDigitais[nP], modoPinos[nP]);
    }
}

void loop()
{

    WiFiClient  client = server.available();

    if (client) { 
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) { 
                char c = client.read(); 
                HTTP_req += c;  
                
                if (c == '\n' && currentLineIsBlank ) { 

                    if ( mainPageRequest(&HTTP_req) ) {
                        URLValue = getURLRequest(&HTTP_req);
                        Serial.println(HTTP_req);
                                                 
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-Type: text/html");
                        client.println("Connection: keep-alive");              //<------ ATENCAO
                        client.println();
                        
                        //Conteudo da Página HTML
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

                    
                    } else if (HTTP_req.indexOf("solicitacao_via_ajax") > -1) {     //<----- NOVO

                        Serial.println(HTTP_req);

                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-Type: text/html");
                        client.println("Connection: keep-alive");      
                        client.println();                      

                            
                    } else {

                        Serial.println(HTTP_req);
                        client.println("HTTP/1.1 200 OK");
                    }
                    HTTP_req = "";    
                    break;
                }
                
                if (c == '\n') {
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    currentLineIsBlank = false;
                }
            }
        } 
        delay(1);     
        client.stop(); 
    } 
}


String getURLRequest(String *requisicao) {
int inicio, fim;
String retorno;

  inicio = requisicao->indexOf("GET") + 3;
  fim = requisicao->indexOf("HTTP/") - 1;
  retorno = requisicao->substring(inicio, fim);
  retorno.trim();

  return retorno;
}

bool mainPageRequest(String *requisicao) {
String valor;
bool retorno = false;

  valor = getURLRequest(requisicao);
  valor.toLowerCase();

  if (valor == "/") {
     retorno = true;
  }

  if (valor.substring(0,2) == "/?") {
     retorno = true;
  }  

  if (valor.substring(0,10) == "/index.htm") {
     retorno = true;
  }  

  return retorno;
}
