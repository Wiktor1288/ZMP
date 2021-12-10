#include <iostream>
#include "Interp4Move.hh"
#include "MobileObj.hh"
#include "network_sending.hh"
using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}

 Interp4Move::~Interp4Move(){
   cout <<"\n Usuwam Move\n";
 }
/*!
 *
 */
Interp4Move::Interp4Move(): _Speed_mmS(0), _Distance_m(0)
{cout <<"\n Tworze Move\n";}


/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _ObjectName << " " << _Speed_mmS << " "  << _Distance_m << endl;
}


/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Move::ExecCmd( MobileObj  *pMobObj,  AccessGuard * pAccCtrl , Sender *_sender) const
{
  int _direction, _iterations;
  
  if(this-> _Speed_mmS < 0 ){
    _direction=-1;
  }

  else{
    _direction=1;
  }

  _iterations=floor(this->_Distance_m/this->_Speed_mmS);

  for(int i=0; i<_iterations; ++i){
    pAccCtrl->LockAccess();
    auto _position = pMobObj->GetPositoin_m();
    auto _angle= pMobObj->GetAng_Roll_deg();

    _position[0] += this->_Speed_mmS * _direction * cos(M_PI * _angle/180);
    _position[1] += this->_Speed_mmS * _direction * sin(M_PI * _angle/180);

    pMobObj->SetPosition_m(_position);
    std::string message = "UpdateObj";
     message += pMobObj->GetStateDesc();
    Send2Server( _sender->ReturnSocket(),message.c_str());
    pAccCtrl->UnlockAccess();
     usleep(10000);
  }
  
    return true;
  }
  




/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _Speed_mmS >> _Distance_m;
  return !Strm_CmdsList.fail();
}


/*!
 *
 */
Interp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
