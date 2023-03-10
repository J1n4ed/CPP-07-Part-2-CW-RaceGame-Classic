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

class VehicleAir : public Vehicle // -----------------------------------------------------------------------------------------------
    {
    public:          

        void calculate_time_result(int _distance) override = 0;

        // Constructor removal
        VehicleAir() = delete;

        VehicleAir(std::string);

        // Destructor

        // virtual ~VehicleAir() = 0;

    protected:       
        
        bool vehicleType;

    private:
        
    }; // END OF class VehicleAir ---------------------------------------------------------------------------------------------

    // ---------------------------
	
} // end of namespace jinx