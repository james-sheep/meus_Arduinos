#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* ssid = "NET_2G60E226";
const char* password = "4F60E226";

WiFiServer server(80); //Shield irá receber as requisições das páginas (o padrão WEB é a porta 80)

String HTTP_req; 
String URLValue;

void processaPorta(byte porta, byte posicao, WiFiClient cl);
void lePortaDigital(byte porta, byte posicao, WiFiClient cl);        
void lePortaAnalogica(byte porta, byte posicao, WiFiClient cl);   
String getURLRequest(String *requisicao);
bool mainPageRequest(String *requisicao);

const byte qtdePinosDigitais = 7;
byte pinosDigitais[qtdePinosDigitais] = {2           , 4     , 5     ,   12     , 13     , 14     , 15     };
byte modoPinos[qtdePinosDigitais]     = {INPUT_PULLUP, OUTPUT, OUTPUT,   OUTPUT, OUTPUT, OUTPUT, OUTPUT};

const byte qtdePinosAnalogicos = 1;
byte pinosAnalogicos[qtdePinosAnalogicos] = {A0};
WiFiClient  client;
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
client.println("<h1>PORTAS EM FUN&Ccedil;&Atilde;O ANAL&Oacute;GICA</h1>");

for (int nL=0; nL < qtdePinosAnalogicos; nL++) {

    client.print("<div id=\"pino");                         //<----- NOVO
    client.print(pinosAnalogicos[nL]);
    client.print("\">"); 
                                 
    client.print("Porta ");
    client.print(pinosAnalogicos[nL]);
    client.println(" - Valor: ");
       
    client.print( analogRead(pinosAnalogicos[nL]) );
    client.println("</div>");                               //<----- NOVO
       
    client.println("<br/>");                             
}

client.println("<br/>");                        
client.println("<h1>PORTAS EM FUN&Ccedil;&Atilde;O DIGITAL</h1>");
client.println("<form method=\"get\">");

for (int nL=0; nL < qtdePinosDigitais; nL++) {
    processaPorta(pinosDigitais[nL], nL, client);
    client.println("<br/>");
}

client.println("<br/>");
client.println("<button type=\"submit\">Envia para o Esp 32</button>");
client.println("</form>");
                
client.println("<H2> Estado das Portas</H2>");
client.println("Porta n.04:");
client.println( digitalRead(4));
client.println("<br/>");
client.println("Porta n.05:");
client.println( digitalRead(5));
client.println("<br/>");
client.println("Porta n.12:");
client.println( digitalRead(12));
client.println("<br/>");
client.println("Porta n.13:");
client.println( digitalRead(13));



client.println("<div style='background-color: rgb(127, 161, 116); margin-left: 10%; margin-right: 10%; margin-top: 5%; padding-left: 30%; padding-top: 5%; padding-bottom: 5%;' class='conteiner'>");
client.println("<form action='/' method='post'>");
client.println("<h5>DEVICE 1<h5>");
client.println("<button type='button' class='btn btn-danger' name='comando' value='1ON'>Liga</button>");
client.println("<button type='button' class='btn btn-warning' name=' comando' value='1OFF'>Desliga</button>");
client.println("<button type='button' class='btn btn-success'>opcional</button>");
               
client.println("</form>");
client.println("</div>");

client.println("</body>");

client.println("</html>");

                        

                    
                    } else if (HTTP_req.indexOf("solicitacao_via_ajax") > -1) {     //<----- NOVO

                        Serial.println(HTTP_req);

                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-Type: text/html");
                        client.println("Connection: keep-alive");      
                        client.println();                      

                        for (int nL=0; nL < qtdePinosAnalogicos; nL++) {
                            lePortaAnalogica(pinosAnalogicos[nL], nL, client);                            
                        }
                        for (int nL=0; nL < qtdePinosDigitais; nL++) {
                            lePortaDigital(pinosDigitais[nL], nL, client);
                        }
                            
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
