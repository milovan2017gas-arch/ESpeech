#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "ESpeech.h"

#define I2S_WS 16    // for esp32_s I2S_WS 25
#define I2S_SD 7    // for esp32_s I2S_SD 33
#define I2S_SCK 15    // for esp32_s I2S_SCK 32

ESpeech STT(I2S_NUM_1,I2S_SCK,I2S_WS,I2S_SD);

const char *ssid = "Rakib";                                // Your SSID
const char *password = "rakib@2024";                       // Your PASS
#define serverUrl "http://192.168.0.106:8888/uploadAudio"  // Change the IP Address according To Your Server's config

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
  Serial.println("\nConnected to WiFi");
  STT.begin(serverUrl);
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readString();
    if (cmd.indexOf("start") == 0) { //////apply any logic to begin stt. For ex use push_button logic or Upcoming Wakeword like 'hey marvin' !!!! /////////////////
      STT.recordAudio(); // This records the voice with vad
      String intent = STT.getTranscription(); // this returns the speech to text as string
      Serial.println(intent); // just showing the intent
    }
  }
}
