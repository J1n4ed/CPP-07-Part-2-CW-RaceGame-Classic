#include "aveagle.h"

void jinx::AV_Eagle::calculate_time_result(int _distance)
        {
            // Скорость:                    8
            // Коэффициент сокращения расстояния
            //                              Всегда 6%
            
            // VARIABLES

            double bruttDistance = static_cast<double>(_distance);
            double nettDistance = 0;
            double nettTime = 0;
            int distanceCutRatio = 0;

            // РЕАЛИЗАЦИЯ

            distanceCutRatio = 0.06;

            nettDistance = bruttDistance - (bruttDistance * distanceCutRatio);
            nettTime = nettDistance / this->get_vehicle_speed();

            // RETURN

            this->set_time_result(nettTime);
        }
		
jinx::AV_Eagle::AV_Eagle(std::string _vehiclePilot)
            : VehicleAir(_vehiclePilot)
        {
            std::string _vehicleName = "Орёл\t";
            set_vehicle_name(_vehicleName);
            set_vehicle_speed(SPEED_EAGLE);
        }