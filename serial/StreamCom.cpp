#include <Arduino.h>
#include "StreamCom.h"


//Stream *StreamCom::stream;

StreamCom::StreamCom(){
}

/*void StreamCom::init(Stream* stream){
  StreamCom::stream = stream;
}*/
void StreamCom::init(Stream* stream){
  this->stream = stream;
}

bool StreamCom::isMessage(){
  //return StreamCom::stream->available();
  return this->stream->available();
}
void StreamCom::sendMessage(String &msg, char endC1, char endC2 = '0'){
  /*StreamCom::stream->print(msg);
  StreamCom::stream->write(endC1);
  if(endC2 != '0'){
    StreamCom::stream->write(endC2);
  }*/
  this->stream->print(msg);
  this->stream->write(endC1);
  if(endC2 != '0'){
    this->stream->write(endC2);
  }
}
String StreamCom::readMessageUp(char endC1, char endC2 = '0'){
  uint8_t retries = 0;
  String msg = "";
  bool end = false;
  while(true) {
    //if(StreamCom::stream->available()){
	if(this->stream->available()){
      //Leo caracter
      //char c = StreamCom::stream->read();
	  char c = this->stream->read();
      //Serial.println(c);
      //Analizo si ya se habia marcado el fin y si vuelve a coincidir salimos
      if(c == endC2 && end){
        return msg;
      }
      if(c == endC1){
        //Marcamos primer fin
        end = true;
        if(endC2 == '0'){
          //No debe validar el 2do caracter, asi que es final de mensaje
          return msg;
        }
      } else {
        //Agregamos caracter al mensaje
        end = false;
        msg += c;
      }
      //Reinicio Retries
      retries = 0;
    } else {
      delay(5);
      retries += 1;
      if(retries == 3) {
        //Error
        return "**";
      }
    }
  }
}
