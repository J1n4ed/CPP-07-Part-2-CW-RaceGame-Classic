#include "avcarpet.h"

void jinx::AV_Magic_Carpet::calculate_time_result(int _distance)
        {
            // Скорость:                    10
            // Коэффициент сокращения расстояния
            //                              Если расстояние меньше 1000 — без сокращения
            //                              Если расстояние меньше 5000 — 3%
            //                              Если расстояние меньше 10000 — 10%
            //                              Если расстояние больше или равно 10000 — 5%

            // VARIABLES

            double bruttDistance = static_cast<double>(_distance);
            double nettDistance = 0;
            double nettTime = 0;
            int distanceCutRatio = 0;            

            // РЕАЛИЗАЦИЯ

            if (bruttDistance < 1000)
            {
                distanceCutRatio = 0;
            }
            else if ((bruttDistance >= 1000) && (bruttDistance < 5000))
            {
                distanceCutRatio = 0.03;
            }
            else if ((bruttDistance >= 5000) && (bruttDistance < 10000))
            {
                distanceCutRatio = 0.10;
            }
            else
            {
                distanceCutRatio = 0.05;
            }

            nettDistance = bruttDistance - (bruttDistance * distanceCutRatio);
            nettTime = nettDistance / this->get_vehicle_speed();

            // RETURN

            this->set_time_result(nettTime);
        }
		
jinx::AV_Magic_Carpet::AV_Magic_Carpet(std::string _vehiclePilot)
            : VehicleAir(_vehiclePilot)
        {
            std::string _vehicleName = "Ковёр-самолёт";
            set_vehicle_name(_vehicleName);
            set_vehicle_speed(SPEED_CARPET);
        }