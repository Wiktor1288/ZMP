#include <iostream>
#include "Interp4Rotate.hh"
#include "MobileObj.hh"
#include "network_sending.hh"
using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


/*!
 *
 */
Interp4Rotate::Interp4Rotate(): _angle_speed(0), _angle_value(0)
{}


/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _ObjectName << " " << _angle_speed << " " << _axis_name << " " <<  _angle_value << " " << endl;
}


/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Rotate::ExecCmd( MobileObj  *pMobObj, AccessGuard * pAccCtrl, Sender *_sender ) const
{
 
  double progress;
  char axis = this->_axis_name.at(1);

  switch (axis)
  {
  case 'X':
    progress = pMobObj->GetAng_Roll_deg();
    break;

  case 'Y':
    progress = pMobObj->GetAng_Pitch_deg();
    break;

  case 'Z':
    progress = pMobObj->GetAng_Yaw_deg();
    break;
  }

  int direction = this->_angle_speed > 0 ? 1 : -1;
  double setpoint = progress + this->_angle_value * direction;
while (setpoint != progress)
  {
    pAccCtrl->LockAccess();

    progress += this->_angle_speed;

    if (direction == 1)
    {
      if (progress > setpoint)
      {
        progress = setpoint;
      }
    }
    else
    {
      if (progress < setpoint)
      {
        progress = setpoint;
      }
    }

    switch (axis)
    {
    case 'X':
      pMobObj->SetAng_Roll_deg(progress);
      break;

    case 'Y':
      pMobObj->SetAng_Pitch_deg(progress);
      break;

    case 'Z':
      pMobObj->SetAng_Yaw_deg(progress);
      break;
    }
    std::string message = "UpdateObj";
     message += pMobObj->GetStateDesc();
    Send2Server(_sender->ReturnSocket(),message.c_str());
    
    pAccCtrl->UnlockAccess();
    usleep(100000);
  }
  return true;
}


/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList  >> _angle_speed >> _axis_name >> _angle_value ;
  return !Strm_CmdsList.fail();
}


/*!
 *
 */
Interp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu  szybkosc katowa [m/s], nazwa osi kat obortu" << endl;
}
