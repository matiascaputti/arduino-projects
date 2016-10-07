// PROGRAMA DISEÑO INDUSTRIAL - completo

// Defino valores constantes del programa
// en este caso serán los pines donde está conectado cada componente

// Pines con PWD -Modulación de Largo de Pulso- indicado con un simbolo "~" sirven para
// lograr el efecto de prendido y apagado progresivo
#define LED_RGB_ROJO_PIN 3             // pin digital 3
#define LED_RGB_VERDE_PIN 5            // pin digital 5
#define LED_RGB_AZUL_PIN 6             // pin digital 6
// las patitas del led rgb van en esos pines para poder

#define DISPLAY_CANTIDAD_DIGITOS 2     // cantidad de dígitos que tiene nuestro display
#define DISPLAY_DIGITOS_PINES[] {0, 1} // para controlar los dígitos del display, pines digitales
#define DISPLAY_SEGMENTOS_PINES[]
{2, 4, 7, 8, 9, 10, 11}        // para controlar los segmentos del display, pines digitales

#define PARLANTE_SONIDO_PIN A3         // pin analógico 3
#define MODULO_GSM_PIN A4              // pin analógico 4

#define ROTADOR_A_PIN 12               // pin digital 12
#define ROTADOR_B_PIN 13               // pin digital 13

#define PULSADOR_PIN A2                // pin analógico 2

#define SENSOR_LUZ_PIN A0              // el sensor de luz está conectado en el pin analógico 0
#define SENSOR_HUMEDAD_PIN A1          // el sensor de humedad está conectado en el pin digital 1

// Defino librerías externas que tienen funciones ya hechas
#include <SevSeg.h>     // librería usada para mostrar números en el display
#include <dht11.h>      // librería usada para realizar mediciones del sensor DHT11 (humedad)
#include <pitches.h>    // librería con todos los valores de las notas musicales
#include <GSM.h>        // librería para enviar SMS a través del módulo GSM

// Defino valores variables del programa
int VALOR_LIMITE_LUZ_MEDIA = 600;     // valores 0 - 1023
int VALOR_LIMITE_LUZ_ALTA = 900;      // valores 0 - 1023
String TIPO_ACTUAL_LUZ = "MEDIA";     // valores "ALTA" - "MEDIA"
int VALOR_ACTUAL_LUZ;                 // valores sensados por el sensor 0 - 1023
int RANGO_PERMITIDO = 100;            // variación permitida para los valores límites

int VALOR_LIMITE_HUMEDAD = 90;        // será seteado por el usuario con el rotador
int VALOR_ACTUAL_HUMEDAD;             // valores sensados por el sensor 0% - 100%

String NUMERO_SMS = 5412217779999;
String MENSAJE_SMS;
bool ESTADO_MODULO_GSM_PIN = false;


// Configuración general del programa
void setup() {
  // Defino el canal del monitor del puerto serie para ver los valores que se van a ir imprimiendo
  Serial.begin(9600);

  // Imprimo el nombre del programa por el puerto serie
  // (se ve desde el programa de Arduino, desde "Herramientas > Monitor Serie")
  Serial.println("==============================");
  Serial.println("  PROGRAMA DISEÑO INDUSTRIAL  ");
  Serial.println("==============================");

  // defino cada pin usado como entrada o salida
  pinMode(LED_RGB_ROJO_PIN, OUTPUT);
  pinMode(LED_RGB_VERDE_PIN, OUTPUT);
  pinMode(LED_RGB_AZUL_PIN, OUTPUT);

  pinMode(ROTADOR_A_PIN, INPUT);
  pinMode(ROTADOR_B_PIN, INPUT);

  pinMode(PULSADOR_PIN, INPUT);

  pinMode(SENSOR_LUZ_PIN, INPUT);
  pinMode(SENSOR_HUMEDAD_PIN, INPUT);

  // defino configuración del display, 'COMMON_ANODE' es el tipo del display
  SevSeg INSTANCIA_DISPLAY; // Inicializo objeto que controla los 7 segmentos
  INSTANCIA_DISPLAY.begin(COMMON_ANODE, DISPLAY_CANTIDAD_DIGITOS, DISPLAY_DIGITOS_PINES, DISPLAY_SEGMENTOS_PINES);
  INSTANCIA_DISPLAY.setBrightness(90); // le defino el brillo en 90

  // defino una variable del tipo dht11 para el sensor de humedad
  dht11 INSTANCIA_SENSOR_HUMEDAD;

  // defino una variable del tipo GSM para el módulo GSM SMS y el mensaje SMS
  GSM INSTANCIA_MODULO_GSM;
  GSM_SMS INSTANCIA_MODULO_SMS;

  // Imprimo que ya está todo listo para empezar
  // (se ve desde el programa de Arduino, desde "Herramientas > Monitor Serie")
  Serial.println("(setup del programa terminado)");
}


