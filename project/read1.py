import picamera
from time import sleep
from __future__ import print_function
import paho.mqtt.publish as publish
import psutil
import string
import random
import base64

camera = picamera.PiCamera()

try: 
    camera.start_preview()
    sleep(1)
    camera.capture('image_test.jpg', resize=(500,281))
    camera.stop_preview()
    pass
finally:
    camera.close()


def convertImageToBase64():
    with open("image_test.jpg", "rb") as image_file:
    encoded = base64.b64encode(image_file.read())
    return encoded





# The ThingSpeak Channel ID.
# Replace <YOUR-CHANNEL-ID> with your channel ID.
channelID = " 581232"

# The Write API Key for the channel.
# Replace <YOUR-CHANNEL-WRITEAPIKEY> with your write API key.
writeAPIKey = "AQHOP6HQLCGKLCDP"

# The Hostname of the ThingSpeak MQTT broker.
mqttHost = "mqtt.thingspeak.com"

# You can use any Username.
mqttUsername = "archana6789"

# Your MQTT API Key from Account > My Profile.
mqttAPIKey ="YXMYX3UB2PBFH7GP"

# Set the transport mode to WebSockets.
tTransport = "websockets"
tPort = 80

# Create the topic string.
topic = "channels/" + channelID + "/publish/" + writeAPIKey

def randomword(length):
        return ''.join(random.choice(string.lowercase) for i in range(length))

def publishEncodedImage(encoded):
    end = packet_size
    start = 0
    length = len(encoded)
    picId = randomword(8)
    pos = 0
    no_of_packets = math.ceil(length/packet_size)

    


while(1):

    clientID = ''

# Create a random clientID.
    
    # attempt to publish this data to the topic.
    try:
        while start <= len(encoded):
            data = {"data": encoded[start:end], "pic_id":picId, "pos": pos, "size": no_of_packets}
            client.publishEvent("Image-Data",json.JSONEncoder().encode(data))
            end += packet_size
            start += packet_size
            pos = pos +1

    except (KeyboardInterrupt):
        break

    except:
        print ("There was an error while publishing the data.")
 
