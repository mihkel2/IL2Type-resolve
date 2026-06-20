#include "Il2CppResolver.h"
#include <dlfcn.h>
#include <string.h>
#include <fstream>
#include <sstream>

namespace Resolver {
    void* il2cpp_handle = nullptr;
    Il2CppDomain* (*il2cpp_domain_get)() = nullptr;
    const Il2CppAssembly** (*il2cpp_domain_get_assemblies)(const Il2CppDomain* domain, size_t* size) = nullptr;
    const Il2CppImage* (*il2cpp_assembly_get_image)(const Il2CppAssembly* assembly) = nullptr;
    const char* (*il2cpp_image_get_name)(const Il2CppImage* image) = nullptr;
    size_t (*il2cpp_image_get_class_count)(const Il2CppImage* image) = nullptr;
    const Il2CppClass* (*il2cpp_image_get_class)(const Il2CppImage* image, size_t index) = nullptr;
    Il2CppClass* (*il2cpp_class_from_name)(const Il2CppImage* image, const char* namespaze, const char* name) = nullptr;
    Il2CppClass* (*il2cpp_class_get_nested_types)(Il2CppClass* klass, void** iter) = nullptr;
    const char* (*il2cpp_class_get_name)(Il2CppClass* klass) = nullptr;
    const char* (*il2cpp_class_get_namespace)(Il2CppClass* klass) = nullptr;
    const Il2CppMethod* (*il2cpp_class_get_methods)(Il2CppClass* klass, void** iter) = nullptr;
    const Il2CppMethod* (*il2cpp_class_get_method_from_name)(Il2CppClass* klass, const char* name, int argsCount) = nullptr;
    Il2CppField* (*il2cpp_class_get_fields)(Il2CppClass* klass, void** iter) = nullptr;
    Il2CppField* (*il2cpp_class_get_field_from_name)(Il2CppClass* klass, const char* name) = nullptr;
    const char* (*il2cpp_field_get_name)(Il2CppField* field) = nullptr;
    void (*il2cpp_field_get_value)(void* obj, Il2CppField* field, void* value) = nullptr;
    void (*il2cpp_field_set_value)(void* obj, Il2CppField* field, void* value) = nullptr;
    void (*il2cpp_field_static_get_value)(Il2CppField* field, void* value) = nullptr;
    void (*il2cpp_field_static_set_value)(Il2CppField* field, void* value) = nullptr;
    const char* (*il2cpp_method_get_name)(const Il2CppMethod* method) = nullptr;
    int (*il2cpp_method_get_param_count)(const Il2CppMethod* method) = nullptr;
    Il2CppObject* (*il2cpp_type_get_object)(const Il2CppType* type) = nullptr;
    const Il2CppType* (*il2cpp_class_get_type)(Il2CppClass* klass) = nullptr;
    uint32_t (*il2cpp_array_length)(Il2CppArray* array) = nullptr;
    Il2CppObject* (*il2cpp_runtime_invoke)(const Il2CppMethod* method, void* obj, void** params, Il2CppObject** exc) = nullptr;
    void* (*il2cpp_object_get_class)(Il2CppObject* obj) = nullptr;

