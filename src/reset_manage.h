//Este modulo es un modulo de uso generico para el reseteo del arduino mediante un boton pullup. Limpia la EEPROM y DEBERIA luego reiniciar.
//Necesita que se definan:
//Pin de Reseteo y pin asociado al arduino
//  #define resetPin 2
//  #define resetPoint 0

#ifndef GenUseReset_h
#define GenUseReset_h

#include <Arduino.h>
#include <EEPROM.h>
#include <common_initial.h>

#ifndef resetPin
  #define resetPin 2
#endif
#ifndef resetPoint
  #define resetPoint 0
#endif

#ifndef resetPoint
  #define resetPoint 0
#endif

#ifndef RESET_BEGIN
  #define RESET_BEGIN "START RESET"
#endif
#ifndef RESET_END
  #define RESET_END "END RESET"
#endif

//Llamada por interrupcion
void resetConfiguration(){
  noInterrupts();
  uint8_t cant= 0;
  while(cant < 5){ delay(1); cant++; }
  cant= 0;
  if(digitalRead(resetPin) == LOW){
    DEB_DO_PRINTLN(RESET_BEGIN);
    EEPROM.update(0, 0);
    DEB_DO_PRINTLN(RESET_END);
  }
  interrupts();
}

void initialReset(){
  //Reset PIN
  pinMode(resetPin, INPUT_PULLUP);
  //Aseguro que este abajo
  digitalWrite(resetPin, HIGH);
  //Inicio interrupciones
  attachInterrupt(resetPoint, resetConfiguration, FALLING);
}

#endif
