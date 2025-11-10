

# Entrenamiento del modelo con Teachable Machine y exportación a TensorFlow Lite

## ¿Qué es Teachable Machine?

<img width="1327" height="584" alt="Image" src="https://github.com/user-attachments/assets/83a1c433-0992-42df-8139-d9ee7a7d8f81" />

Teachable Machine es una herramienta gratuita creada por Google que permite entrenar modelos de aprendizaje automático de manera sencilla, sin necesidad de escribir código. La plataforma está orientada a usuarios que desean:

* Entrenar modelos de reconocimiento de imágenes
* Clasificar sonidos
* Clasificar poses
* Exportar los modelos entrenados a distintos formatos, incluyendo TensorFlow, TensorFlow.js y TensorFlow Lite

Su principal ventaja es que permite cargar datasets propios o capturar datos directamente desde la cámara o micrófono, y entrenar modelos en pocos minutos mediante una interfaz visual e intuitiva.

## ¿Qué es TensorFlow y TensorFlow Lite?

<img width="1349" height="587" alt="Image" src="https://github.com/user-attachments/assets/6d2178a0-c405-4943-b9ab-2feb222967fe" />

TensorFlow es un framework de machine learning desarrollado por Google para construir y ejecutar modelos de inteligencia artificial. Permite entrenar redes neuronales, procesar datos y ejecutar modelos en servidores, computadoras o dispositivos móviles.

TensorFlow Lite es una versión optimizada de TensorFlow diseñada específicamente para dispositivos embebidos, microcontroladores y sistemas con recursos limitados. Esta versión reduce el tamaño del modelo y lo convierte en un formato adecuado para ejecutarse en placas como:

* Arduino Nano 33 BLE Sense
* ESP32 / ESP32-CAM
* Dispositivos IoT

TensorFlow Lite usa modelos compactos eficientes en memoria, capaces de correr inferencias en tiempo real dentro de hardware con muy poca RAM y CPU.

---

## Procedimiento: Entrenamiento del modelo en Teachable Machine

### 1. Acceso a la plataforma

Ingresar a la herramienta desde el navegador en la página oficial de Teachable Machine.

### 2. Selección del tipo de proyecto

<img width="550" height="270" alt="Image" src="https://github.com/user-attachments/assets/7e93e6db-e658-4e0a-894a-90152358ea3f" />

Elegir el tipo de modelo que se desea entrenar, según la aplicación:

* Image Project
* Audio Project
* Pose Project

Para este proyecto se utilizó un modelo de **clasificación de imágenes**, ya que se requiere detectar estados o condiciones específicas mediante una cámara.

### 3. Creación de clases y captura de datos

<img width="1251" height="469" alt="Image" src="https://github.com/user-attachments/assets/04777926-746d-4987-afbb-58ace27a92d6" />

Dentro del proyecto de imágenes:

* Se crean las clases necesarias para el modelo (por ejemplo: “Despierto”, “Dormido”).
* Se cargan imágenes o se capturan desde la cámara del navegador.
* Se recomienda equilibrar la cantidad de imágenes por clase y capturar variación en iluminación, ángulos y expresiones.

<img width="1306" height="555" alt="image" src="https://github.com/user-attachments/assets/11c92526-a36b-498e-8d3a-e67a1c871c65" />


### 4. Entrenamiento del modelo

Una vez completada la captura de datos:


<img width="234" height="218" alt="image" src="https://github.com/user-attachments/assets/28347e5e-bb3e-48c6-aa6d-7d3126767b82" />


* Presionar el botón “Train Model”.
* Teachable Machine procesa los datos y entrena un modelo de clasificación utilizando una red neuronal.
* Se puede ajustar el tiempo de entrenamiento y la estructura del modelo según el rendimiento deseado.

### 5. Evaluación del modelo

Después del entrenamiento, la plataforma muestra una vista previa del modelo en ejecución.
Aquí se puede:

<img width="301" height="553" alt="image" src="https://github.com/user-attachments/assets/f8bdf7df-af80-4d5b-bac9-cf51e380a921" />
<img width="304" height="565" alt="image" src="https://github.com/user-attachments/assets/d9c4f20d-88b7-4c4a-b914-37487437ab7c" />


* Probar el modelo en tiempo real
* Ver la probabilidad de clasificación
* Ajustar o corregir las clases si es necesario
* Re-entrenar para mejorar resultados

### 6. Exportación del modelo

<img width="815" height="262" alt="image" src="https://github.com/user-attachments/assets/4391e8ea-d39b-4127-a45b-61a9ea6060fe" />


Cuando el modelo tiene un rendimiento adecuado, se exporta.

Teachable Machine ofrece varias opciones de exportación. Para uso en microcontroladores, se debe seleccionar:

TensorFlow Lite
→ TensorFlow Lite (for Arduino)

Esta opción genera:

* Un archivo `.h` o `.cpp` que contiene el modelo ya convertido a formato TensorFlow Lite listo para microcontroladores
* Un archivo `.txt` con las etiquetas
* Un ejemplo de código `.ino`

Todos estos archivos deben ser importados al proyecto en el IDE correspondiente.

---

## Integración con TensorFlow Lite

Al exportar el modelo en formato TensorFlow Lite para Arduino, Teachable Machine realiza el proceso de conversión y optimización automáticamente. Esto incluye:

* Cuantización del modelo
* Reducción de tamaño en memoria
* Adaptación del formato a tensores adecuados para microcontroladores
* Generación de un archivo en C/C++ que contiene los bytes del modelo

Este archivo se utiliza directamente dentro del sketch de Arduino para ejecutar la inferencia en tiempo real.

El proceso final consiste en:

