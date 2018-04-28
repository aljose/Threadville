#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN        6
#define NUMPIXELS  128
String data = "";
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void fila_puente(int i){
  Serial.println("/n");
  Serial.println(data.charAt(i));
  Serial.println("/n");
  switch (data.charAt(i)) {
      case '0':
        pixels.setPixelColor(i, pixels.Color(255,255,255)); // Moderately bright green color.
        pixels.show(); // This sends the updated pixel color to the hardware.    
        break;
      case '1':
        pixels.setPixelColor(i, pixels.Color(200,100,190)); // Moderately bright green color.
        pixels.show(); // This sends the updated pixel color to the hardware.
        break;
      case '2':
        pixels.setPixelColor(i, pixels.Color(125,185,130)); // Moderately bright green color.
        pixels.show(); // This sends the updated pixel color to the hardware.    
        break;
      case '3':
        pixels.setPixelColor(i, pixels.Color(255,195,195)); // Moderately bright green color.
        pixels.show(); // This sends the updated pixel color to the hardware.    
        break;
      case '4':
        pixels.setPixelColor(i, pixels.Color(255,195,0)); // Moderately bright green color.
        pixels.show(); // This sends the updated pixel color to the hardware.    
        break;
      default:
        pixels.setPixelColor(i, pixels.Color(255,255,255)); // Moderately bright green color.
        pixels.show(); // This sends the updated pixel color to the hardware.
        break;
  }
   // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    
}

void agente(int i){
  char a = '0';
  switch (a) {
      case '0':
        pixels.setPixelColor(i, pixels.Color(0,25,250)); // Moderately bright green color.
        pixels.show(); // This sends the updated pixel color to the hardware.    
        break;
      case '1':
        pixels.setPixelColor(i, pixels.Color(0,25,250)); // Moderately bright green color.
        pixels.show(); // This sends the updated pixel color to the hardware.
        break;
      case '2':
        pixels.setPixelColor(i, pixels.Color(0,10,0)); // Moderately bright green color.
        pixels.show(); // This sends the updated pixel color to the hardware.    
        break;
      case '3':
        pixels.setPixelColor(i, pixels.Color(0,25,250)); // Moderately bright green color.
        pixels.show(); // This sends the updated pixel color to the hardware.    
        break;
      default:
        break;
  }
}

void setup() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin(); // This initializes the NeoPixel library.
  Serial.begin(9600);
}

void loop() {
  if (Serial.available())
   {
      data = Serial.readString();
      Serial.print(data);
      for(int i=0;i<128;i++){
        switch (i) {
        case 0:
          fila_puente(i);
          break;
        case 1:
          fila_puente(i);
          break;
        case 2:
          fila_puente(i);
          break;
        case 3:
          fila_puente(i);
          break;
        case 4:
          fila_puente(i);
          break;
        case 6:
          agente(i);
          break;
        case 64:
         agente(i);
          break;
       case 66:
          fila_puente(i);
          break;
        case 67:
         fila_puente(i);
          break;
        case 68:
          fila_puente(i);
          break;
        case 69:
          fila_puente(i);
          break;
        case 70:
          fila_puente(i);
         break;
        case 8:
          fila_puente(i);
          break;
        case 9:
          fila_puente(i);
          break;
        case 10:
          fila_puente(i);
          break;
        case 11:
          fila_puente(i);
          break;
        case 12:
          fila_puente(i);
          break;
        case 13:
          fila_puente(i);
          break;
       case 14:
          fila_puente(i);
          break;
        case 15:
         fila_puente(i);
         break;
        case 72:
          fila_puente(i);
          break;
        case 73:
          fila_puente(i);
          break;
        case 74:
          fila_puente(i);
          break;
        case 75:
          fila_puente(i);
          break;
        case 76:
          fila_puente(i);
          break;
        case 77:
          fila_puente(i);
          break;
        case 78:
          fila_puente(i);
          break;
        case 24:
          fila_puente(i);
          break;
        case 25:
          fila_puente(i);
          break;
        case 26:
          fila_puente(i);
          break;
        case 27:
         fila_puente(i);
          break;
        case 28:
          fila_puente(i);
          break;
        case 30:
          agente(i);
          break;
        case 88:
          agente(i);
          break;
        case 90:
          fila_puente(i);
          break;
        case 91:
          fila_puente(i);
          break;
        case 92:
          fila_puente(i);
          break;
        case 93:
          fila_puente(i);
          break;
        case 94:
          fila_puente(i);
          break;
        case 32:
          fila_puente(i);
          break;
        case 33:
          fila_puente(i);
          break;
        case 34:
         fila_puente(i);
          break;
        case 35:
          fila_puente(i);
          break;
        case 36:
          fila_puente(i);
          break;
        case 37:
          fila_puente(i);
         break;
        case 38:
          fila_puente(i);
          break;
        case 39:
          fila_puente(i);
          break;
        case 96:
          fila_puente(i);
          break;
        case 97:
          fila_puente(i);
          break;
        case 98:
          fila_puente(i);
          break;
        case 99:
          fila_puente(i);
          break;
        case 100:
          fila_puente(i);
          break;
        case 101:
         fila_puente(i);
         break;
        case 102:
          fila_puente(i);
          break;
        case 48:
          fila_puente(i);
          break;
        case 49:
          fila_puente(i);
          break;
        case 50:
          fila_puente(i);
          break;
        case 51:
          fila_puente(i);
          break;
        case 52:
          fila_puente(i);
          break;
        case 54:
          agente(i);
          break;
        case 112:
          agente(i);
          break;
        case 114:
         fila_puente(i);
         break;
       case 115:
         fila_puente(i);
         break;
      case 116:
        fila_puente(i);
        break;
      case 117:
        fila_puente(i);
         break;
      case 118:
        fila_puente(i);
        break;
      case 56:
        fila_puente(i);
        break;
      case 57:
        fila_puente(i);
        break;
      case 58:
        fila_puente(i);
        break;
      case 59:
        fila_puente(i);
        break;
      case 60:
        fila_puente(i);
        break;
     case 61:
        fila_puente(i);
        break;
      case 62:
       fila_puente(i);
        break;
      case 63:
        fila_puente(i);
        break;
      case 120:
        fila_puente(i);
        break;
      case 121:
        fila_puente(i);
       break;
      case 122:
        fila_puente(i);
      case 123:
        fila_puente(i);
        break;
      case 124:
        fila_puente(i);
        break;
      case 125:
        fila_puente(i);
       break;
      case 126:
        fila_puente(i);
        break;
      default:
        break;
      }
    }
    delay(500); // Delay for a period of time (in milliseconds).
  }else{}
}
