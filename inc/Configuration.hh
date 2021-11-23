#pragma once

#include "Scene.hh"
#include <vector>


/*!
 * \file
 * \brief Zawiera definicję klasy Configuration
 *
 * Plik zawiera definicję klasy Configuration.
 * jest to definicja klasy, która przechowuje Listę obiektów klasy MobileObj, które zostały
 * sczytane z pliku xml w celu konfiguracji Sceny.
 * 
 * Plik zawiera również listę nazw bibliotek wspódzielonych jakie należy wczytać
 */
class Configuration {

  
/*!
 * 
 * \brief Lista obiektów w postaći typu map gdzie kluczem jest nazwa obiektu string
 */
  Map_MobileObj object_list;

/*!
 * 
 * \brief Lista nazw bibliotek do wczytania
 */
  vector<std::string> lib_int_list;

public:

 /*!
  * 
  * \brief Metoda pozwalająca na dodanie Obiektu typu MobileObject do listy
  * 
  */
  void AddMobileObject( const Vector3D &shift, const std::string &name, const Vector3D &scale, const Vector3D &rot, const Vector3D &trans, const std::string rgb);
  void AddLibToVector(const string &name_lib);
  std::vector<std::string> & GetLibList();
  Map_MobileObj & GetObjectList();


};



