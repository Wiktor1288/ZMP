#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"
#include "network_sending.hh"
using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 *
 */
Interp4Set::Interp4Set():  _wsp_X(0), _wsp_Y(0), _OX_angle(0), _OY_angle(0), _OZ_angle(0)
{}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName()  << " " << _ObjectName << " " <<   _wsp_X << " " << _wsp_Y << " " << _OX_angle << " " << _OY_angle << " " << _OZ_angle << " " << endl;
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Set::ExecCmd( MobileObj  *pMobObj,  AccessGuard * pAccCtrl , Sender *_sender) const
{
 pAccCtrl->LockAccess();

  Vector3D new_position = pMobObj->GetPositoin_m();
  new_position[0] = this->_wsp_X;
  new_position[1] = this->_wsp_Y;
  pMobObj->SetPosition_m(new_position);
  pMobObj->SetAng_Roll_deg(_OX_angle);
  pMobObj->SetAng_Pitch_deg(_OY_angle);
  pMobObj->SetAng_Yaw_deg(_OZ_angle);

  std::string message = "UpdateObj";
  message += pMobObj->GetStateDesc();
  Send2Server(_sender->ReturnSocket(),message.c_str());
  pAccCtrl->UnlockAccess();
  usleep(300000);

  return true;
}


/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _wsp_X >> _wsp_Y >> _OX_angle >> _OY_angle >> _OZ_angle;
  return !Strm_CmdsList.fail();
}


/*!
 *
 */
Interp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  wspX[m] wspY[m]  kat_OX[stopnie] kat_OY[stopnie] kat_OZ[stopnie]" << endl;
}
