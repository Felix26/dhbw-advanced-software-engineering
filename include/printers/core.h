#pragma once

namespace Printers
{
    template <typename T>
    struct PrettyWrapper
    {
        const T &value;
    };

    template <typename T>
    inline PrettyWrapper<T> pretty(const T &value)
    {
        return PrettyWrapper<T>{value};
    }
}