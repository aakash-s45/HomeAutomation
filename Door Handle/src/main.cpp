#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *ssid = "OnePlus 7";
const char *password = "ramuanuj";

const char *mqttServer = "192.168.43.54";
const int mqttPort = 1883;




#define pin1 D5
#define pin2 D6
#define button1 D1
#define button2 D2

int val1 = 0;     // variable for reading the pin status
int val2 = 0;     // variable for reading the pin status
int m = 2;

#define sub2 "esp2/door"



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
        m=1;
    } 
    else if(s.equals(String("OFF"))) {
        m=0;
    }
    else if(s.equals(String("FOFF"))) {
        m=2;
    }
}

void connect() {
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
    while(!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP2")) {
            Serial.println("connected");
            client.subscribe(sub2);
            
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
pinMode(pin1, OUTPUT);
pinMode(pin2, OUTPUT);
pinMode(button1, INPUT);
pinMode(button2, INPUT);

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


void loop()
{
val1 = digitalRead(button1); 
val2 = digitalRead(button2);

if (val1 == LOW && m==1){
    digitalWrite(pin1,HIGH);
    digitalWrite(pin2,LOW);
}
else if (val1 == HIGH && m==1) {
    digitalWrite(pin1,LOW);
    digitalWrite(pin2,LOW);
}
else if(val2 == LOW && m==0){
    digitalWrite(pin2,HIGH);
    digitalWrite(pin1,LOW);
}
else if (val2 == HIGH && m==0) {
    digitalWrite(pin1,LOW);
    digitalWrite(pin2,LOW);
}

else if(m==2){ 
    digitalWrite(pin1,LOW);
    digitalWrite(pin2,LOW);
}

     if (!client.connected()){
        connect();
    }
    client.loop();
}