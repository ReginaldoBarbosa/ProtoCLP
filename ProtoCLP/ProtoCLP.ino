#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void ldcPrint(String command,int col = 0,int lin = 0,int flagClear = 0);

class commandList{
  private:
    String commandStringList[8] = {"INICIO","END","COMUTAR","GOTO","AQUI","IF","ENDIF","DELAY"};
    String commandCodList[8]    = {"(",")","A#","G#","H#","C#$","]","D#"};
    String stateList[2]         = {"T","F"};
    int    nCommand             = 8;
  public:
    commandList(){};
    
    String getCommandString(int command){
      return commandStringList[command];
    }
    String getCommandCod(int command){
      return commandCodList[command];
    }
    String getState(int command){
      return stateList[command];
    }    
    int getNcommand(){
      return nCommand;
    }
    
};

class commandLine{
  
  private:
    String lineCommand;
    String command;
    String state = "3";
    String value;
 
  public:
    commandLine(){};
    commandLine(String lineCommand){
      lineComman(lineCommand);
      }
    
    void lineComman(String lineCommand){
      lineCommand.toUpperCase();
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
        if(!strcmp(stateStr.c_str(),"TRUE"))setState("TRUE");
        else if(!strcmp(stateStr.c_str(),"FALSE")) setState("FALSE");
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

class commandTranslate{
  private:
    commandList reference;
  
    String commandTranslated = "";
        
  public:

    commandTranslate(){};
    
    String translater(commandLine command){
      String transl;
      int commandNumber = reference.getNcommand();
      
      for(int i = 0; i<commandNumber;i++){
        if(command.getCommand() == reference.getCommandString(i)){
          transl = reference.getCommandCod(i);
          break;
        }
      }
      
      if((transl.indexOf('#')!=-1)&&(transl.indexOf('$')==-1)){
        transl = transl.substring(0,(int)transl.indexOf('#')) + command.getValue();
      }
      if((transl.indexOf('#')!=-1)&&(transl.indexOf('$')!=-1)){
        transl = transl.substring(0,(int)transl.indexOf('#')) + command.getValue(); 
        if(command.getState()=="TRUE") transl= transl.substring(0,(int)transl.indexOf('$')) + reference.getState(0)+"[";
        if(command.getState()=="FALSE")transl= transl.substring(0,(int)transl.indexOf('$')) + reference.getState(1)+"[";         
      }
      return transl + " "; 
    }
    void append(commandLine command){
      this->commandTranslated = this->commandTranslated + translater(command);
    }
    String getCommandTranslated(){
      return this->commandTranslated;
    }
};

String SCRIPT[10] = {"INICIO;","COMUTAR 2;","AQUI 2;","COMUTAR 1;","IF 3 TRUE;","GOTO 2;","ENDIF;","DELAY 10;","COMUTAR 1;","END;"};


void setup() {
  Serial.begin(9600);


  commandLine comand;
  commandTranslate ct;
  String script;
  int i = 0;
  
  while(i<(sizeof(SCRIPT)/sizeof(String))){
   script = SCRIPT[i];
   comand.lineComman(script);
   ct.append(comand);
   i++;
   
  }
  
  Serial.println(ct.getCommandTranslated());


  
}

void loop() {

}


void ldcPrint(String command,int col,int lin,int flagClear){

   if(flagClear == 1)lcd.clear();
   lcd.setCursor(col, lin);
   lcd.print(command);
}
