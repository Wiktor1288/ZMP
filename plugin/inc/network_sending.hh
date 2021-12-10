#ifndef NETWORK_SENDING_HH
#define NETWORK_SENDING_HH


/*!
 * \file
 * \brief Zawiera jedynie funkcję do przesyłania tekstu poprzez
 *        gniazdo sieciowe.
 */

int Send2Server(int Sk2Server, const char *sMesg);

#endif
