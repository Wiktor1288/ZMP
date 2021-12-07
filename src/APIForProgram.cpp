
#include "APIForProgram.hh"
#define LINE_SIZE 500


APIForProgram::APIForProgram(Map_MobileObj &list_Objects){

    this->_scene= new Scene(list_Objects);
    OpenConnection();
    InitObjects();

}


APIForProgram::~APIForProgram(){

    if(this->_scene != nullptr){
        delete this->_scene;
    }

    if(this->_sender != nullptr){
        delete this->_sender;
    }

}


void APIForProgram::OpenConnection(){

    this->_sender = new Sender(this->_scene);

    if(this->_sender->OpenConnection()==false){
        cerr << "Nie udało się otworzyć połączenia!" << endl;
        exit(7);
    }
}

void APIForProgram::InitObjects(){

    auto objects_list = this->_scene->GetObjectPointer();
   if (!this->_sender->OpenConnection()){
    cerr << "Connection problem" << endl;
    exit(6);
  } 
for (auto object_ptr : objects_list)
  {
    auto object = object_ptr.get();

    string message = "AddObj ";
    message += object->GetStateDesc();

    this->_sender->Send(message.c_str());
    cout<< message <<endl;
  }
}



bool APIForProgram::ExecActions(istream &Str4Cmds_read, Set4LibInterface &LibInterfaces){

  return false;
  
}

bool APIForProgram::ExecPreprocesor(const char * File_name,istringstream & IStrm4Cmds )
{
  string Cmd4Preproc = "cpp -P ";
  char Line[LINE_SIZE];
  ostringstream OTmpStrm;

  Cmd4Preproc += File_name;
  FILE * pProc = popen(Cmd4Preproc.c_str(),"r");

  if(!pProc)
    return false;

  while(fgets(Line,LINE_SIZE,pProc)){
    OTmpStrm<<Line;
  }

  IStrm4Cmds.str(OTmpStrm.str());
  return pclose(pProc) == 0;
}

