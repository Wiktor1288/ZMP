#include "LibInterface.hh"
using namespace std;

bool LibInterface::Init_LibInter(const string& Plugin_Name){
    Lib_Hnd_p = dlopen(Plugin_Name.c_str(), RTLD_LAZY);

    if(!Lib_Hnd_p){
       cerr << "Problem with open Lib_HND_p" << endl;
       return false;
    }

    void *Fun_p = dlsym(Lib_Hnd_p,"CreateCmd");

    if(!Fun_p){
        cerr << "CreateCmd doesn't exist" << endl;
        return false;
    }
    
    CreateCmd_p = *reinterpret_cast<Interp4Command* (**)(void)>(&Fun_p);

    return true;
}