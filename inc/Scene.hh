#pragma once



#include <string>
#include <iostream>
#include <memory>
#include <map>
#include "MobileObj.hh"
#include "Vector3D.hh"
#include "AccessControl.hh"
#include <vector>

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
class Scene: public AccessControl {

    /*!
     * \brief Lista obiektów klasy MobileObj
     */
    Map_MobileObj List_of_object;

private:

    /*!
     * \brief konstruktor paramertyczy klasy Scene
     *
     * \param [in] List_of_object lista obiektów jąk ma być zainicjalizowana lista Scene::List_of_object
     */
    Scene(Map_MobileObj &List_of_object);

    /*!
     * \brief dekonstruktor  klasy Scene
     */
    ~Scene(){

    }


    /*!
     * \brief Metoda pozwalająca na wyszukanie obiektu o podanej nazwie
     * 
     * \param [in] Name_object - nazwa szukanego  obiektu
     * \retval shared_ptr<MobileObj> - wskaznik na wyszukany obiekt, zwracany w przypadku jego znalezienia
     * \retval nullptr -zwracany  w przypadku jego NIE znalezienia.
     */
    shared_ptr<MobileObj> FindMobileObj(const string Name_object);


    /*!
     * \brief Metoda pozwalająca na dadanie nowego pojedyńczego obiektu do listy Scene::List_of_object
     * 
     * \param [in] Name_object - nazwa szukanego  obiektu
     */
    void AddObjToList(const std::string Name_object);


   
    /*!
     * \brief Metoda zwracająca vector nazw obiektów znajdujących się na scenie
     * 
     */
    vector<string> GetObjectNames();
   
      
    /*!
     * \brief Metoda zwracająca vector wskaźników na obiekty znajdujących się na scenie
     * 
     */
    vector<shared_ptr<MobileObj>> GetObjectPointer();

};





