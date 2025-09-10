#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <WiFi.h>

const char* client_cert = R"EOF(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----
)EOF";

const char* private_key = R"EOF(
-----BEGIN RSA PRIVATE KEY-----

-----END RSA PRIVATE KEY-----
)EOF";

const char* ca_cert = R"EOF(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----
)EOF";

const char* ssid = " ";
const char* password = " ";
const char* mqtt_server = " ";
const int mqtt_port = 8883;
const char* mqtt_topic = " ";
const char* mqtt_client_id = " ";

WiFiClientSecure secureClient;
PubSubClient client(secureClient);

float valor = 0.0;
const int ANALOG_PIN = 34;

void setup_wifi() {
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado.");
}

void connect_to_mqtt() {
  while (!client.connected()) {
    Serial.println("Conectando a AWS IoT...");
    if (client.connect(mqtt_client_id)) {
      Serial.println("Conectado a AWS IoT Core.");
    } else {
      Serial.print("Falló conexión, código: ");
      Serial.print(client.state());
      Serial.println(". Reintentando en 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);

  setup_wifi();

  secureClient.setCACert(ca_cert);
  secureClient.setCertificate(client_cert);
  secureClient.setPrivateKey(private_key);

  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    connect_to_mqtt();
  }
  int valorCrudo = analogRead(ANALOG_PIN);
  valor = valorCrudo * (3.3 / 4095.0);
  String payload = "{\"valor\": " + String(valor, 4) + "}";
}
