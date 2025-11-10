#ifndef MODEL_SETTINGS_H
#define MODEL_SETTINGS_H

// Configuración de la imagen de entrada
constexpr int kNumCols = 96;       // Ancho de la imagen
constexpr int kNumRows = 96;       // Alto de la imagen  
constexpr int kNumChannels = 1;    // Canales (1 para escala de grises)

// Categorías de clasificación
constexpr int kCategoryCount = 3;
const char* kCategoryLabels[kCategoryCount] = {
    "alerta",
    "somnoliento"
};

#endif
