#pragma once


#include <unistd.h>
#include <thread>
#include "Scene.hh"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "AccessGuard.hh"
#include "Port.hh"
#include <string.h>


class Sender {
  /*!
   * \brief Wartość tego pola decyduje o kontynuacji wykonywania wątku.
   * 
   * Wartość tego pola decyduje o kontynuacji wykonywania wątku.
   * W przypadku wartości \p true, pętla wątku będzie wykonywana.
   * Natomiast wartość \p false powoduje przerwanie pętli.
   */
  /*!
   * \brief Deskryptor gniazda sieciowego, poprzez które wysyłane są polecenia.
   */
   int             _Socket = 0;
  /*!
   * \brief Wskaźnik na scenę, które stan jest przesyłany w postaci
   *        poleceń do serwera graficzneg.
   */
   Scene *_pScn = nullptr;
   bool connected;
  
 public:
 /*!
 * \brief Konstruktor parametryczny
 *
 * Konstruktor parametryczny klasy Sender
 *  \param[in] scene - wskaźnik na element klasy Scene
 */
  Sender(Scene *_scene):  _pScn(_scene) {}
/*!
 * \brief Wysyła napis do poprzez gniazdo sieciowe.
 *
 * Wysyła napis do poprzez gniazdo sieciowe.
 * \param[in] sMesg - zawiera napis, który ma zostać wysłany poprzez
 *                    gniazdo sieciowe.
 */
int Send(const char *sMesg);


/*!
 * \brief Otwiera połączenie sieciowe
 * 
 * Metoda pozwalająca na utworzenie połączenia z serwerem graficznym
 */
bool OpenConnection();

~Sender();

int ReturnSocket(){
  return _Socket;
}
  
};












