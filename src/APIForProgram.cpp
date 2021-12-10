
#include "APIForProgram.hh"


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
    this->_scene->SetSocket(this->_sender->ReturnSocket());
}

void APIForProgram::InitObjects(){
    this->_sender->Send("Clear \n");
    auto objects_list = this->_scene->GetObjectPointer();
  
for (auto object_ptr : objects_list)
  {
    auto object = object_ptr.get();

    string message = "AddObj ";
    message += object->GetStateDesc();

    this->_sender->Send(message.c_str());
    cout<< message  << "xx"<<endl;
  }

   
}



bool APIForProgram::ExecActions(const char* file_name, Set4LibInterface &lib_interfaces){

    istringstream _input_string;
    this->ExecPreprocesor(file_name,_input_string);
    string commnad_name;
    string object_name;
   

    while(_input_string >> commnad_name){
    vector<std::thread*> threads_vector;
        while(!(commnad_name=="Begin_Parallel_Actions")){
            _input_string >> commnad_name;
        }

        while(!(commnad_name=="End_Parallel_Actions")){
          
            _input_string >> commnad_name;

            if(commnad_name == "End_Parallel_Actions"){
                break;
            }

            _input_string >> object_name;
            auto _lib = lib_interfaces.Find_TheInterface(commnad_name);

            if(_lib == nullptr){
                cerr << "\n  Program doesn't find library: " << commnad_name << endl;
                return false;
            }

            auto _cmd = _lib->CreateCmd_p();
            if(_cmd->ReadParams(_input_string)==false){
                cerr << "Reading command " << commnad_name << " field" << endl;
                delete _cmd;
                return false;
            }

            auto _object = _scene->FindMobileObj(object_name);
            if(!_object){
                cerr << "Object:" << object_name <<"doesn't exist"  << endl;
                delete _cmd;
                return false;
            }

            std::thread  *_nthread = new std::thread(&Interp4Command::ExecCmd, _cmd, _object.get(), _scene,_sender);
            threads_vector.push_back(_nthread);
      
        }

            for(auto thread_obj : threads_vector){
                cout << "cps\n";
                thread_obj->join();
                delete thread_obj;
            }

        }
    return true;
  
}

bool APIForProgram::ExecPreprocesor(const char * file_name, istringstream & iStrm4Cmds )
{
  string Cmd4Preproc = "cpp -P ";
  char Line[LINE_SIZE];
  ostringstream OTmpStrm;

  Cmd4Preproc += file_name;
  FILE * pProc = popen(Cmd4Preproc.c_str(),"r");

  if(!pProc)
    return false;

  while(fgets(Line,LINE_SIZE,pProc)){
    OTmpStrm<<Line;
  }

  iStrm4Cmds.str(OTmpStrm.str());
  return pclose(pProc) == 0;
}

