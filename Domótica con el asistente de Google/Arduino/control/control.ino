#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

// Configurar conexión WiFi
WiFiClient client;
#define SSID_WIFI       "SSID"
#define PASS_WIFI       "PASSWORD"

//Configurar datos de conexión con Adafruit
#define servidor_adafruit      "io.adafruit.com"
#define puerto_adafruit  1883
#define nombre_de_usuario    "nombreDeUsuarioAdafruitIO"
#define API_KEY         "tuApiKey"

Adafruit_MQTT_Client mqtt(&client, servidor_adafruit, puerto_adafruit, nombre_de_usuario, API_KEY);

//Configurar el feed de Adafruit
Adafruit_MQTT_Subscribe led = Adafruit_MQTT_Subscribe(&mqtt, nombre_de_usuario "/feeds/LED");

void setup() {
  Serial.begin(115200);
  pinMode(D4,OUTPUT);
  delay(10);
  // Conectarse a la red WiFi
  Serial.println(); Serial.println();
  Serial.print("Conectando a ");
  Serial.println(SSID_WIFI);
  WiFi.begin(SSID_WIFI, PASS_WIFI);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi Conectado");

  // Subscribirse al feed del LED en Adafruit
  mqtt.subscribe(&led);

  // Conectarse a Adafruit IO
  int8_t ret;
  if (!mqtt.connected()) {
    Serial.print("Conectandose a Adafruit IO");
    uint8_t intentos = 3;
    while ((ret = mqtt.connect()) != 0) {
         Serial.println(mqtt.connectErrorString(ret));
         Serial.println("Volviendo a intentarlo en 5 segundos");
         mqtt.disconnect();
         delay(5000);  // Esperar en 5 segundos
         intentos--;
         //Si se ha fallado 3 veces, no volver a intentar
         if (intentos == 0) {
           while (1);
         }
    }
    Serial.println("Conectado a MQTT!");
  }

}

void loop() {
  //Esperar a recibir mensajes desde Adafruit IO
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(1000))) {
    //Comprobar si el mensaje es para el LED
    if (subscription == &led) {
      //Comprobar el mensaje
      if (strcmp((char *)led.lastread, "encender") == 0){
        digitalWrite(D4, HIGH);        
      } else if (strcmp((char *)led.lastread, "apagar") == 0){
        digitalWrite(D4, LOW);
      }
    }
  }
}
