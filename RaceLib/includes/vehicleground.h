#pragma once

// INCLUDES

#include "vehicle.h"

#ifdef _WIN32
#include <string>
#else
#include <string.h>
#endif

// -------

namespace jinx
{

 class VehicleGround : public Vehicle // -----------------------------------------------------------------------------------------------
    {
    public:

        void calculate_time_result(int _distance) override = 0;

        // Constructor removal
        VehicleGround() = delete;

        VehicleGround(std::string);

        // Destructor

        // virtual ~VehicleGround() = 0;

    protected:
        
        bool vehicleType;

    private:
        
    }; // END OF class VehicleGround ---------------------------------------------------------------------------------------------

    // ---------------------------
} // end of namespace jinx