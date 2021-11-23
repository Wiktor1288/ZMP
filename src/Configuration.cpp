#include "Configuration.hh"





void Configuration::AddMobileObject( const Vector3D &shift, const std::string &name, const Vector3D &scale, 
                                        const Vector3D &rot_xyz, const Vector3D &trans, const std::string rgb){

     shared_ptr<MobileObj> new_object=make_shared<MobileObj>();


    new_object->SetName(name.c_str());
    new_object->SetAng_Pitch_deg(rot_xyz[0]);
    new_object->SetAng_Roll_deg(rot_xyz[1]);
    new_object->SetAng_Yaw_deg(rot_xyz[2]);
    new_object->SetColourRGB(rgb);
    new_object->SetScale(scale);
    new_object->SetShift(shift);
    new_object->SetPosition_m(trans);

    this->object_list.insert({name,new_object});
}



void Configuration::AddLibToVector(const string &name_lib){

    this->lib_int_list.push_back(name_lib);
}



Map_MobileObj & Configuration::GetObjectList(){

  return this->object_list;
}



std::vector<std::string> & Configuration::GetLibList(){
    
    return this->lib_int_list;
}