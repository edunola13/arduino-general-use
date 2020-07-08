//
//Con esta clase definimos una forma facil de enviar mensajes a traves de comunicacion serial
//Para que funcione bien ahi que definir bien el protocolo: velocidad, final de msj y formato contenido.

//Formas de Conexion: Master-Slave, Master-Master, Master-VariosSlave
//Master-VariosSlave: Habria que conectar todos los rx a la misma linea

//Antes la variable Stream era por clase pero por ahi en este caso podemos tener mas de una sola comunicacion serial y por distintos lugares.
//Dejo la definicion de los estatico para tenerlo.

#ifndef StreamCom_h
#define StreamCom_h
//#include "WConstants.h"
#include <Arduino.h>

class StreamCom{
  protected:
    //static Stream *stream;
	   Stream *stream;

  public:
    StreamCom();

    //static void init(Stream* stream);
	   void init(Stream* stream);

    bool isMessage();
    void sendMessage(String &msg, char endC1, char endC2 = '0');
    String readMessageUp(char endC1, char endC2 = '0');
};

#endif
