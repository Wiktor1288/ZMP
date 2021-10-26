#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "Interp4Command.hh"
#include "MobileObj.hh"

using namespace std;


int main()
{
  void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Move)(void);
  void *pLibHnd_Set = dlopen("libInterp4Set.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Set)(void);
  void *pFun;
  void *sFun;
  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
    return 1;
  }


  pFun = dlsym(pLibHnd_Move,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Move = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);

  Interp4Command *pCmd = pCreateCmd_Move();


if (!pLibHnd_Set) {
    cerr << "!!! Brak biblioteki: Interp4Set.so" << endl;
    return 1;
  }


  sFun = dlsym(pLibHnd_Set,"CreateCmd");
  if (!sFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Set = *reinterpret_cast<Interp4Command* (**)(void)>(&sFun);


  Interp4Command *sCmd = pCreateCmd_Set();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  delete pCmd;

  dlclose(pLibHnd_Move);
  cout << endl;
  cout << sCmd->GetCmdName() << endl;
  cout << endl;
  sCmd->PrintSyntax();
  cout << endl;
  sCmd->PrintCmd();
  cout << endl;
  
  delete sCmd;

  dlclose(pLibHnd_Set);
}
