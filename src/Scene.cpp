#include "Scene.hh"

Scene::Scene(Map_MobileObj &List_of_object): List_of_object(List_of_object)
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



vector<string> Scene::GetObjectNames(){
    
    vector<string> name_vector;
    Map_MobileObj::iterator it;

    for (it = List_of_object.begin(); it != List_of_object.end(); it++){
        name_vector.push_back(it->first);
    }

    return name_vector;
}

vector<shared_ptr<MobileObj>> Scene::GetObjectPointer(){
    vector<shared_ptr<MobileObj>> object_vector;
    Map_MobileObj::iterator it;

    for (it = List_of_object.begin(); it != List_of_object.end(); it++){
        object_vector.push_back(it->second);
    }

    return object_vector;
}

