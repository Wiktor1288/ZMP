#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <string>
#include <sstream>
#include "Interp4Command.hh"
#include "MobileObj.hh"

#define LINE_SIZE 500
using namespace std;

/*!
 * \brief Wykonuje preprocesor na podanym pliku.
 *
 * \param[in] NazwaPliku - Nazwa pliku do interpretacji.
 * \param[out] IStrm4Cmds - Strumień, do którego jest wczytywana zinterpretowana zawartość.
 * \retval true - jeśli preprocesor został wykonany poprawnie i nastąpiło zamknięcie pliku.
 * \retval false - Niepowodzenie wykonania.
 */
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

int main()
{
  void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Move)(void);
  void *pLibHnd_Set = dlopen("libInterp4Set.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Set)(void);
  void *pLibHnd_Pause = dlopen("libInterp4Pause.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Pause)(void);
  void *pLibHnd_Rotate = dlopen("libInterp4Rotate.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Rotate)(void);
  void *pFun;
  void *sFun;
  void *dFun;
  void *rFun;

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





  if (!pLibHnd_Pause) {
    cerr << "!!! Brak biblioteki: Interp4Pause.so" << endl;
    return 1;
  }


  dFun = dlsym(pLibHnd_Pause,"CreateCmd");
  if (!dFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Pause = *reinterpret_cast<Interp4Command* (**)(void)>(&dFun);

  Interp4Command *dCmd = pCreateCmd_Pause();


    if (!pLibHnd_Rotate) {
    cerr << "!!! Brak biblioteki: Interp4Rotate.so" << endl;
    return 1;
  }


  rFun = dlsym(pLibHnd_Rotate,"CreateCmd");
  if (!rFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Rotate = *reinterpret_cast<Interp4Command* (**)(void)>(&rFun);

  Interp4Command *rCmd = pCreateCmd_Rotate();


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


  cout << endl;
  cout << dCmd->GetCmdName() << endl;
  cout << endl;
  dCmd->PrintSyntax();
  cout << endl;
  dCmd->PrintCmd();
  cout << endl;
  delete dCmd;
  dlclose(pLibHnd_Pause);

  cout << endl;
  cout << rCmd->GetCmdName() << endl;
  cout << endl;
  rCmd->PrintSyntax();
  cout << endl;
  rCmd->PrintCmd();
  cout << endl;
  delete rCmd;
  dlclose(pLibHnd_Rotate);
}
