#include "Il2CppResolver.h"
#include <string.h>
#include <fstream>
#include <sstream>

namespace Resolver {
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
        void* handle = dlopen("libil2cpp.so", RTLD_LAZY);
        if (!handle) return false;

        il2cpp_domain_get = (Il2CppDomain* (*)())dlsym(handle, "il2cpp_domain_get");
        il2cpp_domain_get_assemblies = (const Il2CppAssembly** (*)(const Il2CppDomain*, size_t*))dlsym(handle, "il2cpp_domain_get_assemblies");
        il2cpp_assembly_get_image = (const Il2CppImage* (*)(const Il2CppAssembly*))dlsym(handle, "il2cpp_assembly_get_image");
        il2cpp_image_get_name = (const char* (*)(const Il2CppImage*))dlsym(handle, "il2cpp_image_get_name");
        il2cpp_image_get_class_count = (size_t (*)(const Il2CppImage*))dlsym(handle, "il2cpp_image_get_class_count");
        il2cpp_image_get_class = (const Il2CppClass* (*)(const Il2CppImage*, size_t))dlsym(handle, "il2cpp_image_get_class");
        il2cpp_class_from_name = (Il2CppClass* (*)(const Il2CppImage*, const char*, const char*))dlsym(handle, "il2cpp_class_from_name");
        il2cpp_class_get_nested_types = (Il2CppClass* (*)(Il2CppClass*, void**))dlsym(handle, "il2cpp_class_get_nested_types");
        il2cpp_class_get_name = (const char* (*)(Il2CppClass*))dlsym(handle, "il2cpp_class_get_name");
        il2cpp_class_get_namespace = (const char* (*)(Il2CppClass*))dlsym(handle, "il2cpp_class_get_namespace");
        il2cpp_class_get_methods = (const Il2CppMethod* (*)(Il2CppClass*, void**))dlsym(handle, "il2cpp_class_get_methods");
        il2cpp_class_get_method_from_name = (const Il2CppMethod* (*)(Il2CppClass*, const char*, int))dlsym(handle, "il2cpp_class_get_method_from_name");
        il2cpp_class_get_fields = (Il2CppField* (*)(Il2CppClass*, void**))dlsym(handle, "il2cpp_class_get_fields");
        il2cpp_class_get_field_from_name = (Il2CppField* (*)(Il2CppClass*, const char*))dlsym(handle, "il2cpp_class_get_field_from_name");
        il2cpp_field_get_name = (const char* (*)(Il2CppField*))dlsym(handle, "il2cpp_field_get_name");
        il2cpp_field_get_value = (void (*)(void*, Il2CppField*, void*))dlsym(handle, "il2cpp_field_get_value");
        il2cpp_field_set_value = (void (*)(void*, Il2CppField*, void*))dlsym(handle, "il2cpp_field_set_value");
        il2cpp_field_static_get_value = (void (*)(Il2CppField*, void*))dlsym(handle, "il2cpp_field_static_get_value");
        il2cpp_field_static_set_value = (void (*)(Il2CppField*, void*))dlsym(handle, "il2cpp_field_static_set_value");
        il2cpp_method_get_name = (const char* (*)(const Il2CppMethod*))dlsym(handle, "il2cpp_method_get_name");
        il2cpp_method_get_param_count = (int (*)(const Il2CppMethod*))dlsym(handle, "il2cpp_method_get_param_count");
        il2cpp_type_get_object = (Il2CppObject* (*)(const Il2CppType*))dlsym(handle, "il2cpp_type_get_object");
        il2cpp_class_get_type = (const Il2CppType* (*)(Il2CppClass*))dlsym(handle, "il2cpp_class_get_type");
        il2cpp_array_length = (uint32_t (*)(Il2CppArray*))dlsym(handle, "il2cpp_array_length");
        il2cpp_runtime_invoke = (Il2CppObject* (*)(const Il2CppMethod*, void*, void**, Il2CppObject**))dlsym(handle, "il2cpp_runtime_invoke");
        il2cpp_object_get_class = (void* (*)(Il2CppObject*))dlsym(handle, "il2cpp_object_get_class");

        return true;
    }

    Il2CppClass* GetClass(const char* assemblyName, const char* namespaze, const char* className) {
        Il2CppDomain* domain = il2cpp_domain_get();
        size_t size;
        const Il2CppAssembly** assemblies = il2cpp_domain_get_assemblies(domain, &size);
        for (size_t i = 0; i < size; ++i) {
            const Il2CppImage* image = il2cpp_assembly_get_image(assemblies[i]);
            if (strcmp(il2cpp_image_get_name(image), assemblyName) == 0) {
                return il2cpp_class_from_name(image, namespaze, className);
            }
        }
        return nullptr;
    }

    Il2CppClass* GetClassFromImage(const Il2CppImage* image, const char* namespaze, const char* className) {
        if (!image) return nullptr;
        return il2cpp_class_from_name(image, namespaze, className);
    }

    Il2CppClass* GetNestedClass(Il2CppClass* klass, const char* name) {
        if (!klass) return nullptr;
        void* iter = nullptr;
        while (Il2CppClass* sub = il2cpp_class_get_nested_types(klass, &iter)) {
            if (strcmp(il2cpp_class_get_name(sub), name) == 0) return sub;
        }
        return nullptr;
    }

    uintptr_t GetMethod(Il2CppClass* klass, const char* methodName, int argsCount) {
        const Il2CppMethod* method = il2cpp_class_get_method_from_name(klass, methodName, argsCount);
        if (!method) return 0;
        return *(uintptr_t*)method;
    }

    Il2CppObject* GetSystemType(Il2CppClass* klass) {
        if (!klass) return nullptr;
        return il2cpp_type_get_object(il2cpp_class_get_type(klass));
    }

    bool IsValidObject(Il2CppObject* obj) {
        if (!obj) return false;
        return il2cpp_object_get_class(obj) != nullptr;
    }

    void Il2cppDump(const char* outPath) {
        std::ofstream out(outPath);
        if (!out.is_open()) return;

        Il2CppDomain* domain = il2cpp_domain_get();
        size_t assemCount;
        const Il2CppAssembly** assemblies = il2cpp_domain_get_assemblies(domain, &assemCount);

        for (size_t i = 0; i < assemCount; i++) {
            const Il2CppImage* image = il2cpp_assembly_get_image(assemblies[i]);
            out << "// Assembly: " << il2cpp_image_get_name(image) << "\n";
            size_t classCount = il2cpp_image_get_class_count(image);

            for (size_t j = 0; j < classCount; j++) {
                Il2CppClass* klass = (Il2CppClass*)il2cpp_image_get_class(image, j);
                if (!klass) continue;

                out << "class " << il2cpp_class_get_namespace(klass) << "::" << il2cpp_class_get_name(klass) << " {\n";

                // Dump Fields
                void* fIter = nullptr;
                while (Il2CppField* field = il2cpp_class_get_fields(klass, &fIter)) {
                    out << "  " << il2cpp_field_get_name(field) << ";\n";
                }

                // Dump Methods
                void* mIter = nullptr;
                while (const Il2CppMethod* method = il2cpp_class_get_methods(klass, &mIter)) {
                    out << "  " << il2cpp_method_get_name(method) << "(" << il2cpp_method_get_param_count(method) << "); // addr: " << (void*)(*(uintptr_t*)method) << "\n";
                }
                out << "}\n\n";
            }
        }
        out.close();
    }
}
