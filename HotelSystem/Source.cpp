#include <iostream>
#include <fstream>
#include <string>

//Years between which the program functions
const int StartYear = 2020;
const int EndYear = 2030;


class Date
{
private:
	int day, month, year;
public:
	//Constructor
	Date(int Day = 1, int Month = 1, int Year = StartYear)
	{
		if (Year >= StartYear && Year <= EndYear)
			//Check date validity
			if (((Month > 12 || Month < 1 || Day < 1 || Day > 31 ||
					Month == 4 || Month == 6 || Month == 9 || Month == 11) && Day > 30) ||					//account for 30-day months
					(Month == 2 && Year % 4 != 0 && Day > 28) ||											//account for February
					(Year%4==0 && Month == 2 && Day > 29))													//acount for leap years

					throw("Invalid date");
			else	
				{
					day = Day;
					month = Month;						
					year = Year;
				}
		else throw ("Date is outside of the schedule's scope");
	}

	void operator++ ()
	{
		if (day == 31 ||
			((month == 4 || month == 6 || month == 9 || month == 11) && day == 30) ||
			(month == 2 && year % 4 != 0 && day == 28) ||
			(year % 4 == 0 && month == 2 && day == 29))
		{
			if (month != 12)
			{
				month++;
				day = 1;
			}
			else
			{
				year++;
				month = 1;
				day = 1;
			}
		}
		else day++;
	}

	bool operator>= (Date date2)
	{
		if (year > date2.year) return 1;
		else
			if (year == date2.year && month > date2.month) return 1;
			else
				if (year == date2.year && month == date2.month && day >= date2.day) return 1;
				else return 0;
	}

	bool operator<= (Date date2)
	{
		if (year < date2.year) return 1;
		else
			if (year == date2.year && month < date2.month) return 1;
			else
				if (year == date2.year && month == date2.month && day <= date2.day) return 1;
				else return 0;
	}
};

class Room
{
private:
	int number, beds;
public:
	Room(int Num, int Bed)
	{
		number = Num;
		beds = Bed;
	}
};