
#include"Config.h"
//Wifi 
const char* ssid = "Status-Monitor";
const char* password = "password123"; 

//WebSocket
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

//Retrieve files
void getWebsite(){
    // Initialize LittleFS
    if (!LittleFS.begin(true)) { 
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
    Serial.println("LittleFS mounted successfully.");
        // Serve HTML, CSS, and JS files from LittleFS
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){//lambda
        request->send(LittleFS, "/index.html", "text/html");
    });
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/style.css", "text/css");
    });
    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/script.js", "text/javascript");
    });
}

//WebSocket Actions
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
                
    if (type == WS_EVT_CONNECT) {
        Serial.printf("WebSocket client #%u connected\n", client->id());
        DebugStatus.broadcastStatus(String(ws.count()));
    } else if (type == WS_EVT_DISCONNECT) {
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        DebugStatus.broadcastStatus(String(ws.count()));
    }
}

//Start the main server
void StartWSServer(){

    ws.onEvent(onEvent);
    server.addHandler(&ws);
    server.begin();
    Serial.println("[success]::[SERVER STARTED]");
}

void StartWiFiAP(const char* name,const char* lock){
        // Start SoftAP
    WiFi.softAP(name,lock);
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());
    WiFi.setTxPower(WIFI_POWER_8_5dBm);
}

void WaitForMe(){
    while(ws.count()==0){Serial.print("<+=+>");delay(1000);}
}