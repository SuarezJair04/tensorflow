#ifndef IMAGE_PROVIDER_H
#define IMAGE_PROVIDER_H

#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/c/common.h"

// Funciones para obtener propiedades de la imagen
int GetImageWidth();
int GetImageHeight();
int GetImageChannels();

// Función principal para capturar y procesar imágenes
TfLiteStatus GetImage(tflite::ErrorReporter* error_reporter, int image_width,
                      int image_height, int channels, int8_t* image_data);

#endif
