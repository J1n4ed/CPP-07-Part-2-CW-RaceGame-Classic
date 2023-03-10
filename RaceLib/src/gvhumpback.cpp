#include "gvhumpback.h"

void jinx::GV_Humpback::calculate_time_result(int _distance)
{
// ��������:                    10
// ����� �������� �� ������:    30
// ������������ ������: 
//                              ������ ���: 5
//                              ��� ����������� ����: 8

// VARIABLES

    double brutTime = _distance / this->get_vehicle_speed();
    double nettTime = brutTime;
    int restNum = static_cast<int>(brutTime) / 30;
    bool firstRest = true;

            for (int i = 1; i <= restNum; ++i)
            {
                if (firstRest)
                {
                    nettTime += 5;
                    firstRest = false;
                }
                else
                {
                    nettTime += 8;
                }
            }

            this->set_time_result(nettTime);
}

jinx::GV_Humpback::GV_Humpback(std::string _vehiclePilot) : VehicleGround(_vehiclePilot)
{
    std::string _vehicleName = "�������\t";
    set_vehicle_name(_vehicleName);
    set_vehicle_speed(SPEED_HUMPBACK);
}