// Código que se ejecutará cíclicamente
void loop() {

  // Invocación a mi función MODULO_HUMEDAD
  MODULO_HUMEDAD();

  // Invocación a mi función MODULO_LUZ
  MODULO_LUZ();
}


// Submódulo del programa para medir y setear variables relacionadas con la humedad
void MODULO_HUMEDAD() {
  // obtengo el valor de humedad actual
  VALOR_ACTUAL_HUMEDAD = OBTENER_VALOR_HUMEDAD();

  PRENDER_LED_RGB(255, 255, 255);

  // si supera al máximo definido para ese tipo de luz
  // hacer que el led prenda y apague cada 350 mseg
  if (VALOR_ACTUAL_HUMEDAD >= VALOR_LIMITE_HUMEDAD + 10) {
    PRENDER_LED_RGB(0, 255, 255); // prende CELESTE
    EMITIR_SONIDO();
    ENVIAR_SMS("Hay exceso de humedad!");
  }

  if (VALOR_ACTUAL_HUMEDAD >= VALOR_LIMITE_HUMEDAD + 15) {
    PRENDER_LED_RGB(0, 0, 255); // prende AZUL
    EMITIR_SONIDO();
    ENVIAR_SMS("Hay MUCHO exceso de humedad!");
  }

  if (VALOR_ACTUAL_HUMEDAD <= VALOR_LIMITE_HUMEDAD - 10) {
    PRENDER_LED_RGB(255, 0, 255); // prende VIOLETA
    EMITIR_SONIDO();
    ENVIAR_SMS("Falta humedad!");
  }

  if (VALOR_ACTUAL_HUMEDAD <= VALOR_LIMITE_HUMEDAD - 15) {
    PRENDER_LED_RGB(255 0, 0); // prende ROJO
    EMITIR_SONIDO();
    ENVIAR_SMS("Falta MUCHA humedad!");
  }

  // chequeo el valor del rotador, para ver si cambio en valor máximo de humedad
  MODIFICAR_HUMEDAD_CON_VALOR_ROTADOR();
}

