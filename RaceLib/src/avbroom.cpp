#include "avbroom.h"

void jinx::AV_Broom::calculate_time_result(int _distance)
{
            // Скорость:                    20
            // Коэффициент сокращения расстояния
            //                              Увеличивается на 1% за каждую 1000 у.е. расстояния
            //                              Например, для расстояния 5600 коэффициент будет 5%
            
            // VARIABLES

            double bruttDistance = static_cast<double>(_distance);
            double nettDistance = 0;
            double nettTime = 0;
            int distanceCutRatio = 0;
            int counter = 0;

            // РЕАЛИЗАЦИЯ

            counter = _distance / 1000;

            for (int i = 0; i < counter; ++i)
            {
                distanceCutRatio += 0.01;
            }

            nettDistance = bruttDistance - (bruttDistance * distanceCutRatio);
            nettTime = nettDistance / this->get_vehicle_speed();

            // RETURN

            this->set_time_result(nettTime);
        }
		
jinx::AV_Broom::AV_Broom(std::string _vehiclePilot)
            : VehicleAir(_vehiclePilot)
        {
            std::string _vehicleName = "Метла\t";
            set_vehicle_name(_vehicleName);
            set_vehicle_speed(SPEED_BROOM);
        }