// racesim.cpp

/*
�������� ���� ���������, �������� ������� ������� main()
*/

// DEFINITIONS

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define RETURN_SUCCESS 0
#define RETURN_FAILURE 1
#define _UNICODE

#ifdef _WIN32			// windows
#include <windows.h>
#include <string>
#include <cstdlib>
#else					// POSIX
#include <stdlib.h>
#include <string.h>
#endif 

// -----------

#include "gvhumpback.h"
#include "gvhumpbackfast.h"
#include "gvcentaur.h"
#include "gvboots.h"

#include "avcarpet.h"
#include "aveagle.h"
#include "avbroom.h"

// -----------

#include <iostream>
#include "utility.h"
#include <vector>
#include <time.h>

int main(int argc, char ** argv)
{

#ifdef _WIN32					// Windows
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#else							// POSIX
	setlocale(LC_ALL, "Russian");
#endif
	
	// ���������� --------------------------------------------

	std::string userName;					// ��� ������
	bool flagExit = false;					// ���� ������
	short playerMenuInput = -1;				// ���� ������ � ���� ����	
	short raceType = -1;					// ��� ��������� �����
	bool repeatKey = false;					// ���� ��������� ����

	// -------------------------------------------------------

	// SETUP

	jinx::clear_screen();

	std::cout << "------------------------------------------------------------------------\n";
	std::cout << "\t\t\t>>> ���� ��������� �����! <<<\n";	
	std::cout << "------------------------------------------------------------------------\n\n";

	std::cout << " ������� ��� ������\n> ";

	getline(std::cin, userName);

	// ------------------------------------------------------
	// ------- MAIN GAMEPLAY LOOP ---------------------------

	do // while (!flagExit);
	{
		jinx::clear_screen();
		playerMenuInput = -1;		// drop to default
		raceType = -1;				// drop to default

		// ������ ����
		jinx::print_menu_header(userName);

		// �������� �������� ����
		jinx::draw_menu_selector(repeatKey, &playerMenuInput, userName);		

		switch (playerMenuInput)
		{
		case 0:
		{
			flagExit = true;
			break;
		}
		case 1:
		{
			// - GAME ENTREE -
			jinx::start_game(userName);

			if (!repeatKey) repeatKey = true;
			break;
		}
		default:
		{
			std::cout << " ����� �� ���������... ���������� �����\n";
			std::cin.get();
			break;
		}
		}
		// END OF ���� ������ � ����

		std::cout << std::endl << std::endl;

	} while (!flagExit);

	// ------ END GAME PLAY LOOP ----------------------------

	std::cin.clear();
	std::cout << "\n\t\t-- ���� �������� --\n";

	// clear and exit

	// ------------------

	std::cout << std::endl;

#ifdef _WIN32			// windows
	system("pause");
#else					// POSIX
	std::cout << " ������� ����� ������ ��� ����������...\n";
	std::cin.get();
#endif 
	
	return EXIT_SUCCESS;
}