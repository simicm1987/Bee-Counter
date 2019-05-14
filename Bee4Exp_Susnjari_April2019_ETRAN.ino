#include <SPI.h>
#include <SD.h>
#include <DS3231.h>

DS3231  rtc(SDA, SCL);
File myfile;

const int chipSelect = 4;
unsigned long duration_alg1=0;

char file_name[] = "susnjari.TXT";    
char extension[] = "TXT"; 

char delay_var = 0;

String dataString = "";

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

char k =0;

void setup()
{
pinMode(10, OUTPUT);
digitalWrite(10, HIGH);

pinMode(7, OUTPUT);
digitalWrite(7, LOW);

rtc.begin();
 Serial.begin(115200);
 while (!Serial) 
  {
    ; 
  }
  
 dataString = "";
 dataString += rtc.getDateStr();
 dataString += " ";
 dataString += rtc.getTimeStr();
 dataString += " ";
if (!SD.begin(chipSelect)) 
  {
    pinMode(5, OUTPUT);
    tone(5, 1000); 
    delay(500);       
    noTone(5); 
    //return;
  }

 unsigned char addr = 0;
 unsigned char value;
    pinMode(5, OUTPUT);
    tone(5, 1000); 
    delay(500);       
    noTone(5); 
//Serial.println(dataString);
}

void loop()
{       
if (stringComplete) 
{
  if (inputString.equals("**\r\n"))
  {
    Serial.println("Read file");
    // clear the string:
    inputString = "";
    stringComplete = false;
     myfile = SD.open(file_name);
  if (myfile)
  {
    Serial.println("Read bee4exp.txt");
    
    // read all the text written on the file
    while (myfile.available()) 
    {
      Serial.write(myfile.read());
    }
    // close the file:
    myfile.close();
  } else 
  {
    Serial.println("error opening the text file!");
  }
  }
  if (inputString.equals("delete\r\n"))
  {
    myfile.close();
  if(SD.remove(file_name))
  {
  Serial.println("file has been deleted,please reset device (it is in while (1) loop)!");
    while(1);
  }
  }
}
  delay_var = 2;
  duration_alg1 = micros();
  //dataString = "";
    //INPUTS
  dataString += String(analogRead(0)); //A0
  dataString += " "; delay(delay_var);
  dataString += String(analogRead(1)); //A1
  dataString += " "; delay(delay_var);
  dataString += String(analogRead(2)); //A2
  dataString += " "; delay(delay_var);
  dataString += String(analogRead(3)); //A3
  dataString += " "; delay(delay_var);
    //OUTPUTS
  dataString += String(analogRead(4)); //A4
  dataString += " "; delay(delay_var);
  dataString += String(analogRead(5));//A5
  dataString += " ";delay(delay_var);
  dataString += String(analogRead(8)); //A6
  dataString += " "; delay(delay_var);
  dataString += String(analogRead(9));//A7
  dataString += " ";
  File dataFile = SD.open(file_name, FILE_WRITE);
  if (dataFile) 
  {
    dataFile.println(dataString);
    dataFile.close();
  }
  else
  {
    pinMode(5, OUTPUT);
    tone(5, 1000); 
    delay(500);       
    noTone(5); 
  }
 Serial.println(dataString);
  
  duration_alg1 = micros() - duration_alg1;

  dataString = "";
  dataString += String(duration_alg1/1000); 
  dataString += " ";
}
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString = inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}


