# HomeAutomation
This is a Home Automation project using ESP8266+ MQTT Broker+ Node-Red+ Google Assistant/Home.
In this project, an online MQTT broker is used : Mosquitto which can be run on virtual machine, Your PC, or single board computer like Rpi.
In this project, Mosquitto broker is installed in computer. Because it is free to use, and more speed as compared to cloud Broker.
Node MCU subscribe to a Topic on Broker.
Broker take the message from publisher and send this to subscribers.
When a particular message is send to NodeMCU it will turn ON the desired pin.
To Publish messages(Payload) to MQTT broker,  Node-red, Node-red Dashboard and NORA is used. Node-red is a flow based development tool, where we can make working dashboard to control NodeMCU by connecting some nodes.
To connect google assistant, NORA is used ( an addon for Node-Red) which is a free service.

Apps, Programs and Websites Used:

            1. Node-Red
            2. MQTT Broker
            3. google Home
            4. Platform IO IDE
            5. VS Code

Demo Video Link: https://drive.google.com/file/d/1QJq77MxuinNgsMrbrPK-WxY564YLUF1L/view?usp=sharing

