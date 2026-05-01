#include <cassert>

#include <sstream>

#include "valueObjects/allValueObjectHeaders.h"

int main()
{
    Distance distance = Distance::fromMeters(12345.67);
    Duration duration = Duration::fromMinutes(90);
    Speed speed = distance / duration;
    Count count = Count(5);

    std::stringstream ss;
    ss << distance;
    assert(ss.str() == "12.35 km");

    ss.str("");
    ss << Distance::fromMeters(500);
    assert(ss.str() == "500 m");

    ss.str("");
    ss << duration;
    assert(ss.str() == "1h 30m");

    ss.str("");
    ss << speed;
    assert(ss.str() == "8.23 km/h");

    ss.str("");
    ss << count;
    assert(ss.str() == "5x");

    assert(distance.getDistanceInMeters() == 12345.67);
    assert(distance.getValueTypeName() == "Distanz");
    assert(distance + distance == Distance::fromMeters(24691.34));
    assert(distance - Distance::fromMeters(2345.67) == Distance::fromMeters(10000));
    assert(distance * 2 == Distance::fromMeters(24691.34));
    assert(distance / 2 == Distance::fromMeters(6172.835));
    assert(distance / distance == 1.0);

    distance += Distance::fromMeters(1000);
    assert(distance.getDistanceInMeters() == 13345.67);
    distance -= Distance::fromMeters(345.67);
    assert(distance.getDistanceInMeters() == 13000);
    distance *= 2;
    assert(distance.getDistanceInMeters() == 26000);
    distance /= 2;
    assert(distance.getDistanceInMeters() == 13000);


    assert(duration.getDurationInMinutes() == 90);
    assert(duration.getValueTypeName() == "Dauer");
    assert(duration + duration == Duration::fromMinutes(180));
    assert(duration - Duration::fromMinutes(30) == Duration::fromMinutes(60));
    assert(duration * 2 == Duration::fromMinutes(180));
    assert(duration / 2 == Duration::fromMinutes(45));
    assert(duration / duration == 1.0);

    duration += Duration::fromMinutes(30);
    assert(duration.getDurationInMinutes() == 120);
    duration -= Duration::fromMinutes(20);
    assert(duration.getDurationInMinutes() == 100);
    duration *= 1.5;
    assert(duration.getDurationInMinutes() == 150);
    duration /= 2;
    assert(duration.getDurationInMinutes() == 75);


    assert(speed.getSpeedInKmH() - (distance.getDistanceInMeters() / 1000.0) / (duration.getDurationInMinutes() / 60.0) < 0.01);
    assert(speed.getValueTypeName() == "Geschwindigkeit");
    assert(speed / speed == 1.0);

    Speed speed2 = speed;
    speed += speed;
    speed = speed / 2;
    assert(speed.getSpeedInKmH() - speed2.getSpeedInKmH() < 0.01);

    assert(count.getValueTypeName() == "Anzahl");
    assert(count + count == Count(10));
    assert(count - Count(2) == Count(3));
    assert(count * 2 == Count(10));
    assert(count / count == 1.0);

    count += Count(3);
    assert(count == Count(8));
    count *= 2;
    assert(count == Count(16));
    count = count / 2;
    assert(count == Count(8));
    count -= Count(5);
    assert(count == Count(3));

    return 0;
}