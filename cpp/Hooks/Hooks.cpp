#include "Hooks.h"
#include "Utils/Logger.h"
#include "Resolver/Il2CppResolver.h"
#include "ThirdParty/Dobby/include/dobby.h"

namespace Hooks {

    void Hook(void* address, void* replace_call, void** origin_call) {
        if (!address) {
            LOGE("Hook failed: Address is null");
            return;
        }

        int result = DobbyHook(address, replace_call, origin_call);
        if (result == 0) {
            LOGI("Successfully hooked address: %p", address);
        } else {
            LOGE("Failed to hook address %p. Result code: %d", address, result);
        }
    }

    void Install() {
        LOGI("Installing Hooks...");
        // This is called from Core.cpp
        LOGI("Hooks installation finished.");
    }
}
