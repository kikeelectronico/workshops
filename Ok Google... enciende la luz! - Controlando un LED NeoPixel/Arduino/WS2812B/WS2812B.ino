#include <Adafruit_NeoPixel.h>

//Pin del LED
/*************************** Selecciona el puerto adecuado ***********************/
#define pin D2
//#define pin D4

//Objeto pixel
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, pin, NEO_GRB + NEO_KHZ800);

void setup() {
  //Inicializar el pixel
  pixel.begin();
}

void loop() {
  //Configurar el color
  pixel.setPixelColor(0, pixel.Color(255,0,0));
  //Actualizar el LED
  pixel.show();
  //Esperar 100 milisegundos
  delay(100);
}
