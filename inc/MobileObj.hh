#ifndef MOBILEOBJ_HH
#define MOBILEOBJ_HH


#include <string>
#include "Vector3D.hh"
#include <sstream>

/*!
 * \file
 * \brief Zawiera definicję klasy MobileObj
 *
 * Plik zawiera definicję klasy MobileObj.
 * Definicja to może być rozszerzona i zmienione mogą
 * być nazwy pól. Obowiązkowe są jedynie nazwy metod.
 */




   /*!
    * Nazwy pól klasy są jedynie propozycją i mogą być zmienione
    * Nazwy metod są obowiązujące.
    */
    class MobileObj {
       /*!
        * \brief Kąt \e yaw reprezentuje rotację zgodnie z ruchem wskazówek zegara
        *        wokół osi \e OZ.
	*
	* Kąt \e yaw reprezentuje rotację zgodnie z ruchem wskazówek zegara
        * wokół osi \e OZ. Wartość kąta wyrażona jest w stopniach.
        */
       double _Ang_Yaw_deg = 0;

       /*!
        * \brief Kąt \e pitch reprezentuje rotację zgodnie z ruchem wskazówek zegara
        *        wokół osi \e OY.
	*
	* Kąt \e pitch reprezentuje rotację zgodnie z ruchem wskazówek zegara
        * wokół osi \e OY. Wartość kąta wyrażona jest w stopniach.
        */
       double _Ang_Pitch_deg = 0;

       /*!
        * \brief Kąt \e roll reprezentuje rotację zgodnie z ruchem wskazówek zegara
        *        wokół osi \e OX.
	*
	* Kąt \e roll reprezentuje rotację zgodnie z ruchem wskazówek zegara
        * wokół osi \e OX. Wartość kąta wyrażona jest w stopniach.
        */
       double _Ang_Roll_deg = 0;

       /*!
        * \brief Współrzędne aktualnej pozycji obiektu.
	*
	* Współrzędne aktualnej pozycji obiektu. Przyjmuje się,
	* że współrzędne wyrażone są w metrach.
        */
       Vector3D  _Position_m;

       /*!
        * \brief Nazwa obiektu, która go indentyfikuje.
        *
        * Nazwa obiektu, która go indentyfikuje. Z tego względu musi
        * musi to być nazwa unikalna wśród wszystkich obiektów na scenie.
        */
       std::string  _Name;


       /*!
        * \brief Przesunięcie geometrycznego środka obiektu
        *
        * jest to zmiena która definiuje przesunięcie geometrycznego środka obiektu. 
        */
       Vector3D _shift;
       

       /*!
        * \brief Zmiena przechowująca współczynnik skali
        *
        * Zawiera współczynniki skali względem poszczególnych osi. Wartości te nie mogą być ujemne. Dopuszczalny jest przypadek,
        * gdy wszystkie współczynniki skali będą równe 0. 
        */
       Vector3D _scale;


       /*!
        * \brief Tablica przechowująca kolor obiektu 
        *
        * Tablica przechowująca kolor obiektu zgodnie z modelem RGB 
        */
       int _colour[3];

     public:
      /*!
       * \brief Udostępia wartość kąta \e roll.
       *
       * Udostępia wartość kąta \e roll. Jest ona wyrażona w stopniach.
       */
       double GetAng_Roll_deg() const { return _Ang_Roll_deg; }
      /*!
       * \brief Udostępia wartość kąta \e pitch.
       *
       * Udostępia wartość kąta \e pitch. Jest ona wyrażona w stopniach.
       */
       double GetAng_Pitch_deg() const { return _Ang_Pitch_deg; }
       /*!
       * \brief Udostępia wartość kąta \e yaw.
       *
       * Udostępia wartość kąta \e yaw. Jest ona wyrażona w stopniach.
       */
       double GetAng_Yaw_deg() const { return _Ang_Yaw_deg; }

      /*!
       * \brief Zmienia wartość kąta \e roll.
       *
       * Zmienia wartość kąta \e roll.
       * \param[in] Ang_Roll_deg - nowa wartość kąta \e roll wyrażona w stopniach.
       */
       void SetAng_Roll_deg(double Ang_Roll_deg) { _Ang_Roll_deg = Ang_Roll_deg; }
      /*!
       * \brief Zmienia wartość kąta \e pitch.
       *
       * Zmienia wartość kąta \e pitch.
       * \param[in] Ang_Pitch_deg - nowa wartość kąta \e pitch wyrażona w stopniach.
       */
       void SetAng_Pitch_deg(double Ang_Pitch_deg) { _Ang_Pitch_deg = Ang_Pitch_deg; }
      /*!
       * \brief Zmienia wartość kąta \e yaw.
       *
       * Zmienia wartość kąta \e yaw.
       * \param[in] Ang_Yaw_deg - nowa wartość kąta \e yaw wyrażona w stopniach.
       */
       void SetAng_Yaw_deg(double Ang_Yaw_deg) { _Ang_Yaw_deg = Ang_Yaw_deg; }

      /*!
       * \brief Udostępnia współrzędne położenia obiektu w trybie tylko do odczytu.
       *
       * Udostępnia współrzędne punktu, który definiuje położenia obiektu
       * w trybie tylko do odczytu.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       */
       const Vector3D & GetPositoin_m() const { return _Position_m; }
      /*!
       * \brief Udostępnia współrzędne położenia obiektu w trybie modyfikacji.
       *
       * Udostępnia współrzędne punktu, który definiuje położenia obiektu
       * w trybie modyfikacji.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       */
       Vector3D & UsePosition_m() { return _Position_m; }
      /*!
       * \brief Zmienia współrzędne położenia obiektu.
       *
       * Zmienia współrzędne punktu, który definiuje położenia obiektu.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       * \param[in] rPos_m - współrzędne nowgo położenia. Przyjmuje się,
       *                     że są one wyrażone w metrach.
       */
       void SetPosition_m(const Vector3D &rPos_m) { _Position_m = rPos_m; }


      /*!
       * \brief Zmienia nazwę obiektu.
       *
       *  Zmienia nazwę obiektu.
       *  \param[in] sName - nowa nazwa obiektu.
       */
       void SetName(const char* sName) { _Name = sName; }
       /*!
        * \brief Udostępnia nazwę obiektu.
	*
	* Udostępnia nazwę obiektu w trybie tylko do odczytu.
        */
       const std::string & GetName() const { return _Name; }


      /*!
       * \brief Metoda zapisująca kolor do tablicy z napisu
       *
       *  Zapisuje wartości poszczególnych składowych koloru opisanego przez model RGB
       *  \param[in] colour_str - napis zwierajacy informacje o kolorze zgodnie z modelem RGB
       */
        void SetColourRGB(const std::string colour_str){
       
                std::istringstream iStrm;

                iStrm.str(colour_str);
                iStrm >> this->_colour[0] >> this->_colour[1] >> this->_colour[2];
       }

      /*!
       * \brief Metoda pozwalająca wypełnić zmienną MobileObj::_shift
       *
       *  Inicjalizuje wartość zmiennej MobileObj::_shift
       *  \param[in] _shift - zmiena inicjaluzjąca zmienną MobileObj::_shift
       *
       */
        void SetShift(const Vector3D _shift){
       
                this->_shift=_shift;
       }



      /*!
       * \brief Metoda pozwalająca wypełnić zmienną  MobileObj::_scale
       *
       *  Inicjalizuje wartość zmiennej MobileObj::_scale 
       *  \param[in] _scale - dane zapisywane do zmiennej MobileObj::_scale
       */
        void SetScale(const Vector3D _scale){
                
                this->_scale=_scale;
       }

        std::string GetStateDesc()
        {
                  char buffor[200];

                int length = sprintf(buffor, " Name=%s RotXYZ_deg=(%f,%f,%f) RGB=(%d,%d,%d) Scale=(%f,%f,%f) Shift=(%f,%f,%f) Trans_m=(%f,%f,%f)\n", 
                this->_Name.c_str(), 
                this->_Ang_Yaw_deg, this->_Ang_Pitch_deg, this->_Ang_Roll_deg,
                this->_colour[0], this->_colour[1], this->_colour[2],
                this->_scale[0], this->_scale[1], this->_scale[2],
                this->_shift[0], this->_shift[1], this->_shift[2],
                _Position_m[0], _Position_m[1], _Position_m[2]  );

                std::string result(buffor, length);

                return result;

        }




    };


#endif
