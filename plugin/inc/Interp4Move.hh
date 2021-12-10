#ifndef  COMMAND4MOVE_HH
#define  COMMAND4MOVE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Move
 *
 * Plik zawiera definicję klasy Interp4Move ...
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch do przodu
 *
 *  Klasa modeluje ...
 */
class Interp4Move: public Interp4Command {
  /*!
   * \brief Nazwa obiektu
   * 
   * Nadana nazwa obiektu
   */
  std::string _ObjectName;
  
  /*!
   * \brief Szybkość ruchu podawana w m/s
   * 
   * Szybkość poruszania sie objektu
   */

  double  _Speed_mmS;

  /*!
   * \brief Przebyty dystans w m
   * 
   * Dystans jaki obiekt ma poknac podawany w m
   */
  double _Distance_m;
  
 public:
  /*!
   * \brief
   */
  Interp4Move();  
  ~Interp4Move();
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
  virtual bool ExecCmd( MobileObj  *pMobObj, AccessGuard * pAccCtrl, Sender *_sender) const;
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
