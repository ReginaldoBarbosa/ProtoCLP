#include <LiquidCrystal.h>


void ldcPrint(String command,int col = 0,int lin = 0,int flagClear = 0);

class commandLine{
  
  private:
    String lineCommand;
    String command;
    int state = 3;
    int value;
 
  public:

    commandLine(String lineCommand){

      String commandStr,valueStr,stateStr = "#", wordAux = "";
      int count = 0, countVar = 0;
      do{
        wordAux = wordAux + lineCommand[count];
        count++;         
        if((lineCommand[count] == ' ')||(lineCommand[count] == ';')){
          if(countVar == 0)commandStr = wordAux;
          if(countVar == 1)valueStr   = wordAux;
          if(countVar == 2)stateStr   = wordAux;
          
          countVar++;
          wordAux = "";
          if(lineCommand[count] == ';')count--;
          count++;
        }
 
      }while(lineCommand[count] != ';');

      setCommand(commandStr);
      setValue(atoi(valueStr.c_str()));
      if(strcmp(stateStr.c_str(),"#")){
        stateStr.toLowerCase();
        if(!strcmp(stateStr.c_str(),"true")){
          setState(1);
        }
        else if(!strcmp(stateStr.c_str(),"false")){
          setState(0);
        } 
        else setState(2);            
      }

    }
    
    void setCommand(String command){
      this->command = command;
    }

    void setValue(int value){
      this->value = value;
    }

    void setState(int state){
      this->state = state;
    }
    
    String getCommand(){
      return this->command;
    }
    
    int getValue(){
      return this->value;
    }

    int getState(){
      return this->state;
    }

};

String SCRIPT = "PALAVRA 345 tRue;\n";

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {
  Serial.begin(9600);
  commandLine line(SCRIPT);

  Serial.print("Comando:");
  Serial.println(line.getCommand());
  Serial.print("Valor:");
  Serial.println(line.getValue());
  Serial.print("Estado:");
  Serial.print(line.getState());  
}

void loop() {

  
  

}


void ldcPrint(String command,int col,int lin,int flagClear){

   if(flagClear == 1)lcd.clear();
   lcd.setCursor(col, lin);
   lcd.print(command);
}
