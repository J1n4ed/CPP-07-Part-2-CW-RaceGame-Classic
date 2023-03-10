#pragma once

#include <iostream>

namespace jinx
{

	class WrongVehicleClassException : public std::exception
	{
	public:
		const char* what() const override
		{
			return "�������� �������� ������ ��!\n";
		}
	};

	class ErrorReadingFileForInput : public std::exception
	{
	public:
		const char* what() const override
		{
			return "��������� ��������� ����!\n";
		}
	};

} // END OF jinx namespace