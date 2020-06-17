#include <SPI.h> 
#include <MFRC522.h> // RFID Module
#include <LiquidCrystal.h> // LCD Module
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

#define beep_pin 8
float amt1=0;                       // for RFID-1
float amt2=0;                       // for RFID-2
float total=0;                      // Total Billing amount
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Setting RS:2,EN:3,D4:4,D5:5,D6:6,D7:7 PINS of LCD display
void setup()
{
  Serial.begin(9600);   // Initiate a serial communication
 
  pinMode(beep_pin,OUTPUT); // Setting pin 8 as output pin for BUZZER
  digitalWrite(beep_pin,LOW); // Initializing BUZZER->LOW
 
  lcd.begin(16, 2);  // Number of columns and rows of LCD Display (Size of LCD Display)      
  lcd.setCursor(0, 0);     // Setting up co-ordinates(X,Y) on LCD for cursor at (0,0)
  lcd.print("Circuit is Ready"); // Display in LCD
  delay(2000); // Time the Text should be displayed on LCD in milliseconds
  lcd.clear();  // Clear the LCD display
 
   
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop()
{
  digitalWrite(beep_pin, LOW); // Set the buzzer as low initially
  lcd.clear(); // Clear the display of LCD
  lcd.setCursor(0,0); // Set the coordinates of Display
  lcd.print("SMART SHOPPING");  // Display the text on LCD
  lcd.setCursor(0,1); // Next line of LCD
  lcd.print("    CART"); // Display the text on LCD
  delay(1000); // Display the text for 1 second
  lcd.setCursor(0, 0); // Set the coordinates of Display
  lcd.print("Put your card to"); // Display the text on LCD
  lcd.setCursor(0, 1); // Next line of LCD
  lcd.print("the reader......");// Display the text on LCD
  delay(4000); // Display the text for 4 seconds
 
                                             // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
                                             // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  } 
// Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor 
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  
 if (content.substring(1) == "F9 B4 28 B9" or content.substring(1) == " B2 74 F0 2D" /*|| content.substring(1) == " 41 38 B0 09"*/ ) //change here the UID of the card/cards that have Acccess
    digitalWrite(beep_pin,HIGH); // Buzzer is set to high
    delay(200); // For 2 seconds
    digitalWrite(beep_pin,LOW); // Then buzzer is set to low
    delay(100); // In 1 second
    lcd.clear(); // Clear the LCD Display
    lcd.setCursor(0, 0); 
    lcd.print("Product ID : ");
    lcd.print(content.substring(1)); // Display the UID of the tag
    delay(1500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ITEM-1 scanned"); // Display Name of Product
    delay(1500);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Amount: Rs.100/-"); //Display price of Product
    delay(1500);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("THANK YOU!!!"); 
    Serial.println("Authorized access"); // Access Accepted
    delay(1500);      
  }
 
 else   {
    digitalWrite(beep_pin,HIGH);
    lcd.setCursor(0, 0);
    lcd.print("ID : "); // UID of the tag
    lcd.print(content.substring(1));
    lcd.setCursor(0, 1);
    lcd.print("Access denied"); // Access denied for not registered members
    Serial.println(" Access denied");
    delay(1500);
     }
}  