// Sumódulo del programa para medir y setear variables relacionadas con la luz
void MODULO_LUZ() {
  // obtengo el valor de luz actual
  VALOR_ACTUAL_LUZ = OBTENER_VALOR_LUZ();

  // uso una estructura condicional para ejecutar cierto bloque de código
  // sólo si el tipo de luz es MEDIA
  if (TIPO_ACTUAL_LUZ == "MEDIA") {
    // si se encuentra dentro del rango correcto la luz permanece prendida
    PRENDER_LED_RGB(255, 255, 255);

    // si la cantidad de luz es mayor que la cota máxima definida para ese tipo de luz
    // hacer que el led prenda y apague cada 80 mseg (prende y apaga rápido)
    if (VALOR_ACTUAL_LUZ > VALOR_LIMITE_LUZ_MEDIA + RANGO_PERMITIDO ) {
      delay(100);
      PRENDER_LED_RGB(0, 0, 0);
      delay(80);
    }

    // si la cantidad de luz es menor que la cota mínima definida para ese tipo de luz
    // hacer que el led prenda y apague cada 350 mseg (prende y apaga lento)
    if (VALOR_ACTUAL_LUZ < VALOR_LIMITE_LUZ_MEDIA - RANGO_PERMITIDO) {
      delay(100);
      PRENDER_LED_RGB(0, 0, 0);
      delay(350);
    }
  }

  // uso una estructura condicional para ejecutar cierto bloque de código
  // sólo si el tipo de luz es ALTA
  if (TIPO_ACTUAL_LUZ == "ALTA") {
    // si se encuentra dentro del rango correcto la luz permanece prendida
    PRENDER_LED_RGB(255, 255, 255);

    // si la cantidad de luz es mayor que la cota máxima definida para ese tipo de luz
    // hacer que el led prenda y apague cada 80 mseg (prende y apaga rápido)
    if (VALOR_ACTUAL_LUZ > VALOR_LIMITE_LUZ_ALTA + RANGO_PERMITIDO ) {
      delay(100);
      PRENDER_LED_RGB(0, 0, 0);
      delay(80);
    }

    // si la cantidad de luz es menor que la cota mínima definida para ese tipo de luz
    // hacer que el led prenda y apague cada 350 mseg (prende y apaga lento)
    if (VALOR_ACTUAL_LUZ < VALOR_LIMITE_LUZ_ALTA - RANGO_PERMITIDO) {
      delay(100);
      PRENDER_LED_RGB(0, 0, 0);
      delay(350);
    }
  }
}


// INFO SOBRE LAS MEDICIONES ANALÓGICAS:
// Arduino discretiza en 1024 valores (0 a 1023).
// Esto quiere decir que si tenemos un rango de valores de entre 0 V y 5 V,
// cuando el sensor nos de un valor de 0 V con analogRead tendremos un valor
// de 0 y cuando nos de 5 V tendremos 1023.

// Función que devuelve el valor sensado de humedad
int OBTENER_VALOR_HUMEDAD() {
  // Comienzo la medición en 0
  int LECTURA_HUMEDAD = 0;

  // Leo el valor que está tomando el sensor en este instante
  int estado_medicion = SENSOR_HUMEDAD.read(SENSOR_HUMEDAD_PIN);

  // Si midió el valor correctamente, lo asigno a una variable
  if (estado_medicion == DHTLIB_OK)
  {
    LECTURA_HUMEDAD = SENSOR_HUMEDAD.humidity;
  }

  // Imprimo valores por el puerto serie
  Serial.print("HUMEDAD (%): ");
  Serial.println(LECTURA_HUMEDAD);

  // Devuelvo el valor sensado
  return LECTURA_HUMEDAD;
}

// Función que devuelve el valor sensado de luz
int OBTENER_VALOR_LUZ() {
  // Comienzo la medición en 0
  int LECTURA_LUZ = 0;

  // Leo el valor que está tomando el sensor en este instante
  LECTURA_LUZ = analogRead(SENSOR_LUZ_PIN);

  // Imprimo valores por el puerto serie
  Serial.print("LUZ (0-1023): ");
  Serial.println(LECTURA_LUZ);

  // Devuelvo el valor sensado
  return LECTURA_LUZ;
}

// Función que modifica el valor de la humedad según el valor del rotador
void MODIFICAR_HUMEDAD_CON_VALOR_ROTADOR() {
  // Comienzo las mediciones
  char LECTURA_PIN_A;
  char LECTURA_PIN_B;

  // Leo el valor que está tomando el componente en este instante
  LECTURA_PIN_A = digitalRead(ROTADOR_A_PIN);
  LECTURA_PIN_B = digitalRead(ROTADOR_B_PIN);

  // Si todavía no llegué a los límites máximo o mínimo de humedad
  if (VALOR_LIMITE_HUMEDAD >= 0 && VALOR_LIMITE_HUMEDAD <= 100) {

    // Agrego o quito de a una unidad al valor límite de humedad
    if (LECTURA_PIN_A == "HIGH" && LECTURA_PIN_B == "LOW") {
      VALOR_LIMITE_HUMEDAD ++;
    } else {
      VALOR_LIMITE_HUMEDAD --;
    }

  }

  // Muestro el valor de humedad definido en el display
  PRENDER_DISPLAY(VALOR_LIMITE_HUMEDAD);

  // Imprimo valores por el puerto serie
  Serial.print("VALOR_ACTUAL_HUMEDAD: ");
  Serial.println(VALOR_ACTUAL_HUMEDAD);
}

