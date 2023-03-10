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
    ������� ����������� ����� Vehicle
    */
    class EXPORT_API Vehicle // -----------------------------------------------------------------------------------------------
    {
    public:       
    // PUBLIC CODE AREA ----------------------------------------------------------------------------------------------

        virtual void calculate_time_result(int _distance) = 0;

        // ������� ������ ----------------------------

        /*
        ��������� ���������� �������
        */
        void set_time_result(double);

        /*
        ���������� ��� ��
        */
        void set_vehicle_name(std::string);

        /*
        ���������� �������� ��
        */
        void set_vehicle_speed(int);

        // ------------------------------------------

        // ������� ������ ---------------------------

        /*
        ����� ��� ��
        */
        std::string get_vehicle_name();

        /*
        ����� ��� ������
        */
        std::string get_pilot_name();

        /*
        ����� ��������
        */
        int get_vehicle_speed();

        /*
        ����� ���������
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
        
        std::string vehiclePilot;       // ����� ��
        std::string vehicleName;        // �������� ��
        int speed;                      // �������� ��
        double raceResultTime;             // ��������� ����������� ���������� �
       
    }; // END OF class Vehicle

    // ---------------------------
} // end of namespace jinx