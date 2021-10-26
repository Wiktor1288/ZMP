#ifndef  COMMAND4SET_HH
#define  COMMAND4SET_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Set
 *
 * Plik zawiera definicję klasy Interp4Set odpwiedzialnej za postawienie objektu w podanym, docelowym miejscu
 */

/*!
 * \brief Modeluje polecenie dla obiektu, które powoduje ustawienie obiektu w docelowym mie
 *
 *  Klasa modeluje polecenie pozwalające na postawieniu obiektu w docelowym miejscu, które jest 
 * definiowane poprzez podanie współrzędnych X i Y oraz kątów OX OY OZ (w stopniach)
 */
class Interp4Set: public Interp4Command {

  /*!
   * \brief Nazwa obiektu
   * 
   * Nadana nazwa obiektu
   */

  std::string _ObjectName;

  /*!
   * \brief Współrzędna X [m]
   * 
   * Wspołrzędna X położenia obiektu podawana w metrach
   */

  double  _wsp_X;

  /*!
   * \brief Współrzędna Y [m] 
   * 
   * Wspołrzędna X położenia obiektu podwana w metrach
   */

  double  _wsp_Y;

  /*!
   * \brief kąt obrotu osi X [stopnie] 
   * 
   * Kąt obrotu obiektu wokół osi X podawany w stopniach
   */

  double  _OX_angle;

  /*!
   * \brief kąt obrotu osi Y [stopnie] 
   * 
   * Kąt obrotu obiektu wokół osi Y podawany w stopniach
   */

  double  _OY_angle;

  /*!
   * \brief kąt obrotu osi Z [stopnie] 
   * 
   * Kąt obrotu obiektu wokół osi Z podawany w stopniach
   */

  double  _OZ_angle;


 public:
  /*!
   * \brief
   */
  Interp4Set();  
  /*!
   * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
   */
  virtual void PrintCmd() const;
  /*!
   * \brief Wyświetla składnię polecenia
   */
  virtual void PrintSyntax() const;
  /*!
   * \brief Wyświetla nazwę polecenia
   */
  virtual const char* GetCmdName() const;
  /*!
   * \brief Wykonuje polecenie oraz wizualizuje jego realizację
   */
  virtual bool ExecCmd( MobileObj  *pMobObj, int Socket) const;
  /*!
   * \brief Czyta wartości parametrów danego polecenia
   */
  virtual bool ReadParams(std::istream& Strm_CmdsList);
  /*!
   * \brief Wyświetla wartości wczytanych parametrów
   */
  virtual void PrintParams() {}
  /*!
   * \brief
   *
   *  Ta metoda nie musi być zdefiniowna w klasie bazowej.
   */
  static Interp4Command* CreateCmd();
 };

#endif
