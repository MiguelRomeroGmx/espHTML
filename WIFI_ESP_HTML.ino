//#include <SoftwareSerial.h>
 // arduino Rx (pin 2) ---- ESP8266 Tx
 // arduino Tx (pin 3) ---- ESP8266 Rx
//SoftwareSerial esp8266(18,19); 
void setup()
{
 Serial.begin(115200);  // monitor serial del arduino
 Serial1.begin(115200); // baud rate del ESP8255

 pinMode(10,OUTPUT); //configuramos los pines como salidas
 digitalWrite(10,LOW); 
 pinMode(11,OUTPUT);
 digitalWrite(11,LOW);
 pinMode(9,OUTPUT);
 digitalWrite(9,LOW);
 pinMode(8,OUTPUT);
 digitalWrite(8,LOW);
 pinMode(7,OUTPUT);
 digitalWrite(7,LOW);
 pinMode(6,OUTPUT);
 digitalWrite(6,LOW);
 pinMode(5,OUTPUT);
 digitalWrite(5,LOW);
pinMode(4,OUTPUT);
 digitalWrite(4,LOW);
 pinMode(44,OUTPUT);
 digitalWrite(44,LOW);
 
 sendData("AT+RST\r\n",2000);      // resetear módulo
 sendData("AT+CWMODE=1\r\n",1000); // configurar como cliente
 //sendData("AT+CWJAP=UMSE ALUMNOS,umse2017\r\n",8000); //SSID y contraseña para unirse a red 
 sendData("AT+CWJAP=ROMERO,romero2016\r\n",8000); //SSID y contraseña para unirse a red 
 sendData("AT+CIFSR\r\n",1000);    // obtener dirección IP
 sendData("AT+CIPMUX=1\r\n",1000); // configurar para multiples conexiones
 sendData("AT+CIPSERVER=1,80\r\n",1000);         // servidor en el puerto 80
}
void loop()
{
 if(Serial1.available())   // revisar si hay mensaje del ESP8266
 {
 if(Serial1.find("+IPD,")) // revisar si el servidor recibio datos
 {
 delay(1000); // esperar que lleguen los datos hacia el buffer
 int conexionID = Serial1.read()-48; // obtener el ID de la conexión para poder responder
 Serial1.find("led="); // bucar el texto "led="
 //int state = (Serial1.read()-48); // Obtener el estado del pin a mostrar
 //digitalWrite(11, state); // Cambiar estado del pin
int pinNumber = (Serial1.read()-48)*10; // conseguir primer número, si el pin es 13, entonces el primer número es 1, entonces se multiplican para obtener 10
pinNumber += (Serial1.read()-48); 
digitalWrite(pinNumber, !digitalRead(pinNumber));  

while(Serial1.available()){
 char c = Serial1.read();
 Serial.print(c);
 }
 
 //responder y cerrar la conexión para que el navegador no se quede cargando 
 // página web a enviar
 //String webpage = "";
// if (state==1) webpage += "<h1>Encender Luces!</h1>";
 //else { webpage += "<h1>Apagar Luces!</h1>";}
 //else { webpage += "<h1>LED_13 = apagado!</h1>";}
 
 // comando para enviar página web
 /*String comandoWebpage = "AT+CIPSEND=";
 comandoWebpage+=conexionID;
 comandoWebpage+=",";
 comandoWebpage+=webpage.length();
 comandoWebpage+="\r\n";
 sendData(comandoWebpage,1000);
 sendData(webpage,1000);*/
 
 // comando para terminar conexión
 String comandoCerrar = "AT+CIPCLOSE=";
 comandoCerrar+=conexionID;
 comandoCerrar+="\r\n";
 sendData(comandoCerrar,3000);
 }
 }
}
/*
Enviar comando al esp8266 y verificar la respuesta del módulo, todo esto dentro del tiempo timeout
*/
void sendData(String comando, const int timeout)
{
 long int time = millis(); // medir el tiempo actual para verificar timeout
 
 Serial1.print(comando); // enviar el comando al ESP8266
 
 while( (time+timeout) > millis()) //mientras no haya timeout
 {
 while(Serial1.available()) //mientras haya datos por leer
 { 
 // Leer los datos disponibles
 char c = Serial1.read(); // leer el siguiente caracter
 Serial.print(c);
 }
 } 
 return;
}
