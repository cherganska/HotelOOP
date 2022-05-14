#include <iostream>
#include <fstream>
#include <string>

//Years between which the program functions
const int StartYear = 2020;
const int EndYear = 2030;
int MaxRes = 20;


class Date
{
private:
	int day, month, year;
public:
	//Constructor
	Date(int Day = 1, int Month = 1, int Year = StartYear)
	{
				day = Day;
				month = Month;
				year = Year;
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

class Reservation
{
private:
	std::string Guest, Notes;
	Date From, To;

public:
	Reservation()
	{
		Guest = "";
		Notes = "";
	}
	Reservation(std::string Name, Date DateFrom, Date DateTo, std::string Info = "No extra notes")
	{
		Guest = Name;
		Notes = Info;
		if (DateFrom <= DateTo)
		{
			From = DateFrom;
			To = DateTo;
		}
		else
		{
			From = DateTo;
			To = DateFrom;
		}
	}
};


class Room
{
private:
	int number, beds, ResCounter;
	Reservation* Booked;
public:
	Room(int Num, int Bed)
	{
		number = Num;
		beds = Bed;
		Booked = new Reservation[MaxRes];
		ResCounter = 0;
	}

	~Room()
	{
		delete[] Booked;
	}

	void Book(Reservation Save)
	{
		Booked[ResCounter] = Save;
		ResCounter++;
	}


	void print()
	{
	std::cout << number << " " << beds << std::endl;
	}


};



//Checks for valid date
bool DateCorrect(int Day, int Month, int Year)						
{
	if (Year >= StartYear && Year <= EndYear)

		if ((Month > 12 || Month < 1 || Day < 1 || Day > 31 ||
			(Month == 4 || Month == 6 || Month == 9 || Month == 11) && Day > 30) ||					//accounts for 30-day months
			(Month == 2 && Year % 4 != 0 && Day > 28) ||											//accounts for February
			(Year % 4 == 0 && Month == 2 && Day > 29))													//acounts for leap years

		{
			std::cout << "Incorrect date";
			return 0;
		}
		else return 1;
	else
	{
		std::cout << "Date is outside of the schedule's scope";
		return 0;
	}
}


/*
void InputRooms()
{
	int Rooms, Number, Beds;
	std::cout << "Number of rooms: ";
	std::cin >> Rooms;
	
	std::ofstream RoomFile;
	RoomFile.open("Rooms.txt", std::ios::out);

	for (int i = 0; i < Rooms; i++)
	{
		std::cout << "Room number and beds:";
		std::cin >> Number >> Beds;
		Room NewRoom(Number, Beds);
		RoomFile.write((char*)&NewRoom, sizeof(NewRoom));
	}
}
*/






int main()
{
	//InputRooms();

	/*std::ifstream RoomFile;
	RoomFile.open("Rooms.txt", std::ios::in);
	Room TestRoom(0, 0);
	RoomFile.read((char*)&TestRoom, sizeof(TestRoom));
	TestRoom.print();*/



}