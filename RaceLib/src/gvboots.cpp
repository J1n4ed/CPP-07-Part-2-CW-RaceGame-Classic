#include "gvboots.h"

void jinx::GV_AllTBoots::calculate_time_result(int _distance)
        {
            // Скорость:                    6
            // Время движения до отдыха:    60
            // Длительность отдыха: 
            //                              Первый раз: 10
            //                              Второй раз: 5

            // VARIABLES

            double brutTime = _distance / this->get_vehicle_speed();
            double nettTime = brutTime;
            int restNum = static_cast<int>(brutTime) / 60; // TIME UNTIL REST
            bool firstRest = true;

            for (int i = 1; i <= restNum; ++i)
            {
                if (firstRest)
                {
                    nettTime += 10;
                    firstRest = false;
                }                
                else
                {
                    nettTime += 5;
                }
            }

            this->set_time_result(nettTime);
        } // END OF calculate_time_result(int _distance)
		
jinx::GV_AllTBoots::GV_AllTBoots(std::string _vehiclePilot)
            : VehicleGround(_vehiclePilot)
        {
            std::string _vehicleName = "Ботинки-вездеходы";
            set_vehicle_name(_vehicleName);
            set_vehicle_speed(SPEED_BOOTS);
        }