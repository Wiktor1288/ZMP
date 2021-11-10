#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include <iostream>
#include <sstream>
#include <cstring>
#include <dlfcn.h>
#include "Interp4Command.hh"

using namespace std;




/*!
 * \file
 * \brief Deklaracja klasy LibInterface
 *
 * Deklaracja i definicja klasy LibInterface
 */


class LibInterface{

    /*!
     * \brief Uchwyt wtyczki
     */
    void* Lib_Hnd_p;

    /*!
     * \brief Wskaznik na konkretny interfejs
     */
    

    public:
    /*!
     * \brief Dekonstuktor  klasy LibInterface
     */
    ~LibInterface(){
        if(Lib_Hnd_p){
            dlclose(Lib_Hnd_p);
        }
    };
    Interp4Command *(*CreateCmd_p)(void);

     /*!
     * \brief Metoda pozwalająca na inicjalizację interfejsu danego polecenia
     *
     * \param [in] Plugin_Name - nazwa polecenia
     * \retval true - Zwracane w przypadku prawidłowego załadowania interfejsu
     * \retval false - Zwracane w przypadku NIE prawidłowego załadowania interfejsu
     */
    bool Init_LibInter(const string& Plugin_Name);
};
#endif
