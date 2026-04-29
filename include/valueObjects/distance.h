#pragma once

#include <ostream>

class Speed;
class Duration;

class Distance
{
    public:
        static Distance fromMeters(double meters);
        Distance() : mDistance(0.0) {}

        double getDistanceInMeters() const;

        Distance operator+(const Distance& other) const;
        Distance &operator+=(const Distance& other);
        Distance operator-(const Distance& other) const;
        Distance &operator-=(const Distance& other);

        Distance operator*(double factor) const;
        Distance &operator*=(double factor);
        Distance operator/(double divisor) const;
        Distance &operator/=(double divisor);

        Speed operator/(const Duration &duration) const;

        auto operator<=>(const Distance& other) const = default;

        double operator/(const Distance& other) const;

        friend std::ostream& operator<<(std::ostream& os, const Distance& distance);
        
        static std::string getValueTypeName();
    private:
        Distance(double distance);

        double mDistance;
};