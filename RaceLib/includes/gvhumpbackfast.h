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
    class EXPORT_API GV_Humpback_Fast : public VehicleGround // -----------------------------------------------------------------------------------------------
    {
    public:

        /*
        Рассчёт времени прохождения дистации
        Для класса GV_Humpback_Fast
        */
        void calculate_time_result(int);

        // Конструкторы

        GV_Humpback_Fast() = delete;

        GV_Humpback_Fast(std::string);

    protected:

    private:

    }; // END OF class GV_Humpback_Fast -------------------------------------------------------------------------------
} // end of namespace jinx