#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <WiFi.h>

const char* client_cert = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAPuJpgYuZrsTf8mPaSmIXBZ0EqPzMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yNTA0MDkxNzQ3
MjBaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCpF53w2JtMNdhdARnE
FtNrK8u77FYERFlgVmeE514TNWcsP/L5M6UMDmHY/gIk1UxoDsEP+fZuZsXOoSVR
c9wAFZVqm14neYzPL1HMtnWzJkh5irKjc2iL0eLlG8bOIfa4AjXHRmWv9sAUapqP
a8mMZAkZDV+WizDCN+NfrjrDTOxAvDBYFAzJda+8w1/f/qpu/7a+uhOy16Omq0nG
aO6bHbbZuz7x5nDo4GaAP42hCs61rWfTk7cSaz5QXxHlA+QyPp1/KyzDhrK7AHJS
VgweC8dT8hzpJW620CenVkyJdiH+vKpzVjmhA9SX6nROEINdbYxO9l+n96CZJR6F
mwVvAgMBAAGjYDBeMB8GA1UdIwQYMBaAFN00tqz4DPH+gcbbtmsNp4wfOn2PMB0G
A1UdDgQWBBQpCJJEscstt2OVRpIBv+Btf7e/ETAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAgAxw4NjYzrBhdITqbdDJ+fGM
wUcX3Ehvx2XwB3S0lQ/d4OrNxGFo09XBdUYO5xfzMju6FRy76HIaTmOLQWrjx9US
+gl5QPRRy3tRQKK6kPpeq6z7MHYLxysI37b8R5sjwW/vE7vC0R3rfdZ0TbsEiH7z
UF3QGaz6/XgcleEtSyMV2g9LrsBSBN0OeH8iwDcIIJ0oXehMquZPn9jttNp60ycK
FWh51t64oKWZke2Z9SXTGsLYot/SoAIzuDYdyHGXMRaw9VM7usu6bxzlSUeyv2pD
7mNgKigdHdFpouTia4YVMJcf5PCrKtRuazMzmZHACpx7xK0T5JyNsFDtzUPtLQ==
-----END CERTIFICATE-----
)EOF";

const char* private_key = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEAqRed8NibTDXYXQEZxBbTayvLu+xWBERZYFZnhOdeEzVnLD/y
+TOlDA5h2P4CJNVMaA7BD/n2bmbFzqElUXPcABWVapteJ3mMzy9RzLZ1syZIeYqy
o3Noi9Hi5RvGziH2uAI1x0Zlr/bAFGqaj2vJjGQJGQ1floswwjfjX646w0zsQLww
WBQMyXWvvMNf3/6qbv+2vroTstejpqtJxmjumx222bs+8eZw6OBmgD+NoQrOta1n
05O3Ems+UF8R5QPkMj6dfyssw4ayuwByUlYMHgvHU/Ic6SVuttAnp1ZMiXYh/ryq
c1Y5oQPUl+p0ThCDXW2MTvZfp/egmSUehZsFbwIDAQABAoIBAERqpuAtdGCYpMu0
x00dAzwow01tKbyePx+ItmgDCYByKiWwVkpYiB5hr1uSIyHuH/U2iw1A0WIIOV8K
usPDQi/Si9tPs//64WtvNQTEiskK42YyJWeXKaTxLoIPBBihi2cWldXkeP6Cs2NP
YuxG64zfaQL280dBWGAtJtWu9F3SmJNH0lRcDhB9pX1dSpwdVSp2WUOob88yg0xP
o1e8tyHOFQAwjLOIdqK/5GyZFE+3gWzejfVGl9Cy2TWJaVPxbKXU2XRaHn8dgNkY
oBqSiUhjipQx6r/Z9gkSSYcxGaXL+PVV/5n+1KPsoSRMg2AC6QAsM2mbCdOq+LCU
tELSkuECgYEA1cP0mbPy5ZcvHX8Ctkg0pNxVIpWmCwPoV8oldjCMC8Yqo6TPMIO8
q3h69NsJ7t/MmFITEaG1MbTVzJ7GBS6HFUYzpuLdRrUbC+rMHkSKy3k2XXRajuAb
yCFziSjKpmbixwlCDiglykR9MDJSeGIKGBkLk77A1fMVH79qV+w4B78CgYEAyoAi
re9XbzsLYbMrPDn175oaz7AnIBkoGMXuver0SgBGgiPs6DB2MS/1imTZjI8GEm7q
82e5fwyFVQlRxi0LFgDaOernMuuxxTLp81iUKFDpWYqDucVf0zbkegade1bMe0JC
U8WDYKuNcCYrRX3PZlLI6GnqkaoaXl69u0KT7lECgYEArD/3dHctTdXSMFltDQcH
7KRisbiWkJ+4dC0+nIsn/kDTkQO3tGci+6TcpzttOJ/70+2m0flU8VW/Rd/Wvsws
K3djHaIHHffHcIXlrqoakTT+GrYsVp69pDlYSPimuwmCyVFrec7eDKu9mL2j+L8/
VQWxb38xEfWLWwa6IVkGGS8CgYAqDmCldR7YmA+uE9L36CW+xGerGK+XiAH+2yTR
RrnDoLkEEEgElQQHBSneu0E/Yvjk3SposPMigswyNARKv1IdGMI54yJvPeomxYM3
Kf9jPCKqmQzwiSB0smLTQQp18jn3o3Q5B71YV2jBkPvNq+pmGu1k75Jq/EQLs2t+
N76XcQKBgQDGeJI/rZuf9HqQjD2+hKLW4DV20aHZb/IXgovXwqXIzA62ksizKxo7
RrpbOeuHzh/d7ZAfNQABTVOiGm17jd7L4Z0u4vSUJvK7p95tRQ9F5LyJH9YQ00yj
1QysHcZ/XdMYl/iYLWfB5NVqqEAY/m4sti2ZMpVW6h2cvwYBv4wVpg==
-----END RSA PRIVATE KEY-----
)EOF";

const char* ca_cert = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

const char* ssid = "lab_PDS";
const char* password = "Fcfmpds01";
const char* mqtt_server = "a31xbogcr1ef8g-ats.iot.us-east-2.amazonaws.com";
const int mqtt_port = 8883;
const char* mqtt_topic = "esp32/timestream";
const char* mqtt_client_id = "ESP32Monitoreo";

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