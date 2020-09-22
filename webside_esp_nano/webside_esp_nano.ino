#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "index.h" //HTML MAIN webpage contents

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
void handleData(void); //send data from esp to server

//===============================================================
//  Variables
//===============================================================
double counter_uebergabe = 0; //double example to send to server

int measureInterval = 20 ; //*100 ms; //update interval for counter_uebergabe
int timer1 = 0; //counter timer for update
int counter = 1; //counter for add to counter_uebergabe

//===============================================================
//  for first call go to main page
//  Functions will executed when open IP in browser
//===============================================================
void handleRoot()
{
  server.send(200, "text/html", MAIN_page, sizeof(MAIN_page)); //Hauptseite aufrufen
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
  
  server.on("/", handleRoot); 
  server.on("/data", handleData);
  //here you can add more pagees
  
  server.begin();
  Serial.println("Server started");
}


void setup()
{
  delay(1000);
  Serial.begin(115200);
   
  setupAP();

  delay(500);

  //server.begin();
  
  counter_uebergabe = 1; //Default Wert setzen
}


void loop()
{


  server.handleClient(); // check for HTTP-Request
  delay(100);
  timer1++; //timer count
  if(timer1 >= measureInterval)
  {
    timer1 = 0;
    counter++;
    Serial.println(WiFi.softAPgetStationNum());
  }  

    counter_uebergabe = counter; //count up global value
     //now you can also work with this values here

}
