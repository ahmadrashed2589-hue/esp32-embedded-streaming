#include "esp_camera.h"
#include <WiFi.h>
#include "camera_pins.h"

// بيانات WiFi
const char* ssid = "WLAN192A1C";
const char* password = "0777224952r"

// اختيار موديل الكاميرا (حسب نوع ESP32-CAM لديك)
#define CAMERA_MODEL_AI_THINKER

void startCameraServer();

void setup() {
  Serial.begin(115200);
  Serial.println();

  // إعداد الكاميرا
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_QVGA; // دقة منخفضة لتجنب التوقف
  config.jpeg_quality = 12;  // جودة متوسطة
  config.fb_count = 1;

  if (esp_camera_init(&config) != ESP_OK) {
    Serial.println("⚠️ فشل تشغيل الكاميرا!");
    return;
  }

  // الاتصال بشبكة WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi متصل!");

  // تشغيل خادم الفيديو
  startCameraServer();

  Serial.print("🎥 البث متاح على: http://");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(10000); // لا تفعل شيئًا، البث يعمل تلقائيًا
}
