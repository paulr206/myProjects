import json
import bmpsensor
import time


while True:
    temp, pressure, altitude = bmpsensor.readBmp180()
    print("Temperature is ",temp)  # degC
    print("Pressure is ",pressure) # Pressure in Pa 
    print("Altitude is ",altitude) # Altitude in meters
    print("\n")
    myObject = {
        "temp": temp,
        "pressure": pressure
    }
    jsonString = json.dumps(myObject)
    jsonFile = open("temp.json", "w")
    jsonFile.write(jsonString)
    jsonFile.close
    time.sleep(60)