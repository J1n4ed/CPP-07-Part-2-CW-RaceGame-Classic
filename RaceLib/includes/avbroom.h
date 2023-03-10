#pragma once

#ifdef RaceLib_EXPORTS
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API __declspec(dllimport)
#endif

// INCLUDES

#include "vehicleair.h"

#ifdef _WIN32
#include <string>
#else
#include <string.h>
#endif

// -------


namespace jinx
{
    class EXPORT_API AV_Broom : public VehicleAir // -----------------------------------------------------------------------------------------------
    {
    public:        

        /*
        Рассчёт времени прохождения дистации
        Для класса AV_Broom
        */
        void calculate_time_result(int);

        // Конструкторы

        AV_Broom() = delete;

        AV_Broom(std::string);

    protected:

    private:

    }; // END OF class AV_Broom ------------------------------------------------------------------
	
} // end of namespace jinx