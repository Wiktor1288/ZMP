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
#include "APIForProgram.hh"


using namespace std;




int main(int argc, char **argv)
{
  Set4LibInterface Set_LibInterfaces;
  istringstream Istrm4Cmds;
  Configuration   Config; 
 
 

  if(argc < 2){
    cerr << "Missed arguments" << endl;
    return 1;
  }

  if (!ReadFile("config/config.xml",Config)){
    cerr << "reading xml failed" << endl;
    return 5;
  } 

/*
  if(!ExecPreprocesor(argv[1],Istrm4Cmds)){
    cerr << "Reading from file failed" << endl;
    return 2;
  }
*/



  auto list_lib = Config.GetLibList();
  cout << "Dodawanie bibliotek ...\n";
  for(size_t i=0; i < list_lib.size(); i++){
    Set_LibInterfaces.Add_Interface(list_lib.at(i));
  }


  auto obj_list=Config.GetObjectList();
  APIForProgram _API_1(obj_list);
  

}











