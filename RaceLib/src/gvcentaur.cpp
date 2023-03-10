#include "gvcentaur.h"

void 	jinx::GV_Centaur::calculate_time_result(int _distance)
        {
            // Скорость:                    15
            // Время движения до отдыха:    8
            // Длительность отдыха: 
            //                              Всегда: 2

            // VARIABLES

            double brutTime = _distance / this->get_vehicle_speed();
            double nettTime = brutTime;
            int restNum = static_cast<int>(brutTime) / 8; // TIME UNTIL REST

            for (int i = 1; i <= restNum; ++i)
            {
                nettTime += 2;
            }

            this->set_time_result(nettTime);
        }
		
jinx::GV_Centaur::GV_Centaur(std::string _vehiclePilot)
            : VehicleGround(_vehiclePilot)
        {
            std::string _vehicleName = "Кентавр\t";
            set_vehicle_name(_vehicleName);
            set_vehicle_speed(SPEED_CENTAUR);
        }