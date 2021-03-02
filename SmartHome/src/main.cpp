// this block is used to include various library

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// here all the pins are defined
#define light1 D1
#define light2 D2
#define fan D3
#define switch D4
#define light3 D5
#define sensor D6

// this is the topic from which we recieve the messages
#define sub1 "esp1/room"


int m;        // variable to store motion light state
int pirValue; // variable to store read PIR Value

//wifi credentials
const char *ssid = "ssid";
const char *password = "password";

// mqtt credentials
const char *mqttServer = "192.168.43.54";
const int mqttPort = 1883;


WiFiClient espClient;
PubSubClient client(espClient);

/*
 this block of code is used to recieve different Messages( payload) from MQTT broker
 and perform the specific action according to the message recieved
 */
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
        digitalWrite(fan, HIGH);
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
        digitalWrite(light3,LOW);
    } else if(s.equals(String("OFFD"))) {
        digitalWrite(light3,HIGH);
    }
// brightness control for led

    if (s.equals(String("00"))) {
        analogWrite(light3,1023);
    } 
    if (s.equals(String("204"))) {
        analogWrite(light3,1023-204);
    } 
    if (s.equals(String("408"))) {
        analogWrite(light3,1023-408);
    } 
    if (s.equals(String("612"))) {
        analogWrite(light3,1023-612);
    } 
    if (s.equals(String("816"))) {
        analogWrite(light3,1023-816);
    } 
    if (s.equals(String("1020"))) {
        analogWrite(light3,0);
    } 
}
// connect() function is used to connect to Broker and to subscribe to the topic

void connect() {
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
    while(!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP1")) {
            Serial.println("connected");
            client.subscribe(sub1);
            
        }
        else {
            Serial.println("failed with state: ");
            Serial.print(client.state());
            Serial.println("trying again in 5 seconds");
            delay(5000);
        }
    }
};
// in setup() function pinmodes are defined and also used to connect to wifi 
void setup()
{
Serial.begin(115200);
pinMode(switch, OUTPUT);
pinMode(light1, OUTPUT);
pinMode(light2, OUTPUT);
pinMode(light3, OUTPUT);
pinMode(fan, OUTPUT);
pinMode(sensor, INPUT);

digitalWrite(light3, HIGH);

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

// loop() function here is only used to read the values from PIR sensor and turn led on and off
// this function also connect function so that connection b/w nodeMCU and Broker does not break

void loop()
{
  if(m == 1){
    pirValue = digitalRead(sensor);
    if(pirValue == HIGH){
        digitalWrite(light3, LOW);
    }
    else{
       digitalWrite(light3, HIGH); 
    }
  }

     if (!client.connected()){
        connect();
    }
    client.loop();
}