    bool Init() {
        il2cpp_handle = dlopen("libil2cpp.so", RTLD_LAZY);
        if (!il2cpp_handle) return false;

        il2cpp_domain_get = (Il2CppDomain* (*)())dlsym(il2cpp_handle, "il2cpp_domain_get");
        il2cpp_domain_get_assemblies = (const Il2CppAssembly** (*)(const Il2CppDomain*, size_t*))dlsym(il2cpp_handle, "il2cpp_domain_get_assemblies");
        il2cpp_assembly_get_image = (const Il2CppImage* (*)(const Il2CppAssembly*))dlsym(il2cpp_handle, "il2cpp_assembly_get_image");
        il2cpp_image_get_name = (const char* (*)(const Il2CppImage*))dlsym(il2cpp_handle, "il2cpp_image_get_name");
        il2cpp_image_get_class_count = (size_t (*)(const Il2CppImage*))dlsym(il2cpp_handle, "il2cpp_image_get_class_count");
        il2cpp_image_get_class = (const Il2CppClass* (*)(const Il2CppImage*, size_t))dlsym(il2cpp_handle, "il2cpp_image_get_class");
        il2cpp_class_from_name = (Il2CppClass* (*)(const Il2CppImage*, const char*, const char*))dlsym(il2cpp_handle, "il2cpp_class_from_name");
        il2cpp_class_get_nested_types = (Il2CppClass* (*)(Il2CppClass*, void**))dlsym(il2cpp_handle, "il2cpp_class_get_nested_types");
        il2cpp_class_get_name = (const char* (*)(Il2CppClass*))dlsym(il2cpp_handle, "il2cpp_class_get_name");
        il2cpp_class_get_namespace = (const char* (*)(Il2CppClass*))dlsym(il2cpp_handle, "il2cpp_class_get_namespace");
        il2cpp_class_get_methods = (const Il2CppMethod* (*)(Il2CppClass*, void**))dlsym(il2cpp_handle, "il2cpp_class_get_methods");
        il2cpp_class_get_method_from_name = (const Il2CppMethod* (*)(Il2CppClass*, const char*, int))dlsym(il2cpp_handle, "il2cpp_class_get_method_from_name");
        il2cpp_class_get_fields = (Il2CppField* (*)(Il2CppClass*, void**))dlsym(il2cpp_handle, "il2cpp_class_get_fields");
        il2cpp_class_get_field_from_name = (Il2CppField* (*)(Il2CppClass*, const char*))dlsym(il2cpp_handle, "il2cpp_class_get_field_from_name");
        il2cpp_field_get_name = (const char* (*)(Il2CppField*))dlsym(il2cpp_handle, "il2cpp_field_get_name");
        il2cpp_field_get_value = (void (*)(void*, Il2CppField*, void*))dlsym(il2cpp_handle, "il2cpp_field_get_value");
        il2cpp_field_set_value = (void (*)(void*, Il2CppField*, void*))dlsym(il2cpp_handle, "il2cpp_field_set_value");
        il2cpp_field_static_get_value = (void (*)(Il2CppField*, void*))dlsym(il2cpp_handle, "il2cpp_field_static_get_value");
        il2cpp_field_static_set_value = (void (*)(Il2CppField*, void*))dlsym(il2cpp_handle, "il2cpp_field_static_set_value");
        il2cpp_method_get_name = (const char* (*)(const Il2CppMethod*))dlsym(il2cpp_handle, "il2cpp_method_get_name");
        il2cpp_method_get_param_count = (int (*)(const Il2CppMethod*))dlsym(il2cpp_handle, "il2cpp_method_get_param_count");
        il2cpp_type_get_object = (Il2CppObject* (*)(const Il2CppType*))dlsym(il2cpp_handle, "il2cpp_type_get_object");
        il2cpp_class_get_type = (const Il2CppType* (*)(Il2CppClass*))dlsym(il2cpp_handle, "il2cpp_class_get_type");
        il2cpp_array_length = (uint32_t (*)(Il2CppArray*))dlsym(il2cpp_handle, "il2cpp_array_length");
        il2cpp_runtime_invoke = (Il2CppObject* (*)(const Il2CppMethod*, void*, void**, Il2CppObject**))dlsym(il2cpp_handle, "il2cpp_runtime_invoke");
        il2cpp_object_get_class = (void* (*)(Il2CppObject*))dlsym(il2cpp_handle, "il2cpp_object_get_class");

        // Require a minimal set of symbols to be present for resolver functionality.
        if (!il2cpp_domain_get || !il2cpp_domain_get_assemblies || !il2cpp_class_from_name) {
            if (il2cpp_handle) dlclose(il2cpp_handle);
            il2cpp_handle = nullptr;
            return false;
        }

        return true;
    }

    Il2CppClass* GetClass(const char* assemblyName, const char* namespaze, const char* className) {
        if (!il2cpp_domain_get || !il2cpp_domain_get_assemblies || !il2cpp_class_from_name) return nullptr;
        Il2CppDomain* domain = il2cpp_domain_get();
        if (!domain) return nullptr;
        size_t size;
        const Il2CppAssembly** assemblies = il2cpp_domain_get_assemblies(domain, &size);
        if (!assemblies) return nullptr;
        for (size_t i = 0; i < size; ++i) {
            const Il2CppImage* image = il2cpp_assembly_get_image(assemblies[i]);
            if (image && strcmp(il2cpp_image_get_name(image), assemblyName) == 0) {
                return il2cpp_class_from_name(image, namespaze, className);
            }
        }
        return nullptr;
    }

