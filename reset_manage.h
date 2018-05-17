//Este modulo es un modulo de uso generico para el reseteo del arduino mediante un boton pullup. Limpia la EEPROM y DEBERIA luego reiniciar.
//Necesita que se definan:
//Pin de Reseteo y pin asociado al arduino
//  #define resetPin 2
//  #define resetPoint 0

//Llamada por interrupcion
void resetConfiguration(){
  noInterrupts();
  uint8_t cant= 0;
  while(cant < 5){ delay(1); cant++; }
  cant= 0;
  if(digitalRead(resetPin) == LOW){
    DEB_DO_PRINTLN(reCo);
    EEPROM.update(0, 0);
    DEB_DO_PRINTLN(enRe);  
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
