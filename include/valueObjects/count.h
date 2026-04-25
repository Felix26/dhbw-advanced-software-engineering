#pragma once

#include <ostream>

class Count
{
    public:
        Count(size_t count);

        Count operator+(const Count& other) const;
        Count &operator+=(const Count& other);
        Count operator-(const Count& other) const;
        Count &operator-=(const Count& other);

        Count operator*(size_t factor) const;
        Count &operator*=(size_t factor);

        auto operator<=>(const Count& other) const = default;

        double operator/(const Count& other) const;

        friend std::ostream& operator<<(std::ostream& os, const Count& count);

        static std::string getValueTypeName();
        
    private:
        size_t mCount;
};