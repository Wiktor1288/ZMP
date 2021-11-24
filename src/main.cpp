#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <string>
#include <sstream>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "Set4LibInterface.hh"
#include <list>
#include "xmlinterp.hh"
#include "Sender.hh"

#define LINE_SIZE 500
using namespace std;
using namespace xercesc;





/*!
 * Czyta z pliku opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param CmdList - (\b we.) zarządca listy poleceń dla robota.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
bool ReadFile(const char* sFileName, Configuration &rConfig);





/*!
 * \brief Wykonuje preprocesor na podanym pliku.
 *
 * \param[in] NazwaPliku - Nazwa pliku do interpretacji.
 * \param[out] IStrm4Cmds - Strumień, do którego jest wczytywana zinterpretowana zawartość.
 * \retval true - jeśli preprocesor został wykonany poprawnie i nastąpiło zamknięcie pliku.
 * \retval false - Niepowodzenie wykonania.
 */
bool ExecPreprocesor(const   char * NazwaPliku, istringstream & IStrm4Cmds );

/*!
 * \brief Wykonuje preprocesor na podanym pliku.
 *
 * \param[in] Str4Cmds_read - Nazwa pliku do interpretacji.
 * \retval true - jeśli preprocesor został wykonany poprawnie i nastąpiło zamknięcie pliku.
 * \retval false - Niepowodzenie wykonania.
 */
bool ExecActions(istream &Str4Cmds_read, Set4LibInterface &LibInterfaces);


int main(int argc, char **argv)
{
  Set4LibInterface Set_LibInterfaces;
  istringstream Istrm4Cmds;
  Configuration   Config;

  int Socket4Sending;   
 
 

  if(argc < 2){
    cerr << "Missed arguments" << endl;
    return 1;
  }

  if (!ReadFile("config/config.xml",Config)){
    cerr << "reading xml failed" << endl;
    return 5;
  } 


  if(!ExecPreprocesor(argv[1],Istrm4Cmds)){
    cerr << "Reading from file failed" << endl;
    return 2;
  }

  if (!OpenConnection(Socket4Sending)){
    cerr << "Connection problem" << endl;
    return 6;
  } 


  auto list_lib = Config.GetLibList();

  cout << "Dodawanie bibliotek ...\n";
  for(size_t i=0; i < list_lib.size(); i++){
    Set_LibInterfaces.Add_Interface(list_lib.at(i));
  }
  auto obj_list=Config.GetObjectList();
  Scene Scn(obj_list);
  Sender   ClientSender(Socket4Sending,&Scn);
  thread   Thread4Sending(Fun_CommunicationThread,&ClientSender);
 auto objects_list = Scn.GetObjectPointer();
for (auto object_ptr : objects_list)
  {
    auto object = object_ptr.get();

    string message = "AddObj ";
    message += object->GetStateDesc();

    Send(Socket4Sending,message.c_str());
  }
  
  if(!ExecActions(Istrm4Cmds, Set_LibInterfaces)){
    cerr << "Reading cmd file failed" << endl;
    return 4;
  }

usleep(100000);
  Send(Socket4Sending,"Close\n");
  ClientSender.CancelCountinueLooping();
  Thread4Sending.join();
  close(Socket4Sending);

}


bool ExecActions(istream &Str4Cmds_read, Set4LibInterface &LibInterfaces){

  string Cmd_Word;
  shared_ptr<LibInterface> Lib_interface_p;

  while(Str4Cmds_read >> Cmd_Word){
    Lib_interface_p=LibInterfaces.Find_TheInterface(Cmd_Word);
    if(Lib_interface_p == nullptr){
      cerr << "Command:  " << Cmd_Word << " doesn't exist" << endl;
      return false;
    }

    Interp4Command *Command_p =Lib_interface_p->CreateCmd_p();
    if (!Command_p->ReadParams(Str4Cmds_read))
    {
      cerr << "Reading command " << Cmd_Word << " field" << endl;
      return false;
    }
    
    cout << "Command: ";
    Command_p->PrintCmd();
  }


  return true;
}


bool ExecPreprocesor(const   char * NazwaPliku, istringstream & IStrm4Cmds )
{
  string Cmd4Preproc = "cpp -P ";
  char Line[LINE_SIZE];
  ostringstream OTmpStrm;

  Cmd4Preproc += NazwaPliku;
  FILE * pProc = popen(Cmd4Preproc.c_str(),"r");

  if(!pProc)
    return false;

  while(fgets(Line,LINE_SIZE,pProc)){
    OTmpStrm<<Line;
  }

  IStrm4Cmds.str(OTmpStrm.str());
  return pclose(pProc) == 0;
}





