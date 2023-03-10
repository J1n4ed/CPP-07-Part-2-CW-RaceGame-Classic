#pragma once

// INCLUDES

#ifdef RaceLib_EXPORTS
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API __declspec(dllimport)
#endif

#ifdef _WIN32
#include <string>
#else
#include <string.h>
#endif

#include "set_defines.h"
#include <vector>
#include <random>

// -------

namespace jinx 
{

	/*
    Базовый абстрактный класс Vehicle
    */
    class EXPORT_API Vehicle // -----------------------------------------------------------------------------------------------
    {
    public:       
    // PUBLIC CODE AREA ----------------------------------------------------------------------------------------------

        virtual void calculate_time_result(int _distance) = 0;

        // СЕТТЕРЫ КЛАССА ----------------------------

        /*
        Установка результата времени
        */
        void set_time_result(double);

        /*
        Установить имя ТС
        */
        void set_vehicle_name(std::string);

        /*
        Установить скорость ТС
        */
        void set_vehicle_speed(int);

        // ------------------------------------------

        // ГЕТТЕРЫ КЛАССА ---------------------------

        /*
        Взять имя тс
        */
        std::string get_vehicle_name();

        /*
        Взять имя пилота
        */
        std::string get_pilot_name();

        /*
        Взять скорость
        */
        int get_vehicle_speed();

        /*
        Взять результат
        */
        double get_race_result();

        // Overloads

        bool operator<(const Vehicle&) const;

        bool operator>(const Vehicle&) const;

        // Constructors ---------------------------
        Vehicle() = delete;

        Vehicle(std::string);
		
        // Destructor

        // virtual ~Vehicle() = 0;

    protected:    
    // PROTECTED CODE AREA ----------------------------------------------------------------------------------------------

    private:
        
        std::string vehiclePilot;       // пилот ТС
        std::string vehicleName;        // название ТС
        int speed;                      // скорость ТС
        double raceResultTime;             // Результат прохождения расстояния Х
       
    }; // END OF class Vehicle

    // ---------------------------
} // end of namespace jinx