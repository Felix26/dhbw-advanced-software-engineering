#include "valueObjects/count.h"

Count::Count(size_t count) : mCount(count) {}


Count Count::operator+(const Count &other) const
{
    return Count(this->mCount + other.mCount);
}

Count &Count::operator+=(const Count &other)
{
    this->mCount += other.mCount;
    return *this;
}

Count Count::operator-(const Count &other) const
{
    return Count(this->mCount - other.mCount);
}

Count &Count::operator-=(const Count &other)
{
    this->mCount -= other.mCount;
    return *this;
}

Count Count::operator*(size_t factor) const
{
    return Count(mCount * factor);
}

Count &Count::operator*=(size_t factor)
{
    this->mCount = this->mCount * factor;
    return *this;
}

double Count::operator/(const Count &other) const
{
    return static_cast<double>(this->mCount) / other.mCount;
}

std::ostream &operator<<(std::ostream &os, const Count &count)
{
    os << count.mCount << "x";
    return os;
}