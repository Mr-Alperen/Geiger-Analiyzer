#include <WiFi.h>
#include <HTTPClient.h>

// WiFi bilgileri
const char* ssid = "WIFI_ADI";
const char* password = "WIFI_SIFRE";

// Geiger sayaç sayaçları
volatile unsigned long alphaCount = 0;
volatile unsigned long gammaCount = 0;

// Geiger giriş pinleri
int alphaPin = 34;   // Alpha pulse
int gammaPin = 35;   // Gamma pulse

// Zamanlama
unsigned long lastTime = 0;

// ISR fonksiyonları
void IRAM_ATTR alphaISR() { alphaCount++; }
void IRAM_ATTR gammaISR() { gammaCount++; }

void setup() {
    Serial.begin(115200);

    // WiFi bağlanma
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(300);
        Serial.print(".");
    }
    Serial.println("\nWiFi bağlandı!");

    // Pinler
    pinMode(alphaPin, INPUT);
    pinMode(gammaPin, INPUT);

    attachInterrupt(alphaPin, alphaISR, RISING);
    attachInterrupt(gammaPin, gammaISR, RISING);
}

void loop() {
    unsigned long current = millis();
    if (current - lastTime >= 1000) { // Her 1 saniye
        lastTime = current;

        float cpsAlpha = alphaCount;
        float cpsGamma = gammaCount;

        unsigned long cpmAlpha = cpsAlpha * 60.0;
        unsigned long cpmGamma = cpsGamma * 60.0;

        String json = "{";
        json += "\"alpha_cps\":" + String(cpsAlpha) + ",";
        json += "\"alpha_cpm\":" + String(cpmAlpha) + ",";
        json += "\"gamma_cps\":" + String(cpsGamma) + ",";
        json += "\"gamma_cpm\":" + String(cpmGamma);
        json += "}";

        Serial.println(json);

        // HTTP POST operatöre gönder
        if (WiFi.status() == WL_CONNECTED) {
            HTTPClient http;
            http.begin("http://192.168.163.19:8080/geiger");
            http.addHeader("Content-Type", "application/json");
            http.POST(json);
            http.end();
        }

        // Sayaçları sıfırla
        alphaCount = 0;
        gammaCount = 0;
    }
}
