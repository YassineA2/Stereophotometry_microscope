import os
import time
import sys
import json
import base64

import paho.mqtt.client as mqtt

SERVER = '169.254.5.226' # address of the broker (mosquitto), it's the RPi address

image_path = "received_image.jpg"
# Define callback function to handle received messages
def on_message(client, userdata, message):
    print("Received message on topic " + message.topic)

    # Decode the image data from base64
    image_data = base64.b64decode(message.payload)

    # Save the image data to a file
    with open(image_path, "wb") as f:
        f.write(image_data)

    print("Saved image to " + image_path)

# Set up MQTT client and subscribe to topic
client = mqtt.Client()
client.connect(SERVER, 1883, 60)
client.subscribe("img_sender")
client.on_message = on_message

# Start the MQTT client loop to handle incoming messages
client.loop_forever()
