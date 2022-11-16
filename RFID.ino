#include <RFID.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>

int cc, b, k;;

const int p = 2;

int UI[5] = {};

char name[20];
char role[15];

LiquidCrystal_I2C lcd(0x27, 20, 4);
RFID RFID(10, 9);

char u[10] = "";
int UID[4] = {};
int KEY[26][5] = {
	// Keys here.
    // Ex : {0x82, 0x5B, 0xDF, 0x1A, 0x1E},
};
const int buzz = A3;
int check_c(int UID[], int KEY[]) {
  for (int i = 0; i <= 4; i++) {
    if (UID[i] != KEY[i])
      return 0;
  }
  return 1;

}
int check_all(int C[],int K[26][5]){
  UI[5] = {};
  b = 0;
  for(int i = 0;i<=25;i++){
    for (int j = 0;j<= 4;j++){
        UI[j] = K[i][j];
    }  
    if(check_c(C,UI) == 1){
      b = 1;
      cc = i;
      return b;
    }
  }

  return b;
}

void setup() {
  Serial.begin(9600);
  SPI.begin();
  RFID.init();
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome");
  pinMode(buzz, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(p,OUTPUT);
  digitalWrite(p,1);
}

void loop() {
    if (digitalRead (3) == HIGH)
     open();

  if (RFID.isCard()) {

    if (RFID.readCardSerial()) {

      Serial.print("The UID is : ");

      for (int i = 0; i <= 5; i++)
      {
        UID[i] = RFID.serNum[i];
        strcat(UID[i], u);
        Serial.print(u);
        Serial.print(UID[i], HEX);
        Serial.print(" ");
      }
      int c = check_all(UID, KEY);
      if (c == 1) {
          switch(cc){
			  // Adding user for each key.
            case 0:
                strcpy(name,"Andres Iniesta");
                strcpy(role,"PDG");
                break;
            default:
                strcpy(name,"Welcome");           
          }
          lcd.backlight();
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(name);
          lcd.setCursor(0, 1);
          lcd.print(role);
          digitalWrite(6,HIGH);
          digitalWrite(p,0);
          tone(buzz,523,50);
          delay(100);
          tone(buzz, 783, 50);
          delay(100);
          tone(buzz, 1046, 50);
          delay(100);
          tone(buzz, 1568, 50);
          delay(100);
          tone(buzz, 2093, 70);
          delay(250);
          delay(3000);
          digitalWrite(p,1);
          digitalWrite(6,LOW);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Welcome");
        
      }
      else {
        digitalWrite(7, 1);
        tone(buzz,370,50);
        delay(100);
        tone(buzz, 370, 300);
        delay(1000);
        digitalWrite(7, 0);

        lcd.backlight();
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Error !");
        lcd.setCursor(2, 1);
        lcd.print("Members Only");
      }
      Serial.println("");
    }
    RFID.halt();
    delay(100);

  }
}

void open(){
          digitalWrite(6,HIGH);
          digitalWrite(p,0);
          tone(buzz,523,50);
          delay(100);
          tone(buzz, 783, 50);
          delay(100);
          tone(buzz, 1046, 50);
          delay(100);
          tone(buzz, 1568, 50);
          delay(100);
          tone(buzz, 2093, 70);
          delay(250);
          delay(3000);
          digitalWrite(p,1);
          digitalWrite(6,LOW);
}