    Il2CppClass* GetClassFromImage(const Il2CppImage* image, const char* namespaze, const char* className) {
        if (!image || !il2cpp_class_from_name) return nullptr;
        return il2cpp_class_from_name(image, namespaze, className);
    }

    Il2CppClass* GetNestedClass(Il2CppClass* klass, const char* name) {
        if (!klass || !il2cpp_class_get_nested_types || !il2cpp_class_get_name) return nullptr;
        void* iter = nullptr;
        while (Il2CppClass* sub = il2cpp_class_get_nested_types(klass, &iter)) {
            if (strcmp(il2cpp_class_get_name(sub), name) == 0) return sub;
        }
        return nullptr;
    }

    uintptr_t GetMethod(Il2CppClass* klass, const char* methodName, int argsCount) {
        if (!klass || !il2cpp_class_get_method_from_name) return 0;
        const Il2CppMethod* method = il2cpp_class_get_method_from_name(klass, methodName, argsCount);
        if (!method) return 0;
        // Method structs usually start with the function pointer (native code)
        return *(uintptr_t*)method;
    }

    Il2CppClass* GetObjectClass(Il2CppObject* obj) {
        if (!obj || !il2cpp_object_get_class) return nullptr;
        return (Il2CppClass*)il2cpp_object_get_class(obj);
    }

    void* Component_GetTransform(Il2CppObject* component) {
        if (!component) return nullptr;

        static Il2CppClass* compKlass = GetClass("UnityEngine.CoreModule.dll", "UnityEngine", "Component");
        if (!compKlass) compKlass = GetClass("UnityEngine.dll", "UnityEngine", "Component");
        if (!compKlass) compKlass = GetClass("UnityEngine.CoreModule.dll", "UnityEngine", "GameObject");
        if (!compKlass) compKlass = GetClass("UnityEngine.dll", "UnityEngine", "GameObject");
        if (!compKlass) return nullptr;

        static uintptr_t getTransform = GetMethod(compKlass, "get_transform", 0);
        if (!getTransform) return nullptr;
        return CallMethod<void*>(getTransform, component);
    }

    Vector3 Component_GetPosition(void* component) {
        if (!component) return Vector3();
        void* transform = Component_GetTransform((Il2CppObject*)component);
        if (!transform) return Vector3();
        return Transform_GetPosition(transform);
    }

    Il2CppObject* GetSystemType(Il2CppClass* klass) {
        if (!klass || !il2cpp_type_get_object || !il2cpp_class_get_type) return nullptr;
        return il2cpp_type_get_object(il2cpp_class_get_type(klass));
    }

    bool IsValidObject(Il2CppObject* obj) {
        if (!obj || !il2cpp_object_get_class) return false;
        return il2cpp_object_get_class(obj) != nullptr;
    }

    void Il2cppDump(const char* outPath) {
        if (!il2cpp_domain_get || !il2cpp_domain_get_assemblies) return;
        std::ofstream out(outPath);
        if (!out.is_open()) return;

        Il2CppDomain* domain = il2cpp_domain_get();
        if (!domain) return;
        size_t assemCount;
        const Il2CppAssembly** assemblies = il2cpp_domain_get_assemblies(domain, &assemCount);
        if (!assemblies) return;

        for (size_t i = 0; i < assemCount; i++) {
            const Il2CppImage* image = il2cpp_assembly_get_image(assemblies[i]);
            if (!image) continue;
            out << "// Assembly: " << il2cpp_image_get_name(image) << "\n";
            size_t classCount = il2cpp_image_get_class_count(image);

            for (size_t j = 0; j < classCount; j++) {
                Il2CppClass* klass = (Il2CppClass*)il2cpp_image_get_class(image, j);
                if (!klass) continue;

                out << "class " << il2cpp_class_get_namespace(klass) << "::" << il2cpp_class_get_name(klass) << " {\n";

                // Dump Fields
                void* fIter = nullptr;
                if (il2cpp_class_get_fields) {
                    while (Il2CppField* field = il2cpp_class_get_fields(klass, &fIter)) {
                        out << "  " << il2cpp_field_get_name(field) << ";\n";
                    }
                }

                // Dump Methods
                void* mIter = nullptr;
                if (il2cpp_class_get_methods) {
                    while (const Il2CppMethod* method = il2cpp_class_get_methods(klass, &mIter)) {
                        out << "  " << il2cpp_method_get_name(method) << "(" << il2cpp_method_get_param_count(method) << "); // addr: " << (void*)(*(uintptr_t*)method) << "\n";
                    }
                }
                out << "}\n\n";
            }
        }
        out.close();
    }

