#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "index.h" //HTML MAIN webpage contents
#include "color.h" //HTML COLOR_page webpage contents

//===============================================================
//  config NeoPixel
//===============================================================

#include <Adafruit_NeoPixel.h>
//#include <avr/power.h>
#define PIN            4
#define NUMPIXELS      8
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//===============================================================
//  config AP
//===============================================================
const char *ssid = "MINI_ESP_TEST"; //SSID for AP
const char *password = "1234567890"; //PW for AP

IPAddress ap_local_IP(192,168,4,1); //IP for AP
IPAddress ap_gateway(192,168,4,2); //Gateway for AP
IPAddress ap_subnet(255,255,255,0); //Subnet for AP

ESP8266WebServer server(80); //open server

//===============================================================
//  Function for Webserver
//===============================================================
void handleRoot(void); //root Page
void handleColor(void); //root Page
void handleData(void); //send data from esp to server

//===============================================================
//  Variables
//===============================================================

int red, green, blue;
int red_old, green_old, blue_old;
double counter_uebergabe=1;
bool led_array[8];

//===============================================================
//  for first call go to main page
//  Functions will executed when open IP in browser
//===============================================================
void handleRoot()
{
  server.send(200, "text/html", MAIN_page, sizeof(MAIN_page)); //Hauptseite aufrufen
}

//===============================================================
//  Color Page
//  Functions will executed when open IP in browser
//===============================================================
void handleColor()
{
  //Farbinfo lesen aus testwert
  Serial.println("Farbinfo: ");
  Serial.println(server.arg("testwert"));
  Serial.print("Led Status: ");

  //Led Status pruefen und in true oder false wandeln
  led_array[0] = stringtobool(server.arg("led_1"));
  led_array[1] = stringtobool(server.arg("led_2"));
  led_array[2] = stringtobool(server.arg("led_3"));
  led_array[3] = stringtobool(server.arg("led_4"));
  led_array[4] = stringtobool(server.arg("led_5"));
  led_array[5] = stringtobool(server.arg("led_6"));
  led_array[6] = stringtobool(server.arg("led_7"));
  led_array[7] = stringtobool(server.arg("led_8"));

  //slider auslesen (Helligkeit) (0-255)
  int slider = server.arg("slide").toInt();

  //Werte anzeigen
  Serial.println(server.arg("led_1") + " " + server.arg("led_2") + " " + server.arg("led_3") + " " + server.arg("led_4") + " " + server.arg("led_5") + " " + server.arg("led_6") + " " + server.arg("led_7") + " " + server.arg("led_8") + " " + String(slider));

  //Helligkeit einstellen
  pixels.setBrightness(slider);
  //Leds Updaten
  pixels.show();

  //Testwert String in Char Array umwandeln
  char hexString[8];
  server.arg("testwert").toCharArray(hexString, 8);
  
  byte r,g,b;
  //Hexfarbsting in rgb wandeln
  getRGB(hexString,r,g,b);
  Serial.print("R: ");Serial.print(r);
  Serial.print(" G: ");Serial.print(g);
  Serial.print(" B: ");Serial.println(b);
  red = r;
  green = g;
  blue = b;

  //Seite erneut aufrufen
  server.send(200, "text/html", COLOR_page, sizeof(COLOR_page)); //Hauptseite aufrufen
}

//===============================================================
//  send data to webserver via json
//===============================================================
void handleData(){
  server.send(200, "text/json", "{\"uebergabe\":" + String(counter_uebergabe,1) + "}"); //send value
}

//===============================================================
//  Accesspoint start
//===============================================================
void setupAP(void) {
  delay(100);
  WiFi.mode(WIFI_STA); //wifi mode
  WiFi.disconnect(); //if connected send disconnect
  delay(100);
  Serial.print("Setting soft-AP ... ");
  WiFi.softAPConfig(ap_local_IP, ap_gateway, ap_subnet); //config AP
  WiFi.softAP(ssid, password); //start AP
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP()); //print IP from AP
  
  server.on("/", handleRoot); //root Seite
  server.on("/color", handleColor); //Led Color Seite
  server.on("/data", handleData); //datenuebergabe JSON
  
  server.begin(); //Server starten
  Serial.println("Server started");
}

//===============================================================
//  Hex in RGB umwandeln
//===============================================================

void getRGB(char* text, byte &r, byte &g, byte &b)
{
  long l=strtol(text+1,NULL,16);
  r=l>>16;
  g=l>>8;
  b=l;
}

//===============================================================
//  String in bool umwandeln
//===============================================================

bool stringtobool(String var)
{
  if(var == "true"){
      return true;
  } else if(var == "True"){
      return true;
  } else {
      return false;
  }

}


void setup()
{
  delay(1000);
  Serial.begin(115200);
   
  setupAP(); //Accesspoint starten

  delay(500);

  pixels.begin(); //Leds starten
  pixels.setBrightness(0); // Set BRIGHTNESS to about 1/5 (max = 255)
  
  counter_uebergabe = 1; //Default Wert setzen
}


void loop()
{

  server.handleClient(); // check for HTTP-Request
 
  //nur die Led Updaten wenn sich an RGB was geandert hat 
  if(red != red_old || green != green_old || blue != blue_old){
    //einmal senden Wert wird hoeher gesetzt
    counter_uebergabe++;
    //Pixel durchlaufen
    for(int i=0;i<NUMPIXELS;i++){
        //wenn true von der Webseite kommt diese einzelne Led updaten
        if(led_array[i] == true) {
          pixels.setPixelColor(i, pixels.Color(red,green,blue)); //Werte fuer Led setze
          pixels.show(); //update LED
      
        }
    }
    //alte rgb Werte speichern
    red_old = red;
    green_old = green;
    blue_old = blue;
  }
  
}
