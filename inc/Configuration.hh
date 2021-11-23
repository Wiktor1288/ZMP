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
  * \brief Metoda pozwalająca na dodanie Obiektu typu MobileObject do listy Configuration::object_list
  * \param [in] shift przesunięcie geometrycznego środka obiektu zdefiniowane jako Vector3D
  * \param [in] name Nazwa obiektu jaki ma zostać dodany do listy
  * \param [in] scale odpowiada parametrowi S. Zawiera współczynniki skali względem poszczególnych osi. Wartości te nie mogą być ujemne.
  * \param [in] rot_xyz  zawiera wartości kątów φ, θ oraz ψ. Są one wyrażone w stopniach. Zapis analogiczny jak w przypadku atrybutu Shift.
  * \param [in] trans przesunięcie obiektu zdefiniowane Vector3D
  * \param [in] rgb definiuje kolor obiektu we współrzędnych RGB
  */
  void AddMobileObject( const Vector3D &shift, const std::string &name, const Vector3D &scale, const Vector3D &rot_xyz, const Vector3D &trans, const std::string rgb);


 /*!
  * 
  * \brief Metoda pozwalająca na dodanie nazwy biblioteki jaka ma zostać wczytana
  * \param [in] name_lib Nazwa biblioteki jaka ma być dodana do listy Configuration::lib_int_list
  *
  */
  void AddLibToVector(const string &name_lib);


 /*!
  * 
  * \brief Metoda pozwalająca zwrócić listę bibliotek Configuration::lib_int_list
  *
  */
  std::vector<std::string> & GetLibList();

  /*!
  * 
  * \brief Metoda pozwalająca zwrócić listę obiektów Configuration::object_list
  *
  */
  Map_MobileObj & GetObjectList();

};



