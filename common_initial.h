//Este modulo es un modulo de uso generico para los proyectos.
//Funcionalidad:
//  -Define si se usa o no serial
//  -Define constantes funciones que reemplazan a Serial.print y .println
//  -Define si arranca WatchDog
//ULTIMA MODIFICACION: 17-05-2018
#ifdef USE_WDT
  #include <avr/wdt.h>
#endif

// Define where debug output will be printed.
#define DEB_DO_PRINTER Serial
// Setup debug printing macros.
#ifdef DOMO_DEBUG
  #define DEB_DO_PRINT(...) { DEB_DO_PRINTER.print(__VA_ARGS__); }
  #define DEB_DO_PRINTLN(...) { DEB_DO_PRINTER.println(__VA_ARGS__); }
#else
  #define DEB_DO_PRINT(...) {}
  #define DEB_DO_PRINTLN(...) {}
#endif

void initialGeneric(){
  #ifdef USE_WDT
    wdt_disable(); //Siempre es bueno empezar deshabilitando
    wdt_enable(WDT_TIME); //Seteo el Watch Dog en 8s
  #endif
  #ifdef DOMO_DEBUG
    #ifdef DOMO_SPEED
      Serial.begin(DOMO_SPEED);
    #else
      Serial.begin(115200);
    #endif    
    while (!Serial) {; // wait for serial port to connect. Needed for native USB port only
    }
    Serial.println("INICIALIZANDO");
  #endif
}

void resetWatchDow(){
  #ifdef USE_WDT
    wdt_reset();
  #endif
}
