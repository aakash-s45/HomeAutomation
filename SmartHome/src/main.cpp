#include <Arduino.h>
#include <Credentials.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <MQTTCredentials.h>


#define light1 D1
#define light2 D2
#define fan D3
#define switch D4
#define light3 D5
#define sensor D6
int m;        // variable to store motion light state
int pirValue; // variable to store read PIR Value

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.print(topic);
    payload[length] = '\0';
    String s = String((char *)payload);
    Serial.println(s);
    
// For Switch
    if (s.equals(String("ON"))) {
        digitalWrite(switch, HIGH);
    } else if(s.equals(String("OFF"))) {
        digitalWrite(switch, LOW);
    }
// For Light 1
     if (s.equals(String("ONL1"))) {
        digitalWrite(light1, HIGH);
    } else if(s.equals(String("OFFL1"))) {
        digitalWrite(light1, LOW);
    }
// For Light 2
    if (s.equals(String("ONL2"))) {
        digitalWrite(light2, HIGH);
    } else if(s.equals(String("OFFL2"))) {
        digitalWrite(light2, LOW);
    }
// For Fan
    if (s.equals(String("ONF"))) {
        
    } else if(s.equals(String("OFFF"))) {
        digitalWrite(fan, LOW);
    }
// For Motion Sensor
    if (s.equals(String("ONM"))) {
        m = 1;
    } else if(s.equals(String("OFFM"))) {
        m = 0;
    }
// For LED

    if (s.equals(String("OND"))) {
        digitalWrite(light3, HIGH);
    } else if(s.equals(String("OFFD"))) {
        digitalWrite(light3, LOW);
    }
};

void connect() {
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
    while(!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP1", mqttUser, mqttPassword)) {
            Serial.println("connected");
            client.subscribe("/****TOPIC*******/");
            
        }
        else {
            Serial.println("failed with state: ");
            Serial.print(client.state());
            Serial.println("trying again in 5 seconds");
            delay(5000);
        }
    }
};

void setup()
{
Serial.begin(115200);
pinMode(switch, OUTPUT);
pinMode(light1, OUTPUT);
pinMode(light2, OUTPUT);
pinMode(light3, OUTPUT);
pinMode(fan, OUTPUT);
pinMode(sensor, INPUT);

digitalWrite(light3, LOW);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print("waiting for wifi to be connected");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    connect();

}

// the loop function runs over and over again forever
void loop()
{
  if(m == 1){
    pirValue = digitalRead(sensor);
  digitalWrite(light3, pirValue);
  }

     if (!client.connected()){
        connect();
    }
    client.loop();
}
