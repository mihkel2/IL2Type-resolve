UnityResolve

A lightweight Unity resolver orginal made for modding Counter Critical now a full project :D

Works well when paired with Unity wrappers.

# video showcase / what ive done before
![](IMG_0939.gif)


Contribution / Credits

* Sneakyevil — Base API

Basic Documentation

Classes
Il2CppClass* g_class = nullptr;
// Or
Il2CppClass* Class = Resolver::GetClass("", "", "");

std::vector<void*> objects = Resolver::FindObjectsOfType<void*>("");


Resolver::SetFieldValue<T>(instance, Class, "FieldName", value);



Resolver::GetMethod(Class, "MethodName", 0);



static uintptr_t addMoneyPtr =
    Resolver::GetMethod(Class, "AddMoney", 1); // argument count


Resolver::CallMethod<void>(addMoneyPtr, instance, 5000);

static methods are the same btw :)

Mod Example

Il2CppClass* playerClass =
    Resolver::GetClass("", "Player", "PlayerData");
Resolver::SetFieldValue<int>(playerInstance, playerClass, "coins", 9999);




with the new introduction of Gameobjects,Bone and mesh resolving and audios ⚙️ 


heres some examples



Animation 



Also have runtime animator contorllers 
Animator_GetRuntimeAnimatorController()Il2cppobject,animator


Animator_GetClioNames(il2cppobject* animtor)

we alwo fan resolve compnents by children ill need to get more into this a different time its a little more complicated



Rendering



WorldToScreen(vector3,worldpos,Vector3&,screenpos,float matrix)






component


il2cppGameObject* smr Resolver::GameObject_GetComponentByName()

Camera_GetMain()



// GameObjects
il2cppObject* PlayerGo = Resolver::GameObject_Find("") // find GO




//transforms

Transforms also come with the vector3 header so if your looking to get a players world pos youd call
trans = Resolver::Transform_GetTransform(playergo)
then resolving positions is nealry the same


you also have the other not as useful stuff
Transform_SetLocalScale(void transform, Vector,scale)
Transform_GetParent(void* transform)
