# README
Integración de Hardware: Se ha diseñado un esquema que utiliza un relevador como interruptor de potencia para el servomotor, optimizando el consumo de energía y protegiendo el microcontrolador.

Control Biométrico: El sistema ahora procesa la imagen de la huella y la compara en tiempo real con la base de datos local del sensor.

Lógica de Acceso: Se implementó una función secuencial (abrirCerradura) que gestiona el encendido del motor, el movimiento de apertura, el tiempo de espera y el bloqueo automático.

Eficiencia Energética: Al usar el pin Normally Open (NO) del relevador, el servomotor permanece desenergizado el 99% del tiempo, evitando ruidos (humming) y calentamiento.
