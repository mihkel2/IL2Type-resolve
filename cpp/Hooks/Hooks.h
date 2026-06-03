#ifndef HOOKS_H
#define HOOKS_H

#include "Utils/Macros.h"
#include "Resolver/Il2CppResolver.h"

namespace Hooks {
    void Install();
    void Hook(void* address, void* replace_call, void** origin_call);
}

#endif // HOOKS_H
