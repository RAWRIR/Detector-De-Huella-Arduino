#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Servo.h> // Librería para el control del motor

// Configuración de Pines
const int relayPin = 4;    // Pin que activa el relevador
const int servoPin = 9;    // Pin de señal del servomotor
SoftwareSerial mySerial(2, 3); // RX, TX para el sensor

// Objetos
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
Servo miCerradura;

void setup() {
  Serial.begin(9600);
  
  // Configuración de salidas
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Aseguramos que empiece apagado
  
  miCerradura.attach(servoPin);
  miCerradura.write(0); // Posición inicial: Cerrado
  
  Serial.println("Inicializando sistema de seguridad...");

  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Sensor detectado correctamente.");
  } else {
    Serial.println("Error: No se detectó el sensor de huella.");
    while (1) { delay(1); }
  }
}

void loop() {
  int fingerprintID = getFingerprintID();

  // Si se detecta una huella válida (ID mayor o igual a 0)
  if (fingerprintID >= 0) {
    abrirCerradura();
  }
  
  delay(50); // Pequeña pausa para estabilidad
}

// Lógica de apertura
void abrirCerradura() {
  Serial.println("Acceso Concedido. Abriendo...");
  
  digitalWrite(relayPin, HIGH); // Paso 1: Encender energía del servo
  delay(200);                   // Paso 2: Esperar estabilización eléctrica
  
  miCerradura.write(90);        // Paso 3: Girar servo para abrir
  delay(3000);                  // Paso 4: Mantener abierto por 3 segundos
  
  miCerradura.write(0);         // Paso 5: Regresar servo a posición de cierre
  delay(600);                   // Paso 6: Esperar a que el motor termine de girar
  
  digitalWrite(relayPin, LOW);  // Paso 7: Cortar energía (Ahorro y seguridad)
  Serial.println("Cerradura bloqueada. Esperando huella...");
}

// Función para obtener ID de huella (Mejorada)
int getFingerprintID() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) {
    Serial.println("Acceso Denegado: Huella desconocida.");
    return -1;
  }

  Serial.print("ID Encontrado: #");
  Serial.println(finger.fingerID);
  return finger.fingerID;
}
