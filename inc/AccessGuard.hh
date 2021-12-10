#ifndef ACCESSGUARD_HH
#define ACCESSGUARD_HH

#include <mutex>

/*!
 * \file
 * \brief Zawiera definicję klasy AccessGuard
 */

/*!
 * \brief Przechowuje deskryptor gniazda
 *
 *  Przechowuje deskryptor gniazda wraz z obiektem klasy std::mutex,
 *  który powinien być wykorzystany nadzorca wyłącznego dostępu
 *  do sceny oraz gniazda połączenia sieciowego z serwerem.
 */
class AccessGuard {
   /*!
    * \brief Zapewnia wyłączny dostęp do obiektu w trakcie modyfikacji.
    */
    std::mutex   _Guard;
    
   /*!
    * \brief Przechowuje deskryptor pliku skojarzonym z połączeniem
    *        sieciowym z serwerem.
    *
    * Przechowuje deskryptor pliku skojarzonym z połączeniem
    * sieciowym z serwerem.
    * Wartość poprawnego deskrytora musi być różna od 0.
    */ 
    int         _Socket = 0;
 public:

  /*!
   * \brief Udostępnia deskryptor pliku skojarzonego z połączeniem
   *        sieciowym z serwerem.
   *
   *  Udostępnia deskryptor skojarzonego z połączeniem sieciowym z serwerem.
   * \return Deskryptor pliku.
   */
   int GetSocket() const { return _Socket; }
  /*!
   * \brief Zamyka dostęp całej sceny i gniazda.
   */
   void LockAccess() { _Guard.lock(); }
  /*!
   * \brief Otwiera dostęp do całej sceny i gniazda.
   */
   void UnlockAccess() { _Guard.unlock(); }
   /*!
    * \brief Udostępnia mutex w trybie modyfikacji.
    *
    *  Udostępnia mutex w trybie modyfikacji.
    *  Jest to przydatne, gdy planowany jest inny typ zamknięcie,
    *  np. poprzez klasę std::lock_gaurd, która daje możliwość
    *  bezpieczniejszego zamknięcia.
    */
   std::mutex &UseGuard() { return _Guard; }

   void SetSocket(int _socket){
      this->_Socket=_Socket;
   }
};


#endif
