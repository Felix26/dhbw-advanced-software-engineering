#pragma once

#include <chrono>
#include <ostream>

class Duration
{
    public:
        static Duration fromMinutes(int minutes);
        Duration() : mDuration(std::chrono::minutes(0)) {}

        int getDurationInMinutes() const;
        int getDurationInSeconds() const;

        Duration operator+(const Duration& other) const;
        Duration &operator+=(const Duration& other);
        Duration operator-(const Duration& other) const;
        Duration &operator-=(const Duration& other);

        Duration operator*(double factor) const;
        Duration &operator*=(double factor);
        Duration operator/(double divisor) const;
        Duration &operator/=(double divisor);

        auto operator<=>(const Duration& other) const = default;

        double operator/(const Duration& other) const;

        friend std::ostream& operator<<(std::ostream& os, const Duration& duration);

        static std::string getValueTypeName();
    private:
        Duration(std::chrono::minutes duration);

        std::chrono::minutes mDuration;
};