# MQTT Broker Docker Container
Reference: https://hometechhacker.com/mqtt-home-assistant-using-docker-eclipse-mosquitto/

1. Create the folders
mkdir -p mosquitto/{log,config,data}

2. Create the mosquitto config then input texts in << >>
nano mosquitto/config/mosquitto.conf

<<
persistence true
persistence_location /mosquitto/data/

user mosquitto

# Listen on all interfaces 
listener 1883

#Allow connection without authentication
allow_anonymous true

log_dest file /mosquitto/log/mosquitto.log
log_dest stdout
>>

3. Ctrl+o - Enter, Ctrl+x to save

4. Run the MQTT docker container
docker run -itd \
--name=mqtt \
--restart=always \
--net=host \
-v <folder_path>/mosquitto/config:/mosquitto/config \
-v <folder_path>>/mosquitto/data:/mosquitto/data \
-v <folder_path>>/mosquitto/log:/mosquitto/log \
eclipse-mosquitto


# Home Assistant Docker Container
Reference: https://www.home-assistant.io/installation/linux#install-home-assistant-container

1. Create the folder
mkdir ha

2. Run the Home Assistant docker container
docker run -d \
  --name homeassistant \
  --privileged \
  --restart=unless-stopped \
  -e TZ=Asia/Manila \
  -v <folder_path>/ha:/config \
  -v /run/dbus:/run/dbus:ro \
  --network=host \
  ghcr.io/home-assistant/home-assistant:stable

# Arduino Pico-W sample code
git@github.com:daniloc/PicoW_HomeAssistant_Starter.git

How to
1. Set up the MQTT broker docker
   a. Make sure that the mosquitto.conf file is set
      Note: Error occurs when Adding user name and password, the docker image restarts always. Use without credentials.
2. Test the MQTT broker
   a. Can use the Linux terminal as mosquitto-client
   b. Subscribe to a topic
      mosquitto_sub -h <mqtt host> -t <topic>
   c. Test publish to a topic
      mosquitto_pub -h <mqtt host> -t <topic> - m <topic>
3. Set up the Home Assistant docker
   a. Add MQTT in the integration section
   b. Supply the configuration and credentials required for the MQTT broker (i.e. broker ip, port, username, password)
4. Download the Arduino Pico-W project
   a. Configure the Credentials.h and supply the credentials of the MQTT broker
   b. Load the project to the pico-w board

Supposedly, the Pico-W board will automatically be added to the Home Assistant dashboard!

How?
- The Home Assistant supports auto discovery. The PicoW creates a discovery message within the firmware and publishes it to the topic that Home Assistant for configuration.
