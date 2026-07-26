# Smart Hydration Remainder

A Simple Arduino - based hydration remainder that monitors temperature and humidity using a DHT11 sensor and reminds the user to drink water after a configurable interval using non-blocking timing with 'millis()'

##Components
- Arduino Uno
- DHT11 Sensor
- LED
- Push Button
- Breadboard
- Jumper wires

##Features
- temperature monitoring (optional humidity too)
- Non blocking timing using 'millis()
- Drink Water remainder
- button debounce acknowledgement
- Easy to modify

##Limitations
- sensors which are used here are won't measure accurate measurements 
- Fixed bottle size and radius required
- This system provides local remainders only and does not send notifications to a mobile device

##Future Improvements
- ESP32 or NodeMCU ESP8266  for mobile integration
- supportive configuration of bottle
- data logging to the cloud for hydration tracking


##Author -
Subhani Mahmad
