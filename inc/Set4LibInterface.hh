#ifndef SET4LIBINTERFACE_HH
#define SET4LIBINTERFACE_HH


#include <string>
#include <iostream>
#include <memory>
#include "LibInterface.hh"
#include <map>


using namespace std;
/*!
* \brief Zdefiniowanie typu do trzymania wtyczek
*/
typedef  map<string, shared_ptr<LibInterface>>  Map_LibIter;


/*!
 * \file
 * \brief Zawiera definicję klasy Set4LibInterface
 *
 * Plik zawiera definicję klasy Set4LibInterface.
 * jest to definicja klasy, która przechowuje zbiór wtyczek zapisanych w postaci klasy Interp4Command
 */

class Set4LibInterface{
    /*!
    * \brief Obiekt typu Mapa przechowujący interfejsy klasy LibInterface
    *
    * Obiekt pozwalający na przechowywanie interfejsów zdefiniowanych poprzez klasę LibInterface
    */
    Map_LibIter Set4LibInterfaces;

    public:
    
    /*!
    * \brief Metoda pozwalająca na dodanie nowego interfejsu
    *
    * \param [in] Name_Interface - nazwa interfejsu do dodania
    * \retval true - Zwracane w przypadku prawidłowego załadowania interfejsu
    * \retval false - Zwracane w przypadku NIE prawidłowego załadowania interfejsu
    */
    bool Add_Interface(const string& Name_Interface);


    /*!
     * \brief Metoda pozwalająca na wyszukanie konkretego interfejsu
     * 
     * \param [in] Name - nazwa szukanego  interfejsu
     * \retval shared_ptr<LibInterface> - wskaznik na wyszukany interfejs w przypadku jego znalezienia
     * \retval nullptr - w przypadku jego NIE znalezienia
     */
    shared_ptr<LibInterface> Find_TheInterface(const string& Name);

};




#endif