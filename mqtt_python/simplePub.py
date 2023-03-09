import os
import time
import sys
import json

import paho.mqtt.client as mqtt


SERVER = '169.254.5.226' # address of the broker (mosquitto), it's the RPi address

client = mqtt.Client()
client.connect(SERVER, 1883, 60)

# Check if an integer argument was provided
if len(sys.argv) != 2:
    print("Usage: python publisher.py <integer>")
    sys.exit(1)

try:
    message = int(sys.argv[1])
except ValueError:
    print("Invalid input, please enter an integer.")
    sys.exit(1)

# Publish the integer as an MQTT message
client.publish("command_nbr", message)

# Disconnect from MQTT broker
client.disconnect()