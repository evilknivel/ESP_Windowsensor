#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <WiFiManager.h>         // https://github.com/tzapu/WiFiManager
#include <PubSubClient.h>        // https://github.com/knolleary/pubsubclient/
#include <EEPROM.h>

const char* mqtt_server = "192.168.1.20";
const int mqtt_port = 1883;
const char* mqtt_user = "****";
const char* mqtt_pass = "****";

unsigned long StartTime;
unsigned long CurrentTime;
unsigned long ElapsedTime;
unsigned long waste = millis();
unsigned long wifiTime;

#define wifi_setup 13


WiFiClient espClient;

void callback(char* topic, byte* payload, unsigned int length);


PubSubClient client(mqtt_server, mqtt_port, callback, espClient);

float volt = 0.0;
ADC_MODE(ADC_VCC);
int timeout = 0;


bool changed_data = false;

#define WIFI_CONFIG_ADDRESS 10


struct package {
    uint val = 0;
    char str[20] = "";
    char WIFI_SSID[20] = "";
    char WIFI_PASS[40] = "";
    uint8 bssid[6];
    IPAddress ip; //Node static IP
    IPAddress gateway;
    IPAddress subnet;
    uint8 APchannel = 0;
};
typedef struct package Package;
Package data;
Package new_data;

void setup() {
    StartTime = millis();
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH);

    pinMode(4, INPUT);

    pinMode(wifi_setup, INPUT_PULLUP);


    Serial.begin(115200);

    if (!digitalRead(wifi_setup)) {

        wifimgn();

    }

    EEPROM.begin(sizeof(package) + WIFI_CONFIG_ADDRESS);
    Serial.print("sizeof(package): "); Serial.println(sizeof(package) + WIFI_CONFIG_ADDRESS);


    volt = ((float)ESP.getVcc()) / 1024;
    Serial.print("Battery: "); Serial.println(volt);


    EEPROM.get(WIFI_CONFIG_ADDRESS, data);

    Serial.println("EEPROM values are: " + String(data.val) + "," + String(data.str));
    Serial.println("EEPROM values are: " + String(data.WIFI_SSID) + "," + String(data.WIFI_PASS) + ", CH:" + String(data.APchannel));
    Serial.printf("Connect to AP with mac address from EEPROM: %02x:%02x:%02x:%02x:%02x:%02x\n", data.bssid[0], data.bssid[1], data.bssid[2], data.bssid[3], data.bssid[4], data.bssid[5]);
    if (data.val == 0)
    {
        Serial.println("EEPROM is empty!");
        wifimgn();

    }
    IPAddress dns(192, 168, 1, 1);
   
    WiFi.config(data.ip, data.gateway, data.subnet, dns); // Set static IP (2,7s) or 8.6s with DHCP  + 2s on battery
    //WiFi.persistent( false ); // slowed wifi connection 1s, why???
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(data.WIFI_SSID, data.WIFI_PASS, data.APchannel, data.bssid, true);
    
    

}

void loop() {
    Serial.println("loop");
    Serial.println(WiFi.waitForConnectResult());
    

    
    
    if (WiFi.waitForConnectResult() == WL_CONNECTED)
    {
        Serial.println(WiFi.waitForConnectResult());
        Serial.println(WiFi.localIP());
        Serial.printf("BSSID: %s\n", WiFi.BSSIDstr().c_str());



        client.connect("espClient", mqtt_user, mqtt_pass);
        //client.publish("outTopic", String(volt).c_str());
        //client.publish("outTopic", String(digitalRead(4)).c_str());
        //client.subscribe("inTopic");

        client.publish("homeassistant/binary_sensor/windows/config", "{\"name\": \"office\", \"device_class\": \"opening\", \"unique_id\" :\"12345\", \"state_topic\": \"homeassistant/binary_sensor/windows/state\",\"payload_on\": \"1\",\"payload_off\": \"0\"}");
        client.publish("homeassistant/binary_sensor/windows/state", String(digitalRead(4)).c_str());

        client.disconnect();
        WiFi.disconnect();

        digitalWrite(2, LOW);

        Serial.println(digitalRead(4));
        CurrentTime = millis();
        ElapsedTime = CurrentTime - StartTime;
        Serial.print(ElapsedTime / 1000.0, 2);
        Serial.println(" Sek");

        delay(100);

        digitalWrite(5, LOW);
        ESP.deepSleep(0);
        yield();
    }
    else {

        Serial.println("else status");
        if (timeout > 10) {
            Serial.println("if timeout");
            Serial.println(timeout);
            //Serial.println("cannot connect-> WifiManager call()");
            Serial.println("cannot connect-> power off ESP");
            //WiFi.begin(data.WIFI_SSID, data.WIFI_PASS);
            //wifimgn();
            digitalWrite(5, LOW);
        }
        timeout++;

        
    }

    

}

void wifimgn() {

WiFiManager wifiManager;

if (digitalRead(!wifi_setup)) {
    wifiManager.resetSettings();
}
wifiManager.setRemoveDuplicateAPs(false);


wifiManager.setSTAStaticIPConfig(IPAddress(192, 168, 1, 205), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0)); // static ips for the device, optional DNS 4th argument

wifiManager.autoConnect("AutoConnectAP");

Serial.println("Connected via WifiManager.");


write_eeprom();

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.channel());
  Serial.println(WiFi.subnetMask());
  Serial.println(WiFi.gatewayIP());
  uint8_t macAddr[6];
  WiFi.macAddress(macAddr);
  Serial.printf("Connected, mac address: %02x:%02x:%02x:%02x:%02x:%02x\n", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
  Serial.printf("Default hostname: %s\n", WiFi.hostname().c_str());
  Serial.printf("SSID: %s\n", WiFi.SSID().c_str());
  Serial.printf("BSSID: %s\n", WiFi.BSSIDstr().c_str());
  Serial.printf("RSSI: %d dBm\n", WiFi.RSSI());
  delay(100);

  digitalWrite(5, LOW);
  ESP.deepSleep(0);
  yield();
}

void write_eeprom()
{
    // GET new data
    new_data.APchannel = uint8(WiFi.channel());
    if (new_data.APchannel != data.APchannel) changed_data = true;  // if channel is changed
    uint8* mac = WiFi.BSSID();
    if (uint8(*mac) != data.bssid[0]) changed_data = true;    // if first byte of AP MAC is changed
    if (changed_data) // siplified.. do not write to EEPROM if data is not changed
    {
        for (int i = 0; i < 6; ++i) {
            new_data.bssid[i] = uint8(*mac);
            mac++;
        }
        new_data.val = data.val + 5;
        if (new_data.val > 100) new_data.val = 0;
        if (strcmp(new_data.str, "hello") == 0)
            strncpy(new_data.str, "jerry", 20);
        else
            strncpy(new_data.str, "hello", 20);
        strncpy(new_data.WIFI_SSID, WiFi.SSID().c_str(), 20);
        strncpy(new_data.WIFI_PASS, WiFi.psk().c_str(), 40);
        new_data.ip = WiFi.localIP();
        new_data.subnet = WiFi.subnetMask();
        new_data.gateway = WiFi.gatewayIP();
        EEPROM.put(WIFI_CONFIG_ADDRESS, new_data);
        EEPROM.commit();
        Serial.println(" saved to EEPROM");
    }



}

void callback(char* topic, byte* payload, unsigned int length) {
    // handle message arrived
    Serial.println("MQTT Nachricht abgekommen!");
    //ATTiny Signal senden zum abschalten des ESP
    
    digitalWrite(5, HIGH);
}
