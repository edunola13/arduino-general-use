//Servidor HTTP
#ifdef USE_SERVER
HttpServer server(80);
#endif
//Cliente HTTP
EthernetClient client;

//CONFIGURABLE
byte mac[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
//IPAddress ip(0,0,0,0);
IPAddress ip(192, 168, 0, 201);
bool changeIp= false;
#ifdef USE_NOTIFICATIONS
  //Notificaciones
  HttpClientAr notifier;
  //IPAddress notifierip(0,0,0,0);
  IPAddress notifierip(192,168,0,11);
  String urlNotifier= "/ArduinoTest/simple_json.php";
  String keyNotifier= "";
  bool waitRta= true;
#endif

//
//INICIO
void initialEthernet(){
  //Creamos el server
  if(ip[0] == 0){
    //Cuando conecto sin ip fija si o si ya tiene que estar conectado el cable de red. Si no, no toma ip.
    server.beginServer(mac);
    ip= Ethernet.localIP();
  }else{
    server.beginServer(mac, ip);
  }  
  DEB_DO_PRINTLN(Ethernet.localIP());
}

//
//CHANGE IP, SI CORRESPONDE
void actualizeIp(){
  if(changeIp){
    DEB_DO_PRINTLN(chaIp);
    server.beginServer(mac, ip);
    changeIp= false;
    DEB_DO_PRINTLN(Ethernet.localIP());
  }
}

#ifdef USE_NOTIFICATIONS
  //
  //NOTIFICACIONES
  bool sendNotification(){  
    DEB_DO_PRINTLN(seNo);
    if(notifierip[0] == 0){
      notification= false;
      DEB_DO_PRINTLN(noNCon);
      return false;
    }
    notifier.stop();
    if(notifier.connect(notifierip, 80)){
      String method= "GET";
      String url= urlNotifier;
      if(keyNotifier != ""){
        url+= "key=" + keyNotifier;
      }
      String contentType= "application/json";
      notifier.sendRequest(method, url);  
      DEB_DO_PRINTLN(noSe); 
    }else{
      DEB_DO_PRINTLN(noNCo);
    }
    //Espera RTA - En este caso no me importa
    if(waitRta){
      while(notifier.connected() && !notifier.available()){
        delay(1); //waits for data
      }
      if(notifier.available()) {
        notification= false;
        HttpResponse httpResponse= notifier.httpResponse();
        //DEB_DO_PRINTLN(httpResponse.getBody());
      }
    }
    notification= false;
    notifier.stop();
    return true;
  }
#endif

//
//CONFIGURACION
void readConfEthernet(uint8_t &pos){
  EEPROM.get(pos, ip);pos+= 6;
  #ifdef USE_NOTIFICATIONS
    char url[50];
    EEPROM.get(pos, url);pos+= 50;
    urlNotifier= url;
    char ke[20];
    EEPROM.get(pos, ke);pos+= 20;
    keyNotifier= ke;
    EEPROM.get(pos, notifierip);pos+= 6;
  #endif
}
void saveConfEthernet(uint8_t &pos){
  EEPROM.put(pos, ip);pos+= 6;
  #ifdef USE_NOTIFICATIONS
    char url[50]; urlNotifier.toCharArray(url, 50);
    EEPROM.put(pos, url);pos+= 50;
    char ke[20]; keyNotifier.toCharArray(ke, 20);
    EEPROM.put(pos, ke);pos+= 20;
    EEPROM.put(pos, notifierip);pos+= 6;
  #endif
}

//
//JSON
void jsonEthernet(){
  #ifdef USE_NOTIFICATIONS
    server.partialSendApiRest(client, "\"urlN\": \"" + urlNotifier + "\"");server.partialSendApiRest(client, ",");
    server.partialSendApiRest(client, "\"keyN\": \"" + keyNotifier + "\"");server.partialSendApiRest(client, ",");
    server.partialSendApiRest(client, "\"ipN\": \"" + String(notifierip[0]) + "." + String(notifierip[1]) + "." + String(notifierip[2]) + "." + String(notifierip[3]) + "\"");
    server.partialSendApiRest(client, ",");
  #endif
  server.partialSendApiRest(client, "\"ip\": \"" + String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]) + "\"");
}

//
//UPDATE
void updateEthernet(HttpRequest &httpRequest){
  //IP
  String value= parseProperty(httpRequest.getPunteroBody(), "ip1");
  if(isNotNull(value)){ ip[0]= value.toInt(); changeIp= true; }    
  value= parseProperty(httpRequest.getPunteroBody(), "ip2");
  if(isNotNull(value)){ ip[1]= value.toInt(); }    
  value= parseProperty(httpRequest.getPunteroBody(), "ip3");
  if(isNotNull(value)){ ip[2]= value.toInt(); }    
  value= parseProperty(httpRequest.getPunteroBody(), "ip4");
  if(isNotNull(value)){ ip[3]= value.toInt(); }
     
  #ifdef USE_NOTIFICATIONS
    //NOTIFIER
    value= parseProperty(httpRequest.getPunteroBody(), "urlN");
    if(isNotNull(value)){ urlNotifier= value; }
    value= parseProperty(httpRequest.getPunteroBody(), "keyN");
    if(isNotNull(value)){ keyNotifier= value; }  
    //NOTIFIER IP
    value= parseProperty(httpRequest.getPunteroBody(), "ipN1");
    if(isNotNull(value)){ notifierip[0]= value.toInt(); }    
    value= parseProperty(httpRequest.getPunteroBody(), "ipN2");
    if(isNotNull(value)){ notifierip[1]= value.toInt(); }    
    value= parseProperty(httpRequest.getPunteroBody(), "ipN3");
    if(isNotNull(value)){ notifierip[2]= value.toInt(); }    
    value= parseProperty(httpRequest.getPunteroBody(), "ipN4");
    if(isNotNull(value)){ notifierip[3]= value.toInt(); }
  #endif   
}
