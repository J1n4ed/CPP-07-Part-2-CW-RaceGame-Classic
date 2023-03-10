// utility.cpp

// INCLUDES

#include "utility.h"
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>

#ifdef _WIN32       // Windows
#include <cstdlib>
#include <string>
#else               // POSIX
#include <stdlib.h>
#include <string.h>
#endif

#include "gvhumpback.h"
#include "gvhumpbackfast.h"
#include "gvcentaur.h"
#include "gvboots.h"

#include "avcarpet.h"
#include "aveagle.h"
#include "avbroom.h"

/*
������� ������ �������
*/
void jinx::clear_screen()
{
#ifdef _WIN32
    std::system("cls");
#else
    // Assume POSIX
    std::system("clear");
#endif
} // END OF clear_screen()

/*
����� ������ ����
*/
void jinx::print_menu_header(std::string userName)
{
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "\t\t\t>>> ���� ��������� �����! <<<\n";
    std::cout << "\t\t\t�����: " << userName << "\n";
    std::cout << "------------------------------------------------------------------------\n\n";
}

/*
��������� ����
*/
void jinx::draw_menu_selector(bool repeatKey, short * playerMenuInput, std::string userName)
{
	if (!repeatKey)
	{
		std::cout << " ���� (�������� ��������):	\n" <<
					" 1. ������ ����\n" <<
					" 0. �����\n";
	}
	else
	{
		std::cout << " ���� (�������� ��������):	\n" <<
			" 1. ��������� ����?\n" <<
			" 0. �����\n";
	}
	// ���� ������ � ����

	do // while (playerMenuInput == -1);
	{
		std::cout << "\n" << userName << "> ";
		std::cin >> *playerMenuInput;

	} while (*playerMenuInput == -1);
}

// -----------------------------------------------------------------------------------
/* ��� ������� ---------------------------------------------------------------------- */

//

// ��������� ��������� �����
int jinx::get_race_distance(std::string userName)
{
	std::cout << " ������� ��������� ����� (min 99, max 999999): \n";

	int raceDistance = 0;

	do
	{
		std::cout << userName << "> ";
		std::cin >> raceDistance;
	} while ((raceDistance < 99) || (raceDistance > 999999));

	return raceDistance;
}

// ��������� ���������� �����
int jinx::get_competitors_count(std::string userName)
{
	jinx::clear_screen();

	std::cout << " ������� ���������� ������ ���������� (min 3, max 100): \n";

	int botNumber = 0;

	do
	{
		std::cout << userName << "> ";
		std::cin >> botNumber;
	} while ((botNumber < 3) || (botNumber > 100));

	return botNumber;
}

// ��������

/*
����������� ������ � ������� ������� ����������
*/
void jinx::print_race_roster(std::vector<jinx::Vehicle*> raceRoster)
{	
	int size = static_cast<int>(raceRoster.size());
	
	for (int i = 0; i < size; ++i)
	{
		std::cout << " �����: " << raceRoster[i]->get_pilot_name() << "\t��: " << raceRoster[i]->get_vehicle_name() << "\t��������: " << raceRoster[i]->get_vehicle_speed();
		std::cout << '\n';
	} // END OF for (int i = 0; i < size; ++i)
} // END OF print_race_roster(std::vector<jinx::Vehicle*>* raceRoster)

/*
����������� ������ � ������� ���������� � �������� ������
*/
void jinx::print_race_results(std::vector<jinx::Vehicle*> raceRoster)
{
	int size = static_cast<int>(raceRoster.size());
	
	for (int i = 0; i < size; ++i)
	{
		std::cout << " �������: " << i + 1 << "\t�����: " << raceRoster[i]->get_pilot_name() << "\t��: " << raceRoster[i]->get_vehicle_name() << "\t ��������� ������: " << raceRoster[i]->get_race_result();
		std::cout << '\n';
	} // END OF for (int i = 0; i < size; ++i)
} // END OF print_race_results(std::vector<jinx::Vehicle*> * raceRoster)

