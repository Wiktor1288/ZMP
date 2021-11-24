#include "Scene.hh"

Scene::Scene(Map_MobileObj &List_of_object): List_of_object{List_of_object}
{}


shared_ptr<MobileObj> Scene::FindMobileObj(const string Name_object){

    auto obj= List_of_object.find(Name_object);

    if (obj == List_of_object.end()){
        return nullptr;
    }

    else{
    return (obj->second);
    }
 }



 void Scene::AddObjToList(const std::string Name_object){

  auto new_obj = std::make_shared<MobileObj>();
  List_of_object.insert({Name_object, new_obj});

 }
