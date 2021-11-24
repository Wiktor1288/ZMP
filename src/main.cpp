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

/*!
 * \brief Funkcja pozwalająca załadować biblioteki do obiektu klasy Set4LibInterface 
 *
 * \param[in] LibInterfaces - Nazwa obiektu przechowującego interfejsy wtyczek.
 * \retval true - Zwracane jeśli operacja załączania bibliotek przebiegła prawidłowo
 * \retval false - Zwracane jeśli operacja załączania bibliotek przebiegła NIE prawidłowo
 */
/*bool Init_LIBs(Set4LibInterface &LibInterfaces);*/

int main(int argc, char **argv)
{
  Set4LibInterface Set_LibInterfaces;
  istringstream Istrm4Cmds;
  Configuration   Config;
 

  if (!ReadFile("config/config.xml",Config)) return 1;

  if(argc < 2){
    cerr << "Missed arguments" << endl;
    return 1;
  }


  if(!ExecPreprocesor(argv[1],Istrm4Cmds)){
    cerr << "Reading from file failed" << endl;
    return 2;
  }


  auto list_lib = Config.GetLibList();

  cout << "Dodawanie bibliotek ...\n";
  for(int i=0; i < list_lib.size(); i++){
    Set_LibInterfaces.Add_Interface(list_lib.at(i));
  }

  if(!ExecActions(Istrm4Cmds, Set_LibInterfaces)){
    cerr << "Reading cmd file failed" << endl;
    return 4;
  }

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

/*
bool Init_LIBs(Set4LibInterface &LibInterfaces){
  
  if(LibInterfaces.Add_Interface("libs/libInterp4Move.so"))
    if(LibInterfaces.Add_Interface("libs/libInterp4Rotate.so"))
      if(LibInterfaces.Add_Interface("libs/libInterp4Set.so"))
        if(LibInterfaces.Add_Interface("libs/libInterp4Pause.so"))
          return true;


  return false;
}*/



