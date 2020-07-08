#include <SoftwareSerial.h>
#include <serial/StreamCom.h>

StreamCom streamCom;
SoftwareSerial stream(2, 3); // RX | TX

void setup()
{
  Serial.begin(9600);
  stream.begin(57600);
  streamCom.init(&stream);
}

void loop()
{
  if(streamCom.isMessage()){
    Serial.println("Hay Mensaje");
    String msg = streamCom.readMessageUp('\n');
    Serial.println(msg);
  }
}
