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

    class EXPORT_API GV_Humpback : public VehicleGround // ----------------------------------------
    {
    public:

        void calculate_time_result(int);

        // Конструкторы

        GV_Humpback() = delete;

        GV_Humpback(std::string);

    protected:

    private:       

    }; // END OF class GV_Humpback ---------------------------------------------------------------------
	
} // end of namespace jinx