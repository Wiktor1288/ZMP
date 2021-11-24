#include "Sender.hh"







int Send(int Sk2Server, const char *sMesg)
{
  ssize_t  IlWyslanych;
  ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);

  while ((IlWyslanych = write(Sk2Server,sMesg,IlDoWyslania)) > 0) {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0) {
    cerr << "*** Blad przeslania napisu." << endl;
  }
  return 0;
}




void Fun_CommunicationThread(Sender  *pSender)
{
  pSender->Watching_and_Sending();
}

bool OpenConnection(int &rSocket)
{
  struct sockaddr_in  DaneAdSerw;

  bzero((char *)&DaneAdSerw,sizeof(DaneAdSerw));

  DaneAdSerw.sin_family = AF_INET;
  DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
  DaneAdSerw.sin_port = htons(PORT);


  rSocket = socket(AF_INET,SOCK_STREAM,0);

  if (rSocket < 0) {
     cerr << "*** Blad otwarcia gniazda." << endl;
     return false;
  }

  if (connect(rSocket,(struct sockaddr*)&DaneAdSerw,sizeof(DaneAdSerw)) < 0)
   {
     cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
     return false;
   }
  return true;
}





bool Sender::ShouldCountinueLooping() const{ 

    return _ContinueLooping; 
}

void Sender::CancelCountinueLooping() 
{ 
  _ContinueLooping = false; 
}




void Sender::Watching_and_Sending() {

    while (ShouldCountinueLooping()) {
        if (!_pScn->IsChanged()){
            usleep(10000);
            continue; 
        }

        _pScn->LockAccess();
       
       vector<shared_ptr<MobileObj>> MobileObject_list=_pScn->GetObjectPointer();
    for (auto spObj : MobileObject_list){

        auto *pObj = spObj.get();
        std::string ObjState = pObj->GetStateDesc();

        cout << "Wysyłam: " << ObjState;
        Send(_Socket, ObjState.c_str()); // Tu musi zostać wywołanie odpowiedniej
                                       // metody/funkcji gerującej polecenia dla serwera.
    }
       
       _pScn->CancelChange();
       _pScn->UnlockAccess();
     }
   }