* Incluir los archivos generados en el proyecto
* Inicializar el intérprete de TensorFlow Lite en el microcontrolador
* Alimentar el modelo con datos del sensor o cámara
* Ejecutar la inferencia
* Leer la salida del modelo y actuar en consecuencia

---

# Proyecto de Detección de Estado de Alerta para Transportistas con TensorFlow Lite en Arduino

## Descripción del Proyecto

Este proyecto implementa un sistema de monitoreo en tiempo real para detectar si un transportista se encuentra en estado de somnolencia o alerta. Utiliza TensorFlow Lite Micro ejecutándose en una placa Arduino Nano 33 con capacidad de procesamiento de imágenes. El modelo de machine learning fue entrenado específicamente para reconocer patrones asociados con estados de fatiga y alerta.

## Aplicación Práctica

El sistema está diseñado para ser instalado en vehículos de transporte, donde monitorea continuamente al conductor y alerta cuando detecta signos de somnolencia, contribuyendo a la prevención de accidentes por fatiga al volante.

## Requisitos de Hardware

- Arduino Nano 33 BLE Sense
- Cable USB-C
- Computadora con Arduino IDE instalado

## Instalación del Arduino IDE

<img width="250" height="200" alt="image" src="https://github.com/user-attachments/assets/5d7db18a-3c54-4e39-853d-b3ff2d23b33b" />


1. Descarga Arduino IDE desde https://www.arduino.cc/en/software
2. Ejecuta el instalador y sigue las instrucciones del asistente
3. Abre el Arduino IDE después de la instalación

<img width="450" height="290" alt="image" src="https://github.com/user-attachments/assets/7baf3457-f316-4970-8a19-e881c88afd7a" />


## Configuración del Board Manager

1. Ve a Herramientas -> Placa -> Gestor de placas
2. Busca "Arduino Mbed OS Nano Boards"
3. Instala la versión más reciente
4. Selecciona: Herramientas -> Placa -> "Arduino Nano 33 BLE"

<img width="250" height="180" alt="image" src="https://github.com/user-attachments/assets/8ffbad11-6577-4853-abaa-4727621150e4" />


## Instalación de Librerías Requeridas

En el Arduino IDE, ve a Programa -> Incluir Librería -> Gestionar Librerías e instala:

1. Arduino_TensorFlowLite (por TensorFlow Authors)
2. Arduino_OV767X (por Arduino)
3. Arduino_HTS221 (por Arduino)
4. Arduino_LPS22HB (por Arduino)
5. Arduino_APDS9960 (por Arduino)

## Estructura del Proyecto

- tm_template_script.ino - Sketch principal
- arduino_image_provider.cpp - Captura y procesamiento de imágenes faciales
- arduino_image_provider.h - Header para procesamiento de imágenes
- main_functions.h - Declaraciones principales
- model_settings.h - Configuración de dimensiones del modelo
- person_detect_model_data.cpp - Modelo entrenado para detección de estados
- person_detect_model_data.h - Header del modelo

## Explicación del Código

### Configuración del Modelo (model_settings.h)

El modelo está configurado para procesar imágenes de 96x96 píxeles en escala de grises, optimizado para detectar características faciales asociadas con estados de alerta y somnolencia.

```cpp
constexpr int kNumCols = 96;      // Ancho de imagen
constexpr int kNumRows = 96;      // Alto de imagen
constexpr int kNumChannels = 1;   // Escala de grises
```

### Inicialización de TensorFlow Lite

El sketch principal inicializa el motor de TensorFlow Lite Micro y carga el modelo entrenado para detección de estados de alerta. El modelo procesa características faciales como:

- Posición de los párpados
- Apertura ocular
- Inclinación de la cabeza
- Expresiones faciales asociadas con fatiga

### Procesamiento de Imágenes

La función GetImage() en arduino_image_provider.cpp:

1. Captura imágenes de la cámara OV7675
2. Recorta la región facial
3. Convierte a escala de grises
4. Preprocesa la imagen para el modelo
5. Normaliza los valores de píxeles

### Inferencia y Resultados

El modelo devuelve probabilidades para dos estados:

- kAlertIndex: Probabilidad de que el conductor esté alerta
- kDrowsyIndex: Probabilidad de que el conductor muestre signos de somnolencia

```cpp
// En el loop principal:
float alert_score = output->data.f[kAlertIndex];
float drowsy_score = output->data.f[kDrowsyIndex];
```

## Instalación y Configuración

### Carga del Programa

1. Conecta el Arduino Nano 33 BLE Sense via USB-C
2. Selecciona el puerto correcto: Herramientas -> Puerto
3. Verifica la placa: Herramientas -> Placa -> "Arduino Nano 33 BLE"
4. Compila el sketch: Sketch -> Verificar/Compilar
5. Sube el programa: Sketch -> Subir

### Configuración Física

- Instala la placa en una posición que permita capturar claramente el rostro del conductor
- Asegura una iluminación adecuada en la cabina
- Orienta la cámara hacia el área del asiento del conductor

## Operación del Sistema

Una vez instalado y energizado:

1. El sistema inicializa automáticamente
2. La cámara comienza a capturar imágenes continuamente
3. El modelo procesa cada frame en busca de signos de somnolencia
4. Los resultados se muestran en el monitor serial
5. En una implementación completa, se activarían alertas audibles o vibratorias cuando se detecte somnolencia

## Interpretación de Resultados

Ejemplo de salida en monitor serial:

```
Estado: ALERTA - 92%
Estado: SOMNOLENCIA - 8%
Conductor en estado óptimo
```

```
Alerta: 35%
Somnolencia: 65%
¡ALERTA: Posible estado de fatiga detectado!
```
