#include <TensorFlowLite.h>
#include "main_functions.h"
#include "image_provider.h"
#include "model_settings.h"
#include "drowsiness_model_data.h"  // Modelo entrenado para somnolencia

// Includes de TensorFlow Lite
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"

// Variables globales para TensorFlow Lite
namespace {
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;

// Memoria para operaciones de TensorFlow
constexpr int kTensorArenaSize = 136 * 1024;
uint8_t tensor_arena[kTensorArenaSize];
}  // namespace

// Índices para las clasificaciones de somnolencia
const int kAlertIndex = 0;      // Conductor alerta
const int kDrowsyIndex = 1;     // Conductor somnoliento
const int kDistractedIndex = 2; // Conductor distraído

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  // Inicializar el reporte de errores
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  // Cargar el modelo de detección de somnolencia
  model = tflite::GetModel(g_drowsiness_model_data);
  
  // Verificar versión del modelo
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Error: Versión del modelo incompatible");
    return;
  }

  // Configurar el resolver de operaciones
  static tflite::AllOpsResolver resolver;

  // Crear el intérprete de TensorFlow Lite
  static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArenaSize);
      
  interpreter = &static_interpreter;

  // Asignar memoria para los tensores
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    Serial.println("Error: No se pudieron asignar los tensores");
    return;
  }

  // Obtener referencias a los tensores de entrada y salida
  input = interpreter->input(0);
  output = interpreter->output(0);

  Serial.println("Sistema de detección de somnolencia inicializado");
  Serial.println("Monitoreando estado del conductor...");
}

void loop() {
  // Capturar imagen del conductor
  TfLiteStatus image_status = GetImage(error_reporter, kNumCols, kNumRows, kNumChannels, input->data.int8);
  if (image_status != kTfLiteOk) {
    Serial.println("Error al capturar imagen");
    delay(1000);
    return;
  }

  // Ejecutar la inferencia del modelo
  TfLiteStatus invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    Serial.println("Error en la inferencia del modelo");
    delay(1000);
    return;
  }

  // Procesar resultados de la detección
  float alert_score = output->data.f[kAlertIndex];
  float drowsy_score = output->data.f[kDrowsyIndex];
  float distracted_score = output->data.f[kDistractedIndex];

  // Determinar el estado del conductor
  String estado = "INDETERMINADO";
  float confianza = 0.0;

  if (drowsy_score > alert_score && drowsy_score > distracted_score) {
    estado = "SOMNOLIENTO";
    confianza = drowsy_score;
  } else if (alert_score > drowsy_score && alert_score > distracted_score) {
    estado = "ALERTA";
    confianza = alert_score;
  } else {
    estado = "DISTRAIDO";
    confianza = distracted_score;
  }

  // Mostrar resultados
  Serial.println("=== ANÁLISIS DEL CONDUCTOR ===");
  Serial.print("Estado: ");
  Serial.println(estado);
  Serial.print("Confianza: ");
  Serial.println(confianza);
  Serial.print("Alert: ");
  Serial.print(alert_score);
  Serial.print(" | Somnoliento: ");
  Serial.print(drowsy_score);
  Serial.print(" | Distraído: ");
  Serial.println(distracted_score);

  // Activar alertas si se detecta somnolencia
  if (estado == "SOMNOLIENTO" && confianza > 0.7) {
    Serial.println("¡ALERTA! Posible somnolencia detectada");
    // Aquí se activarían alarmas audibles o vibratorias
  }

  Serial.println("-------------------------------");
  delay(2000); // Esperar 2 segundos entre análisis
}
