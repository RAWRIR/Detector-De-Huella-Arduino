#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

// Pines para comunicación con el sensor
SoftwareSerial mySerial(2, 3); // RX, TX
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
  Serial.begin(9600);
  while (!Serial); // Espera a que el puerto serie esté listo
  Serial.println("Inicializando sensor de huella...");

  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Sensor detectado correctamente.");
  } else {
    Serial.println("No se pudo encontrar el sensor. Verifica conexiones.");
    while (1) { delay(1); }
  }
}

void loop() {
  Serial.println("Coloca tu dedo en el sensor...");
  getFingerprintID();
  delay(2000);
}

// Función para obtener ID de huella
int getFingerprintID() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) {
    Serial.println("Huella no encontrada.");
    return -1;
  }

  // Si se encuentra
  Serial.print("Huella encontrada con ID #");
  Serial.print(finger.fingerID);
  Serial.print(" con confianza de ");
  Serial.println(finger.confidence);
  return finger.fingerID;
}
