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

int Duration::getDurationInSeconds() const
{
    return std::chrono::duration_cast<std::chrono::seconds>(mDuration).count();
}


Duration Duration::operator+(const Duration &other) const
{
    return Duration(this->mDuration + other.mDuration);
}

Duration &Duration::operator+=(const Duration &other)
{
    this->mDuration += other.mDuration;
    return *this;
}

Duration Duration::operator-(const Duration &other) const
{
    return Duration(this->mDuration - other.mDuration);
}

Duration &Duration::operator-=(const Duration &other)
{
    this->mDuration -= other.mDuration;
    return *this;
}

Duration Duration::operator*(double factor) const
{
    return Duration(std::chrono::minutes(static_cast<int>(this->mDuration.count() * factor)));
}

Duration &Duration::operator*=(double factor)
{
    this->mDuration = std::chrono::minutes(static_cast<int>(this->mDuration.count() * factor));
    return *this;
}

Duration Duration::operator/(double divisor) const
{
    return Duration(std::chrono::minutes(static_cast<int>(this->mDuration.count() / divisor)));
}

Duration &Duration::operator/=(double divisor)
{
    this->mDuration = std::chrono::minutes(static_cast<int>(this->mDuration.count() / divisor));
    return *this;
}

double Duration::operator/(const Duration &other) const
{
    return static_cast<double>(this->getDurationInSeconds()) / other.getDurationInSeconds();
}

std::ostream &operator<<(std::ostream &os, const Duration &duration)
{
    int totalMinutes = duration.getDurationInMinutes();

    int hours = totalMinutes / 60;
    int minutes = totalMinutes % 60;

    os << hours << "h " << minutes << "m";
    return os;
}