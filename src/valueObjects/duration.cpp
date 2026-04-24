#include "valueObjects/duration.h"

Duration::Duration(std::chrono::minutes duration) : mDuration(duration) {}

Duration Duration::fromMinutes(int minutes)
{
    return Duration(std::chrono::minutes(minutes));
}

int Duration::getDurationInMinutes() const
{
    return mDuration.count();
}

std::ostream &operator<<(std::ostream &os, const Duration &duration)
{
    int totalMinutes = duration.getDurationInMinutes();

    int hours = totalMinutes / 60;
    int minutes = totalMinutes % 60;

    os << hours << "h " << minutes << "m";
    return os;
}