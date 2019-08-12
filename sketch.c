#include <Nefry.h>
#include <NefryRESTAPI.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTTYPE DHT11
#define DHTPIN D4

DHT dht(DHTPIN,DHTTYPE);

#define MAX_TEMP 30.0f

// String KEY = "";

void setup() {
  NefryRESTAPI.begin();
  NefryRESTAPI.setPassword(KEY);

  Nefry.setLed(0,0,0);
  dht.begin();

  Nefry.getWebServer()->on("/api/1.0/TEMPERATURE", [&]() {
    // if (!(Nefry.getWebServer()->arg("pass")).equals(KEY)) {
    //   Nefry.getWebServer()->send(403, "text/html", "password err");
    // } else {
//      String ps = Nefry.getWebServer()->arg("pin");
      float t = dht.readTemperature();
      String content = F("{\"mode\":\"Temperature\",\"value\":");
      content += String(t);
      content += F("}");
      Nefry.getWebServer()->send(200, "application/json", content);
    // }
  });
}

void loop() {

  if(WiFi.status() != WL_CONNECTED){
    Nefry.reset();
  }
  
//  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(t)) { // || isnan(h)
    Nefry.println("Failed to read from DHT sensor!");
    Nefry.ndelay(5 *1000);
    return;
  }
  Nefry.print("Temp: ");
  Nefry.print(t);
  Nefry.print(" *C");

  Nefry.println("");

//   if (t >= MAX_TEMP) {
//     HTTPClient client;
//     // client.begin("http://www.example.com/");
//     int httpCode = client.GET();
  
//     // httpCode will be negative on error
//     if(httpCode > 0) {
//       Nefry.print("Code: ");
//       Nefry.print(httpCode);
//       Nefry.println("");
  
//       if(httpCode == HTTP_CODE_OK) {
//         String payload = client.getString();
//         Nefry.println(payload);
//       }
//     }
//     client.end();
//   }

//  float hif = dht.computeHeatIndex(f, h);
//  float hic = dht.computeHeatIndex(t, h, false);

//  Nefry.print("Humidity: ");
//  Nefry.print(h);
//  Nefry.print(" %\t");
//  Nefry.print("Temperature: ");
//  Nefry.print(t);
//  Nefry.print(" *C ");
//  Nefry.print(f);
//  Nefry.print(" *F\t");
//  Nefry.print("Heat index: ");
//  Nefry.print(hic);
//  Nefry.print(" *C ");
//  Nefry.print(hif);
//  Nefry.println(" *F");

  Nefry.ndelay(10 *1000);
}
