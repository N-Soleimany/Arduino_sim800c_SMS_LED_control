/*        GND     >>>   GND
 *        RX  8   >>>   TX    
 *        TX  9   >>>   RX
*/
#include <BareBoneSim800.h>

BareBoneSim800 sim800;

int previousSMSIndex = 0;
int currentSMSIndex = 0;
String message = "";
const char* number = "-------PhoneNumber------"; //enter Ur PhoneNumber
const char* messagesend;
char on = 0;
char off = 0;
char deletes = 0;

void setup() {
  Serial.begin(9600);
  sim800.begin();
  sim800.dellAllSMS();
  pinMode(13, OUTPUT);  //LED init

  Serial.println("Testing GSM module");
  messagesend = "Testing GSM module";
  bool messagemodule = sim800.sendSMS(number, messagesend);
  delay(8000); //this delay is necessary for the module to be ready and connected

  bool deviceAttached = sim800.isAttached();
  if (deviceAttached){
    Serial.println("Device is Attached");
    messagesend = "Device is Attached";
    bool messageattached = sim800.sendSMS(number, messagesend);
    
    //saving the last SMS index
    currentSMSIndex = sim800.currentMessageIndex; //read the last saved SMS index
    previousSMSIndex = currentSMSIndex;
    Serial.println("Ready, Send your new SMS");
    messagesend = "Ready, Send SMS";
    bool messagesendFlag = sim800.sendSMS(number, messagesend);
  }
  
  if(!deviceAttached){
    Serial.println("Not Attached");
  }

  
}

void loop() {
  bool checkSMS = sim800.checkNewSMS();
  if (checkSMS) {
    Serial.println("New SMS received");
    currentSMSIndex = sim800.currentMessageIndex;
    message = sim800.readSMS(currentSMSIndex);
    message.trim(); 
    Serial.print("Received Message: ");
    Serial.println(message); 

    //index of the SMS order
    int ledOnIndex = message.indexOf("LED ON");
    int ledOffIndex = message.indexOf("LED OFF");
    int DeleteMessageIndex = message.indexOf("EMPTY");

    if (ledOnIndex != -1) {
      message = "LED ON";
      on = 1;
    } else if (ledOffIndex != -1) {
      message = "LED OFF";
      off = 1;
    } else if (DeleteMessageIndex != -1) {
      message = "EMPTY";
      deletes = 1;
    }
    else {
      message = "";
    }

    Serial.print("SMS : ");
    Serial.println(message); 

    if (message == "LED ON" && on == 1) {
      digitalWrite(13, HIGH);
      Serial.println("LED IS ON");
      const char* messagesend = "LED IS SET ON";
      
      bool messageSent = sim800.sendSMS(number, messagesend);
      on = 0;
      if(messageSent)
          Serial.println("Message Sent");
      else
          Serial.println("Not Sent, Something happened");
      
    } 
    else if (message == "LED OFF" && off == 1) {
      digitalWrite(13, LOW);
      Serial.println("LED IS OFF");
      const char* messagesend = "LED IS SET OFF";
      
      bool messageSent = sim800.sendSMS(number, messagesend);
      off = 0;
      if(messageSent)
          Serial.println("Message Sent");
      else
          Serial.println("Not Sent, Something happened");
    }
    else if (message == "EMPTY" && deletes == 1) {
      sim800.dellAllSMS();
      Serial.println("Deleting messages");
      const char* messagesend = "Messages Deleted";
      
      bool messageSent = sim800.sendSMS(number, messagesend);
      deletes = 0;
      if(messageSent)
          Serial.println("Message Sent");
      else
          Serial.println("Not Sent, Something happened");
    } else {
      sim800.dellAllSMS();
      Serial.println("Message did not match LED ON  / LED OFF / EMPTY");
    }

    previousSMSIndex = currentSMSIndex; 
  }
  delay(5000);
}