#ifndef  APIFORPROGRAM_HH
#define  APIFORPROGRAM_HH
#include "Interp4Command.hh"
#include "Scene.hh"
#include "Sender.hh"
#include "Set4LibInterface.hh"
#include <thread>
#include <sstream> 
#define LINE_SIZE 500

/*!
 * \brief Klasa APIForProgram 
 *
 * Klasa zawiera wszystkie niezbędne składowe potrzebne do rozpoczęcia 
 * pracy z programem graficznym 
 *  
 */
class APIForProgram{

/*!
 * \brief Wskaźnik na obiekt typu Scena
 *
 *  Wskaźnik zwierający obiekt typu Scena
 *  
 */
    Scene *_scene;


/*!
 * \brief Wskaźnik na obiekt typu Sender
 *
 *  Wskaźnik zwierający obiekt typu Sender
 *  
 */
    Sender *_sender;


/*!
 * \brief metoda inicjalizująca obiekty 
 *
 * Metoda pozwala na zainicjalizowanie serwera graficznego elementami określonymi
 * w pliku xml
 *  
 */
    void InitObjects();
/*!
 * \brief metoda inicjalizująca polączenie z serwerem
 *
 * Metoda pozwala na zainicjalizowanie połączenia z serwerem
 *  
 */
    void OpenConnection();
/*!
 * \brief Wykonuje preprocesor na podanym pliku.
 *
 * \param[in] NazwaPliku - Nazwa pliku do interpretacji.
 * \param[out] IStrm4Cmds - Strumień, do którego jest wczytywana zinterpretowana zawartość.
 * \retval true - jeśli preprocesor został wykonany poprawnie i nastąpiło zamknięcie pliku.
 * \retval false - Niepowodzenie wykonania.
 */
    bool ExecPreprocesor(const   char * file_name, std::istringstream & iStrm4Cmds );

public:

/*!
 * \brief Konstruktor bezparametryczny klasy APIForProgram
 *
 * Konstruktor inicjalizujący wskaźniki klasy wartościami nullptr  
 */
    APIForProgram(): _scene(nullptr), _sender(nullptr) {}


/*!
 * \brief Konstruktor parametryczny klasy APIForProgram
 *
 * Pozwala na zainicjalizowanie klasy z elementami zawartymi w argumencie metody
 *  \param [in] list_Objects obiekt typu Map_MobileObj przechowujący elementy 
 */
    APIForProgram(Map_MobileObj &list_Objects);


/*!
 * \brief dekonstruktor  klasy APIForProgram
 *
 * Pozwala bezpiecznie usunąć obiekt klasy APIForProgram
 */
    ~APIForProgram();

/*!
 * \brief Wykonuje preprocesor na podanym pliku.
 *
 * \param[in] Str4Cmds_read - Nazwa pliku do interpretacji.
 * \retval true - jeśli preprocesor został wykonany poprawnie i nastąpiło zamknięcie pliku.
 * \retval false - Niepowodzenie wykonania.
 */
    bool ExecActions(const char* file_name, Set4LibInterface &lib_interfaces);

};

#endif