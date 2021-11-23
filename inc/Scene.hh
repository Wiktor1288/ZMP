#pragma once



#include <string>
#include <iostream>
#include <memory>
#include <map>
#include "MobileObj.hh"
#include "Vector3D.hh"
using namespace std;

/*!
* \brief Zdefiniowanie typu  Map_MobileObj jako map obiektów klasy MobileObj z kluczem string
*/
typedef  map<string, shared_ptr<MobileObj>> Map_MobileObj;


/*!
 * \file
 * \brief Zawiera definicję klasy Scene
 *
 * Plik zawiera definicję klasy Scene.
 * jest to definicja klasy, która przechowuje Listę obiektów klasy MobileObj, które powinny zostać wyświetlone
 * w programie wizualizującym
 */
class Scene{

    /*!
     * \brief Lista obiektów klasy MobileObj
     */
    Map_MobileObj List_of_object;

private:

    /*!
     * \brief konstruktor bezparametryczny klasy Scene
     */
    Scene();

    /*!
     * \brief dekonstruktor  klasy Scene
     */
    ~Scene();


    /*!
     * \brief Metoda pozwalająca na wyszukanie obiektu o podanej nazwie
     * 
     * \param [in] Name_object - nazwa szukanego  obiektu
     * \retval shared_ptr<MobileObj> - wskaznik na wyszukany obiekt, zwracany w przypadku jego znalezienia
     * \retval nullptr -zwracany  w przypadku jego NIE znalezienia.
     */
    shared_ptr<MobileObj> FindMobileObj(string Name_object);

};





