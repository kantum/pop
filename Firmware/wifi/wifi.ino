#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#define HOST "vps416438.ovh.net"

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
    WiFi.setAutoConnect(false);
}

unsigned long stp = 0;
typedef unsigned char byte;
void loop() {
  if (Serial.available()) {
    byte rd = Serial.read();
    if (stp < 3) {
      if (rd == '!') {
        stp++;
        return;
      }
    }
    if (stp == 3) {
      if (rd == 'S') Serial.print("O");
      if (rd == 'C') connectWifi();
      if (rd == 'U') updateList();
      if (rd == 'O') orderElement();
      if (rd == 'L') scanNets();
      if (rd == 'D') disconnectWifi();
    }
    stp = 0;
  }
}

void error(void) {
  Serial.print("E");
}

void disconnectWifi(void) {
  if (WiFi.isConnected()) {
  do {
      WiFi.disconnect(false); 
      delay(100);
    } while (WiFi.isConnected());
  }
  Serial.print("O");
}

void connectWifi(void) {
  while (!Serial.available());
  if (Serial.read() != '?') return (error());
  byte rd = 0x00;
  char ssid[20];
  char pass[20];
  int i = 0;
  while (i < 19) {
    while (!Serial.available());
    rd = Serial.read();
    if (rd == '~') break;
    ssid[i++] = rd;
  }
  ssid[i] = 0x00;
  i = 0;
  while (i < 19) {
    while (!Serial.available());
    rd = Serial.read();
    if (rd == '~') break;
    pass[i++] = rd;
  }
  pass[i] = 0x00;
  WiFi.begin(ssid, pass);
  if (WiFi.waitForConnectResult() == WL_CONNECTED)
    Serial.print("O");
  else
    return (error());
}

void updateList(void) {
  // Use WiFiClientSecure class to create TLS connection
  WiFiClient client;
  if (!client.connect(HOST, 80)) {
    return (error());
  }
  client.print(String("GET ") + "/?q=update" + " HTTP/1.1\r\n" +
               "Host: " + HOST + "\r\n" +
               "Connection: close\r\n\r\n");
  
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") { break; }
  }
  String line = client.readStringUntil('\n');
  Serial.println(line);
}

void orderElement(void) {
  // Use WiFiClientSecure class to create TLS connection
  while (!Serial.available());
  if (Serial.read() != '?') return (error());
  char id[5];
  byte rd;
  int i = 0;
  while (i < 4) {
    while (!Serial.available());
    rd = Serial.read();
    if (rd == '~') break;
    id[i++] = rd;
  }
  id[i] = 0x00;
  
  WiFiClient client;
  if (!client.connect(HOST, 80)) {
    return (error());
  }
  client.print(String("GET ") + "/?q=order&id=" + id + " HTTP/1.1\r\n" +
               "Host: " + HOST + "\r\n" +
               "Connection: close\r\n\r\n");
  
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") { break; }
  }
  String line = client.readStringUntil('\n');
  Serial.println(line);
}

String encryptionTypeStr(uint8_t authmode) {
    switch(authmode) {
        case ENC_TYPE_NONE:
            return "O";
        case ENC_TYPE_WEP:
            return "P";
        case ENC_TYPE_TKIP:
            return "P";
        case ENC_TYPE_CCMP:
            return "P";
        case ENC_TYPE_AUTO:
            return "P";
        default:
            return "U";
    }
}

byte  calcStrength(size_t val, size_t bst, size_t wst) {
val *= -1;
bst *= -1;
wst *= -1;
wst -= bst;
val -= bst;
switch((int)(((float) val / (float) wst) * 5)) {
  case 0:
    return '5';
  case 1:
    return '4';
   case 2:
    return '3';
   case 3:
    return '2';
   case 4:
    return '1';
    case 5:
      return '0';
}
}

void  scanNets(void) {
//  Serial.println("scan start");
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks(false,false);
  //  Serial.println("scan done");
  int o = n;
  int loops = 0;
  
  if (n == 0)
    return(error());
  else
  {
    // sort by RSSI
    int indices[n];
    int skip[n];
    
    String ssid;
    
    for (int i = 0; i < n; i++) {
      indices[i] = i;
    }

    // CONFIG
    bool sortRSSI   = true; // sort aps by RSSI
    bool removeDups = true; // remove dup aps ( forces sort )
    bool printAPs   = true; // print found aps
    
    bool printAPFound = false; // do home ap check   
    const char* homeAP = "MYAP"; // check for this ap on each scan
    // --------

    bool homeAPFound   = false;
    
    if(removeDups || sortRSSI){
      for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
          if (WiFi.RSSI(indices[j]) > WiFi.RSSI(indices[i])) {
            loops++;
            //int temp = indices[j];
            //indices[j] = indices[i];
            //indices[i] = temp;
            std::swap(indices[i], indices[j]);  
            std::swap(skip[i], skip[j]);  
          }
        }
      }
    }

    if(removeDups){
      for (int i = 0; i < n; i++) {
        if(indices[i] == -1){
          --o;
          continue;
        }
        ssid = WiFi.SSID(indices[i]);
        for (int j = i + 1; j < n; j++) {
          loops++;
          if (ssid == WiFi.SSID(indices[j])) {
            indices[j] = -1;
          }
        }
      }
    }
//    Serial.println((String)loops);

    size_t bst_signal = WiFi.RSSI(indices[0]);
    size_t wst_signal = WiFi.RSSI(indices[n - 1]);

    for (int i = 0; i < n; ++i)
    {
      if(printAPFound && (WiFi.SSID(indices[i]) == homeAP)) homeAPFound = true;
    
      if(printAPs && indices[i] != -1){
      // Print SSID and RSSI for each network found
      Serial.print((String) encryptionTypeStr(WiFi.encryptionType(indices[i])));
      Serial.print((char)calcStrength(WiFi.RSSI(indices[i]), bst_signal, wst_signal));
      Serial.print(WiFi.SSID(indices[i]));
      Serial.print("\n");
      }
      delay(10);
    }
     Serial.print("\n");
  }
}


