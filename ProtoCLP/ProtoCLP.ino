#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void ldcPrint(String command,int col = 0,int lin = 0,int flagClear = 0);

class commandLine{
  
  private:
    String lineCommand;
    String command;
    String state = "3";
    String value;
 
  public:

    commandLine(String lineCommand){
      lineCommand.toLowerCase();
      String commandStr,valueStr,stateStr = "#", wordAux = "";
      int count = 0, countVar = 0;
      do{
        wordAux = wordAux + lineCommand[count];
        count++;         
        if((lineCommand[count] == ' ')||(lineCommand[count] == ';')){
          if(countVar == 0)setCommand(wordAux);
          if(countVar == 1)setValue(wordAux);
          if(countVar == 2)stateStr = wordAux;
          
          countVar++;
          wordAux = "";
          if(lineCommand[count] == ';')count--;
          count++;
        }
 
      }while(lineCommand[count] != ';');

      if(strcmp(stateStr.c_str(),"#")){
        if(!strcmp(stateStr.c_str(),"true"))setState("true");
        else if(!strcmp(stateStr.c_str(),"false")) setState("false");
             else setState("$");            
      }

    }
    
    void setCommand(String command){
      this->command = command;
    }

    void setValue(String value){
      this->value = value;
    }

    void setState(String state){
      this->state = state;
    }
    
    String getCommand(){
      return this->command;
    }
    
    String getValue(){
      return this->value;
    }

    String getState(){
      return this->state;
    }

};


String SCRIPT[10] = {};


void setup() {
  Serial.begin(9600);

  commandLine comand("PALAVRA 12 TRUE;");

  Serial.println(comand.getCommand());
  Serial.println(comand.getValue());
  Serial.println(comand.getState());

  
}

void loop() {

}


void ldcPrint(String command,int col,int lin,int flagClear){

   if(flagClear == 1)lcd.clear();
   lcd.setCursor(col, lin);
   lcd.print(command);
}
