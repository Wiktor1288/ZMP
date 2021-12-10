#ifndef  INTERP4COMMAND_HH
#define  INTERP4COMMAND_HH

#include <iostream>
#include "MobileObj.hh"
#include "AccessGuard.hh"
#include <unistd.h>
#include "Sender.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Command
 *
 * Plik zawiera definicję klasy Interp4Command ...
 */

/*!
 * \file
 * \brief Zawiera definicję klasy Interp4Command
 *
 * Plik zawiera definicję klasy Interp4Command.
 * jest to definicja klasy, która przechowuje  plugin do danej komendy
 */
 class Interp4Command {
  public:
   /*!
    * \brief Destruktor wirtualny ze wzgledu na klasy pochodne
    *
    *  
    */
   virtual ~Interp4Command() {}
   /*!
    * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów).
    */
   virtual void PrintCmd() const = 0;
   /*!
    * \brief Wyświetla składnię polecenia.
    */
   virtual void PrintSyntax() const = 0;
   /*!
    * \brief Wyświetla nazwę polecenia.
    */
   virtual const char* GetCmdName() const = 0;
   /*!
    * \brief Wykonuje polecenie oraz wizualizuje jego realizację.
    */
   virtual bool ExecCmd( MobileObj *pMobObj, AccessGuard *pAccCtrl, Sender *_sender )  const = 0;
   /*!
    * \brief Czyta wartości parametrów danego polecenia.
    */
   virtual bool ReadParams(std::istream& Strm_CmdsList) = 0;
 };

#endif
