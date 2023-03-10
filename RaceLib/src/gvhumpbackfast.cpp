#include "gvhumpbackfast.h"

void jinx::GV_Humpback_Fast::calculate_time_result(int _distance)
        {
            // Скорость:                    40
            // Время движения до отдыха:    10
            // Длительность отдыха: 
            //                              Первый раз: 5
            //                              Второй раз: 6.5
            //                              Все последующие разы: 8

            // VARIABLES

            double brutTime = _distance / this->get_vehicle_speed();
            double nettTime = brutTime;
            int restNum = static_cast<int>(brutTime) / 10; // TIME UNTIL REST
            bool firstRest = true;
            bool secondRest = true;

            for (int i = 1; i <= restNum; ++i)
            {
                if (firstRest)
                {
                    nettTime += 5;
                    firstRest = false;
                }
                else if (secondRest)
                {
                    nettTime += 6.5;
                    secondRest = false;
                }
                else
                {
                    nettTime += 8;
                }
            }

            this->set_time_result(nettTime);
        } // END OF calculate_time_result(int _distance)
		
jinx::GV_Humpback_Fast::GV_Humpback_Fast(std::string _vehiclePilot)
            : VehicleGround(_vehiclePilot)
        {
            std::string _vehicleName = "Верблюд-быстроход";
            set_vehicle_name(_vehicleName);
            set_vehicle_speed(SPEED_HUMPBACKFAST);
        }