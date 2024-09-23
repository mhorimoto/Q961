#include <LiquidCrystal_I2C.h>   // ライブラリのインクルード
#include <IRremote.hpp>
#include <IRremote.h>

// LiquidCrystal_I2C型変数の宣言
LiquidCrystal_I2C lcd(0x27, 16 , 2);  // 0x27のアドレス,16列2行のLCDを使用

#define BUTTON_PIN      2

int value = 0;
int SEND_LED_PIN1 = 8;

volatile int currentdata;
volatile int lastdata;

IRsend IrSender1;
IRsend IrSender2;
IRsend IrSender3;
IRsend IrSender4;

uint8_t sCommand1 = 0x10;
uint8_t sCommand2 = 0x11;
uint8_t sCommand3 = 0x12;
uint8_t sCommand4 = 0x13;
uint8_t sRepeats = 0;

void setup(){

  pinMode(5,OUTPUT);

  lcd.init();                    // LCDの初期化
  //lcd.backlight();               // LCDバックライトの点灯

  lcd.setCursor(0, 0);           // カーソルの位置を指定
  lcd.print("I2C connect");      // 文字の表示

  lcd.setCursor(0, 1);           // カーソルの位置を指定
  lcd.print(" Arduino ");  // 文字の表示

  pinMode(BUTTON_PIN,INPUT_PULLUP );

  Serial.begin(115200);

  lastdata = digitalRead(BUTTON_PIN); 

  attachInterrupt(0,IR,FALLING);

  digitalWrite(5,LOW);

  IrSender1.begin(SEND_LED_PIN1);
  IrSender2.begin(SEND_LED_PIN1);
  IrSender3.begin(SEND_LED_PIN1);
  IrSender4.begin(SEND_LED_PIN1);
}

void loop(){
  switch(value) {
  case 1:
    IrSender1.sendNEC(0x00, sCommand1, sRepeats);
    lcd.setCursor(0, 0);           
    lcd.print("0xEF10FF00 ");
    lcd.setCursor(0, 1);           
    lcd.print("street1");
    delay(100);
    Serial.println("ggg");
  break;
  case 2:
    IrSender2.sendNEC(0x00, sCommand2, sRepeats);
    lcd.setCursor(0, 0);           
    lcd.print("0xEE11FF00 ");
    lcd.setCursor(0, 1);           
    lcd.print("street2");
  break;
  case 3:
    IrSender3.sendNEC(0x00, sCommand3, sRepeats);
    lcd.setCursor(0, 0);           
    lcd.print("0xED12FF00 ");
    lcd.setCursor(0, 1);           
    lcd.print("street3");
  break;
  case 4:
    IrSender4.sendNEC(0x00, sCommand4, sRepeats);
    lcd.setCursor(0, 0);           
    lcd.print("0xEC13FF00 ");
    lcd.setCursor(0, 1);           
    lcd.print("street4");
  break;
  default:
    lcd.setCursor(0, 0);           
    lcd.print("  No signal  ");
    lcd.setCursor(0, 1);           
    lcd.print("                  ");
  }
  delay(100);
}

void IR(void){
  delay(50);
  int i,j;
  for(i=0;i<50;i++) {
    i=i+i-i;
    j=j*j;
  }
  currentdata = digitalRead(BUTTON_PIN);
  if ((currentdata != lastdata) && (currentdata == 0)) {
    value++;
    Serial.print(value);
    Serial.print(" ");
    if(value>4){
      value = 0;
    }
  }
  currentdata = 1;
  lastdata = currentdata;
}