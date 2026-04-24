#pragma once

#include <ostream>

class Speed
{
    public:
        auto operator<=>(const Speed& other) const = default;

        friend std::ostream& operator<<(std::ostream& os, const Speed& speed);

        double getSpeedInKmH() const;

    private:
        Speed(double speed);
        friend class Distance; 

        double mSpeed; // Speed in meters per second
};