#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <string>
#include <sstream>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "Set4LibInterface.hh"
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xmlinterp.hh"
#include <list>


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
bool Init_LIBs(Set4LibInterface &LibInterfaces);

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

  if(!Init_LIBs(Set_LibInterfaces)){
    cerr << "Opening libs failed" << endl;
    return 3;
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


bool Init_LIBs(Set4LibInterface &LibInterfaces){
  
  if(LibInterfaces.Add_Interface("libs/libInterp4Move.so"))
    if(LibInterfaces.Add_Interface("libs/libInterp4Rotate.so"))
      if(LibInterfaces.Add_Interface("libs/libInterp4Set.so"))
        if(LibInterfaces.Add_Interface("libs/libInterp4Pause.so"))
          return true;


  return false;
}



bool ReadFile(const char* sFileName, Configuration &rConfig)
{
   try {
            XMLPlatformUtils::Initialize();
   }
   catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cerr << "Error during initialization! :\n";
            cerr << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return 1;
   }

   SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

   pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
   pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
   pParser->setFeature(XMLUni::fgXercesDynamic, false);
   pParser->setFeature(XMLUni::fgXercesSchema, true);
   pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

   pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

   DefaultHandler* pHandler = new XMLInterp4Config(rConfig);
   pParser->setContentHandler(pHandler);
   pParser->setErrorHandler(pHandler);

   try {
     
     if (!pParser->loadGrammar("config/config.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
       cerr << "!!! Plik grammar/actions.xsd, '" << endl
            << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
            << endl;
       return false;
     }
     pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
     pParser->parse(sFileName);
   }
   catch (const XMLException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            XMLString::release(&sMessage);
            return false;
   }
   catch (const SAXParseException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            cerr << "Blad! " << endl
                 << "    Plik:  " << sSystemId << endl
                 << "   Linia: " << Exception.getLineNumber() << endl
                 << " Kolumna: " << Exception.getColumnNumber() << endl
                 << " Informacja: " << sMessage 
                 << endl;

            XMLString::release(&sMessage);
            XMLString::release(&sSystemId);
            return false;
   }
   catch (...) {
            cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
   }

   delete pParser;
   delete pHandler;
   return true;
}
