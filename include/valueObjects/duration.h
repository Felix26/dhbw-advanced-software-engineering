#pragma once

#include <chrono>
#include <ostream>

class Duration
{
    public:
        static Duration fromMinutes(int minutes);

        int getDurationInMinutes() const;

        friend std::ostream& operator<<(std::ostream& os, const Duration& duration);

    private:
        Duration(std::chrono::minutes duration);

        std::chrono::minutes mDuration;
};