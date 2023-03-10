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
    class EXPORT_API GV_Centaur : public VehicleGround // -----------------------------------------------------------------------------------------------
    {
    public:        

        void calculate_time_result(int);

        // Конструкторы

        GV_Centaur() = delete;

        GV_Centaur(std::string);

    protected:

    private:

    }; // END OF  class GV_Centaur -------------------------------------------------------------------------
} // end of namespace jinx