    std::string ToString(Il2CppString* str) {
        if (!str) return "NULL";
        size_t lengthOffset = (sizeof(void*) == 8) ? 0x10 : 0x08;
        size_t charsOffset = (sizeof(void*) == 8) ? 0x14 : 0x0C;

        int32_t length = *(int32_t*)((uintptr_t)str + lengthOffset);
        if (length < 0 || length > 8192) return "INVALID";

        const uint16_t* chars = (const uint16_t*)((uintptr_t)str + charsOffset);
        std::string s;
        s.reserve(length);
        for (int i = 0; i < length; i++) {
            s += (char)chars[i];
        }
        return s;
    }

    Il2CppObject* GameObject_Find(const char* name) {
        static Il2CppClass* goKlass = GetClass("UnityEngine.CoreModule.dll", "UnityEngine", "GameObject");
        if (!goKlass) goKlass = GetClass("UnityEngine.dll", "UnityEngine", "GameObject");
        if (!goKlass) return nullptr;
        static uintptr_t findMethod = GetMethod(goKlass, "Find", 1);
        if (!findMethod) return nullptr;

        // il2cpp_string_new is usually available
        typedef Il2CppString* (*il2cpp_string_new_t)(const char*);
        static il2cpp_string_new_t il2cpp_string_new = (il2cpp_string_new_t)dlsym(il2cpp_handle, "il2cpp_string_new");

        if (!il2cpp_string_new) return nullptr;
        Il2CppString* str = il2cpp_string_new(name);
        return CallMethod<Il2CppObject*>(findMethod, nullptr, str);
    }

    void* GameObject_GetTransform(Il2CppObject* gameObject) {
        if (!gameObject) return nullptr;
        static Il2CppClass* goKlass = GetClass("UnityEngine.CoreModule.dll", "UnityEngine", "GameObject");
        if (!goKlass) goKlass = GetClass("UnityEngine.dll", "UnityEngine", "GameObject");
        if (!goKlass) return nullptr;
        static uintptr_t getTransform = GetMethod(goKlass, "get_transform", 0);
        if (!getTransform) return nullptr;
        return CallMethod<void*>(getTransform, gameObject);
    }

    void Transform_SetPosition(void* transform, Vector3 pos) {
        if (!transform) return;
        static Il2CppClass* transKlass = GetClass("UnityEngine.CoreModule.dll", "UnityEngine", "Transform");
        if (!transKlass) transKlass = GetClass("UnityEngine.dll", "UnityEngine", "Transform");
        if (!transKlass) return;
        static uintptr_t setPos = GetMethod(transKlass, "set_position", 1);
        if (!setPos) return;
        CallMethod<void>(setPos, transform, pos);
    }

    void Transform_SetRotation(void* transform, Quaternion rot) {
        if (!transform) return;
        static Il2CppClass* transKlass = GetClass("UnityEngine.CoreModule.dll", "UnityEngine", "Transform");
        if (!transKlass) transKlass = GetClass("UnityEngine.dll", "UnityEngine", "Transform");
        if (!transKlass) return;
        static uintptr_t setRot = GetMethod(transKlass, "set_rotation", 1);
        if (!setRot) return;
        CallMethod<void>(setRot, transform, rot);
    }

    void Transform_SetLocalScale(void* transform, Vector3 scale) {
        if (!transform) return;
        static Il2CppClass* transKlass = GetClass("UnityEngine.CoreModule.dll", "UnityEngine", "Transform");
        if (!transKlass) transKlass = GetClass("UnityEngine.dll", "UnityEngine", "Transform");
        if (!transKlass) return;
        static uintptr_t setScale = GetMethod(transKlass, "set_localScale", 1);
        if (!setScale) return;
        CallMethod<void>(setScale, transform, scale);
    }

