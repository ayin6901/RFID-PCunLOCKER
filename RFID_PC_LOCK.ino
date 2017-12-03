//-------------------------------------------------------------------------------//
//                  ______________________________________________               //
//         ________|            _     _             __   __       |_______       //
//         \       |     |/ |/ |_     | | | |\ | | |  | |__|      |      /       //
//          \      |     |\ |\  _|  __| |_| | \| | |__| |  \      |     /        //
//          /      |______________________________________________|     \        //
//         /__________)                                        (_________\       //
//                                                                               //
//                                                                               //
// Arduino code to lock/unlock windows using Arduino and RC522 RFID Module       //
//                                                                               //
// Coded by kks junior (w!z)                                                     //
// www.instructables.com/member/kksjunior                                        //
// www.hackster.io/kksjunior                                                     //
// www.github.com/kksjunior                                                      //
// Contact : dream.code.make@gmail.com                                           //
//                                                                               //
// Connections                                                                   //
//                                                                               //
// VCC  - 3.3V                                                                   //
// RST  - PIN 5                                                                  //
// GND  - GND                                                                    //
// irq  - Not Connected                                                          //
// MISO - ICSP1 (PIN 14)                                                         //
// MOSI - ICSP4 (PIN 16)                                                         //
// SCK  - ICSP3 (PIN 15)                                                         //
// SDA  - PIN 10                                                                 //
//
//170804
//-------------------------------------------------------------------------------//


#include <Keyboard.h>
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
#define KEY_RETURN 0xB0                 //The hex value for the return key is 0xB0.
#define KEY 2
MFRC522 mfrc522 ( SS_PIN, RST_PIN ) ;
char Enter = KEY_RETURN;                //Return key is declared as Enter.
String readid;
String card1 = "b4bc4815";              //Change this value to the UID of your card.

void setup( )
{
  pinMode(KEY, INPUT);
  Serial.begin(9600);
  Keyboard.begin();
  SPI.begin();
  mfrc522.PCD_Init();
}

void temp(byte *buffer, byte bufferSize)//function to store card uid as a string datatype.
{
  readid = "";
  for (byte i = 0; i < bufferSize; i++)
  {
    readid = readid + String(buffer[i], HEX);
  }
}
void loop( )
{
  if (digitalRead(KEY) == 0)
  {
    Keyboard.press(KEY_LEFT_GUI);              //Press the left windows key.
    Keyboard.press('l');                       //Press the "l" key.
    Keyboard.releaseAll();                     //Release all keys.
    delay (1000);
  }
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));  // Display card details in serial Monitor.
  temp(mfrc522.uid.uidByte, mfrc522.uid.size);
  if (readid == card1)
  {

    /*
      Keyboard.press(Enter);                     //Press the Enter key.
      Keyboard.release(Enter);                   //Release the Enter key.
      delay(100);*/
    Keyboard.print("170804");                    // Change this value to your Windows PIN/Password.
    Keyboard.releaseAll();
    delay(100);
    Keyboard.press(Enter); Keyboard.releaseAll();  
    
    delay(1000);

  }
  else
  {
    return;
  }
}

