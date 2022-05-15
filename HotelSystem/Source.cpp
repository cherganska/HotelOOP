#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//Years between which the program functions
const int StartYear = 2020;
const int EndYear = 2030;

const int MaxRes = 20;
const int NumberOfRooms = 15;


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

//Checks for valid date
bool DateCorrect(int Day, int Month, int Year)
{
	if (Year >= StartYear && Year <= EndYear)
	{
		if ((Month > 12 || Month < 1 || Day < 1 || Day > 31 ||
			(Month == 4 || Month == 6 || Month == 9 || Month == 11) && Day > 30) ||					//accounts for 30-day months
			(Month == 2 && Year % 4 != 0 && Day > 28) ||											//accounts for February
			(Year % 4 == 0 && Month == 2 && Day > 29))												//acounts for leap years

		{
			cout << "Incorrect date\n";
			return 0;
		}
		else return 1;
	}
	else
	{
		cout << "Date is outside of the schedule's scope\n";
		return 0;
	}
}

class Reservation
{
private:
	string Guest, Notes;
	Date From, To;
public:

	Reservation()
	{
		Guest = "";
		Notes = "";
	}
	Reservation(string Name, Date DateFrom, Date DateTo, string Info = "")
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

	Date getFrom()
	{
		return From;
	}
	Date getTo()
	{
		return To;
	}


	void setFrom(Date date)
	{
		From = date;
	}
	void setTo(Date date)
	{
		To=date;
	}


	void operator= (Reservation Second)
	{
		Guest = Second.Guest;
		Notes = Second.Notes;
		From = Second.From;
		To = Second.To;
	}
};


class Room
{
private:
	int number, beds, ResCounter;
	Reservation* Booked;
public:
	Room(int Num = 0, int Bed = 0)
	{
		number = Num;
		beds = Bed;
		Booked = new Reservation[MaxRes];
		ResCounter = 0;
	}

	/*~Room()
	{
		delete[] Booked;
	}*/

	void Book(Reservation Save)
	{
		Booked[ResCounter] = Save;
		ResCounter++;
	}

	void Free(Date Clear)
	{
		for (int i = 0; i < ResCounter; i++)
		{
			if (Booked->getFrom() <= Clear && Booked->getTo() >= Clear)
			{
				Booked->setTo(Clear);
			}
		}
	}
	/*void print()
	{
		cout << number << " " << beds << "" << ResCounter << endl;
	}*/

	friend void BookRoom(Room Rooms[NumberOfRooms]);
	friend void FindVacant(Room Rooms[NumberOfRooms]);
	friend bool FindRoom(int num, Room Rooms[NumberOfRooms], int& i);
};

bool FindRoom(int num, Room Rooms[NumberOfRooms], int& i)
{
	for (i = 0; i < NumberOfRooms; i++)
	{
		if (Rooms[i].number == num)
		{
			return 1;
		}
	}
	return 0;
}

void BookRoom(Room Rooms[NumberOfRooms])
{
	int num;
	cout << "Which room would you like to book?" << endl;
	cin >> num;

	bool found = 0, free = 1;
	int i;
	
	if (FindRoom(num, Rooms, i))
	{
		int day, month, year;
		do
		{
			cout << "Insert first day of reservation (DD MM YYYY): ";
			cin >> day >> month >> year;
		} while (DateCorrect(day, month, year) == 0);
		Date from(day, month, year);
		do
		{
			cout << "Insert last day of reservation (DD MM YYYY): ";
			cin >> day >> month >> year;
		} while (DateCorrect(day, month, year) == 0);
		Date to(day, month, year);

		if (to <= from)
		{
			Date Placeholder;
			Placeholder = to;
			to = from;
			from = Placeholder;
		}


		for (int j = 0; j < Rooms[i].ResCounter; j++)
		{
			if ((to >= Rooms[i].Booked[j].getFrom() && to <= Rooms[i].Booked[j].getTo()) ||
				(from >= Rooms[i].Booked[j].getFrom() && from <= Rooms[i].Booked[j].getTo()) ||
				(Rooms[i].Booked[j].getFrom() >= from && Rooms[i].Booked[j].getTo() <= to))
			{
				free = 0;
				break;
			}
		}
		if (free)
		{
			cout << endl;
			cout << "Guest Name: ";
			string Name, Notes = "";
			getline(cin >> ws, Name, '\n');
			cout << "Are there any notes to the reservation?" << endl;;
			char answer;
			do
			{
				cout << "Type y / n: ";
				cin >> answer;
			} while (answer != 'y' && answer != 'n');
			if (answer == 'y')
			{
				cout << "Notes: ";
				getline(cin >> ws, Notes, '\n');
			}
			Reservation New(Name, from, to, Notes);

			Rooms[i].Book(New);
		}
	}
	else cout << "A room with that number doesn't exist" << endl;;
}