    void* Transform_GetParent(void* transform) {
        if (!transform) return nullptr;
        static Il2CppClass* transKlass = GetClass("UnityEngine.CoreModule.dll", "UnityEngine", "Transform");
        if (!transKlass) transKlass = GetClass("UnityEngine.dll", "UnityEngine", "Transform");
        if (!transKlass) return nullptr;
        static uintptr_t getParent = GetMethod(transKlass, "get_parent", 0);
        if (!getParent) return nullptr;
        return CallMethod<void*>(getParent, transform);
    }

    Vector3 Transform_GetPosition(void* transform) {
        if (!transform) return Vector3();
        static Il2CppClass* transKlass = GetClass("UnityEngine.CoreModule.dll", "UnityEngine", "Transform");
        if (!transKlass) transKlass = GetClass("UnityEngine.dll", "UnityEngine", "Transform");
        if (!transKlass) return Vector3();
        static uintptr_t getPos = GetMethod(transKlass, "get_position", 0);
        if (!getPos) return Vector3();
        return CallMethod<Vector3>(getPos, transform);
    }

    Quaternion Transform_GetRotation(void* transform) {
        if (!transform) return Quaternion();
        static Il2CppClass* transKlass = GetClass("UnityEngine.CoreModule.dll", "UnityEngine", "Transform");
        if (!transKlass) transKlass = GetClass("UnityEngine.dll", "UnityEngine", "Transform");
        if (!transKlass) return Quaternion();
        static uintptr_t getRot = GetMethod(transKlass, "get_rotation", 0);
        if (!getRot) return Quaternion();
        return CallMethod<Quaternion>(getRot, transform);
    }

    Vector3 Transform_GetLocalScale(void* transform) {
        if (!transform) return Vector3();
        static Il2CppClass* transKlass = GetClass("UnityEngine.CoreModule.dll", "UnityEngine", "Transform");
        if (!transKlass) transKlass = GetClass("UnityEngine.dll", "UnityEngine", "Transform");
        if (!transKlass) return Vector3();
        static uintptr_t getScale = GetMethod(transKlass, "get_localScale", 0);
        if (!getScale) return Vector3();
        return CallMethod<Vector3>(getScale, transform);
    }

    Il2CppObject* Camera_GetMain() {
        static Il2CppClass* camKlass = GetClass("UnityEngine.CoreModule.dll", "UnityEngine", "Camera");
        if (!camKlass) camKlass = GetClass("UnityEngine.dll", "UnityEngine", "Camera");
        if (!camKlass) return nullptr;
        static uintptr_t getMain = GetMethod(camKlass, "get_main", 0);
        if (!getMain) return nullptr;
        return CallMethod<Il2CppObject*>(getMain, nullptr);
    }

    bool WorldToScreen(Vector3 worldPos, Vector3& screenPos, float* matrix) {
        Il2CppObject* cam = Camera_GetMain();
        if (!cam) return false;

        static Il2CppClass* camKlass = GetClass("UnityEngine.CoreModule.dll", "UnityEngine", "Camera");
        if (!camKlass) camKlass = GetClass("UnityEngine.dll", "UnityEngine", "Camera");
        static uintptr_t w2s = GetMethod(camKlass, "WorldToScreenPoint", 1);
        if (!w2s) return false;

        Vector3 res = CallMethod<Vector3>(w2s, cam, worldPos);

        if (res.z < 0) return false;

        screenPos = res;
        return true;
    }

    Il2CppObject* GameObject_GetComponentByName(Il2CppObject* gameObject, const char* componentTypeName) {
        if (!gameObject || !componentTypeName) return nullptr;

        Il2CppClass* componentClass = GetClass("UnityEngine.CoreModule.dll", "UnityEngine", componentTypeName);
        if (!componentClass) componentClass = GetClass("UnityEngine.dll", "UnityEngine", componentTypeName);
        if (!componentClass) return nullptr;

        Il2CppObject* typeObj = GetSystemType(componentClass);
        if (!typeObj) return nullptr;

        static Il2CppClass* goKlass = GetClass("UnityEngine.CoreModule.dll", "UnityEngine", "GameObject");
        if (!goKlass) goKlass = GetClass("UnityEngine.dll", "UnityEngine", "GameObject");
        if (!goKlass) return nullptr;

        static uintptr_t getComponent = GetMethod(goKlass, "GetComponent", 1);
        if (!getComponent) return nullptr;

        return CallMethod<Il2CppObject*>(getComponent, gameObject, typeObj);
    }

