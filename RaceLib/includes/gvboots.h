#pragma once

#ifdef RaceLib_EXPORTS
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API __declspec(dllimport)
#endif

// INCLUDES

#include "vehicleground.h"

#ifdef _WIN32
#include <string>
#else
#include <string.h>
#endif

// -------

namespace jinx
{
    class EXPORT_API GV_AllTBoots : public VehicleGround // -----------------------------------------------------------------------------------------------
    {
    public:        

        /*
        Рассчёт времени прохождения дистации
        Для класса GV_AllTBoots
        */
        void calculate_time_result(int);

        // Конструкторы

        GV_AllTBoots() = delete;

        GV_AllTBoots(std::string);

    protected:

    private:

    }; // END OF class GV_AllTBoots ------------------------------------------------------------------------
	
} // end of namespace jinx