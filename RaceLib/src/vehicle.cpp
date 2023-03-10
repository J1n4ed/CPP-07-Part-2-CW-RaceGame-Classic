#include "vehicle.h"

/*
Установка результата времени
*/
void jinx::Vehicle::set_time_result(double _resultTime)
{
    raceResultTime = _resultTime;
}
	
	
/*
Установить имя ТС
*/
void jinx::Vehicle::set_vehicle_name(std::string _vehicleName)
{
    vehicleName = _vehicleName;
}

/*
Установить скорость ТС
*/
void jinx::Vehicle::set_vehicle_speed(int _speed)
{
    // RNG GENERATION

    // Random seed
    std::random_device rd;

    // Initialize Mersenne Twister pseudo-random number generator
    std::mt19937 gen(rd());

    // Generate pseudo-random numbers
    // uniformly distributed in range (1, 100)
    std::uniform_int_distribution<> dis(1, 3);
    // int ... = dis(gen);

    // --------------
    int rng_seed = dis(gen);

        std::uniform_int_distribution<> dis2(1, 2);

        if (dis2(gen) == 1)
        {
            rng_seed *= -1;
        }

    speed = _speed + rng_seed;
}

 /*
 Взять имя тс
*/
std::string jinx::Vehicle::get_vehicle_name()
{
    return vehicleName;
}

/*
Взять имя пилота
*/
std::string jinx::Vehicle::get_pilot_name()
{
    return vehiclePilot;
}

/*
Взять скорость
*/
int jinx::Vehicle::get_vehicle_speed()
{
    return speed;
}

/*
Взять результат
*/
double jinx::Vehicle::get_race_result()
{
    return raceResultTime;
}

bool jinx::Vehicle::operator<(const Vehicle& Veh) const
{
    return (raceResultTime < Veh.raceResultTime);
}

bool jinx::Vehicle::operator>(const Vehicle& Veh) const
{
    return (raceResultTime > Veh.raceResultTime);
}

jinx::Vehicle::Vehicle(std::string _vehiclePilot)
{
	this->vehiclePilot = _vehiclePilot;
}