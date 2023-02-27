#include <LiquidCrystal.h>


String SCRIPT = "ACIONAR 2";

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void ldcPrint(String comand,int col = 0,int lin = 0,int flagClear = 0);
String getScriptLine();


void setup() {
  lcd.begin(16, 2);

  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);

}

void loop() {
  
  if(getScriptLine() == "ACIONAR 1")digitalWrite(8,HIGH);
  if(getScriptLine() == "ACIONAR 2")digitalWrite(9,HIGH);
  if(getScriptLine() == "ACIONAR 3")digitalWrite(10,HIGH);
  ldcPrint(getScriptLine());  
 
}


void ldcPrint(String comand,int col,int lin,int flagClear){

   if(flagClear == 1)lcd.clear();
   lcd.setCursor(col, lin);
   lcd.print(comand);
    
  
  }

String getScriptLine(){
  return SCRIPT; 
 }
