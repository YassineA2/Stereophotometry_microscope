import os
import time
import sys
import json
import subprocess
import base64 

import paho.mqtt.client as mqtt


# open and encode an image, preparing it to be sent via mqtt
img_path = "img.jpg"
with open(img_path, "rb") as f:
    img_data = f.read()
img_base= base64.b64encode(img_data).decode()


SERVER = '169.254.5.226' # address of the broker (mosquitto), it's the RPi address


# Define callback function to handle received messages
def on_message(client, userdata, message):
    number = int(message.payload)

    # this serie of values represents the led's, basically useful to test the command of leds
    if number == 0:
        os.system("sudo ./test 0") 
    elif number == 1:
        os.system("sudo ./test 1")
    elif number == 2:
        os.system("sudo ./test 2")
    elif number == 3:
        os.system("sudo ./test 3")
    elif number == 4:
        os.system("sudo ./test 4")
    elif number == 5:
        os.system("sudo ./test 5")
    elif number == 6:
        os.system("sudo ./test 6")
    
    # this command allows us to test the led command and img acquisition using just the two first leds    
    elif number == 99:
        client.publish("img_sender", "0",qos=1)
        os.system("sudo ./test 0")
        os.system("sudo ./init_img 0")

        os.system("sudo ./test 1")
        os.system("sudo ./init_img 1")
        
    # this command allows us to do the whole process
    elif number == 100:
        os.system("sudo ./test 0")
        os.system("sudo ./init_img 0")

        os.system("sudo ./test 1")
        os.system("sudo ./init_img 1")

        os.system("sudo ./test 2")
        os.system("sudo ./init_img 2")

        os.system("sudo ./test 3")
        os.system("sudo ./init_img 3")

        os.system("sudo ./test 4")
        os.system("sudo ./init_img 4")

        os.system("sudo ./test 5")
        os.system("sudo ./init_img 5")
        
        os.system("sudo ./test 6")
        os.system("sudo ./init_img 6")

    # command to test if the image can be sent or not
    elif number == 404:
        client.publish("img_sender", img_base, qos = 1)     
    else:
        print(f"Received message: {number}")

# Set up MQTT client and subscribe to topic
client = mqtt.Client()
client.connect(SERVER, 1883, 60)
client.subscribe("command_nbr")
client.on_message = on_message

# Start the MQTT client loop to handle incoming messages
client.loop_forever()
