#include "image_provider.h"
#include "model_settings.h"
#include <Arduino.h>
#include <Arduino_OV767X.h>

const int kCaptureWidth = 320;
const int kCaptureHeight = 240;
byte captured_data[kCaptureWidth * kCaptureHeight * 2];

TfLiteStatus GetImage(tflite::ErrorReporter* error_reporter, int image_width,
                      int image_height, int channels, int8_t* image_data) {
  static bool g_is_camera_initialized = false;

  // Inicializar cámara si es la primera vez
  if (!g_is_camera_initialized) {
    if (!Camera.begin(QVGA, RGB565, 1)) {
      Serial.println("Error: No se pudo inicializar la cámara");
      return kTfLiteError;
    }
    g_is_camera_initialized = true;
  }

  // Capturar frame de la cámara
  Camera.readFrame(captured_data);

  // Procesar imagen: recortar y convertir a escala de grises
  for (int y = 0; y < image_height; y++) {
    for (int x = 0; x < image_width; x++) {
      // Mapear coordenadas para recorte central
      int cap_x = (x * kCaptureWidth) / image_width;
      int cap_y = (y * kCaptureHeight) / image_height;
      
      int read_index = (cap_y * kCaptureWidth + cap_x) * 2;
      uint8_t high_byte = captured_data[read_index];
      uint8_t low_byte = captured_data[read_index + 1];
      
      // Convertir RGB565 a escala de grises
      uint16_t color = ((uint16_t)high_byte << 8) | low_byte;
      uint8_t r = ((color & 0xF800) >> 11) * 8;
      uint8_t g = ((color & 0x07E0) >> 5) * 4;
      uint8_t b = ((color & 0x001F) >> 0) * 8;
      
      // Calcular luminancia
      float gray_value = (0.299 * r) + (0.587 * g) + (0.114 * b);
      
      // Convertir a formato del modelo (int8_t)
      int index = y * image_width + x;
      image_data[index] = static_cast<int8_t>(gray_value - 128);
    }
  }

  return kTfLiteOk;
}
