#include <LiquidCrystal.h>


class commandValue{
  
  private:
    String lineCommand;
    
    String command;
    String state;
    
    int value;

    
    
    
  
  public:

    commandValue(String lineCommand){

      String commandStr,valueStr,stateStr;
      
    }
    
    void setCommand(String command){
      this->command = command;
    }

    void setValue(int value){
      this->value = value;
    }

    String getCommand(){
      return this->command;
    }
    
    int getValue(){
      return this->value;
    }
};

String SCRIPT = "PALAVRA\n";

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void ldcPrint(String command,int col = 0,int lin = 0,int flagClear = 0);


void setup() {
  Serial.begin(9600);
  commandValue line(SCRIPT);

  Serial.print("Comando: ");
  Serial.println(line.getCommand());
  Serial.print("Valor: ");
  Serial.print(line.getValue());
  
}

void loop() {

  
  

}


void ldcPrint(String command,int col,int lin,int flagClear){

   if(flagClear == 1)lcd.clear();
   lcd.setCursor(col, lin);
   lcd.print(command);
    
  
  }
