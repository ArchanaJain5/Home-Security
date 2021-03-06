import httplib, urllib
import time
sleep = 60 # how many seconds to sleep between posts to the channel
key = 'AQHOP6HQLCGKLCDP'  # Thingspeak channel to update

#Report Raspberry Pi internal temperature to Thingspeak Channel
def senddata():
    while True:
        #Calculate CPU temperature of Raspberry Pi in Degrees C
        image = int(open('/sys/class/thermal/thermal_zone0/temp').read()) / 1e3 # Get Raspberry Pi CPU temp
        params = urllib.urlencode({'field1': image, 'key':key }) 
        headers = {"Content-typZZe": "application/x-www-form-urlencoded","Accept": "text/plain"}
        conn = httplib.HTTPConnection("api.thingspeak.com:80")
        try:
            conn.request("POST", "/update", params, headers)
            response = conn.getresponse()
        
            print response.status, response.reason
            data = response.read()
            conn.close()
        except:
            print "connection failed"
        break
#sleep for desired amount of time
if __name__ == "__main__":
        while True:
                senddata()
                time.sleep(sleep)