// ���������� ������� ����������

/*
���������� ����������� �����
*/
void jinx::sort_result_roster(std::vector<jinx::Vehicle*> & raceRoster)
{
	// VARIABLES -----------------
	bool madeChange = false;
	int vectorSize = raceRoster.size();
	// ---------------------------	

	do {
		madeChange = false;

		for (int i = 0; i < vectorSize - 1; ++i) 
		{
			if (raceRoster[i + 1]->get_race_result() < raceRoster[i]->get_race_result())
			{
				jinx::Vehicle * temp;

				temp = raceRoster[i + 1];

				raceRoster[i + 1] = raceRoster[i];
				raceRoster[i] = temp;
				madeChange = true;
			}
			
		}
	} while (madeChange);		

} // END OF jinx::sort_result_roster(std::vector<jinx::Vehicle*> raceRoster)

// ��������� ����� --------

bool jinx::get_bot_names(std::vector<std::string>* nameVector)
{
	std::ifstream file_botnames;

	file_botnames.open("botnames.txt", std::ios::in);

	if (file_botnames.is_open())
	{
		std::string reader;

		while (!file_botnames.eof())
		{
			getline(file_botnames, reader, '\n');
			nameVector->push_back(reader);
			reader.clear();
		}

		return EXIT_SUCCESS;
	}
	else
	{		
		return EXIT_FAILURE;
	}
}

