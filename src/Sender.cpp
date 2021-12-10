#include "Sender.hh"



Sender::~Sender(){
  if (true == this->connected)
  {
    this->Send("Close\n");
  }
  close(_Socket);
}



int Sender::Send( const char *sMesg)
{
  ssize_t  IlWyslanych;
  ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);
  string messs= sMesg;
  while ((IlWyslanych = write(_Socket,sMesg,IlDoWyslania)) > 0) {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0) {
    cerr << "*** Blad przeslania napisu." << endl;
  }
  cout << "d: " << messs << "xxx\n";
  return 0;
}



bool Sender::OpenConnection()
{
  struct sockaddr_in  DaneAdSerw;

  bzero((char *)&DaneAdSerw,sizeof(DaneAdSerw));

  DaneAdSerw.sin_family = AF_INET;
  DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
  DaneAdSerw.sin_port = htons(PORT);


  this->_Socket = socket(AF_INET,SOCK_STREAM,0);

  if (this->_Socket < 0) {
     cerr << "*** Blad otwarcia gniazda." << endl;
     return false;
  }

  if (connect(this->_Socket,(struct sockaddr*)&DaneAdSerw,sizeof(DaneAdSerw)) < 0)
   {
     cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
     return false;
   }
  return true;
}