void FindVacant(Room Rooms[NumberOfRooms])
{
	int day, month, year;
	cout << "Insert Date (DD MM YYYY): ";
	cin >> day >> month >> year;
	if (DateCorrect(day, month, year))
	{
		cout << "Free rooms:" << endl;
		Date Chosen(day, month, year);
		for (int i = 0; i < NumberOfRooms; i++)
		{
			bool busy = 0;
			for (int j = 0; j < Rooms[i].ResCounter; j++)
			{
				if (Chosen >= Rooms[i].Booked[j].getFrom() && Chosen <= Rooms[i].Booked[j].getTo())
				{
					busy = 1;
					break;
				}
			}
			if (!busy) cout << Rooms[i].number << endl;;
		}
	}
}



/*
void InputRooms()
{
	int Rooms, Number, Beds;
	cout << "Number of rooms: ";
	cin >> Rooms;

	ofstream RoomFile;
	RoomFile.open("Rooms.txt", ios::out);
	for (int i = 0; i < Rooms; i++)
	{
		cout << "Room number and beds:";
		cin >> Number >> Beds;
		Room NewRoom(Number, Beds);
		RoomFile.write((char*)&NewRoom, sizeof(NewRoom));
	}
}
*/


//Menu
int Selection()
{
	cout << "Which action would you like to take?" << endl;
	cout << endl;
	cout << "1) Make a reservation" << endl;
	cout << "2) Find vacant rooms by date" << endl;
	cout << "3) Mark room as free" << endl;
	cout << "4) Check number of days rooms were used" << endl;
	cout << "5) Find a room" << endl;
	cout << "6) Mark room as unavailable" << endl;
	cout << "7) Exit" << endl;
	cout << endl;

	int Input;
	do
	{
		cout << "Please choose a command between 1-7" << endl;
		cin >> Input;
	} while (Input < 1 || Input > 7);
	return Input;
}


int main()
{
	//InputRooms();

	fstream RoomFile;
	RoomFile.open("Rooms.txt", ios::in);

	Room Rooms[NumberOfRooms];

	for (int i = 0; i < NumberOfRooms; i++)
	{
		RoomFile.read((char*)&Rooms[i], sizeof(Rooms[i]));
		//Rooms[i].print();
	}

	int operation;
	do
	{
		operation = Selection();
		switch (operation)
		{
		case 1:
		{
			BookRoom(Rooms);
			break;
		}
		case 2:
		{
			FindVacant(Rooms);
			break;
		}
		case 3:
		{
			int num, i;
			cout << "Which room would you like to free?";
			cin >> num;

			if (FindRoom(num, Rooms, i))
			{
				int day, month, year;
				do
				{
					cout << "Enter date (DD MM YYYY): ";
					cin >> day >> month >> year;
				} while (DateCorrect(day, month, year) == 0);
				Rooms[i].Free(Date(day, month, year));
			}
			else "A room with that number doesn't exist";
			break;
		}
		case 4:
		{

		}
		case 5:
		{

		}
		case 6:
		{

		}
		}
		cout << "....." << endl;
	} while (operation != 7);

	RoomFile.close();
	/*RoomFile.open("Rooms.txt", ios::out);
	for (int i = 0; i < NumberOfRooms; i++)
	{
		RoomFile.write((char*)&Rooms[i], sizeof(Rooms[i]));
	}*/
}