    Il2CppObject* GameObject_GetComponentsInChildrenByName(Il2CppObject* gameObject, const char* componentTypeName, bool includeInactive) {
        if (!gameObject || !componentTypeName) return nullptr;

        Il2CppClass* componentClass = GetClass("UnityEngine.CoreModule.dll", "UnityEngine", componentTypeName);
        if (!componentClass) componentClass = GetClass("UnityEngine.dll", "UnityEngine", componentTypeName);
        if (!componentClass) return nullptr;

        Il2CppObject* typeObj = GetSystemType(componentClass);
        if (!typeObj) return nullptr;

        static Il2CppClass* goKlass = GetClass("UnityEngine.CoreModule.dll", "UnityEngine", "GameObject");
        if (!goKlass) goKlass = GetClass("UnityEngine.dll", "UnityEngine", "GameObject");
        if (!goKlass) return nullptr;

        static uintptr_t getComponents = GetMethod(goKlass, "GetComponentsInChildren", 2);
        if (!getComponents) return nullptr;

        return CallMethod<Il2CppObject*>(getComponents, gameObject, typeObj, includeInactive);
    }

    std::vector<void*> Array_ToVector(void* array) {
        std::vector<void*> result;
        if (!array || !il2cpp_array_length) return result;

        uint32_t len = il2cpp_array_length((Il2CppArray*)array);
        uintptr_t dataOffset = (sizeof(void*) == 8) ? 0x20 : 0x10;
        void** data = reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(array) + dataOffset);
        for (uint32_t i = 0; i < len; ++i) {
            result.push_back(data[i]);
        }
        return result;
    }

    std::vector<void*> SkinnedMeshRenderer_GetBones(Il2CppObject* skinnedMeshRenderer) {
        std::vector<void*> bones;
        if (!skinnedMeshRenderer) return bones;

        Il2CppClass* klass = GetClass("UnityEngine.CoreModule.dll", "UnityEngine", "SkinnedMeshRenderer");
        if (!klass) klass = GetClass("UnityEngine.dll", "UnityEngine", "SkinnedMeshRenderer");
        if (!klass) return bones;

        static uintptr_t getBones = GetMethod(klass, "get_bones", 0);
        if (!getBones) return bones;

        Il2CppObject* boneArray = CallMethod<Il2CppObject*>(getBones, skinnedMeshRenderer);
        if (!boneArray) return bones;

        return Array_ToVector(boneArray);
    }

    Il2CppObject* Animator_GetRuntimeAnimatorController(Il2CppObject* animator) {
        if (!animator) return nullptr;

        Il2CppClass* klass = GetClass("UnityEngine.CoreModule.dll", "UnityEngine", "Animator");
        if (!klass) klass = GetClass("UnityEngine.dll", "UnityEngine", "Animator");
        if (!klass) return nullptr;

        static uintptr_t getController = GetMethod(klass, "get_runtimeAnimatorController", 0);
        if (!getController) return nullptr;

        return CallMethod<Il2CppObject*>(getController, animator);
    }

    std::vector<std::string> Animator_GetClipNames(Il2CppObject* animator) {
        std::vector<std::string> names;
        if (!animator) return names;

        Il2CppObject* controller = Animator_GetRuntimeAnimatorController(animator);
        if (!controller) return names;

        Il2CppClass* controllerKlass = GetObjectClass(controller);
        if (!controllerKlass) return names;

        static uintptr_t getClips = GetMethod(controllerKlass, "get_animationClips", 0);
        if (!getClips) return names;

        Il2CppObject* clipArray = CallMethod<Il2CppObject*>(getClips, controller);
        if (!clipArray) return names;

        std::vector<void*> clips = Array_ToVector(clipArray);
        for (void* clip : clips) {
            if (!clip) continue;
            Il2CppClass* clipKlass = GetObjectClass(reinterpret_cast<Il2CppObject*>(clip));
            if (!clipKlass) continue;
            static uintptr_t getName = GetMethod(clipKlass, "get_name", 0);
            if (!getName) continue;
            Il2CppString* str = CallMethod<Il2CppString*>(getName, clip);
            if (!str) continue;
            names.emplace_back(ToString(str));
        }
        return names;
    }
}
