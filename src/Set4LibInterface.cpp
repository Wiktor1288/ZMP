    
#include "Set4LibInterface.hh"


using namespace std;

shared_ptr<LibInterface> Set4LibInterface::Find_TheInterface(const string& Name){
    const string& Plugin_Name = "libs/libInterp4" + Name + ".so";


    
    auto it = Set4LibInterfaces.find(Plugin_Name);
    if (it == Set4LibInterfaces.end()){
        return nullptr;
    }
    return it->second;
}

bool Set4LibInterface::Add_Interface(const string& Name_Interface){
    shared_ptr<LibInterface> libInterface = make_shared<LibInterface>();
    if(!libInterface->Init_LibInter(Name_Interface)){
        cerr << "Couldnt load " << Name_Interface << endl;
        return false;
    }
    Set4LibInterfaces.insert({Name_Interface, libInterface});
   
    return true;
}