bool jinx::get_bot_callsigns(std::vector<std::string>* nameVector)
{
	std::ifstream file_botcallsigns;

	file_botcallsigns.open("botcallsigns.txt", std::ios::in);

	if (file_botcallsigns.is_open())
	{
		std::string reader;

		while (!file_botcallsigns.eof())
		{
			getline(file_botcallsigns, reader);
			nameVector->push_back(reader);
			reader.clear();
		}

		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
}

void jinx::get_bots(std::vector<std::string>* list, int botCount)
{
	std::vector<std::string> botNames;
	std::vector<std::string> botCallsigns;

	jinx::get_bot_names(&botNames);
	jinx::get_bot_callsigns(&botCallsigns);

	int namePoolSize = 0;
	int callsignPoolSize = 0;
	int nameIndexRng = 0;
	int callsignIndexRng = 0;

	namePoolSize = static_cast<int>(botNames.size());
	callsignPoolSize = static_cast<int>(botCallsigns.size());

	// RNG GENERATION

	// Random seed
	std::random_device rd;

	// Initialize Mersenne Twister pseudo-random number generator
	std::mt19937 gen(rd());

	// Generate pseudo-random numbers
	// uniformly distributed in range (1, 100)
	// std::uniform_int_distribution<> dis(1, 100);
	// int ... = dis(gen);

	// --------------


	for (int i = 1; i <= botCount; ++i)
	{
		std::uniform_int_distribution<> dis1(1, namePoolSize - 1);
		nameIndexRng = dis1(gen);
		std::uniform_int_distribution<> dis2(1, callsignPoolSize - 1);
		callsignIndexRng = dis2(gen);

		std::string rngNameGen = botNames[nameIndexRng] + " " + botCallsigns[callsignIndexRng];

		list->push_back(rngNameGen);
	}

}

// ROSTER PRINTER

// ����� ���������� � ������ � �����������
void jinx::print_roster(bool raceResults, int raceType, int raceDistance, int participantsCount, std::vector<jinx::Vehicle*>& raceList)
{
	std::cout << " - ��������� ����� \n\n";
	std::cout << " - ��� �����: ";

	if (raceType == 1)
	{
		std::cout << "�������� �����\n";
	}
	else if (raceType == 2)
	{
		std::cout << "��������� �����\n";
	}
	else if (raceType == 3)
	{
		std::cout << "��������� �����\n";
	}
	else
	{
		std::cerr << "�������� �������� ���� �����!";
	}

	std::cout << " - ��������� �����: " << raceDistance << '\n';
	std::cout << " - ���������� ����������: " << raceList.size() << '\n';

	if (raceResults)
	{
		std::cout << " - ���������� ���������� ������: \n\n";

		if (raceList.size() != 0)
		{
			jinx::print_race_results(raceList);
		}
		else
		{
			std::cout << "-- ����� --";
		}
	}
	else
	{
		std::cout << " - ������ ���������� ������: \n\n";

		if (raceList.size() != 0)
		{			
			jinx::print_race_roster(raceList);
		}
		else
		{
			std::cout << "-- ����� --";
		}
	}	

	// ���������� � �����

#ifdef _WIN32			// windows
	system("pause");
#else					// POSIX
	std::cout << " ������� ����� ������ ��� �����������...\n";
	std::cin.get();
#endif 
}

// -------------------------------------------------------
// �������� �����

void jinx::run_ground_race(std::string userName)
{
	// VARIABLES

	short localPlayerInput = -1;
	jinx::Vehicle * vehicle_ptr;
	std::vector<std::string> botList;
	int botNumber = 0;
	int seed = 0;
	std::vector<jinx::Vehicle*> raceList;	// ������ ���������� �����
	int raceDistance = 0;
	bool raceResults = false;				// ������������� ������
	const int raceType = 1;					// 1 - ��� �������� �����

	std::vector < jinx::GV_Humpback> bot_humpback_list;
	std::vector < jinx::GV_Humpback_Fast> bot_humpback_fast_list;
	std::vector < jinx::GV_Centaur> bot_centaur_list;
	std::vector < jinx::GV_AllTBoots> bot_boots_list;

	jinx::GV_Humpback temp_vehicle_1(userName);
	jinx::GV_Humpback_Fast temp_vehicle_2(userName);
	jinx::GV_Centaur temp_vehicle_3(userName);
	jinx::GV_AllTBoots temp_vehicle_4(userName);

	// -----------------------------

	// RNG GENERATION

	// Random seed
	std::random_device rd;

	// Initialize Mersenne Twister pseudo-random number generator
	std::mt19937 gen(rd());

	// Generate pseudo-random numbers
	// uniformly distributed in range (1, 100)
	// std::uniform_int_distribution<> dis(1, 100);
	// int ... = dis(gen);

	// --------------

	// -----------------------------

	jinx::clear_screen();

	jinx::print_menu_header(userName);
	
	std::cout << " �������� �� ��� ������: \n"
		<< " 1. �������\n"
		<< " 2. �������-���������\n"
		<< " 3. �������\n"
		<< " 4. �������-���������\n";

	do // while ((localPlayerInput <= 0) || (localPlayerInput > 4) );
	{
		std::cout << "\n" << userName << "> ";
		std::cin >> localPlayerInput;

	} while ((localPlayerInput <= 0) || (localPlayerInput > 4) );

	switch (localPlayerInput)
	{
	case 1:
	{
		vehicle_ptr = &temp_vehicle_1;
		break;
	} // end case 1
	case 2:
	{
		vehicle_ptr = &temp_vehicle_2;
		break;
	} // end case 2
	case 3:
	{
		vehicle_ptr = &temp_vehicle_3;
		break;
	} // end case 3
	case 4:
	{
		vehicle_ptr = &temp_vehicle_4;
		break;
	} // end case 4	
	default:
	{
		break;
	} // end default
	} // end switch (localPlayerInput)

	raceList.push_back(vehicle_ptr);
	vehicle_ptr = nullptr;

	botNumber = get_competitors_count(userName);

	jinx::get_bots(&botList, botNumber);

	for (int i = 0; i < botNumber; ++i)
	{
		std::uniform_int_distribution<> dis(1, 4);
		seed = dis(gen);		
		
		switch (seed)
		{
		case 1:
		{	
			jinx::GV_Humpback bot_temp_vehicle_1(botList[i]);
			bot_humpback_list.push_back(bot_temp_vehicle_1);
			break;
		} // end case 1
		case 2:
		{
			jinx::GV_Humpback_Fast bot_temp_vehicle_2(botList[i]);
			bot_humpback_fast_list.push_back(bot_temp_vehicle_2);
			break;
		} // end case 2
		case 3:
		{
			jinx::GV_Centaur bot_temp_vehicle_3(botList[i]);
			bot_centaur_list.push_back(bot_temp_vehicle_3);
			break;
		} // end case 3
		case 4:
		{
			jinx::GV_AllTBoots bot_temp_vehicle_4(botList[i]);
			bot_boots_list.push_back(bot_temp_vehicle_4);
			break;
		} // end case 4	
		default:
		{

			// DEBUG -------------------------
			// std::cout << "\nEntered default switch\n";
			// END DEBUG ---------------------

			break;
		} // end default
		} // end switch (seed)		

	} // END for (int i = 0; i < playerNumber; ++i)

	if (bot_humpback_list.size() > 0)
	{
		for (int i = 0; i < bot_humpback_list.size(); ++i)
		{
			vehicle_ptr = &bot_humpback_list[i];
			raceList.push_back(vehicle_ptr);
		}
	}

	if (bot_humpback_fast_list.size() > 0)
	{
		for (int i = 0; i < bot_humpback_fast_list.size(); ++i)
		{
			vehicle_ptr = &bot_humpback_fast_list[i];
			raceList.push_back(vehicle_ptr);
		}
	}

	if (bot_centaur_list.size() > 0)
	{
		for (int i = 0; i < bot_centaur_list.size(); ++i)
		{
			vehicle_ptr = &bot_centaur_list[i];
			raceList.push_back(vehicle_ptr);
		}
	}

	if (bot_boots_list.size() > 0)
	{
		for (int i = 0; i < bot_boots_list.size(); ++i)
		{
			vehicle_ptr = &bot_boots_list[i];
			raceList.push_back(vehicle_ptr);
		}
	}

	// RESET SCREEN -----------------

	jinx::clear_screen();
	jinx::print_menu_header(userName);

	// -------------------------------

	std::cout << "\n ������ ����������:\n\n";

	if (raceList.size() != 0)
	{
		jinx::print_race_roster(raceList);
	}
	else
	{
		std::cout << " -- ����� --";
	}

#ifdef _WIN32			// windows
	system("pause");
#else					// POSIX
	std::cout << " ������� ����� ������ ��� �����������...\n";
	std::cin.get();
#endif 

	// RESET SCREEN -----------------

	jinx::clear_screen();
	jinx::print_menu_header(userName);

	// -------------------------------

	// ������� ������������ ����� -------------------------------

	raceDistance = jinx::get_race_distance(userName);

	// RESET SCREEN -----------------

	jinx::clear_screen();
	jinx::print_menu_header(userName);

	// -------------------------------

	jinx::print_roster(raceResults, raceType, raceDistance, static_cast<int>(raceList.size()), raceList);

	// ��������� ����������� �����

	for (int i = 0; i < raceList.size(); ++i)
	{
		raceList[i]->calculate_time_result(raceDistance);
	}	

	raceResults = true;

	// ���������� ����������� �����

	jinx::sort_result_roster(raceList);

	// ����� ����������� �����

	// RESET SCREEN -----------------

	jinx::clear_screen();
	jinx::print_menu_header(userName);

	// -------------------------------

	jinx::print_roster(raceResults, raceType, raceDistance, static_cast<int>(raceList.size()), raceList);
}


// -------------------------------------------------------
// ��������� �����

void jinx::run_air_race(std::string userName)
{
	// VARIABLES

	short localPlayerInput = -1;
	jinx::Vehicle* vehicle_ptr;
	std::vector<std::string> botList;
	int botNumber = 0;
	int seed = 0;
	std::vector<jinx::Vehicle*> raceList;	// ������ ���������� �����
	int raceDistance = 0;
	bool raceResults = false;				// ������������� ������
	const int raceType = 2;					// 2 - ��� ��������� �����

	std::vector < jinx::AV_Magic_Carpet> bot_carpet_list;
	std::vector < jinx::AV_Eagle> bot_eagle_list;
	std::vector < jinx::AV_Broom> bot_broom_list;

	jinx::AV_Magic_Carpet temp_vehicle_1(userName);
	jinx::AV_Eagle temp_vehicle_2(userName);
	jinx::AV_Broom temp_vehicle_3(userName);

	// -----------------------------

	// RNG GENERATION

	// Random seed
	std::random_device rd;

	// Initialize Mersenne Twister pseudo-random number generator
	std::mt19937 gen(rd());

	// Generate pseudo-random numbers
	// uniformly distributed in range (1, 100)
	// std::uniform_int_distribution<> dis(1, 100);
	// int ... = dis(gen);

	// --------------

	// -----------------------------

	jinx::clear_screen();

	jinx::print_menu_header(userName);

	std::cout << " �������� �� ��� ������: \n"
		<< " 1. ����-������\n"
		<< " 2. ���\n"
		<< " 3. �����\n";

	do // while (localPlayerInput == -1);
	{
		std::cout << "\n" << userName << "> ";
		std::cin >> localPlayerInput;

	} while (localPlayerInput == -1);

	switch (localPlayerInput)
	{
	case 1:
	{
		vehicle_ptr = &temp_vehicle_1;
		break;
	} // end case 1
	case 2:
	{
		vehicle_ptr = &temp_vehicle_2;
		break;
	} // end case 2
	case 3:
	{
		vehicle_ptr = &temp_vehicle_3;
		break;
	} // end case 3
	default:
	{
		break;
	} // end default
	} // end switch (localPlayerInput)

	raceList.push_back(vehicle_ptr);
	vehicle_ptr = nullptr;

	botNumber = get_competitors_count(userName);

	jinx::get_bots(&botList, botNumber);

	for (int i = 0; i < botNumber; ++i)
	{
		std::uniform_int_distribution<> dis(1, 4);
		seed = dis(gen);

		switch (seed)
		{
		case 1:
		{
			jinx::AV_Magic_Carpet bot_temp_vehicle_1(botList[i]);
			bot_carpet_list.push_back(bot_temp_vehicle_1);
			break;
		} // end case 1
		case 2:
		{
			jinx::AV_Eagle bot_temp_vehicle_2(botList[i]);
			bot_eagle_list.push_back(bot_temp_vehicle_2);
			break;
		} // end case 2
		case 3:
		{
			jinx::AV_Broom bot_temp_vehicle_3(botList[i]);
			bot_broom_list.push_back(bot_temp_vehicle_3);
			break;
		} // end case 3		
		default:
		{

			// DEBUG -------------------------
			// std::cout << "\nEntered default switch\n";
			// END DEBUG ---------------------

			break;
		} // end default
		} // end switch (seed)		

	} // END for (int i = 0; i < playerNumber; ++i)

	if (bot_carpet_list.size() > 0)
	{
		for (int i = 0; i < bot_carpet_list.size(); ++i)
		{
			vehicle_ptr = &bot_carpet_list[i];
			raceList.push_back(vehicle_ptr);
		}
	}

	if (bot_eagle_list.size() > 0)
	{
		for (int i = 0; i < bot_eagle_list.size(); ++i)
		{
			vehicle_ptr = &bot_eagle_list[i];
			raceList.push_back(vehicle_ptr);
		}
	}

	if (bot_broom_list.size() > 0)
	{
		for (int i = 0; i < bot_broom_list.size(); ++i)
		{
			vehicle_ptr = &bot_broom_list[i];
			raceList.push_back(vehicle_ptr);
		}
	}	

	// RESET SCREEN -----------------

	jinx::clear_screen();
	jinx::print_menu_header(userName);

	// -------------------------------

	std::cout << "\n ������ ����������:\n\n";

	if (raceList.size() != 0)
	{
		jinx::print_race_roster(raceList);
	}
	else
	{
		std::cout << "-- ����� --";
	}

#ifdef _WIN32			// windows
	system("pause");
#else					// POSIX
	std::cout << " ������� ����� ������ ��� �����������...\n";
	std::cin.get();
#endif 

	// RESET SCREEN -----------------

	jinx::clear_screen();
	jinx::print_menu_header(userName);

	// -------------------------------

	// ������� ������������ ����� -------------------------------

	raceDistance = jinx::get_race_distance(userName);

	// RESET SCREEN -----------------

	jinx::clear_screen();
	jinx::print_menu_header(userName);

	// -------------------------------

	jinx::print_roster(raceResults, raceType, raceDistance, static_cast<int>(raceList.size()), raceList);

	// ��������� ����������� �����

	for (int i = 0; i < raceList.size(); ++i)
	{
		raceList[i]->calculate_time_result(raceDistance);
	}

	raceResults = true;

	// ���������� ����������� �����

	// std::sort(raceList.begin(), raceList.end());

	jinx::sort_result_roster(raceList);

	// ����� ����������� �����

	// RESET SCREEN -----------------

	jinx::clear_screen();
	jinx::print_menu_header(userName);

	// -------------------------------

	jinx::print_roster(raceResults, raceType, raceDistance, static_cast<int>(raceList.size()), raceList);
}


// -------------------------------------------------------
// ��������� �����


void jinx::run_mixed_race(std::string userName)
{
	// VARIABLES

	short localPlayerInput = -1;
	jinx::Vehicle* vehicle_ptr;
	std::vector<std::string> botList;
	int botNumber = 0;
	int seed = 0;
	std::vector<jinx::Vehicle*> raceList;	// ������ ���������� �����
	int raceDistance = 0;
	bool raceResults = false;				// ������������� ������
	const int raceType = 3;					// 3 - ��� ��������� �����

	std::vector < jinx::GV_Humpback> bot_humpback_list;
	std::vector < jinx::GV_Humpback_Fast> bot_humpback_fast_list;
	std::vector < jinx::GV_Centaur> bot_centaur_list;
	std::vector < jinx::GV_AllTBoots> bot_boots_list;

	std::vector < jinx::AV_Magic_Carpet> bot_carpet_list;
	std::vector < jinx::AV_Eagle> bot_eagle_list;
	std::vector < jinx::AV_Broom> bot_broom_list;

	jinx::GV_Humpback temp_vehicle_1(userName);
	jinx::GV_Humpback_Fast temp_vehicle_2(userName);
	jinx::GV_Centaur temp_vehicle_3(userName);
	jinx::GV_AllTBoots temp_vehicle_4(userName);	

	jinx::AV_Magic_Carpet temp_vehicle_5(userName);
	jinx::AV_Eagle temp_vehicle_6(userName);
	jinx::AV_Broom temp_vehicle_7(userName);

	// -----------------------------

	// RNG GENERATION

	// Random seed
	std::random_device rd;

	// Initialize Mersenne Twister pseudo-random number generator
	std::mt19937 gen(rd());

	// Generate pseudo-random numbers
	// uniformly distributed in range (1, 100)
	// std::uniform_int_distribution<> dis(1, 100);
	// int ... = dis(gen);

	// --------------

	// -----------------------------

	jinx::clear_screen();

	jinx::print_menu_header(userName);

	std::cout << " �������� �� ��� ������: \n"
		<< " 1. �������\n"
		<< " 2. �������-���������\n"
		<< " 3. �������\n"
		<< " 4. �������-���������\n"
		<< " 5. ����-������\n"
		<< " 6. ���\n"
		<< " 7. �����\n";

	do // while (localPlayerInput == -1);
	{
		std::cout << "\n" << userName << "> ";
		std::cin >> localPlayerInput;

	} while (localPlayerInput == -1);

	switch (localPlayerInput)
	{
	case 1:
	{
		vehicle_ptr = &temp_vehicle_1;
		break;
	} // end case 1
	case 2:
	{
		vehicle_ptr = &temp_vehicle_2;
		break;
	} // end case 2
	case 3:
	{
		vehicle_ptr = &temp_vehicle_3;
		break;
	} // end case 3
	case 4:
	{
		vehicle_ptr = &temp_vehicle_4;
		break;
	} // end case 4	
	case 5:
	{
		vehicle_ptr = &temp_vehicle_5;
		break;
	} // end case 4	
	case 6:
	{
		vehicle_ptr = &temp_vehicle_6;
		break;
	} // end case 4	
	case 7:
	{
		vehicle_ptr = &temp_vehicle_7;
		break;
	} // end case 4	
	default:
	{
		break;
	} // end default
	} // end switch (localPlayerInput)

	raceList.push_back(vehicle_ptr);
	vehicle_ptr = nullptr;

	botNumber = get_competitors_count(userName);

	jinx::get_bots(&botList, botNumber);	

	for (int i = 0; i < botNumber; ++i)
	{
		std::uniform_int_distribution<> dis(1, 7);
		seed = dis(gen);		

		switch (seed)
		{
		case 1:
		{
			jinx::GV_Humpback bot_temp_vehicle_1(botList[i]);
			bot_humpback_list.push_back(bot_temp_vehicle_1);
			break;
		} // end case 1
		case 2:
		{
			jinx::GV_Humpback_Fast bot_temp_vehicle_2(botList[i]);
			bot_humpback_fast_list.push_back(bot_temp_vehicle_2);
			break;
		} // end case 2
		case 3:
		{
			jinx::GV_Centaur bot_temp_vehicle_3(botList[i]);
			bot_centaur_list.push_back(bot_temp_vehicle_3);
			break;
		} // end case 3
		case 4:
		{
			jinx::GV_AllTBoots bot_temp_vehicle_4(botList[i]);
			bot_boots_list.push_back(bot_temp_vehicle_4);
			break;
		} // end case 4	
		case 5:
		{
			jinx::AV_Magic_Carpet bot_temp_vehicle_5(botList[i]);
			bot_carpet_list.push_back(bot_temp_vehicle_5);
			break;
		} // end case 4	
		case 6:
		{
			jinx::AV_Eagle bot_temp_vehicle_6(botList[i]);
			bot_eagle_list.push_back(bot_temp_vehicle_6);
			break;
		} // end case 4	
		case 7:
		{
			jinx::AV_Broom bot_temp_vehicle_7(botList[i]);
			bot_broom_list.push_back(bot_temp_vehicle_7);
			break;
		} // end case 4	
		default:
		{

			// DEBUG -------------------------
			// std::cout << "\nEntered default switch\n";
			// END DEBUG ---------------------

			break;
		} // end default
		} // end switch (seed)		

	} // END for (int i = 0; i < playerNumber; ++i)

	if (bot_humpback_list.size() > 0)
	{
		for (int i = 0; i < bot_humpback_list.size(); ++i)
		{
			vehicle_ptr = &bot_humpback_list[i];
			raceList.push_back(vehicle_ptr);
		}
	}

	if (bot_humpback_fast_list.size() > 0)
	{
		for (int i = 0; i < bot_humpback_fast_list.size(); ++i)
		{
			vehicle_ptr = &bot_humpback_fast_list[i];
			raceList.push_back(vehicle_ptr);
		}
	}

	if (bot_centaur_list.size() > 0)
	{
		for (int i = 0; i < bot_centaur_list.size(); ++i)
		{
			vehicle_ptr = &bot_centaur_list[i];
			raceList.push_back(vehicle_ptr);
		}
	}

	if (bot_boots_list.size() > 0)
	{
		for (int i = 0; i < bot_boots_list.size(); ++i)
		{
			vehicle_ptr = &bot_boots_list[i];
			raceList.push_back(vehicle_ptr);
		}
	}

	if (bot_carpet_list.size() > 0)
	{
		for (int i = 0; i < bot_carpet_list.size(); ++i)
		{
			vehicle_ptr = &bot_carpet_list[i];
			raceList.push_back(vehicle_ptr);
		}
	}

	if (bot_eagle_list.size() > 0)
	{
		for (int i = 0; i < bot_eagle_list.size(); ++i)
		{
			vehicle_ptr = &bot_eagle_list[i];
			raceList.push_back(vehicle_ptr);
		}
	}

	if (bot_broom_list.size() > 0)
	{
		for (int i = 0; i < bot_broom_list.size(); ++i)
		{
			vehicle_ptr = &bot_broom_list[i];
			raceList.push_back(vehicle_ptr);
		}
	}

	// RESET SCREEN -----------------

	jinx::clear_screen();
	jinx::print_menu_header(userName);

	// -------------------------------

	std::cout << "\n ������ ����������:\n\n";

	if (raceList.size() != 0)
	{
		jinx::print_race_roster(raceList);
	}
	else
	{
		std::cout << " -- ����� --";
	}

#ifdef _WIN32			// windows
	system("pause");
#else					// POSIX
	std::cout << " ������� ����� ������ ��� �����������...\n";
	std::cin.get();
#endif 

	// RESET SCREEN -----------------

	jinx::clear_screen();
	jinx::print_menu_header(userName);

	// -------------------------------

	// ������� ������������ ����� -------------------------------

	raceDistance = jinx::get_race_distance(userName);

	// RESET SCREEN -----------------

	jinx::clear_screen();
	jinx::print_menu_header(userName);

	// -------------------------------

	jinx::print_roster(raceResults, raceType, raceDistance, static_cast<int>(raceList.size()), raceList);

	// ��������� ����������� �����

	for (int i = 0; i < raceList.size(); ++i)
	{
		raceList[i]->calculate_time_result(raceDistance);
	}

	raceResults = true;

	// ���������� ����������� �����

	jinx::sort_result_roster(raceList);

	// ����� ����������� �����

	// RESET SCREEN -----------------

	jinx::clear_screen();
	jinx::print_menu_header(userName);

	// -------------------------------

	jinx::print_roster(raceResults, raceType, raceDistance, static_cast<int>(raceList.size()), raceList);
}


// -------------------------------------------------------

/*
������ ����
*/
void jinx::start_game(std::string userName)
{
	// VARIABLES

	short localPlayerInput = -1;

	// ------------------------------

	jinx::clear_screen();
	jinx::print_menu_header(userName);

	std::cout << " ���� (�������� ��������), �������� ��� �����:	\n"
		<< " 1. �������� �����\n"
		<< " 2. ��������� �����\n"
		<< " 3. ��������� �����\n";

	do // while (playerMenuInput == -1);
	{
		std::cout << "\n" << userName << "> ";
		std::cin >> localPlayerInput;

	} while (localPlayerInput == -1);

	switch (localPlayerInput)
	{
	case 1:
	{
		// �������� �����
		jinx::run_ground_race(userName);
		break;
	}
	case 2:
	{
		// ��������� �����
		jinx::run_air_race(userName);
		break;
	}
	case 3:
	{
		// ��������� �����
		jinx::run_mixed_race(userName);
		break;
	}
	default:
	{
		std::cout << "����� �� ���������... ���������� �����\n";
		std::cin.get();
		break;
	}
	} // switch (localPlayerInput)
}