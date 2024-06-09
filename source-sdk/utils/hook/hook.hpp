#pragma once
namespace utils {
    /**
     * 
     * @brief hook a function by vmt
     * 
     * @tparam T the type of the function
     * @tparam C the type of the class
     * 
     * @param function  a pointer to the hook function
     * @param index     the index in the vmt
     * @param klass     a pointer to the class
     * 
     * @returns the original function
     * 
     */
    template <typename T, typename C>
    inline T HookVMT(T function, uint32_t index, C *klass) {
        const auto vmt = *reinterpret_cast<uintptr_t **>(klass);
        const uintptr_t original = vmt[index];

        vmt[index] = reinterpret_cast<uintptr_t>(function);

        return original;
    }
};