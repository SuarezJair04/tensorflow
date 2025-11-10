#include <TensorFlowLite.h>
#include "main_functions.h"
#include "image_provider.h"
#include "model_settings.h"
#include "person_detect_model_data.h"

// Includes de TensorFlow Lite con la ruta CORRECTA
#include "tensorflow/lite/micro/tflite_bridge/micro_error_reporter.h"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"

// Globals
namespace {
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;

constexpr int kTensorArenaSize = 136 * 1024;
uint8_t tensor_arena[kTensorArenaSize];
}  // namespace

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  // Inicializa TensorFlow Lite
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  // Carga el modelo
  model = tflite::GetModel(g_person_detect_model_data);
  
  // Verifica versión
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    Serial.print("Error: Model version ");
    Serial.print(model->version());
    Serial.print(", expected ");
    Serial.println(TFLITE_SCHEMA_VERSION);
    return;
  }

  // Resolver de operaciones
  static tflite::AllOpsResolver resolver;

  // Interprete
  static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArenaSize);
      
  interpreter = &static_interpreter;

  // Asigna tensores
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    Serial.println("Error: AllocateTensors failed");
    return;
  }

  input = interpreter->input(0);
  output = interpreter->output(0);

  Serial.println("✅ TensorFlow Lite inicializado CORRECTAMENTE");
}

void loop() {
  Serial.println("🔍 Ejecutando inferencia TensorFlow Lite...");
  
  // 1. Obtener imagen
  TfLiteStatus image_status = GetImage(error_reporter, kNumCols, kNumRows, kNumChannels, input->data.int8);
  if (image_status != kTfLiteOk) {
    Serial.println("❌ Error en GetImage");
    return;
  }

  // 2. Ejecutar modelo
  TfLiteStatus invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    Serial.println("❌ Error en Invoke");
    return;
  }

  // 3. Procesar resultados
  Serial.println("📊 Resultados TensorFlow Lite:");
  
  // Prueba ambas versiones:
  if (output->type == kTfLiteFloat32) {
    // Modelo float
    float person_score = output->data.f[0];
    float no_person_score = output->data.f[1];
    Serial.print("Persona (float): ");
    Serial.println(person_score, 4);
    Serial.print("No persona (float): ");
    Serial.println(no_person_score, 4);
  } else if (output->type == kTfLiteInt8) {
    // Modelo int8
    int8_t person_score = output->data.int8[0];
    int8_t no_person_score = output->data.int8[1];
    Serial.print("Persona (int8): ");
    Serial.println(person_score);
    Serial.print("No persona (int8): ");
    Serial.println(no_person_score);
  }

  Serial.println("-------------------");
  delay(3000);
}
