#pragma once

#include <ostream>

class Speed
{
    public:
        auto operator<=>(const Speed& other) const = default;

        friend std::ostream& operator<<(std::ostream& os, const Speed& speed);

    private:
        Speed(double speed);

        double mSpeed; // Speed in meters per second
};