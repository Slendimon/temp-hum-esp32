#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <time.h>
#include "DHT.h"
#include "config.h"

#define DHTPIN 14
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

String getDateTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "No se pudo obtener la hora";
  }
  char buf[30];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
  return String(buf);
}

String getSensorPage() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    return "<h2>Error leyendo el sensor DHT!</h2>";
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width,initial-scale=1'>";
  html += "<title>Monitor de Temperatura y Humedad</title>";
  html += "<style>";
  html += "body{background:#222;color:#fff;font-family:sans-serif;text-align:center;padding:2em;}";
  html += ".card{background:#333;border-radius:1em;display:inline-block;padding:2em 3em;box-shadow:0 0 20px #0006;}";
  html += "h1{color:#4FC3F7;} .data{font-size:2em;margin:1em 0;}";
  html += "</style></head><body>";
  html += "<div class='card'>";
  html += "<h1>ESP32 - DHT22</h1>";
  html += "<div class='data'>Fecha y hora:<br><b>" + getDateTime() + "</b></div>";
  html += "<div class='data'>Humedad: <b>" + String(h, 1) + "%</b></div>";
  html += "<div class='data'>Temperatura: <b>" + String(t, 1) + "°C / " + String(f, 1) + "°F</b></div>";
  html += "<div class='data'>Índice de calor: <b>" + String(hic, 1) + "°C / " + String(hif, 1) + "°F</b></div>";
  html += "<br><small>Actualiza la página para nuevos datos</small>";
  html += "</div></body></html>";
  return html;
}

void handleRoot() {
  server.send(200, "text/html", getSensorPage());
}

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  configTime(-5 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  dht.begin();

  server.on("/", handleRoot);
  server.begin();
  Serial.println("Servidor web iniciado");
}

void loop() {
  server.handleClient();
  delay(10); // Pequeño delay para estabilidad
}