// Función que modifica luz MEDIA o luz ALTA según valor del pulsador
void MODIFICAR_LUZ_CON_VALOR_PULSADOR() {
  // Comienzo las mediciones
  int LECTURA_PULSADOR;

  // Leo el valor que está tomando el componente en este instante
  LECTURA_PULSADOR = analogRead(PULSADOR_PIN);

  // Si detecto que se pulsó el botón pulsador
  if (LECTURA_PULSADOR == 1023) {
    // Si el tipo actual de luz es "MEDIA", cambio a "ALTA"
    if (TIPO_ACTUAL_LUZ == "ALTA") {
      TIPO_ACTUAL_LUZ = "MEDIA";
    }

    // Si el tipo actual de luz es "ALTA", cambio a "MEDIA"
    if (TIPO_ACTUAL_LUZ == "ALTA") {
      TIPO_ACTUAL_LUZ = "MEDIA";
    }
  }

  // Imprimo valores por el puerto serie
  Serial.print("TIPO_ACTUAL_LUZ: ");
  Serial.println(TIPO_ACTUAL_LUZ);
}

// Función para prender y apagar el led rgb cátodo
// (si fuera led rgb ánodo, hay que invertir los valores para que se prenda correctamente)
void PRENDER_LED_RGB(int LED_RGB_VALOR_ROJO,
                     int LED_RGB_VALOR_VERDE,
                     int LED_RGB_VALOR_AZUL) {
  analogWrite(LED_RGB_ROJO_PIN, LED_RGB_VALOR_ROJO);
  analogWrite(LED_RGB_VERDE_PIN, LED_RGB_VALOR_VERDE);
  analogWrite(LED_RGB_AZUL_PIN, LED_RGB_VALOR_AZUL);

  // Imprimo valores por el puerto serie
  Serial.print("PRENDE LED RGB: ");
  Serial.println(LED_RGB_VALOR_ROJO);
  Serial.println(LED_RGB_VALOR_VERDE);
  Serial.println(LED_RGB_VALOR_AZUL);
}

// Función para encender display con el número solicitado
void PRENDER_DISPLAY(int DISPLAY_NUMERO) {
  INSTANCIA_DISPLAY.setNumber(DISPLAY_NUMERO, -1);
  INSTANCIA_DISPLAY.refreshDisplay();

  // Imprimo valores por el puerto serie
  Serial.print("PRENDE DISPLAY: ");
  Serial.println(DISPLAY_NUMERO);
}

// Función para hacer sonar el speaker
void EMITIR_SONIDO() {
  int DURACION = 1000; // 1 segundo
  int TIPO_NOTA = NOTE_A3; // defino un tipo de nota de todas las disponibles en la librería <pitches.h>

  // ejecuto la función 'tone' con el tipo de nota seleccionado
  tone(PARLANTE_SONIDO_PIN, TIPO_NOTA, DURACION);

  // Imprimo valores por el puerto serie
  Serial.print("EMITO SONIDO POR SPEAKER");
}

// Función para enviar un mensaje SMS
void ENVIAR_SMS(char MENSAJE_SMS) {
  // Inicio el módulo GSM si no está inicializado aún
  while (ESTADO_MODULO_GSM_PIN == false)
  {
    if (INSTANCIA_MODULO_GSM.begin(MODULO_GSM_PIN) == GSM_READY) {
      ESTADO_MODULO_GSM_PIN = true;
    } else {
      Serial.println("> El módulo GSM no está conectado");
      delay(1000);
    }
  }

  Serial.println("> El módulo GSM está conectado");

  // Envío el mensaje SMS
  INSTANCIA_MODULO_SMS.beginSMS(NUMERO_SMS);
  INSTANCIA_MODULO_SMS.print(MENSAJE_SMS);
  INSTANCIA_MODULO_SMS.endSMS();

}
