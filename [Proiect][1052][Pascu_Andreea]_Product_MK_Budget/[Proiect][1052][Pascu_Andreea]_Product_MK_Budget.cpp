// PRODUCT MARKETING BUDGET
//------ - PRODUCT MARKETING BUDGET CODING SYSTEM------ -
//
//100 -- - PRODUCT RESEARCH
//101 ------Competitive Analysis
//102 ------Focus Groups
//103 ------Paid Studies
//
//200 -- - MARKETING RESEARCH
//201 ------Impact Studies
//202 ------Surveys
//
//300 -- - PRODUCT RELEASE
//301 ------Hardware / Software
//302 ------Launch Events
//303 ------Public Relations
//304 ------Advertising
//
//400 -- - CONTENT MARKETING
//401 ------Press Releases
//402 ------Case Studies
//403 ------Office Supply
//
//500 -- - EMPLOYEES


//DATA files:
//Backup_budget_allocation.dat
//Backup_expenses.dat
//Backup_employees.dat
//Backup_users.dat

//TXT files:
//Backup_budget_allocation.txt
//Backup_expenses.txt
//Backup_employees.txt
//Backup_users.txt


#include<iostream>
#include <ctime>
#include <string>
#include <fstream>
#include<vector>
#include<map>
#include<list>
#include<set>


using namespace std;


class date {
private:
	int dd;
	int mm;
	int yyyy;
	int month_days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };



	friend ostream& operator<<(ostream& console, date d);
	friend istream& operator>>(istream& console, date& d);
	friend bool operator==(const date &date1, const date &date2);
	friend bool operator>(const date &date1, const date &date2);
	friend date operator+(const date &date, const int& numberOfDays);
	friend bool operator!=(const date& Date1, const date& Date2);


public:

	date()
	{
		this->dd = 1;
		this->mm = 1;
		this->yyyy = 1900;
	}
	date(int day, int month, int year)
	{
		if ((month >= 1 && month <= 12) && (day >= 1 && day <= month_days[month - 1]) && (year >= 1900 && year <= 2020))
		{

			this->mm = month;
			this->dd = day;
			this->yyyy = year;
		}
		else
			throw new exception("Invalid date.");

	}

	//getter
	int getDD()
	{
		return this->dd;
	}
	int getMM()
	{
		return this->mm;
	}
	int getYYYY()
	{
		return this->yyyy;
	}

	//setter with verification
	void setDD(int day)
	{
		if (day >= 1 && day <= this->month_days[mm - 1])
		{
			this->dd = day;
		}
		else throw new exception("Invalid date.");
	}
	void setMM(int month)
	{
		if (month >= 1 && month <= 12)
			this->mm = month;
		else throw new exception("Invalid date.");
	}
	void setYYYY(int year)
	{
		if (year >= 1900 && year <= 2020)
			this->yyyy = year;
		else throw new exception("Invalid date.");
	}

	//copy constructor: copy date
	date(const date& d)
	{
		this->dd = d.dd;
		this->mm = d.mm;
		this->yyyy = d.yyyy;
	}
	const date operator++(int)
	{
		date aux = *this;
		//one day incrementing for the date
		int Month_Days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		int day = this->dd + 1;
		int month = this->mm;
		int year = this->yyyy;
		if (day > Month_Days[month - 1])
		{
			day = day - Month_Days[month - 1];
			if (month<12)
				month++;
			else {
				month = 1;
				if (year<2020)
					year = this->yyyy + 1;
				else throw new exception();
			}
		}
		this->dd = day;
		this->mm = month;
		this->yyyy = year;
		return *this;
	}
	date operator=(const date& d1)
	{
		if (this != &d1) {
			this->setDD(d1.dd);
			this->setMM(d1.mm);
			this->setYYYY(d1.yyyy);
			return d1;
		}
		else return *this;
	}
	explicit operator string()
	{
		string temp, vb;
		vb = to_string(this->dd); temp.append(vb); temp.append("."); vb.clear();
		vb = to_string(this->mm); temp.append(vb); temp.append("."); vb.clear();
		vb = to_string(this->yyyy); temp.append(vb); vb.clear();

		return temp;
	}


};
ostream& operator<<(ostream& console, date d)
{
	console << d.dd << "." << d.mm << "." << d.yyyy;
	return console;
}
istream& operator>>(istream& console, date& d)
{
	console >> d.dd >> d.mm >> d.yyyy;
	return console;
}
bool operator==(const date &date1, const date &date2)
{
	return(date1.dd == date2.dd && date1.mm == date2.mm && date1.yyyy == date2.yyyy);
}
bool operator>(const date &date1, const date &date2)
{
	return date1.yyyy >= date2.yyyy && date1.mm >= date2.mm && date1.dd>date2.dd;
}
date operator+(const date &Date, const int& numberOfDays)
{
	//add days to a specific date
	int Month_Days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int day = Date.dd + numberOfDays;
	int month = Date.mm;
	int year = Date.yyyy;
	while (day > Month_Days[month - 1])
	{
		day = day - Month_Days[month - 1];
		if (month<12)
			month++;
		else {
			month = 1;
			if (year<2020)
				year = Date.yyyy + 1;
			else throw new exception();
		}
	}
	return date(day, month, year);
}
bool operator!=(const date& Date1, const date& Date2)
{
	return !((Date1.dd == Date2.dd) && (Date1.mm == Date2.mm) && (Date1.yyyy == Date2.yyyy));
}


class date_time :virtual public date
{
private:
	int hour;
	int minute;
	static int MAXHOUR;
	static int MAXMINUTE;

	friend bool operator!=(const date_time& t1, const date_time& t2);
	friend bool operator==(const date_time& t1, const date_time& t2);
	friend date_time operator-(const date_time& t1, const date_time& t2);
	friend istream& operator>>(istream& console, date_time& t);
	friend void operator<<(ostream& console, date_time& t);


public:
	date_time() :date()
	{
		this->hour = 0;
		this->minute = 0;
	}
	date_time(int day, int month, int year, int hour, int minute) :date(day, month, year)
	{
		if ((hour >= 0 && hour < MAXHOUR) && (minute >= 0 && minute < MAXMINUTE))
		{
			this->hour = hour;
			this->minute = minute;
		}
		else throw exception("Invalid date.");
	}
	date_time(int hour, int minute)
	{
		this->setHour(hour);
		this->setMinute(minute);
	}
	date_time(const date_time& t) :date(t)
	{
		if (this != &t)
		{
			this->setHour(t.hour);
			this->setMinute(t.minute);
		}
	}
	int getHour()
	{
		return this->hour;
	}
	int getMinute()
	{
		return this->minute;
	}
	void setHour(int h)
	{
		if (h >= 0 && h < MAXHOUR)
			this->hour = h;
		else throw exception("Invalid date.");
	}
	void setMinute(int m)
	{
		if (m >= 0 && m < MAXMINUTE)
			this->minute = m;
		else throw exception("Invalid date.");
	}

	void setDate(date* d)
	{
		this->setDD(d->getDD());
		this->setMM(d->getMM());
		this->setYYYY(d->getYYYY());
	}

	date_time getCurrentTime()
	{
		time_t t = time(0);
		struct tm * now = localtime(&t);
		this->hour = now->tm_hour;
		this->minute = now->tm_min;

		return *this;
	}
	date_time operator=(const date_time& t)
	{
		if (this != &t) {
			this->setHour(t.hour);
			this->setMinute(t.minute);

			return t;
		}
		else return *this;
	}
	date_time operator=(date_time* t)
	{
		if (this != t)
		{
			this->hour = t->hour;
			this->minute = t->minute;
		}
		else throw exception();
	}
	bool operator>(const date_time& t)const
	{
		return this->hour > t.hour || this->minute > t.minute;
	}
	const date_time operator++(int)
	{
		date_time aux = *this;
		//one day incrementing for the date

		int hour = this->hour;
		int minute = this->minute + 1;

		if (minute == MAXMINUTE)
		{
			minute = 0;
			hour++;
			if (hour == MAXHOUR)
			{
				hour = 0;
			}
		}
		this->hour = hour;
		this->minute = minute;

		return *this;
	}
	explicit operator string()
	{
		string temp, vb;
		vb = to_string(this->hour); temp.append(vb);
		if (this->hour == 0)
			temp.append("0:");
		else
			temp.append(":");
		vb.clear();

		vb = to_string(this->minute); temp.append(vb);
		if (this->minute == 0)
			temp.append("0");
		vb.clear();

		return temp;
	}
};
int date_time::MAXHOUR = 24;
int date_time::MAXMINUTE = 60;
void operator<<(ostream& console, date_time& t)
{
	cout << endl << t.getHour() << ":" << t.getMinute();
}
istream& operator>>(istream& console, date_time& t)
{
	//read only the hour and minute
	int h, m;
	console >> h >> m;
	t.setHour(h);
	t.setMinute(m);
	return console;
}
bool operator!=(const date_time& t1, const date_time& t2)
{
	return!(t1.hour == t2.hour && t1.minute == t2.minute);
}
bool operator==(const date_time& t1, const date_time& t2)
{
	return (t1.hour == t2.hour && t1.minute == t2.minute);
}
date_time operator-(const date_time& t1, const date_time& t2)
{
	int minutes1 = t1.minute;
	int minutes2 = t2.minute;
	int hour1 = t1.hour;
	int hour2 = t2.hour;
	int T_min = 0, T_hr = 0;
	if ((hour1 == hour2) && minutes1>minutes2)
	{
		T_min = minutes1 - minutes2;
		T_hr = 0;
	}
	if ((hour1 == hour2) && minutes1 < minutes2)
	{
		T_hr = hour1;
		T_min = minutes1;
		hour1 = 23;
		minutes1 = 60;
		T_hr = T_hr + (hour1 - hour2);
		T_min = T_min + (minutes1 - minutes2);
	}
	else
		if (hour1 < hour2)
		{
			//get time to 24:60
			T_hr = hour1;
			T_min = minutes1;
			hour1 = 23;
			minutes1 = 60;
			T_hr = T_hr + (hour1 - hour2);
			T_min = T_min + (minutes1 - minutes2);
			if (T_min == 60)
			{
				T_min = 0;
				T_hr++;
			}

		}
		else
			if (hour1 > hour2)
			{
				T_hr = 0;
				T_min = 0;
				hour1--;
				if (hour1 != hour2)
				{
					while (hour1 != hour2)
					{
						hour1--;
						T_hr++;
					}
				}
				if (minutes1 < minutes2)
				{
					T_min = 60 + minutes1 - minutes2;
				}
				else if (minutes1 > minutes2)
				{
					T_min = minutes1 - minutes2;
				}
				else T_min = 0;
			}

	return date_time(T_hr, T_min);
}



class Transactions
{
public:
	virtual float getAmount() = 0;
	virtual char* getTitle() = 0;
	virtual date* getDate() = 0;
	virtual void save_txt_to_binary(string path) = 0;
	virtual void display_binary_file() = 0;

	virtual void write_to_binary_file(fstream& output_file)
	{
		if (output_file.is_open())
		{
			cout << endl << "Transactions: Binary file is open for writing.";
		}
		else cout << endl << "Transactions: Binary file is not open.";
	}
	virtual void read_from_binary_file(ifstream& input_file)
	{
		if (input_file.is_open())
		{
			cout << endl << "Transactions: Binary file is open for reading.";
		}
		else cout << endl << "Transactions: Binary file is not open.";
	}

};


//budget money allocation class
class budgetAllocation : public Transactions {
private:
	const int budget_id;
	int department_id;
	char* name_of_budget;
	date* date_of_budget;
	float allocated_amount;

	date* current_date;

	static int noCrt;

	friend void operator<<(ostream& console, const budgetAllocation& object);
	friend istream& operator>>(istream& console, budgetAllocation& object);
	friend bool operator==(const budgetAllocation &object1, const int& x);
	friend bool operator>(const budgetAllocation &object1, const budgetAllocation &object2);
	friend bool operator!(const budgetAllocation& object1);
	friend bool operator!=(const budgetAllocation& object1, const budgetAllocation& object2);

public:

	//default constructor
	budgetAllocation() : budget_id(budgetAllocation::noCrt)
	{
		budgetAllocation::noCrt++;
		this->date_of_budget = new date();
		this->date_of_budget = getCurrent_date();
		this->current_date = new date();
		this->current_date = getCurrent_date();
		department_id = 111;
		this->name_of_budget = new char[strlen("Default Budget") + 1];
		strcpy(this->name_of_budget, "Default Budget");
		this->allocated_amount = 0;
	}
	//custom constructor
	budgetAllocation(date* inputDate, int input_department_id, char* inputName, float inputAmount) :budget_id(budgetAllocation::noCrt)

	{
		budgetAllocation::noCrt++;
		this->date_of_budget = new date(inputDate->getDD(), inputDate->getMM(), inputDate->getYYYY());
		this->current_date = new date();
		this->current_date = getCurrent_date();
		this->department_id = input_department_id;
		if (strlen(inputName) > 2)
		{
			this->name_of_budget = new char[strlen(inputName) + 1];
			strcpy(this->name_of_budget, inputName);
		}
		else throw new exception("Invalid name.");
		if (inputAmount != 0) {
			this->allocated_amount = inputAmount;
		}
		else throw new exception("Invalid value.");
	}

	//getter
	int getBudgetId()
	{
		return this->budget_id;
	}
	int getDepartmentId()
	{
		return this->department_id;
	}
	char* getTitle()
	{
		return this->name_of_budget;
	}
	date* getDate()
	{
		return this->date_of_budget;
	}
	date* getCurrent_date()
	{
		int Day;
		int Month;
		int Year;

		time_t now = time(0);
		tm *ltm = localtime(&now);
		Day = ltm->tm_mday;
		Month = 1 + ltm->tm_mon;
		Year = 1900 + ltm->tm_year;

		this->current_date = new date();
		current_date->setDD(Day);
		current_date->setMM(Month);
		current_date->setYYYY(Year);

		return this->current_date;
	}
	float getAmount()
	{
		return this->allocated_amount;
	}



	//setter
	void setDepartmentId(int inputDepartment_id) {
		if (inputDepartment_id)
			this->department_id = inputDepartment_id;
		else throw new exception("Invalid value");
	}
	void setTitle(char* inputName)
	{
		if (strlen(inputName) >2)
		{
			delete[] this->name_of_budget;
			this->name_of_budget = new char[strlen(inputName) + 1];
			strcpy(this->name_of_budget, inputName);
		}
		else throw exception();
	}
	void setAllocatedAmount(float input)
	{
		if (input != 0)
			this->allocated_amount = input;
		else throw exception();
	}
	void setBudgetDate(date* inputDate)
	{
		if (inputDate == NULL)
			throw exception();
		else
		{
			this->date_of_budget = new date(inputDate->getDD(), inputDate->getMM(), inputDate->getYYYY());
		}
	}


	//copy constructor to current date, and system id
	budgetAllocation(const budgetAllocation *object) :budget_id(budgetAllocation::noCrt)
	{
		this->date_of_budget = NULL;
		this->date_of_budget = new date();
		this->date_of_budget = object->date_of_budget;
		this->current_date = NULL;
		this->current_date = new date;
		this->current_date = getCurrent_date();
		this->setDepartmentId(object->department_id);
		this->name_of_budget = NULL;
		this->setTitle(object->name_of_budget);
		this->setAllocatedAmount(object->allocated_amount);
	}
	//operator=
	budgetAllocation&  operator=(const budgetAllocation& x)
	{
		if (*this != x)
		{
			this->date_of_budget = NULL;
			this->date_of_budget = new date();
			this->date_of_budget = getCurrent_date();
			this->current_date = NULL;
			this->current_date = new date();
			this->current_date = getCurrent_date();
			this->setDepartmentId(x.department_id);
			this->name_of_budget = NULL;
			this->setTitle(x.name_of_budget);
			this->setAllocatedAmount(x.allocated_amount);
			return *this;
		}
		else return *this;
	}
	explicit operator int()
	{
		return this->allocated_amount;
	}
	const budgetAllocation operator+(const budgetAllocation &other) const {
		return budgetAllocation(*this) += other;
	}
	budgetAllocation& operator+=(const budgetAllocation& object) {
		this->department_id = 0;
		this->name_of_budget = NULL;
		this->name_of_budget = new char[strlen("TOTAL") + 1];
		strcpy(this->name_of_budget, "TOTAL");

		this->date_of_budget = NULL;
		this->date_of_budget = new date(object.date_of_budget->getDD(), object.date_of_budget->getMM(), object.date_of_budget->getYYYY());

		this->current_date = NULL;
		this->current_date = new date();
		this->current_date = getCurrent_date();

		this->allocated_amount += object.allocated_amount;
		return *this;
	}
	const budgetAllocation operator++(int)
	{
		budgetAllocation temp = *this;
		this->date_of_budget++;
		return temp;
	}

	~budgetAllocation()
	{
		if (this->name_of_budget != NULL)
			delete[] this->name_of_budget;
		if (this->date_of_budget != NULL)
			delete[] this->date_of_budget;
		if (this->current_date != NULL)
			delete[] this->current_date;

		budgetAllocation::noCrt--;
	}


	//read from txt file, one object at a time
	void read_from_file(ifstream& input_file)
	{
		if (input_file.is_open())
		{
			input_file >> *this;
		}
		else cout << "Txt read file is not open";
	}
	//write inside-object to binary file with increment of nr_crt
	void add_object_to_binary_file()
	{
		fstream binary_file;

		binary_file.open("Backup_budget_allocation.dat", ios::in | ios::out | ios::binary);
		int no_of_objects_bin = 0;
		if (binary_file.is_open())
		{
			//if the file exists:
			//rewrite the number of elements
			binary_file.seekp(0);
			binary_file.read((char*)&no_of_objects_bin, sizeof(int));
			no_of_objects_bin++;
			binary_file.seekp(0);
			binary_file.write((char*)&no_of_objects_bin, sizeof(int));
			binary_file.close();

			//write this at the end of file
			binary_file.open("Backup_budget_allocation.dat", ios::binary | ios::out | ios::app);
			if (binary_file.is_open())
			{
				this->write_to_binary_file(binary_file);
			}
			else cout << "BINARY file is not open.";
		}
		else {
			//if file does not exist
			cout << endl << "File will be created" << endl;
			no_of_objects_bin = 1;
			binary_file.open("Backup_budget_allocation.dat", ios::binary | ios::out);
			binary_file.write((char*)&no_of_objects_bin, sizeof(int));
			this->write_to_binary_file(binary_file);
			binary_file.close();
		}

		binary_file.close();
	}
	//display on screen binary file store data
	void display_binary_file()
	{
		ifstream file1;
		file1.open("Backup_budget_allocation.dat", ios::in | ios::binary);
		int number1;
		if (file1.is_open()) {
			file1.seekg(0);
			file1.read((char*)&number1, sizeof(int));
			cout << endl << number1 << " data found." << endl;
			budgetAllocation* array = new budgetAllocation[number1];
			for (int i = 0; i < number1; i++) {

				array[i].read_from_binary_file(file1);
				cout << endl << array[i];
			}
			cout << endl << "BINARY file:  imported successfully.";
		}
		file1.close();
	}
	//write object to binary file
	void write_to_binary_file(fstream& output_file)
	{
		if (output_file.is_open())
		{
			output_file.write((char*)&this->department_id, sizeof(int));
			char buffer[30];
			strcpy(buffer, this->name_of_budget);
			output_file.write(buffer, sizeof(buffer));
			int day; int month; int year;
			day = this->date_of_budget->getDD();
			month = this->date_of_budget->getMM();
			year = this->date_of_budget->getYYYY();
			output_file.write((char*)&day, sizeof(int));
			output_file.write((char*)&month, sizeof(int));
			output_file.write((char*)&year, sizeof(int));
			output_file.write((char*)&this->allocated_amount, sizeof(float));

		}
		else cout << "Binary write file not open";
	}
	void read_from_binary_file(ifstream& input_file)
	{
		if (input_file.is_open())
		{
			int dep_id;
			char buffer[30];
			int day; int month; int year;
			float amount;

			input_file.read((char*)&dep_id, sizeof(int));
			this->department_id = dep_id;
			input_file.read((char*)&buffer, sizeof(buffer));
			this->name_of_budget = NULL;
			this->name_of_budget = new char[30];
			strcpy(this->name_of_budget, buffer);
			input_file.read((char*)&day, sizeof(int));
			input_file.read((char*)&month, sizeof(int));
			input_file.read((char*)&year, sizeof(int));
			this->date_of_budget = NULL;
			this->date_of_budget = new date(day, month, year);
			input_file.read((char*)&amount, sizeof(float));
			this->allocated_amount = amount;
		}
		else cout << "Binary read file not open";
	}
	//don't bother with naming binary files; it is done by default
	void save_txt_to_binary(string path)
	{
		ifstream txt_file;
		fstream binary_file;

		txt_file.open(path, ios::in);
		binary_file.open("Backup_budget_allocation.dat", ios::in | ios::out | ios::binary);

		int no_of_objects_txt = 0;
		int no_of_objects_bin = 0;

		if (txt_file.is_open())
		{
			txt_file >> no_of_objects_txt;
			budgetAllocation* temp;
			temp = new budgetAllocation[no_of_objects_txt];
			if (binary_file.is_open())
			{
				binary_file.seekp(0);
				binary_file.read((char*)&no_of_objects_bin, sizeof(int));
				no_of_objects_bin += no_of_objects_txt;
				binary_file.seekp(0);
				binary_file.write((char*)&no_of_objects_bin, sizeof(int));
				binary_file.close();
				binary_file.open("Backup_budget_allocation.dat", ios::binary | ios::out | ios::app);
				if (binary_file.is_open())
				{
					for (int i = 0; i < no_of_objects_txt; i++)
					{
						temp[i].read_from_file(txt_file);
						temp[i].write_to_binary_file(binary_file);
					}
				}
				else cout << "BINARY file is not open.";
			}
			else
			{
				//if the file does not exist 
				cout << endl << "BINARY file will be created." << endl;
				no_of_objects_bin = no_of_objects_txt;
				binary_file.open("Backup_budget_allocation.dat", ios::binary | ios::out);
				binary_file.write((char*)&no_of_objects_bin, sizeof(int));
				for (int i = 0; i < no_of_objects_bin; i++)
				{
					temp[i].read_from_file(txt_file);
					temp[i].write_to_binary_file(binary_file);
				}
			}

		}
		else cout << "TXT file is not open.";

		txt_file.close();
		binary_file.close();
	}


};
int budgetAllocation::noCrt = 1;
void operator<<(ostream& console, const budgetAllocation& object)
{
	console << endl << object.department_id
		<< "," << object.name_of_budget
		<< "," << object.date_of_budget->getDD()
		<< "." << object.date_of_budget->getMM()
		<< "." << object.date_of_budget->getYYYY()
		<< "," << object.allocated_amount;
}
istream& operator>>(istream& console, budgetAllocation& object)
{
	string word;
	int day = 0;
	int month = 0;
	int year = 0;
	date* temp_date = new date();
	getline(console, word, ',');
	object.department_id = stoi(word, nullptr);

	getline(console, word, ',');
	object.name_of_budget = NULL;
	object.name_of_budget = new char[word.length() + 1];
	strcpy(object.name_of_budget, word.c_str());

	getline(console, word, '.'); day = stoi(word, nullptr);  temp_date->setDD(day);
	getline(console, word, '.'); month = stoi(word, nullptr); temp_date->setMM(month);
	getline(console, word, ','); year = stoi(word, nullptr); temp_date->setYYYY(year);
	object.date_of_budget = temp_date;

	getline(console, word, '\n');
	object.allocated_amount = stof(word, nullptr);
	object.current_date = new date();
	object.current_date = object.getCurrent_date();

	return console;
}
bool operator==(const budgetAllocation &object1, const int& x)
{
	return object1.department_id == x;
}
bool operator>(const budgetAllocation &object1, const budgetAllocation &object2)
{
	return(object1.allocated_amount > object2.allocated_amount);
}
bool operator!(const budgetAllocation& object1)
{
	return  !(object1.allocated_amount || object1.name_of_budget || object1.budget_id || object1.date_of_budget || object1.department_id);
}
bool operator!=(const budgetAllocation& object1, const budgetAllocation& object2)
{
	return (object1.department_id != object2.department_id && object1.budget_id != object2.budget_id &&
		object1.allocated_amount != object2.allocated_amount && object1.date_of_budget != object2.date_of_budget);
}


//expenses parent class
class Expenses :public Transactions {
private:
	const int id;
	int department_id;
	char* title;
	date* Date;
	float amount;

	date* current_date;

	friend void operator<<(ostream& console, const Expenses& object);
	friend istream& operator>>(istream& console, Expenses& object);
	friend bool operator==(const Expenses &object1, const Expenses& object2);
	friend bool operator>(const Expenses &object1, const Expenses &object2);
	friend bool operator!=(const Expenses& object1, const Expenses& object2);
	friend bool operator!(const Expenses& object1);


protected:
	static int noExpenses;

public:

	//default constructor
	Expenses() :id(Expenses::noExpenses)
	{
		Expenses::noExpenses++;
		this->department_id = 600;
		this->title = new char[strlen("Default Title") + 1];
		strcpy(this->title, "Default Title");
		this->current_date = new date();
		this->current_date = getCurrent_date();
		int d, m, y;
		d = this->current_date->getDD();
		m = this->current_date->getMM();
		y = this->current_date->getYYYY();
		this->Date = new date(d, m, y);
		this->amount = 0;
	}
	//custom constructor
	Expenses(int input_department_id, char* inputTitle, date* inputDate, float inputValue) :id(Expenses::noExpenses)
	{
		Expenses::noExpenses++;
		if (input_department_id >= 0)
			this->department_id = input_department_id;
		else throw new exception("Cannot input negative value.");
		this->title = new char[strlen(inputTitle) + 1];
		strcpy(this->title, inputTitle);
		this->current_date = new date();
		this->current_date = getCurrent_date();
		this->Date = new date(inputDate->getDD(), inputDate->getMM(), inputDate->getYYYY());
		if (inputValue != 0)
		{
			this->amount = inputValue;
		}
		else throw new exception("Cannot input negative amount.");
	}

	//getter
	int getDepartment_Id()
	{
		return this->department_id;
	}
	char* getTitle()
	{
		return this->title;
	}
	date* getDate()
	{
		return this->Date;
	}
	float getAmount()
	{
		return this->amount;
	}
	const int getId()
	{
		return this->id;
	}
	date* getCurrent_date()
	{
		int Day;
		int Month;
		int Year;

		time_t now = time(0);
		tm *ltm = localtime(&now);
		Day = ltm->tm_mday;
		Month = 1 + ltm->tm_mon;
		Year = 1900 + ltm->tm_year;

		this->current_date = new date();

		current_date->setDD(Day);
		current_date->setMM(Month);
		current_date->setYYYY(Year);

		return this->current_date;
	}

	static int getNoExpenses()
	{
		return Expenses::noExpenses;
	}

	//setter 
	void setDepartment_Id(int input_department_id)
	{
		if (input_department_id >= 0)
			this->department_id = input_department_id;
		else throw new exception("Cannot input negative value.");
	}
	void setTitle(const char* inputTitle)
	{
		delete[] this->title;
		this->title = new char[strlen(inputTitle) + 1];
		strcpy(this->title, inputTitle);
	}
	void setTitle(const string inputTitle)
	{
		delete[] this->title;
		this->title = new char[inputTitle.length() + 1];
		strcpy(this->title, inputTitle.c_str());
	}
	void setDate(date* inputDate)
	{
		if (inputDate == NULL)
			throw exception();
		else
		{
			//delete[] this->Date;
			this->Date = new date(inputDate->getDD(), inputDate->getMM(), inputDate->getYYYY());
		}
	}
	void setAmount(float input)
	{
		if (input != 0)
			this->amount = input;
		else throw exception();
	}


	//copy constructor
	Expenses(const Expenses& object) :id(object.id)
	{
		this->setDepartment_Id(object.department_id);
		this->title = NULL;
		this->setTitle(object.title);
		this->Date = NULL;
		this->Date = new date(object.Date->getDD(), object.Date->getMM(), object.Date->getYYYY());
		this->setAmount(object.amount);
		this->current_date = NULL;
		this->current_date = new date();
		this->current_date = getCurrent_date();
	}
	//operator=
	Expenses& operator=(const Expenses& x)
	{
		if (*this != x)
		{
			this->setDepartment_Id(x.department_id);
			this->title = NULL;
			this->setTitle(x.title);
			this->Date = NULL;
			this->Date = new date(x.Date->getDD(), x.Date->getMM(), x.Date->getYYYY());
			this->setAmount(x.amount);
			this->current_date = NULL;
			this->current_date = new date();
			this->current_date = getCurrent_date();
			return *this;
		}
		else return *this;
	}
	explicit operator int()
	{
		return this->amount;
	}
	const Expenses operator+(const Expenses &other) const {
		return Expenses(*this) += other;
	}
	Expenses& operator+=(const Expenses& object) {
		this->department_id = 0;
		this->title = NULL;
		this->title = new char[strlen("TOTAL") + 1];
		strcpy(this->title, "TOTAL");
		this->Date = NULL;
		this->Date = new date(object.Date->getDD(), object.Date->getMM(), object.Date->getYYYY());
		this->current_date = NULL;
		this->current_date = new date();
		this->current_date = getCurrent_date();
		this->amount += object.amount;
		return *this;
	}
	const Expenses operator++(int)
	{
		Expenses temp = *this;
		this->Date++;
		return temp;
	}
	//destructor
	virtual ~Expenses()
	{
		if (this->title != 0)
			delete[] this->title;
		if (this->Date != NULL)
			delete[] this->Date;
		if (this->current_date != NULL)
			delete[] this->current_date;

		Expenses::noExpenses--;
	}

	//read from txt file, one object at a time
	virtual void read_from_file(ifstream& input_file)
	{
		if (input_file.is_open())
		{
			input_file >> *this;
		}
		else cout << "Txt read file is not open";
	}
	//write/read object to/from binary file
	virtual void write_to_binary_file(fstream& output_file)
	{
		if (output_file.is_open())
		{
			output_file.write((char*)&this->department_id, sizeof(int));
			char buffer[30];
			strcpy(buffer, this->title);
			output_file.write(buffer, sizeof(buffer));
			int day; int month; int year;
			day = this->Date->getDD();
			month = this->Date->getMM();
			year = this->Date->getYYYY();
			output_file.write((char*)&day, sizeof(int));
			output_file.write((char*)&month, sizeof(int));
			output_file.write((char*)&year, sizeof(int));
			output_file.write((char*)&this->amount, sizeof(float));
		}
		else cout << "Binary write file not open";
	}
	//write inside-object to binary file with increment of nr_crt
	void add_object_to_binary_file()
	{
		fstream binary_file;
		binary_file.open("Backup_expenses.dat", ios::in | ios::out | ios::binary);
		int no_of_objects_bin = 0;
		if (binary_file.is_open())
		{
			//if the file exists:
			//rewrite the number of elements
			binary_file.seekp(0);
			binary_file.read((char*)&no_of_objects_bin, sizeof(int));
			no_of_objects_bin++;
			binary_file.seekp(0);
			binary_file.write((char*)&no_of_objects_bin, sizeof(int));
			binary_file.close();
			//write this at the end of file
			binary_file.open("Backup_expenses.dat", ios::binary | ios::out | ios::app);
			if (binary_file.is_open())
			{
				this->write_to_binary_file(binary_file);
			}
			else cout << "BINARY file is not open.";

		}
		else {
			//if file does not exist
			cout << endl << "File will be created" << endl;
			no_of_objects_bin = 1;
			binary_file.open("Backup_expenses.dat", ios::binary | ios::out);
			binary_file.write((char*)&no_of_objects_bin, sizeof(int));
			this->write_to_binary_file(binary_file);
			binary_file.close();
		}

		binary_file.close();
	}
	//display on screen binary file store data
	void display_binary_file()
	{
		ifstream file2;
		file2.open("Backup_expenses.dat", ios::in | ios::binary);
		int number2;
		if (file2.is_open()) {
			file2.seekg(0);
			file2.read((char*)&number2, sizeof(int));
			cout << endl << number2 << " data found." << endl;
			Expenses* array = new Expenses[number2];
			for (int i = 0; i < number2; i++) {

				array[i].read_from_binary_file(file2);
				cout << endl << array[i];
			}
			cout << endl << "BINARY file:  imported successfully.";
		}
		file2.close();
	}
	virtual void read_from_binary_file(ifstream& input_file)
	{
		if (input_file.is_open())
		{
			int dep_id;
			char buffer[30];
			int day; int month; int year;
			float Amount;
			input_file.read((char*)&dep_id, sizeof(int));
			this->department_id = dep_id;
			input_file.read((char*)&buffer, sizeof(buffer));
			this->title = NULL;
			this->title = new char[30];
			strcpy(this->title, buffer);
			input_file.read((char*)&day, sizeof(int));
			input_file.read((char*)&month, sizeof(int));
			input_file.read((char*)&year, sizeof(int));
			this->Date = NULL;
			this->Date = new date(day, month, year);
			input_file.read((char*)&Amount, sizeof(float));
			this->amount = Amount;
		}
		else cout << "Binary read file not open";
	}
	virtual void save_txt_to_binary(string path)
	{
		ifstream txt_file;
		fstream binary_file;
		txt_file.open(path, ios::in);
		binary_file.open("Backup_expenses.dat", ios::in | ios::out | ios::binary);
		int no_of_objects_txt = 0;
		int no_of_objects_bin = 0;
		if (txt_file.is_open())
		{
			txt_file >> no_of_objects_txt;
			Expenses* temp;
			temp = new Expenses[no_of_objects_txt];
			if (binary_file.is_open())
			{
				binary_file.seekp(0);
				binary_file.read((char*)&no_of_objects_bin, sizeof(int));
				no_of_objects_bin += no_of_objects_txt;
				binary_file.seekp(0);
				binary_file.write((char*)&no_of_objects_bin, sizeof(int));
				binary_file.close();
				binary_file.open("Backup_expenses.dat", ios::binary | ios::out | ios::app);
				if (binary_file.is_open())
				{
					for (int i = 0; i < no_of_objects_txt; i++)
					{
						temp[i].read_from_file(txt_file);
						temp[i].write_to_binary_file(binary_file);
					}
				}
				else cout << "BINARY file is not open.";
			}
			else
			{
				//if the file does not exist 
				cout << endl << "BINARY file will be created." << endl;
				no_of_objects_bin = no_of_objects_txt;
				binary_file.open("Backup_expenses.dat", ios::binary | ios::out);
				binary_file.write((char*)&no_of_objects_bin, sizeof(int));
				for (int i = 0; i < no_of_objects_bin; i++)
				{
					temp[i].read_from_file(txt_file);
					temp[i].write_to_binary_file(binary_file);
				}
			}
		}
		else cout << "TXT file is not open.";
		txt_file.close();
		binary_file.close();
	}
};
int Expenses::noExpenses = 1;
void operator<<(ostream& console, const Expenses& object)
{
	console
		<< object.department_id
		<< "," << object.title
		<< "," << object.Date->getDD()
		<< "." << object.Date->getMM()
		<< "." << object.Date->getYYYY()
		<< "," << object.amount;
}
istream& operator>>(istream& console, Expenses& object)
{
	string word;
	date* inputDate = new date();
	int d, m, y;
	getline(console, word, ',');
	object.department_id = stoi(word, nullptr);
	getline(console, word, ',');
	object.title = NULL;
	object.title = new char[word.length() + 1];
	strcpy_s(object.title, word.length() + 1, word.c_str());

	getline(console, word, '.');  d = stoi(word, nullptr);	inputDate->setDD(d);
	getline(console, word, '.');  m = stoi(word, nullptr);	inputDate->setMM(m);
	getline(console, word, ',');  y = stoi(word, nullptr);   inputDate->setYYYY(y);
	if (inputDate)
	{
		object.Date = inputDate;
	}

	getline(console, word, '\n');
	object.amount = stof(word, nullptr);

	object.current_date = new date();
	object.current_date = object.getCurrent_date();

	return console;
}
//compare 2 dates
bool operator==(const Expenses &object1, const Expenses &object2)
{
	return (object1.Date == object2.Date);
}
bool operator>(const Expenses &object1, const Expenses &object2)
{
	return object1.Date > object2.Date;
}
bool operator!=(const Expenses& object1, const Expenses& object2)
{
	return(object1.department_id != object2.department_id && object1.id != object2.id && object1.amount != object2.amount
		&& object1.Date != object2.Date && object1.title != object2.title);
}
bool operator!(const Expenses& object1)
{
	return !(object1.department_id || object1.id || object1.amount || object1.Date || object1.title);
}

//employee expenses
class Employee : virtual public Expenses {
private:
	char cnp[14];
	char* employee_name;
	date* hire_date;
	date* end_date;
	float subsidy;

	friend void operator<<(ostream& console, const Employee& e);
	friend  istream& operator>>(istream& console, Employee& e);
	friend bool operator==(const Employee& emp1, const Employee& emp2);
	friend  bool operator<(const Employee& emp1, const Employee& emp2);
	friend bool operator!=(const Employee& object1, const Employee& object2);
	friend bool operator!(const Employee& object1);

public:

	Employee() :Expenses()
	{
		date* DATE = new date();
		strcpy(this->cnp, "0000000000000");
		this->employee_name = new char[strlen("Employee default") + 1];
		strcpy(this->employee_name, "Employee default");
		DATE = Expenses::getCurrent_date();
		int d, m, y;
		d = DATE->getDD();
		m = DATE->getMM();
		y = DATE->getYYYY();
		this->hire_date = new date(d, m, y);
		this->end_date = new date(d, m, y);
		this->subsidy = 0;
	}
	Employee(int input_department_id, char* inputTitle, date* inputDate, float inputValue,
		char inputCnp[14], char* inputName, date* Ihire_date, date* Iend_date, float inputSubsidy)
		:Expenses(input_department_id, inputTitle, inputDate, inputValue)
	{
		strcpy(this->cnp, inputCnp);
		this->employee_name = new char[strlen(inputName) + 1];
		strcpy(this->employee_name, inputName);
		this->hire_date = new date(Ihire_date->getDD(), Ihire_date->getMM(), Ihire_date->getYYYY());
		this->end_date = new date(Iend_date->getDD(), Iend_date->getMM(), Iend_date->getYYYY());
		this->subsidy = inputSubsidy;
	}
	//copy constructor
	Employee(const Employee& emp) :Expenses(emp)
	{
		strcpy(this->cnp, "");
		strcpy(this->cnp, emp.cnp);
		this->employee_name = NULL;
		this->setEmployeeName(emp.employee_name);
		this->hire_date = NULL;
		this->setHireDate(emp.hire_date);
		this->end_date = NULL;
		this->setEndDate(emp.end_date);
		this->setSubsidy(emp.subsidy);
	}
	char* getCnp()
	{
		return this->cnp;
	}
	char* getEmployeeName()
	{
		return this->employee_name;
	}
	date* getHire_date()
	{
		return this->hire_date;
	}
	date* getEnd_date()
	{
		return this->end_date;
	}
	float getSubsidy()
	{
		return this->subsidy;
	}

	void setCnp(char inputCnp[14])
	{
		if (strlen(inputCnp) == 13) {
			for (int i = 0; i < 13; i++)
			{
				if (inputCnp[i] == '0' ||
					inputCnp[i] == '1' ||
					inputCnp[i] == '2' ||
					inputCnp[i] == '3' ||
					inputCnp[i] == '4' ||
					inputCnp[i] == '5' ||
					inputCnp[i] == '6' ||
					inputCnp[i] == '7' ||
					inputCnp[i] == '8' ||
					inputCnp[i] == '9')
				{
					strcpy(this->cnp, inputCnp);
				}
				else throw new exception("Cannot input characters.");
			}
		}
		else throw new exception("Invalid cnp.");
	}
	void setEmployeeName(const char* inputName)
	{
		if (strlen(inputName) > 2)
		{
			delete[] this->employee_name;
			this->employee_name = new char[strlen(inputName) + 1];
			strcpy(this->employee_name, inputName);
		}
		else throw new exception("Invalid name");
	}
	void setHireDate(date* inputDate)
	{
		if (inputDate == NULL)
			throw exception();
		else
		{
			delete[] this->hire_date;
			this->hire_date = new date(inputDate->getDD(), inputDate->getMM(), inputDate->getYYYY());
		}
	}
	void setEndDate(date* inputDate)
	{
		if (inputDate == NULL)
			throw exception();
		else
		{
			delete[] this->end_date;
			this->end_date = new date(inputDate->getDD(), inputDate->getMM(), inputDate->getYYYY());
		}
	}
	void setSubsidy(float inputValue)
	{
		if (inputValue >= 0)
			this->subsidy = inputValue;
		else throw exception();
	}



	void operator=(Employee& existingObject)
	{
		if (*this != existingObject)
		{
			strcpy(this->cnp, existingObject.cnp);
			this->employee_name = NULL;
			this->setEmployeeName(existingObject.employee_name);
			this->hire_date = NULL;
			this->setHireDate(existingObject.hire_date);
			this->end_date = NULL;
			this->setEndDate(existingObject.end_date);
			this->setSubsidy(existingObject.subsidy);
		}
	}
	using Expenses::operator+=;
	Employee& operator+=(const Employee& emp)
	{
		const Expenses temp = emp;
		operator+=(temp);
		strcpy(this->cnp, "0000000000000");
		this->setEmployeeName("EMPLOYEE");
		this->hire_date = NULL;
		this->hire_date = getCurrent_date();
		this->end_date = NULL;
		this->end_date = getCurrent_date();
		this->subsidy += emp.subsidy;
		return *this;
	}
	using Expenses::operator+;
	const Employee operator+(const Employee &employee) const {
		Expenses temporary = employee;
		operator+(temporary);
		return Employee(*this) += employee;
	}
	const Employee operator++(int)
	{
		Employee temp = *this;
		this->end_date++;
		return temp;
	}
	explicit operator int()
	{
		return this->subsidy;
	}

	~Employee()
	{
		if (employee_name != "")
			delete[] employee_name;
		if (hire_date != NULL)
			delete[] this->hire_date;
		if (end_date != NULL)
			delete[] this->end_date;
	}

	//read from txt file, one object at a time
	void read_from_file(ifstream& input_file)
	{
		if (input_file.is_open())
		{
			input_file >> *this;
		}
		else cout << "Txt read file is not open";
	}
	//write object to binary file
	void write_to_binary_file(fstream& output_file)
	{
		if (output_file.is_open())
		{
			//write expenses part of employee
			Expenses& temp = *this;
			{
				int dep_id = temp.getDepartment_Id();
				output_file.write((char*)&dep_id, sizeof(int));
				char buffer[30];
				strcpy(buffer, temp.getTitle());
				output_file.write(buffer, sizeof(buffer));
				int day; int month; int year;
				day = temp.getDate()->getDD();
				month = temp.getDate()->getMM();
				year = temp.getDate()->getYYYY();
				output_file.write((char*)&day, sizeof(int));
				output_file.write((char*)&month, sizeof(int));
				output_file.write((char*)&year, sizeof(int));
				float AMOUNT = temp.getAmount();
				output_file.write((char*)&AMOUNT, sizeof(float));
			}
			output_file.write((char*)&this->cnp, sizeof(cnp));
			char buffer[30];
			strcpy(buffer, this->employee_name);
			output_file.write(buffer, sizeof(buffer));
			int day; int month; int year;

			day = this->hire_date->getDD();
			month = this->hire_date->getMM();
			year = this->hire_date->getYYYY();
			output_file.write((char*)&day, sizeof(int));
			output_file.write((char*)&month, sizeof(int));
			output_file.write((char*)&year, sizeof(int));

			day = this->end_date->getDD();
			month = this->end_date->getMM();
			year = this->end_date->getYYYY();
			output_file.write((char*)&day, sizeof(int));
			output_file.write((char*)&month, sizeof(int));
			output_file.write((char*)&year, sizeof(int));

			output_file.write((char*)&this->subsidy, sizeof(float));
		}
		else cout << "Binary write file not open";
	}
	//write inside-object to binary file with increment of nr_crt
	void add_object_to_binary_file()
	{
		fstream binary_file;
		binary_file.open("Backup_employees.dat", ios::in | ios::out | ios::binary);
		int no_of_objects_bin = 0;
		if (binary_file.is_open())
		{
			//if the file exists:
			//rewrite the number of elements
			binary_file.seekp(0);
			binary_file.read((char*)&no_of_objects_bin, sizeof(int));
			no_of_objects_bin++;
			binary_file.seekp(0);
			binary_file.write((char*)&no_of_objects_bin, sizeof(int));
			binary_file.close();

			//write this at the end of file
			binary_file.open("Backup_employees.dat", ios::binary | ios::out | ios::app);
			if (binary_file.is_open())
			{
				this->write_to_binary_file(binary_file);
			}
			else cout << "BINARY file is not open.";

		}
		else {
			//if file does not exist
			cout << endl << "File will be created" << endl;
			no_of_objects_bin = 1;
			binary_file.open("Backup_employees.dat", ios::binary | ios::out);
			binary_file.write((char*)&no_of_objects_bin, sizeof(int));
			this->write_to_binary_file(binary_file);
			binary_file.close();
		}

		binary_file.close();
	}
	//display on screen binary file store data
	void display_binary_file()
	{
		ifstream file3;
		file3.open("Backup_employees.dat", ios::in | ios::binary);
		int number3;
		if (file3.is_open()) {
			file3.seekg(0);
			file3.read((char*)&number3, sizeof(int));
			cout << endl << number3 << " data found." << endl;
			Employee* array = new Employee[number3];

			for (int i = 0; i < number3; i++) {

				array[i].read_from_binary_file(file3);
				cout << endl << array[i];
			}
			cout << endl << "BINARY file:  imported successfully.";
		}
		file3.close();
	}
	void read_from_binary_file(ifstream& input_file)
	{
		if (input_file.is_open())
		{
			Expenses& temp = *this;
			//read the expenses part
			{

				int dep_id;
				char buff[30];
				int Day; int Month; int Year;
				float Amount;

				input_file.read((char*)&dep_id, sizeof(int));
				temp.setDepartment_Id(dep_id);
				input_file.read((char*)&buff, sizeof(buff));
				temp.setTitle(buff);
				//strcpy(this->title, buffer);
				input_file.read((char*)&Day, sizeof(int));
				input_file.read((char*)&Month, sizeof(int));
				input_file.read((char*)&Year, sizeof(int));
				temp.setDate(&date(Day, Month, Year));

				input_file.read((char*)&Amount, sizeof(float));
				temp.setAmount(Amount);

			}
			char CNP[14];
			char buffer[30];
			int day; int month; int year;
			float SUBSIDY;

			input_file.read((char*)&CNP, sizeof(CNP));
			strcpy(this->cnp, CNP);
			input_file.read((char*)&buffer, sizeof(buffer));
			this->employee_name = NULL;
			this->employee_name = new char[30];
			strcpy(this->employee_name, buffer);
			input_file.read((char*)&day, sizeof(int));
			input_file.read((char*)&month, sizeof(int));
			input_file.read((char*)&year, sizeof(int));
			this->hire_date = NULL;
			this->hire_date = new date(day, month, year);
			input_file.read((char*)&day, sizeof(int));
			input_file.read((char*)&month, sizeof(int));
			input_file.read((char*)&year, sizeof(int));
			this->end_date = NULL;
			this->end_date = new date(day, month, year);

			input_file.read((char*)&SUBSIDY, sizeof(float));
			this->subsidy = SUBSIDY;

		}
		else cout << "Binary read file not open";
	}
	void save_txt_to_binary(string path)
	{
		ifstream txt_file;
		fstream binary_file;
		txt_file.open(path, ios::in);
		binary_file.open("Backup_employees.dat", ios::in | ios::out | ios::binary);
		int no_of_objects_txt = 0;
		int no_of_objects_bin = 0;
		if (txt_file.is_open())
		{
			txt_file >> no_of_objects_txt;
			Employee* temp;
			temp = new Employee[no_of_objects_txt];
			if (binary_file.is_open())
			{
				binary_file.seekp(0);
				binary_file.read((char*)&no_of_objects_bin, sizeof(int));
				no_of_objects_bin += no_of_objects_txt;
				binary_file.seekp(0);
				binary_file.write((char*)&no_of_objects_bin, sizeof(int));
				binary_file.close();
				binary_file.open("Backup_employees.dat", ios::binary | ios::out | ios::app);
				if (binary_file.is_open())
				{
					for (int i = 0; i < no_of_objects_txt; i++)
					{
						temp[i].read_from_file(txt_file);
						temp[i].write_to_binary_file(binary_file);

					}
				}
				else cout << "BINARY file is not open.";
			}
			else
			{
				//if the file does not exist 
				cout << endl << "BINARY file will be created." << endl;
				no_of_objects_bin = no_of_objects_txt;
				binary_file.open("Backup_employees.dat", ios::binary | ios::out);
				binary_file.write((char*)&no_of_objects_bin, sizeof(int));
				for (int i = 0; i < no_of_objects_bin; i++)
				{
					temp[i].read_from_file(txt_file);
					temp[i].write_to_binary_file(binary_file);
				}
			}
		}
		else cout << "TXT file is not open.";
		txt_file.close();
		binary_file.close();
	}
};
void operator<<(ostream& console, const Employee& e)
{
	Expenses x = e;
	console << endl << x;
	console << "," << e.cnp
		<< "," << e.employee_name
		<< "," << *e.hire_date
		<< "," << *e.end_date
		<< "," << e.subsidy;
}
istream& operator>>(istream& console, Employee& e)
{
	string word;
	Expenses& x = e;
	date* inputHireDate = new date();
	date* inputEndDate = new date();
	date* inputDate = new date();
	int d, m, y;

	//start

	getline(console, word, ',');
	x.setDepartment_Id(stoi(word, nullptr));
	getline(console, word, ',');
	x.setTitle(word);

	getline(console, word, '.');  d = stoi(word, nullptr);	inputDate->setDD(d);
	getline(console, word, '.');  m = stoi(word, nullptr);	inputDate->setMM(m);
	getline(console, word, ',');  y = stoi(word, nullptr);   inputDate->setYYYY(y);
	if (inputDate)
	{
		x.setDate(inputDate);
	}

	getline(console, word, ',');
	x.setAmount(stof(word, nullptr));

	//current date of x?
	//end

	getline(console, word, ',');
	if (word.length() == 13)
	{
		strcpy(e.cnp, word.c_str());
	}
	else cout << endl << "Invalid cnp";
	getline(console, word, ',');
	e.employee_name = NULL;
	e.employee_name = new char[word.length() + 1];
	strcpy(e.employee_name, word.c_str());

	getline(console, word, '.'); d = stoi(word, nullptr);	inputHireDate->setDD(d);
	getline(console, word, '.'); m = stoi(word, nullptr);	inputHireDate->setMM(m);
	getline(console, word, ','); y = stoi(word, nullptr);   inputHireDate->setYYYY(y);
	if (inputHireDate)
	{
		e.hire_date = inputHireDate;
	}
	getline(console, word, '.'); d = stoi(word, nullptr);	inputEndDate->setDD(d);
	getline(console, word, '.'); m = stoi(word, nullptr);	inputEndDate->setMM(m);
	getline(console, word, ','); y = stoi(word, nullptr);   inputEndDate->setYYYY(y);
	if (inputEndDate)
	{
		e.end_date = inputEndDate;
	}
	getline(console, word, '\n');
	e.subsidy = stof(word, nullptr);
	return console;
}
bool operator==(const Employee& emp1, const Employee& emp2)
{
	return(emp1.hire_date == emp2.hire_date);
}
bool operator<(const Employee& emp1, const Employee& emp2)
{
	//if emp1 has been hired before emp2
	return(emp1.hire_date < emp2.hire_date);
}
bool operator!=(const Employee& object1, const Employee& object2)
{
	Expenses obj1 = object1; Expenses obj2 = object2;
	return (obj1 != obj2 && object1.cnp != object2.cnp && object1.employee_name != object2.employee_name
		&& object1.hire_date != object2.hire_date
		&& object1.end_date != object2.end_date);
}
bool operator!(const Employee& object1)
{
	Expenses obj1 = object1;
	return !(obj1) || !(object1.cnp || object1.employee_name || object1.hire_date || object1.end_date);
}

class User {
private:
	char* user_name;
	char* user_password;
	char* user_email;

	friend void operator<<(ostream& console, const User& object);
	friend istream& operator>>(istream& console, User& object);
	friend bool operator==(const User &object1, const User &object2);
	friend bool operator!(const User& object1);
	friend bool operator!=(const User& object1, const User& object2);

	const int user_id;

	static int user_nr;
public:
	User() :user_id(User::user_nr)
	{
		User::user_nr++;
		this->user_name = new char[strlen("default_user") + 1];
		strcpy(this->user_name, "default_user");
		this->user_password = new char[strlen("12345678") + 1];
		strcpy(this->user_password, "12345678");
		this->user_email = new char[strlen("product_marketing@gmail.com") + 1];
		strcpy(this->user_email, "product_marketing@gmail.com");
	}
	User(char* input_name, char* input_password, char* input_email) :user_id(User::user_nr)
	{
		User::user_nr++;
		if (strlen(input_name) > 2) {
			this->user_name = new char[strlen(input_name) + 1];
			strcpy(this->user_name, input_name);
		}
		else throw exception();
		if (strlen(input_password) > 4) {
			this->user_password = new char[strlen(input_password) + 1];
			strcpy(this->user_password, input_password);
		}
		else throw exception();
		if (strlen(input_email) > 2) {
			this->user_email = new char[strlen(input_email) + 1];
			strcpy(this->user_email, input_email);
		}
		else throw exception();
	}
	User(const User& object) :user_id(User::user_nr)
	{
		User::user_nr++;
		this->user_name = NULL;
		this->setUserName(object.user_name);
		this->user_password = NULL;
		this->setUserPassword(object.user_password);
		this->user_email = NULL;
		this->setUserEmail(object.user_email);
	}
	char* getUserName()
	{
		return this->user_name;
	}
	char* getUserPassword()
	{
		return this->user_password;
	}
	char* getUserEmail()
	{
		return this->user_email;
	}
	const int getUserId()
	{
		return this->user_id;
	}
	void setUserName(const char* input_name)
	{
		if (strlen(input_name) > 2) {
			delete[]this->user_name;
			this->user_name = new char[strlen(input_name) + 1];
			strcpy(this->user_name, input_name);
		}
		else throw exception();
	}
	void setUserPassword(const char* input_password)
	{
		if (strlen(input_password) > 4) {
			delete[] this->user_password;
			this->user_password = new char[strlen(input_password) + 1];
			strcpy(this->user_password, input_password);
		}
		else throw exception();
	}
	void setUserEmail(const char* input_email)
	{
		if (strlen(input_email) > 2) {
			delete[] this->user_email;
			this->user_email = new char[strlen(input_email) + 1];
			strcpy(this->user_email, input_email);
		}
		else throw exception();
	}
	//set for strings
	void setUserName(string input_name)
	{
		if (input_name.length() > 2) {
			delete[]this->user_name;
			this->user_name = new char[input_name.length() + 1];
			strcpy(this->user_name, input_name.c_str());
		}
		else throw exception();
	}
	void setUserPassword(string input_password)
	{
		if (input_password.length() > 4) {
			delete[] this->user_password;
			this->user_password = new char[input_password.length() + 1];
			strcpy(this->user_password, input_password.c_str());
		}
		else throw exception();
	}
	void setUserEmail(string input_email)
	{
		if (input_email.length() > 2) {
			delete[] this->user_email;
			this->user_email = new char[input_email.length() + 1];
			strcpy(this->user_email, input_email.c_str());
		}
		else throw exception();
	}
	User&  operator=(const User& x)
	{
		if (*this != x)
		{
			this->user_name = NULL;
			this->setUserName(x.user_name);
			this->user_password = NULL;
			this->user_password = new char[strlen("12345678") + 1];
			strcpy(this->user_password, "12345678");
			this->user_email = NULL;
			this->setUserEmail(x.user_email);
			return *this;
		}
		else return *this;
	}
	bool operator<(const User& u) const
	{
		return this->user_id <  u.user_id;
	}
	User& operator+(char* NewEmail)
	{
		if (this->user_email != NULL)
		{
			delete[] this->user_email;
			this->setUserEmail(NewEmail);
		}
		else throw exception();
	}
	const User operator--(int)
	{
		User temp = *this;
		this->user_nr--;
		return temp;
	}
	explicit operator string()
	{
		string temp, vb;
		int user_name_length, user_password_length;
		user_name_length = 40;
		user_password_length = 30;
		vb = this->user_name; temp.append(vb);
		for (int i = strlen(this->user_name) + 1; i <= user_name_length; i++)
		{
			temp.append(" ");
		}
		temp.append(","); vb.clear();
		vb = this->user_password; temp.append(vb);
		for (int i = strlen(this->user_password) + 1; i <= user_password_length; i++)
		{
			temp.append(" ");
		}
		temp.append(","); vb.clear();
		vb = this->user_email; temp.append(vb); vb.clear();

		return temp;
	}



	virtual ~User()
	{
		if (this->user_name != NULL)
			delete[] this->user_name;
		if (this->user_password != NULL)
			delete[] this->user_password;
		if (this->user_email != NULL)
			delete[] this->user_email;
		User::user_nr--;
	}

	//read from txt file, one object at a time
	void read_from_file(ifstream& input_file)
	{
		if (input_file.is_open())
		{
			input_file >> *this;
		}
		else cout << "Txt read file is not open";
	}
	//write object to binary file
	void write_to_binary_file(fstream& output_file)
	{
		if (output_file.is_open())
		{
			char buffer[40];
			strcpy(buffer, this->user_name);
			output_file.write(buffer, sizeof(buffer));
			strcpy(buffer, "");
			//char buffer2[20];
			strcpy(buffer, this->user_password);
			output_file.write(buffer, sizeof(buffer));
			strcpy(buffer, "");
			//char buffer3[20];
			strcpy(buffer, this->user_email);
			output_file.write(buffer, sizeof(buffer));
		}
		else cout << "Binary write file not open";
	}
	//write inside-object to binary file with increment of nr_crt
	void add_object_to_binary_file()
	{
		fstream binary_file;

		binary_file.open("Backup_users.dat", ios::in | ios::out | ios::binary);
		int no_of_objects_bin = 0;
		if (binary_file.is_open())
		{
			//if the file exists:
			//rewrite the number of elements
			binary_file.seekp(0);
			binary_file.read((char*)&no_of_objects_bin, sizeof(int));
			no_of_objects_bin++;
			binary_file.seekp(0);
			binary_file.write((char*)&no_of_objects_bin, sizeof(int));
			binary_file.close();

			//write this at the end of file
			binary_file.open("Backup_users.dat", ios::binary | ios::out | ios::app);
			if (binary_file.is_open())
			{
				this->write_to_binary_file(binary_file);
			}
			else cout << "BINARY file is not open.";

		}
		else {
			//if file does not exist
			cout << endl << "File will be created" << endl;
			no_of_objects_bin = 1;
			binary_file.open("Backup_users.dat", ios::binary | ios::out);
			binary_file.write((char*)&no_of_objects_bin, sizeof(int));
			this->write_to_binary_file(binary_file);
			binary_file.close();
		}

		binary_file.close();
	}
	//display on screen binary file store data
	void display_binary_file()
	{
		ifstream file4;
		file4.open("Backup_users.dat", ios::in | ios::binary);
		int number4;
		if (file4.is_open()) {
			file4.seekg(0);
			file4.read((char*)&number4, sizeof(int));
			cout << endl << number4 << " data found." << endl;
			User* array = new User[number4];

			for (int i = 0; i < number4; i++) {

				array[i].read_from_binary_file(file4);
				cout << endl << array[i];
			}
			cout << endl << "BINARY file:  imported successfully.";
		}
		file4.close();
	}
	void read_from_binary_file(ifstream& input_file)
	{
		if (input_file.is_open())
		{

			char buffer[40];
			input_file.read((char*)&buffer, sizeof(buffer));
			this->user_name = NULL;
			this->user_name = new char[sizeof(buffer)];
			strcpy(this->user_name, buffer);
			strcpy(buffer, "");
			input_file.read((char*)&buffer, sizeof(buffer));
			this->user_password = NULL;
			this->user_password = new char[sizeof(buffer)];
			strcpy(this->user_password, buffer);
			strcpy(buffer, "");
			input_file.read((char*)&buffer, sizeof(buffer));
			this->user_email = NULL;
			this->user_email = new char[sizeof(buffer)];
			strcpy(this->user_email, buffer);

		}
		else cout << "Binary read file not open";
	}
	void save_txt_to_binary(string path)
	{
		ifstream txt_file;
		fstream binary_file;

		txt_file.open(path, ios::in);
		binary_file.open("Backup_users.dat", ios::in | ios::out | ios::binary);
		int no_of_objects_txt = 0;
		int no_of_objects_bin = 0;

		if (txt_file.is_open())
		{
			txt_file >> no_of_objects_txt;
			User* temp;
			temp = new User[no_of_objects_txt];
			if (binary_file.is_open())
			{
				binary_file.seekp(0);
				binary_file.read((char*)&no_of_objects_bin, sizeof(int));
				no_of_objects_bin += no_of_objects_txt;

				binary_file.seekp(0);
				binary_file.write((char*)&no_of_objects_bin, sizeof(int));
				binary_file.close();
				binary_file.open("Backup_users.dat", ios::binary | ios::out | ios::app);
				if (binary_file.is_open())
				{
					for (int i = 0; i < no_of_objects_txt; i++)
					{
						temp[i].read_from_file(txt_file);
						temp[i].write_to_binary_file(binary_file);

					}
				}
				else cout << "BINARY file is not open.";
			}
			else
			{
				//if the file does not exist 
				cout << endl << "BINARY file will be created." << endl;
				no_of_objects_bin = no_of_objects_txt;
				binary_file.open("Backup_users.dat", ios::binary | ios::out);
				binary_file.write((char*)&no_of_objects_bin, sizeof(int));
				for (int i = 0; i < no_of_objects_bin; i++)
				{
					temp[i].read_from_file(txt_file);
					temp[i].write_to_binary_file(binary_file);
				}
			}
		}
		else cout << "TXT file is not open.";
		txt_file.close();
		binary_file.close();
	}
};
int User::user_nr = 1;
void operator<<(ostream& console, const User& object)
{
	console << endl
		<< object.user_name << ","
		<< object.user_password << ","
		<< object.user_email;
}
istream& operator>>(istream& console, User& object)
{
	string word;

	getline(console, word, ',');
	object.user_name = NULL;
	object.user_name = new char[word.length() + 1];
	strcpy(object.user_name, word.c_str());

	getline(console, word, ',');
	object.user_password = NULL;
	object.user_password = new char[word.length() + 1];
	strcpy(object.user_password, word.c_str());

	getline(console, word, '\n');
	object.user_email = NULL;
	object.user_email = new char[word.length() + 1];
	strcpy(object.user_email, word.c_str());

	return console;
}
bool operator==(const User &object1, const User &object2)
{
	return(object1.user_name == object2.user_name);
}
bool operator!(const User& object1)
{
	return!(object1.user_email || object1.user_id || object1.user_name || object1.user_password);
}
bool operator!=(const User& object1, const User& object2)
{
	return(object1.user_name != object2.user_name && object1.user_password != object2.user_password &&
		object1.user_email != object2.user_email);
}


class User_Log_History : virtual public User
{
private:

	date * log_date;
	vector <int> activity;
	date_time* start_session;
	date_time* end_sesion;

	date* current_date;
	friend istream& operator>>(istream& console, User_Log_History& object);
	friend void operator<<(ostream& console, const User_Log_History& object);
	friend bool operator==(const User_Log_History &object1, const User_Log_History &object2);
	friend bool operator!(User_Log_History& object1);


public:
	User_Log_History() :User()
	{
		this->current_date = new date();
		this->current_date = get_current_date();
		this->log_date = new date();
		this->log_date = get_current_date();
		this->start_session = new date_time();
		this->start_session->setDate(this->log_date);
		this->end_sesion = new date_time();
		this->end_sesion->setDate(this->log_date);

	}
	User_Log_History(char* user_name, char* user_password, char* user_email, vector <int> Activity) :User(user_name, user_password, user_email)
	{
		this->current_date = new date();
		this->current_date = get_current_date();
		this->log_date = new date();
		this->log_date = get_current_date();
		this->start_session = new date_time();
		this->start_session->setDate(this->log_date);
		this->end_sesion = new date_time();
		this->end_sesion->setDate(this->log_date);
		for (int i = 0; i < Activity.size(); i++)
		{
			this->activity.push_back(Activity[i]);
		}

	}
	User_Log_History(const User_Log_History& object) :User(object)
	{
		this->log_date = NULL;
		this->log_date = new date(object.log_date->getDD(), object.log_date->getMM(), object.log_date->getYYYY());
		this->setActivity(object.activity);
		this->current_date = new date();
		this->current_date = get_current_date();
		this->start_session = new date_time();
		this->start_session->setDate(this->log_date);
		this->end_sesion = new date_time();
		this->end_sesion->setDate(this->log_date);
	}

	date* get_current_date()
	{
		int Day;
		int Month;
		int Year;

		time_t now = time(0);
		tm *ltm = localtime(&now);
		Day = ltm->tm_mday;
		Month = 1 + ltm->tm_mon;
		Year = 1900 + ltm->tm_year;

		this->current_date = new date();
		current_date->setDD(Day);
		current_date->setMM(Month);
		current_date->setYYYY(Year);

		return this->current_date;
	}
	date* getLogDate()
	{
		return this->log_date;
	}
	string getActivity()
	{
		string temp;
		string convert;
		vector<int>::iterator it;
		for (it = activity.begin(); it != activity.end(); it++)
		{
			convert = to_string(*it);
			temp.append(convert);
			convert.clear();
			if (it != activity.end())
				temp.append(" - ");
		}
		return temp;
	}
	date_time* getStartSession()
	{
		return this->start_session;
	}
	date_time* getEndSession()
	{
		return this->end_sesion;
	}

	void setLogDate(date* inputDate)
	{
		if (inputDate == NULL)
			throw exception();
		else
		{
			this->log_date = NULL;
			this->log_date = new date(inputDate->getDD(), inputDate->getMM(), inputDate->getYYYY());
		}

	}
	void setActivity(vector<int> A)
	{
		this->activity.clear();
		for (int i = 0; i<A.size(); i++)
		{
			activity.push_back(A.at(i));
		}
	}
	void addActivity(int number)
	{
		if (number>0)
			this->activity.push_back(number);
		else throw exception();
	}
	void setStartSession(date_time& d)
	{
		if (&d == NULL)
			throw exception();
		else
		{
			this->start_session = NULL;
			this->start_session = new date_time(d.getHour(), d.getMinute());
		}
	}
	void setEndSession(date_time& d)
	{
		if (&d == NULL)
			throw exception();
		else
		{
			this->end_sesion = NULL;
			this->end_sesion = new date_time(d.getHour(), d.getMinute());

		}
	}


	//read from txt file, one object at a time
	void read_from_file(ifstream& input_file)
	{
		if (input_file.is_open())
		{
			input_file >> *this;
		}
		else cout << "Txt read file is not open for user_log_history";
	}
	void read_from_file(string path)
	{
		ifstream input_file;
		input_file.open(path, ios::in);
		if (input_file.is_open())
		{
			input_file >> *this;
		}
		else cout << "Txt read file is not open for user_log_history";
	}
	//write object to binary file
	void write_to_binary_file(fstream& output_file)
	{
		int day, month, year;
		if (output_file.is_open())
		{
			User& temp = *this;
			//write user part
			{
				char buffer[40];
				strcpy(buffer, temp.getUserName());
				output_file.write(buffer, sizeof(buffer));
				strcpy(buffer, "");
				strcpy(buffer, temp.getUserPassword());
				output_file.write(buffer, sizeof(buffer));
				strcpy(buffer, "");
				strcpy(buffer, temp.getUserEmail());
				output_file.write(buffer, sizeof(buffer));
			}
			day = this->log_date->getDD();
			month = this->log_date->getMM();
			year = this->log_date->getYYYY();
			output_file.write((char*)&day, sizeof(int));
			output_file.write((char*)&month, sizeof(int));
			output_file.write((char*)&year, sizeof(int));

			int h = this->start_session->getHour();
			output_file.write((char*)&h, sizeof(int));
			int m = this->start_session->getMinute();
			output_file.write((char*)&m, sizeof(int));
			h = this->end_sesion->getHour();
			output_file.write((char*)&h, sizeof(int));
			m = this->end_sesion->getMinute();
			output_file.write((char*)&m, sizeof(int));

			int dim = this->activity.size();
			output_file.write((char*)&dim, sizeof(int));
			for (int i = 0; i < this->activity.size(); i++)
			{
				output_file.write((char*)&this->activity[i], sizeof(int));
			}

		}
		else cout << "Binary write file not open for user_log_history";
	}
	//write inside-object to binary file with increment of nr_crt
	void add_object_to_binary_file()
	{
		fstream binary_file;

		binary_file.open("Backup_user_log_history.dat", ios::in | ios::out | ios::binary);
		int no_of_objects_bin = 0;
		if (binary_file.is_open())
		{
			//if the file exists:
			//rewrite the number of elements
			binary_file.seekp(0);
			binary_file.read((char*)&no_of_objects_bin, sizeof(int));
			no_of_objects_bin++;
			binary_file.seekp(0);
			binary_file.write((char*)&no_of_objects_bin, sizeof(int));
			binary_file.close();

			//write this at the end of file
			binary_file.open("Backup_user_log_history.dat", ios::binary | ios::out | ios::app);
			if (binary_file.is_open())
			{
				this->write_to_binary_file(binary_file);
			}
			else cout << "BINARY file is not open for user_log_history.";

		}
		else {
			//if file does not exist

			no_of_objects_bin = 1;
			binary_file.open("Backup_user_log_history.dat", ios::binary | ios::out);
			binary_file.write((char*)&no_of_objects_bin, sizeof(int));
			this->write_to_binary_file(binary_file);
			binary_file.close();
		}

		binary_file.close();
	}
	//display on screen binary file store data
	void display_binary_file()
	{
		ifstream file4;
		file4.open("Backup_user_log_history.dat", ios::in | ios::binary);
		int number4;
		if (file4.is_open()) {
			file4.seekg(0);
			file4.read((char*)&number4, sizeof(int));
			cout << endl << number4 << " data found." << endl;

			list<User_Log_History> user_history_list;
			list<User_Log_History>::iterator it;
			User_Log_History u;
			for (int i = 0; i < number4; i++)
			{
				u.read_from_binary_file(file4);
				user_history_list.push_back(u);
				cout << u;
			}
			cout << endl << "BINARY file:  imported successfully.";
		}
		file4.close();
	}
	void read_from_binary_file(ifstream& input_file)
	{
		if (input_file.is_open())
		{
			int Day, Month, Year;
			User& temp = *this;
			{
				char buffer[40];
				input_file.read((char*)&buffer, sizeof(buffer));
				temp.setUserName(buffer);
				strcpy(buffer, "");
				input_file.read((char*)&buffer, sizeof(buffer));
				temp.setUserPassword(buffer);
				strcpy(buffer, "");
				input_file.read((char*)&buffer, sizeof(buffer));
				temp.setUserEmail(buffer);
			}

			input_file.read((char*)&Day, sizeof(int));
			input_file.read((char*)&Month, sizeof(int));
			input_file.read((char*)&Year, sizeof(int));
			this->log_date = NULL;
			this->log_date = new date(Day, Month, Year);
			this->start_session = NULL;
			this->end_sesion = NULL;
			this->start_session = new date_time();
			this->end_sesion = new date_time();
			this->start_session->setDate(this->log_date);
			this->end_sesion->setDate(this->log_date);
			int a, b, c, d;
			input_file.read((char*)&a, sizeof(int)); this->start_session->setHour(a);
			input_file.read((char*)&b, sizeof(int)); this->start_session->setMinute(b);
			input_file.read((char*)&c, sizeof(int)); this->end_sesion->setHour(c);
			input_file.read((char*)&d, sizeof(int)); this->end_sesion->setMinute(d);

			int dim, value;
			input_file.read((char*)&dim, sizeof(int));
			if (dim >= 0)
			{
				this->activity.clear();
				for (int i = 0; i < dim; i++)
				{
					input_file.read((char*)&value, sizeof(int));
					activity.push_back(value);
				}
			}
			else throw exception();

		}
		else cout << "Binary read file not open for user_log_history";
	}
	void save_txt_to_binary(string path)
	{
		ifstream txt_file;
		fstream binary_file;

		txt_file.open(path, ios::in);
		binary_file.open("Backup_user_log_history.dat", ios::in | ios::out | ios::binary);
		int no_of_objects_txt = 0;
		int no_of_objects_bin = 0;

		if (txt_file.is_open())
		{
			txt_file >> no_of_objects_txt;
			User_Log_History* temp;
			temp = new User_Log_History[no_of_objects_txt];
			if (binary_file.is_open())
			{
				binary_file.seekp(0);
				binary_file.read((char*)&no_of_objects_bin, sizeof(int));
				no_of_objects_bin += no_of_objects_txt;

				binary_file.seekp(0);
				binary_file.write((char*)&no_of_objects_bin, sizeof(int));
				binary_file.close();
				binary_file.open("Backup_user_log_history.dat", ios::binary | ios::out | ios::app);
				if (binary_file.is_open())
				{
					for (int i = 0; i < no_of_objects_txt; i++)
					{
						temp[i].read_from_file(txt_file);
						temp[i].write_to_binary_file(binary_file);

					}
				}
				else cout << "BINARY file is not open for user_log_history.";
			}
			else
			{
				//if the file does not exist 

				no_of_objects_bin = no_of_objects_txt;
				binary_file.open("Backup_user_log_history.dat", ios::binary | ios::out);
				binary_file.write((char*)&no_of_objects_bin, sizeof(int));
				for (int i = 0; i < no_of_objects_bin; i++)
				{
					temp[i].read_from_file(txt_file);
					temp[i].write_to_binary_file(binary_file);
				}
			}
		}
		else cout << "TXT file is not open for user_log_history.";
		txt_file.close();
		binary_file.close();
	}


	~User_Log_History()
	{
		if (this->log_date != NULL)
			delete[] this->log_date;
		if (this->current_date != NULL)
			delete[] this->current_date;
	}

	using User::operator=;
	User_Log_History& operator=(User_Log_History& u)
	{
		const User temp = u;
		operator=(temp);
		if (*this != u)
		{
			this->setLogDate(u.log_date);
			this->setActivity(u.activity);
			this->setStartSession(*u.start_session);
			this->setEndSession(*u.end_sesion);

			return *this;

		}
		else return *this;
	}
	User_Log_History& operator+(int Code)
	{
		if (Code >= 0)
		{
			this->addActivity(Code);
		}
		else throw exception();
	}
	bool operator>(const User_Log_History& u) const
	{
		this->log_date > u.log_date;
	}
	const User_Log_History operator++(int)
	{
		User_Log_History temp = *this;
		this->end_sesion++;
		return temp;
	}
	explicit operator string()
	{
		string str, vb;

		date_time* dt = new date_time();
		date_time* ss = new date_time(); *ss = this->getStartSession();
		date_time* es = new date_time(); *es = this->getEndSession();

		*dt = (*es - *ss);


		vb = this->getUserName(); str.append(vb); vb.clear();
		if (strlen(this->getUserName()) <= 40)
		{
			for (int i = strlen(this->getUserName()) + 1; i <= 40; i++)
				str.append(" ");
		}
		str.append("-      ");
		vb = to_string(this->getStartSession()->getHour()); str.append(vb); vb.clear(); str.append(":");
		vb = to_string(this->getStartSession()->getMinute()); str.append(vb); vb.clear(); str.append("      -     ");
		vb = to_string(this->getEndSession()->getHour()); str.append(vb); vb.clear();  str.append(":");
		vb = to_string(this->getEndSession()->getMinute()); str.append(vb); vb.clear(); str.append("     -    ");
		vb = to_string(dt->getHour()); str.append(vb); str.append(":");
		vb = to_string(dt->getMinute()); str.append(vb); vb.clear();

		delete[] dt;
		delete[] ss;
		delete[] es;
		return str;
	}

	string SessionDuration()
	{
		date_time* dt = new date_time();
		date_time* ss = new date_time(); *ss = this->getStartSession();
		date_time* es = new date_time(); *es = this->getEndSession();

		*dt = (*es - *ss);
		string duration, temp;
		temp = to_string(dt->getHour()); duration.append(temp);
		if (dt->getHour() == 0)
			duration.append("0");
		duration.append("h:"); temp.clear();
		if (dt->getMinute() / 10 == 0)
		{
			//only one digit
			duration.append("0");
		}
		temp = to_string(dt->getMinute());
		duration.append(temp);

		duration.append("m");

		delete[] dt;
		delete[] ss;
		delete[] es;
		return duration;
	}
};
istream& operator>>(istream& console, User_Log_History& object)
{
	string word;
	User& x = object;
	int d, m, y;
	date* inputDate = new date();
	int elements, value;
	vector<int> v;

	getline(console, word, ',');
	x.setUserName(word);
	getline(console, word, ',');
	x.setUserPassword(word);
	getline(console, word, ',');
	x.setUserEmail(word);
	getline(console, word, '.'); d = stoi(word, nullptr); inputDate->setDD(d);
	getline(console, word, '.'); m = stoi(word, nullptr); inputDate->setMM(m);
	getline(console, word, ','); y = stoi(word, nullptr); inputDate->setYYYY(y);
	if (inputDate)
	{
		object.setLogDate(inputDate);
	}
	else throw exception();
	getline(console, word, ':'); d = stoi(word, nullptr); object.start_session->setHour(d);
	getline(console, word, ','); d = stoi(word, nullptr); object.start_session->setMinute(d);
	getline(console, word, ':'); d = stoi(word, nullptr); object.end_sesion->setHour(d);
	getline(console, word, ','); d = stoi(word, nullptr); object.end_sesion->setMinute(d);
	object.start_session->setDate(object.log_date);
	object.end_sesion->setDate(object.log_date);

	//first read number of elements of vector
	getline(console, word, '|');
	elements = stoi(word, nullptr);
	if (elements != 0)
	{
		for (int i = 0; i < elements; i++)
		{
			if (i < elements - 1)
			{
				getline(console, word, '-');
			}
			else
			{
				getline(console, word, '\n');
			}
			value = stoi(word, nullptr);
			if (value >= 0)
			{
				v.push_back(value);
			}
			else throw exception();
		}
		object.setActivity(v);
	}
}
void operator<<(ostream& console, const User_Log_History& object)
{
	User x = object;
	console << endl << x;
	console << "," << *object.log_date <<
		"," << object.start_session->getHour() <<
		":" << object.start_session->getMinute() <<
		"," << object.end_sesion->getHour() <<
		":" << object.end_sesion->getMinute() <<
		"," << object.activity.size();
	if (object.activity.size() > 0)
	{
		console << "|";
		for (int i = 0; i < object.activity.size(); i++)
		{
			if (i < object.activity.size() - 1)
			{
				console << object.activity[i] << "-";
			}
			else console << object.activity[i];
		}
	}
}
bool operator==(const User_Log_History &object1, const User_Log_History &object2)
{
	return(object1.log_date == object2.log_date);
}
bool operator!(User_Log_History& object1)
{
	return!(object1.getUserEmail() || object1.getUserId() || object1.getUserName() || object1.getUserPassword()
		|| object1.log_date || object1.start_session || object1.end_sesion);
}

class Report {

public:
	Report()
	{

	}
	void TotalReport(ofstream& file)
	{
		float AllocationArray[7]; int pozAllArr = 0;
		float ExpensesArray[7];   int pozExpArr = 0;
		for (int i = 0; i < 6; i++)
		{
			AllocationArray[i] = 0;
			ExpensesArray[i] = 0;
		}
		ifstream budget_allocation;
		ifstream expenses;
		ifstream employee_expenses;
		budget_allocation.open("Backup_budget_allocation.dat", ios::in | ios::binary);
		int number_of_entries;
		budget_allocation.read((char*)&number_of_entries, sizeof(int));
		for (int i = 0; i < number_of_entries; i++)
		{
			budgetAllocation* B_A_object = new budgetAllocation();
			B_A_object->read_from_binary_file(budget_allocation);
			pozAllArr = B_A_object->getDepartmentId() / 100;
			AllocationArray[pozAllArr - 1] += B_A_object->getAmount();
			B_A_object->~budgetAllocation();
		}
		budget_allocation.close();
		number_of_entries = 0;
		expenses.open("Backup_expenses.dat", ios::in | ios::binary);
		expenses.read((char*)&number_of_entries, sizeof(int));
		for (int i = 0; i < number_of_entries; i++)
		{
			Expenses* E_object = new Expenses();
			E_object->read_from_binary_file(expenses);
			pozExpArr = E_object->getDepartment_Id() / 100;
			ExpensesArray[pozExpArr - 1] += E_object->getAmount();
			E_object->~Expenses();
		}
		expenses.close();
		number_of_entries = 0;
		employee_expenses.open("Backup_employees.dat", ios::in | ios::binary);
		employee_expenses.read((char*)&number_of_entries, sizeof(int));
		for (int i = 0; i < number_of_entries; i++)
		{
			Employee* EMP_object = new Employee();
			EMP_object->read_from_binary_file(employee_expenses);
			pozExpArr = EMP_object->getDepartment_Id() / 100;
			ExpensesArray[pozExpArr - 1] += (EMP_object->getAmount() + EMP_object->getSubsidy());
			EMP_object->~Employee();
		}
		employee_expenses.close();

		float SUM_ALL = 0;
		float SUM_EXP = 0;
		float SUM_EMP = 0;

		if (file.is_open())
		{
			file << "-----TOTAL REPORT EXPENSES-----" << endl << endl;
			file << endl << "Total Budget Allocation: " << endl;
			for (int i = 0; i < 6; i++)
			{
				file << endl << "Dep " << (i + 1) * 100 << ": " << AllocationArray[i];
			}
			file << endl << "Total Expenses(without employees): " << endl;
			for (int i = 0; i < 4; i++)
			{
				file << endl << "Dep " << (i + 1) * 100 << ": " << ExpensesArray[i];
			}
			file << endl << "Dep " << 600 << ": " << ExpensesArray[5];
			file << endl << "Total Employee Expenses: " << endl;
			file << endl << "Dep " << 500 << ": " << ExpensesArray[4];
			file << endl << endl << "GRAND TOTAL ON EACH DEPARTMENT: " << endl;
			for (int i = 0; i < 6; i++)
			{
				file << endl << "Dep " << (i + 1) * 100 << ": " << AllocationArray[i] - ExpensesArray[i];
			}
		}
		else cout << "File is not open";
	}
	void AnnualReport(ofstream& file, int YEAR)
	{
		float AllocationArray[7]; int pozAllArr = 0;
		float ExpensesArray[7];   int pozExpArr = 0;
		for (int i = 0; i < 6; i++)
		{
			AllocationArray[i] = 0;
			ExpensesArray[i] = 0;
		}

		ifstream budget_allocation;
		ifstream expenses;
		ifstream employee_expenses;
		budget_allocation.open("Backup_budget_allocation.dat", ios::in | ios::binary);
		expenses.open("Backup_expenses.dat", ios::in | ios::binary);
		employee_expenses.open("Backup_employees.dat", ios::in | ios::binary);
		int nr_entr_B_A;
		int nr_entr_EXP;
		int nr_entr_EMP;
		budget_allocation.read((char*)&nr_entr_B_A, sizeof(int));
		expenses.read((char*)&nr_entr_EXP, sizeof(int));
		employee_expenses.read((char*)&nr_entr_EMP, sizeof(int));

		for (int i = 0; i<nr_entr_B_A; i++)
		{
			budgetAllocation* B_A_object = new budgetAllocation();
			B_A_object->read_from_binary_file(budget_allocation);

			if (YEAR == B_A_object->getDate()->getYYYY())
			{
				pozAllArr = B_A_object->getDepartmentId() / 100;
				AllocationArray[pozAllArr - 1] += B_A_object->getAmount();
			}
			B_A_object->~budgetAllocation();
		}
		for (int i = 0; i<nr_entr_EXP; i++)
		{
			Expenses* EXP_object = new Expenses();
			EXP_object->read_from_binary_file(expenses);
			if (YEAR == EXP_object->getDate()->getYYYY())
			{
				pozExpArr = EXP_object->getDepartment_Id() / 100;
				ExpensesArray[pozExpArr - 1] += EXP_object->getAmount();
			}
			EXP_object->~Expenses();
		}
		for (int i = 0; i<nr_entr_EMP; i++)
		{
			Employee* EMP_object = new Employee();
			EMP_object->read_from_binary_file(employee_expenses);
			if (YEAR == EMP_object->getDate()->getYYYY())
			{
				pozExpArr = EMP_object->getDepartment_Id() / 100;
				ExpensesArray[pozExpArr - 1] += (EMP_object->getAmount() + EMP_object->getSubsidy());
			}
			EMP_object->~Employee();
		}


		//afisare in fisier
		if (file.is_open())
		{
			file << "-----TOTAL -YEAR- EXPENSES-----" << endl << endl;
			file << endl << "Total -Year- Budget Allocation: " << endl;
			for (int i = 0; i < 6; i++)
			{
				file << endl << "Dep " << (i + 1) * 100 << ": " << AllocationArray[i];
			}
			file << endl << "Total -Year- Expenses(without employees): " << endl;
			for (int i = 0; i < 4; i++)
			{
				file << endl << "Dep " << (i + 1) * 100 << ": " << ExpensesArray[i];
			}
			file << endl << "Dep " << 600 << ": " << ExpensesArray[5];
			file << endl << "Total -Year- Employee Expenses: " << endl;
			file << endl << "Dep " << 500 << ": " << ExpensesArray[4];
			file << endl << endl << "GRAND -YEAR- TOTAL ON EACH DEPARTMENT: " << endl;
			for (int i = 0; i < 6; i++)
			{
				file << endl << "Dep " << (i + 1) * 100 << ": " << AllocationArray[i] - ExpensesArray[i];
			}
		}
		else cout << "File is not open";


		budget_allocation.close();
		expenses.close();
		employee_expenses.close();
	}
	void DepartmentReport(ofstream& file, int dep_id)
	{
		ifstream budget_allocation;
		ifstream expenses;
		ifstream employee_expenses;
		budget_allocation.open("Backup_budget_allocation.dat", ios::in | ios::binary);
		expenses.open("Backup_expenses.dat", ios::in | ios::binary);
		employee_expenses.open("Backup_employees.dat", ios::in | ios::binary);
		float SUM_B_A = 0; int nr_entr_B_A;
		float SUM_EXP = 0; int nr_entr_EXP;
		float SUM_EMP = 0; int nr_entr_EMP;
		budget_allocation.read((char*)&nr_entr_B_A, sizeof(int));
		expenses.read((char*)&nr_entr_EXP, sizeof(int));
		employee_expenses.read((char*)&nr_entr_EMP, sizeof(int));
		for (int i = 0; i<nr_entr_B_A; i++)
		{
			budgetAllocation* B_A_object = new budgetAllocation();
			B_A_object->read_from_binary_file(budget_allocation);

			if ((dep_id / 100) == (B_A_object->getDepartmentId() / 100))
			{
				SUM_B_A += B_A_object->getAmount();
			}
			B_A_object->~budgetAllocation();
		}
		for (int i = 0; i<nr_entr_EXP; i++)
		{
			Expenses* EXP_object = new Expenses();
			EXP_object->read_from_binary_file(expenses);
			if ((dep_id / 100) == (EXP_object->getDepartment_Id() / 100))
			{
				SUM_EXP += EXP_object->getAmount();
			}
			EXP_object->~Expenses();
		}
		for (int i = 0; i<nr_entr_EMP; i++)
		{
			Employee* EMP_object = new Employee();
			EMP_object->read_from_binary_file(employee_expenses);
			if ((dep_id / 100) == (EMP_object->getDepartment_Id() / 100))
			{
				SUM_EMP += EMP_object->getAmount() + EMP_object->getSubsidy();
			}
			EMP_object->~Employee();
		}
		if (file.is_open())
		{
			file << "-----TOTAL -DEPARTMENT " << dep_id << "- EXPENSES-----" << endl << endl;
			file << endl << "Total -DEPARTMENT " << dep_id << "- Budget Allocation: " << SUM_B_A;
			file << endl << "Total -DEPARTMENT " << dep_id << "- Expenses(without employees): " << SUM_EXP;
			file << endl << "Total -DEPARTMENT " << dep_id << "- Employee Expenses: " << SUM_EMP;
			file << endl << endl << "GRAND -DEPARTMENT " << dep_id << "- TOTAL: " << SUM_B_A - SUM_EXP - SUM_EMP;
			if ((SUM_B_A - SUM_EXP - SUM_EMP)<0)
			{
				file << endl << endl << "You are on minus with department " << dep_id;
			}
			else file << endl << endl << "Good job. Profit is on the way.";
		}
		else cout << "File is not open";

	}
	void UserReport(ofstream& file)
	{
		//display the data with all users
		ifstream users;
		users.open("Backup_users.dat", ios::in | ios::binary);
		int nr_entr_users = 0;
		users.read((char*)&nr_entr_users, sizeof(int));

		if (file.is_open())
		{
			file << endl << endl << "-----------USER REPORT-----------";

			set<User> user_set_objects;
			set<User>::iterator it;

			User object;
			for (int i = 0; i < nr_entr_users; i++)
			{
				object.read_from_binary_file(users);
				user_set_objects.insert(object);
			}
			for (it = user_set_objects.begin(); it != user_set_objects.end(); it++)
			{
				file << *it;
			}
		}
		else cout << "File is not open.";

		users.close();
	}

	//--------for user activity---------
	//report on access code
	//report on time spent in application
	//--------for user activity---------
	void UserActivityReport(ofstream& file)
	{
		ifstream user_history;
		user_history.open("Backup_user_log_history.dat", ios::in | ios::binary);
		int nr_entr_users = 0;
		user_history.read((char*)&nr_entr_users, sizeof(int));

		if (file.is_open())
		{
			file << endl << endl << "-----------USER ACTIVITY REPORT-----------";
			file << endl << "--User--        --Log Date--        --Access codes--";
			for (int i = 0; i < nr_entr_users; i++)
			{
				User_Log_History* u = new User_Log_History();
				u->read_from_binary_file(user_history);
				date *D = new date();
				D = u->getLogDate();
				string dt = (string)*D;
				file << endl << u->getUserName() << "     -   " << dt << "    -     " << u->getActivity();
				u->~User_Log_History();
			}
		}
		else throw exception();

	}
	void UserActiveTime(ofstream& file)
	{

		ifstream user_history;
		user_history.open("Backup_user_log_history.dat", ios::in | ios::binary);
		int nr_entr_users = 0;
		user_history.read((char*)&nr_entr_users, sizeof(int));

		if (file.is_open())
		{
			file << endl << endl << "----------------------------------USER ACTIVITY REPORT----------------------------------" << endl << endl;
			file << endl << "                --User--                 --Start Session-- --End Session-- --ActiveTime--";

			map<int, string> USER_MAP;

			for (int i = 0; i < nr_entr_users; i++)
			{
				string s;
				User_Log_History* u = new User_Log_History();
				u->read_from_binary_file(user_history);
				s = (string)*u;
				USER_MAP[i] = s;
				u->~User_Log_History();
			}


			for (int i = 0; i<nr_entr_users; i++)
			{
				file << endl << USER_MAP[i];
			}

		}
		else throw exception();
	}

	//display on screen txt report
	void display_txt_report(ifstream& file)
	{
		if (file.is_open())
		{
			char buffer[200];
			//read and write all file on screen
			while (!file.eof())
			{
				file.getline(buffer, 200);
				cout << endl << buffer;
				strcpy(buffer, "");
			}
		}
		else cout << "File is not open";
	}
};

void main()
{
	Transactions** t = new Transactions*[3];

	budgetAllocation* p1 = new budgetAllocation();
	Expenses* p2 = new Expenses();
	Employee* p3 = new Employee();
	User* p4 = new User();
	User_Log_History* p5 = new User_Log_History();
	Report* r1 = new Report();
	t[0] = p1;
	t[1] = p2;
	t[2] = p3;

	date_time* dt = new date_time();
	p5->get_current_date();
	int code_selection = 0;


	char* USER_NAME = new char[30];
	char* PASSWORD = new char[30];
	char* EMAIL = new char[30];

	char user_n[30];
	char user_p[30];
	char user_e[30];

	ifstream bin;
	bin.open("Backup_users.dat", ios::in, ios::binary);
	int nr, var;
	var = 0;
	if (bin.is_open())
	{
		bin.read((char*)&nr, sizeof(int));
		if (nr == 0)
			p4->add_object_to_binary_file();
		else
		{
			for (int j = 0; j < nr; j++)
			{
				User* temp = new User();
				temp->read_from_binary_file(bin);
				if (strcmp(p4->getUserName(), temp->getUserName()))
				{
					//not the same 
					var = 1;
				}
				temp->~User();
			}	
		}
	}

	bin.close();
	if(var==1)
           p4->add_object_to_binary_file();
	cout << endl << "Welcome!";
	cout << endl << "Do you want to log in?(yes/no)" << endl;


	char user_choice[4];
	cin.getline(user_choice, 4);
	if (!strcmp(user_choice, "yes"))
	{
		cout << endl << endl << "Do you have an existing account?(yes/no)" << endl;
		strcpy(user_choice, "");
		cin.getline(user_choice, 4);
		//iff different than yes and no throw exc
		if (strcmp(user_choice, "yes") && strcmp(user_choice, "no"))
			throw new exception();
		else
		{
			if (!strcmp(user_choice, "yes"))
			{
				cout << endl << "user_name: " << endl;
				cin.getline(user_n, 30);
				//open user backup file

				ifstream user_file;
				user_file.open("Backup_users.dat", ios::binary | ios::in);

				int nr_crit;
				user_file.read((char*)&nr_crit, sizeof(int));
				int val = 0; int i = 0;


				User* usr2 = new User();
				while (val == 0 && i < nr_crit)
				{

					User* usr = new User();
					usr->read_from_binary_file(user_file);
					//if found in backup file
					if (!strcmp(usr->getUserName(), user_n))
					{
						val = 1;
						usr2->setUserName(usr->getUserName());
						usr2->setUserPassword(usr->getUserPassword());
						usr2->setUserEmail(usr->getUserEmail());
					}
					else usr->~User();
					i++;
				}
				//if found in backup file
				if (val == 1)
				{
					//do the next check
					cout << endl << "user_password: " << endl;
					cin.getline(user_p, 30);

					if (!strcmp(usr2->getUserPassword(), user_p))
					{
						cout << endl << "Log in: success" << endl;
						//add usr2 located in backup to history data file with increment of objects
						//name,password,email,current time,00:00,activity 0

						p5->setUserName(usr2->getUserName());
						p5->setUserEmail(usr2->getUserEmail());
						p5->setUserPassword(usr2->getUserPassword());
						p5->setLogDate(p5->get_current_date());
						dt->getCurrentTime();
						p5->setStartSession(*dt);

						//type code
						while (code_selection != 6)
						{
							cout << endl << endl << endl << "What do you want to do today?" << endl;
							cout << endl << "1 --- Add new expenses(input text file) into database";
							cout << endl << "2 --- Add new expenses(input keyboard) into database";
							cout << endl << "3 --- Display existing data from database";
							cout << endl << "4 --- Search for data in database";
							cout << endl << "5 --- Create report";
							cout << endl << "6 --- Exit the program" << endl;

							cin >> code_selection;
							if (code_selection == 1)
							{
								p5->addActivity(code_selection);
								cout << endl << endl << "Choose expense category:";
								cout << endl << "7 --- Budget Allocation";
								cout << endl << "8 --- General Expenses";
								cout << endl << "9 --- Employee Expenses" << endl;
								cin >> code_selection;

								string file_path;
								cout << endl << endl << "Insert the full path of file:" << endl;
								cin.ignore(1, '\n');
								getline(cin, file_path, '\n');

								if (code_selection == 7)
								{

									p5->addActivity(code_selection);
									//insert full path of file
									t[0]->save_txt_to_binary(file_path);
									cout << endl << "Success." << endl;
								}
								else
									if (code_selection == 8)
									{
										p5->addActivity(code_selection);
										t[1]->save_txt_to_binary(file_path);
										cout << endl << "Success." << endl;
									}
									else
										if (code_selection == 9)
										{
											p5->addActivity(code_selection);
											t[2]->save_txt_to_binary(file_path);
											cout << endl << "Success." << endl;
										}
										else
										{
											throw new exception("Invalid choice");
										}
								cout << endl;
								code_selection = 1;
							}
							else if (code_selection == 2)
							{
								p5->addActivity(code_selection);
								//add new expenses from keyboard
								cout << endl << endl << "Choose expense category:";
								cout << endl << "7 --- Budget Allocation";
								cout << endl << "8 --- General Expenses";
								cout << endl << "9 --- Employee Expenses" << endl;
								cin >> code_selection;
								if (code_selection == 7)
								{
									p5->addActivity(code_selection);
									budgetAllocation* BA = new budgetAllocation();
									int day = 0;
									int month = 0;
									int year = 0;
									date* temp_date = new date();


									cout << endl << "Input department id( check the department code list first): ";
									int dep_id;
									cin >> dep_id;
									BA->setDepartmentId(dep_id);

									cout << endl << "Input name: ";
									char* name = new char[30];
									cin.getline(name, 30);
									if (!strcmp(name, ""))
									{
										cin.getline(name, 30);
									}
									BA->setTitle(name);

									cout << endl << "Date(dd,mm,yyyy)" << endl;
									cin >> day;  temp_date->setDD(day);
									cin >> month; temp_date->setMM(month);
									cin >> year; temp_date->setYYYY(year);
									BA->setBudgetDate(temp_date);

									cout << endl << "Input amount: ";
									float amt;
									cin >> amt;
									BA->setAllocatedAmount(amt);


									BA->getCurrent_date();

									//add to expenses: budgetAllocation
									BA->add_object_to_binary_file();
									cout << endl << "Expense has been added." << endl;
									delete[] temp_date;
									delete[] name;
									cout << endl;
								}
								else
									if (code_selection == 8)
									{
										p5->addActivity(code_selection);
										Expenses* EXP = new Expenses();
										date* inputDate = new date();
										int d, m, y;


										cout << endl << "Input department id( check the department code list first): ";
										int depp_id;
										cin >> depp_id;
										EXP->setDepartment_Id(depp_id);

										cout << endl << "Input title: ";
										char* TITLE = new char[30];
										cin.getline(TITLE, 30);
										if (!strcmp(TITLE, ""))
										{
											cin.getline(TITLE, 30);
										}
										EXP->setTitle(TITLE);

										cout << endl << "Input date(dd mm yyyy)" << endl;
										cin >> d;	inputDate->setDD(d);
										cin >> m;	inputDate->setMM(m);
										cin >> y;   inputDate->setYYYY(y);
										if (inputDate)
										{
											EXP->setDate(inputDate);
										}
										cout << endl << "Input  amount: ";
										float amount;
										cin >> amount;
										EXP->setAmount(amount);

										EXP->getCurrent_date();

										EXP->add_object_to_binary_file();
										cout << endl << "Expense has been added." << endl;

										delete[] inputDate;
										delete[] TITLE;
										cout << endl;
									}
									else
										if (code_selection == 9)
										{
											p5->addActivity(code_selection);
											Employee* EMP = new Employee();
											date* inputDate = new date();
											int d, m, y;
											cout << endl << "Input department id(500 for employees): ";
											int depp_id;
											cin >> depp_id;
											EMP->setDepartment_Id(depp_id);

											cout << endl << "Input title: ";
											char* TITLE = new char[30];
											cin.getline(TITLE, 30);
											if (!strcmp(TITLE, ""))
											{
												cin.getline(TITLE, 30);
											}
											EMP->setTitle(TITLE);

											cout << endl << "Input date(dd mm yyyy)" << endl;
											cin >> d;	inputDate->setDD(d);
											cin >> m;	inputDate->setMM(m);
											cin >> y;   inputDate->setYYYY(y);
											if (inputDate)
											{
												EMP->setDate(inputDate);
											}
											cout << endl << "Input  amount: ";
											float amount;
											cin >> amount;
											EMP->setAmount(amount);

											EMP->getCurrent_date();
											//employee part

											date* inputHireDate = new date();
											date* inputEndDate = new date();


											cout << endl << "CNP= ";
											char buffer[14];
											cin >> buffer;
											EMP->setCnp(buffer);

											cout << endl << "Employee name: ";
											TITLE = NULL;
											TITLE = new char[30];
											cin.getline(TITLE, 30);
											if (!strcmp(TITLE, ""))
											{
												cin.getline(TITLE, 30);
											}
											EMP->setEmployeeName(TITLE);
											cout << endl << "Hire date(dd,mm,yyyy):" << endl;
											cin >> d;	inputHireDate->setDD(d);
											cin >> m;	inputHireDate->setMM(m);
											cin >> y;   inputHireDate->setYYYY(y);
											if (inputHireDate)
											{
												EMP->setHireDate(inputHireDate);
											}
											cout << endl << "End date(dd,mm,yyyy):" << endl;
											cin >> d;	inputEndDate->setDD(d);
											cin >> m;	inputEndDate->setMM(m);
											cin >> y;   inputEndDate->setYYYY(y);
											if (inputEndDate)
											{
												EMP->setEndDate(inputEndDate);
											}
											cout << endl << "Subsidy float value: ";
											float subs;
											cin >> subs;
											EMP->setSubsidy(subs);

											EMP->add_object_to_binary_file();
											cout << endl << "Expense has been added." << endl;
											delete[] inputDate;
											delete[] inputHireDate;
											delete[] inputEndDate;
											delete[] TITLE;

											cout << endl;
										}
										else throw new exception("Invalid choice");
										cout << endl;
										code_selection = 2;
							}
							else if (code_selection == 3)
							{
								p5->addActivity(code_selection);
								cout << endl << endl << "Choose category:";
								cout << endl << "7 --- Budget Allocation";
								cout << endl << "8 --- General Expenses";
								cout << endl << "9 --- Employee Expenses";
								cout << endl << "10 --- User Data";
								cout << endl << "11 --- User Log History" << endl;

								cin >> code_selection;
								if (code_selection == 7)
								{
									p5->addActivity(code_selection);
									cout << endl;
									t[0]->display_binary_file();
									cout << endl;
								}
								else
									if (code_selection == 8)
									{
										p5->addActivity(code_selection);
										cout << endl;
										t[1]->display_binary_file();
										cout << endl;
									}
									else
										if (code_selection == 9)
										{
											p5->addActivity(code_selection);
											cout << endl;
											t[2]->display_binary_file();
											cout << endl;
										}
										else
											if (code_selection == 10)
											{
												p5->addActivity(code_selection);
												cout << endl;
												p4->display_binary_file();
												cout << endl;
											}
											else
												if (code_selection == 11)
												{
													p5->addActivity(code_selection);
													cout << endl;
													p5->display_binary_file();
													cout << endl;
												}
												else
												{
													throw new exception("Invalid choice");
												}
								cout << endl;
								code_selection = 3;
							}
							else if (code_selection == 4)
							{
								p5->addActivity(code_selection);
								cout << endl << "Please input the date" << endl;
								int d, m, y;
								cin >> d;
								cin >> m;
								cin >> y;
								date* DATE = new date(d, m, y);
								int nr_crt;
								ifstream FILE;
								FILE.open("Backup_budget_allocation.dat", ios::binary | ios::in);
								FILE.read((char*)&nr_crt, sizeof(int));
								cout << endl << "--------BUDGET ALLOCATION--------" << endl;
								for (int i = 0; i < nr_crt; i++)
								{
									budgetAllocation* B_ALL = new budgetAllocation();
									B_ALL->read_from_binary_file(FILE);
									if (B_ALL->getDate()->getDD() == d && B_ALL->getDate()->getMM() == m && B_ALL->getDate()->getYYYY() == y)
									{
										cout << endl << *B_ALL;
									}
									B_ALL->~budgetAllocation();
								}
								FILE.close();
								FILE.open("Backup_expenses.dat", ios::binary | ios::in);
								FILE.read((char*)&nr_crt, sizeof(int));
								cout << endl << "--------EXPENSES--------" << endl;
								for (int i = 0; i < nr_crt; i++)
								{
									Expenses* EXP = new Expenses();
									EXP->read_from_binary_file(FILE);
									if (EXP->getDate()->getDD() == d && EXP->getDate()->getMM() == m && EXP->getDate()->getYYYY() == y)
									{
										cout << endl << *EXP;
									}
									EXP->~Expenses();
								}
								FILE.close();
								FILE.open("Backup_employees.dat", ios::binary | ios::in);
								FILE.read((char*)&nr_crt, sizeof(int));
								cout << endl << "--------EMPLOYEES--------" << endl;
								for (int i = 0; i < nr_crt; i++)
								{
									Employee* EMP = new Employee();
									EMP->read_from_binary_file(FILE);
									if (EMP->getDate()->getDD() == d && EMP->getDate()->getMM() == m && EMP->getDate()->getYYYY() == y)
									{
										cout << endl << *EMP;
									}
									EMP->~Employee();
								}
								FILE.close();

								delete[] DATE;
								code_selection = 4;
								cout << endl;
							}
							else if (code_selection == 5)
							{
								p5->addActivity(code_selection);
								cout << endl << endl << "Choose report category:";
								cout << endl << "10 --- Total Report";
								cout << endl << "11 --- Annual Report";
								cout << endl << "12 --- Department Report";
								cout << endl << "13 --- User Report";
								cout << endl << "14 --- User Activity Report";
								cout << endl << "15 --- User Active Time Report" << endl;
								cin >> code_selection;

								if (code_selection == 10)
								{
									cout << endl << "Please enter the name of the file. Example: 'report_name.txt'" << endl;
									char* input_name = new char[30];
									cin >> input_name;
									ofstream Data_file;
									Data_file.open(input_name, ios::out | ios::trunc);
									r1->TotalReport(Data_file);
									Data_file.close();
									cout << endl << "Txt file has been created. Do you want to display the content?(yes/no)" << endl;
									strcpy(user_choice, "");
									cin.ignore();
									cin.getline(user_choice, 4);
									if (!strcmp(user_choice, "yes"))
									{
										ifstream txt_file;
										txt_file.open(input_name, ios::in);
										r1->display_txt_report(txt_file);
										txt_file.close();
									}
									else
									{
										if (strcmp(user_choice, "no"))
											throw new exception("Invalid choice");
									}
									strcpy(input_name, "");
									delete[] input_name;

								}
								else
									if (code_selection == 11)
									{
										p5->addActivity(code_selection);
										//annual report
										cout << endl << "Please enter the name of the file. Expample: 'report_name.txt'" << endl;
										char* input_name = new char[30];
										cin >> input_name;
										ofstream Data_file;
										Data_file.open(input_name, ios::out | ios::trunc);
										cout << endl << "Type in the year of the report:" << endl;
										int input_year;
										cin >> input_year;
										r1->AnnualReport(Data_file, input_year);
										Data_file.close();
										cout << endl << "Txt file has been created. Do you want to display the content?(yes/no)" << endl;
										strcpy(user_choice, "");
										cin.ignore();
										cin.getline(user_choice, 4);
										if (!strcmp(user_choice, "yes"))
										{
											ifstream txt_file;
											txt_file.open(input_name, ios::in);
											r1->display_txt_report(txt_file);
											cout << endl << endl << "Do you want to realocate money to the next year?(yes/no)" << endl;
											txt_file.close();
											strcpy(user_choice, "");
											//cin.ignore();
											cin.getline(user_choice, 4);
											if (!strcmp(user_choice, "yes"))
											{
												cout << endl << endl << "Choose department(100,200,300,400,500,600):" << endl;
												int dep_choice;
												cin >> dep_choice;
												if (dep_choice == 100 || dep_choice == 200 || dep_choice == 300 || dep_choice == 400 || dep_choice == 500 || dep_choice == 600)
												{
													cout << endl << endl << "Type amount:" << endl;
													float input_amount;
													cin >> input_amount;
													float minus_amount = -input_amount;
													//add a minus budgetAllocation object to bin file on input date
													//add a plus budgetAllocation object to bin file on next date
													date* DATE = new date();
													DATE->setYYYY(input_year);
													char* NAME = new char[strlen("Redistribution") + 1];
													strcpy(NAME, "Redistribution");
													budgetAllocation* object = new budgetAllocation(DATE, dep_choice, NAME, minus_amount);
													object->add_object_to_binary_file();
													int new_year = input_year;
													new_year++;
													DATE->setYYYY(new_year);
													object->setBudgetDate(DATE);
													object->setAllocatedAmount(input_amount);
													object->add_object_to_binary_file();
													//recreate report file
													Data_file.open(input_name, ios::in | ios::trunc);
													r1->AnnualReport(Data_file, input_year);
													cout << endl << "Annual txt report has been altered. Do you want to display it?(yes/no)" << endl;
													strcpy(user_choice, "");
													cin.ignore();
													cin.getline(user_choice, 4);
													if (!strcmp(user_choice, "yes"))
													{
														ifstream txt_file;
														txt_file.open(input_name, ios::in);
														r1->display_txt_report(txt_file);
														txt_file.close();
													}
													else
													{
														if (strcmp(user_choice, "no"))
															throw new exception("Invalid choice");
													}
													object->~budgetAllocation();
													Data_file.close();
												}
												else
												{
													throw new exception("Department not found.");
												}
											}
										}
										else
										{
											if (strcmp(user_choice, "no"))
												throw new exception("Invalid choice");

										}
										strcpy(input_name, "");
										cout << endl;
										delete[] input_name;
									}
									else
										if (code_selection == 12)
										{
											p5->addActivity(code_selection);
											//department report
											cout << endl << "Please enter the name of the file. Expample: 'report_name.txt'" << endl;
											char* input_name = new char[30];
											cin >> input_name;
											ofstream Data_file;
											Data_file.open(input_name, ios::out | ios::trunc);
											cout << endl << "Enter department code(100,200,300,400,500,600):" << endl;
											int dep_code;
											cin >> dep_code;
											r1->DepartmentReport(Data_file, dep_code);
											Data_file.close();
											cout << endl << "Txt file has been created. Do you want to display the content?(yes/no)" << endl;
											strcpy(user_choice, "");
											cin.ignore();
											cin.getline(user_choice, 4);

											if (!strcmp(user_choice, "yes"))
											{
												ifstream txt_file;
												txt_file.open(input_name, ios::in);
												r1->display_txt_report(txt_file);
												txt_file.close();
											}
											else
											{
												if (strcmp(user_choice, "no"))
													throw new exception("Invalid choice");
											}
											strcpy(input_name, "");
											cout << endl;
											delete[] input_name;
										}
										else
											if (code_selection == 13)
											{
												p5->addActivity(code_selection);
												//user report
												cout << endl << "Please enter the name of the file. Expample: 'report_name.txt'" << endl;
												char* input_name = new char[30];
												cin >> input_name;
												ofstream Data_file;
												Data_file.open(input_name, ios::out | ios::trunc);
												r1->UserReport(Data_file);
												Data_file.close();
												cout << endl << "Txt file has been created. Do you want to display the content?(yes/no)" << endl;
												strcpy(user_choice, "");
												cin.ignore();
												cin.getline(user_choice, 4);

												if (!strcmp(user_choice, "yes"))
												{
													ifstream txt_file;
													txt_file.open(input_name, ios::in);
													r1->display_txt_report(txt_file);
													txt_file.close();
												}
												else
												{
													if (strcmp(user_choice, "no"))
														throw new exception("Invalid choice");
												}
												strcpy(input_name, "");
												delete[] input_name;
												cout << endl;
											}
											else
												if (code_selection == 14)
												{
													p5->addActivity(code_selection);
													//user report
													cout << endl << "Please enter the name of the file. Expample: 'report_name.txt'" << endl;
													char* input_name = new char[30];
													cin >> input_name;
													ofstream Data_file;
													Data_file.open(input_name, ios::out | ios::trunc);
													r1->UserActivityReport(Data_file);
													Data_file.close();
													cout << endl << "Txt file has been created. Do you want to display the content?(yes/no)" << endl;
													strcpy(user_choice, "");
													cin.ignore();
													cin.getline(user_choice, 4);

													if (!strcmp(user_choice, "yes"))
													{
														ifstream txt_file;
														txt_file.open(input_name, ios::in);
														r1->display_txt_report(txt_file);
														txt_file.close();
													}
													else
													{
														if (strcmp(user_choice, "no"))
															throw new exception("Invalid choice");
													}
													strcpy(input_name, "");
													delete[] input_name;
													cout << endl;
												}
												else
													if (code_selection == 15)
													{
														p5->addActivity(code_selection);
														//user report
														cout << endl << "Please enter the name of the file. Expample: 'report_name.txt'" << endl;
														char* input_name = new char[30];
														cin >> input_name;
														ofstream Data_file;
														Data_file.open(input_name, ios::out | ios::trunc);
														r1->UserActiveTime(Data_file);
														Data_file.close();
														cout << endl << "Txt file has been created. Do you want to display the content?(yes/no)" << endl;
														strcpy(user_choice, "");
														cin.ignore();
														cin.getline(user_choice, 4);

														if (!strcmp(user_choice, "yes"))
														{
															ifstream txt_file;
															txt_file.open(input_name, ios::in);
															r1->display_txt_report(txt_file);
															txt_file.close();
														}
														else
														{
															if (strcmp(user_choice, "no"))
																throw new exception("Invalid choice");
														}
														strcpy(input_name, "");
														delete[] input_name;
														cout << endl;
													}
													else
														throw new exception("Invalid choice");


								code_selection = 5;
							}


							if (code_selection != 1 && code_selection != 2 && code_selection != 3 && code_selection != 4 && code_selection != 5 && code_selection != 6)
							{
								cout << endl << "Invalid choice" << endl;
							}
							char answer[4];
							cout << endl << "Do you wish to continue?(yes/no):  " << endl;

							cin.getline(answer, 4);
							if (!strcmp(answer, ""))
							{
								cin.getline(answer, 4);
							}

							if (!strcmp(answer, "yes"))
							{
								code_selection = 0;
							}
							else
								if (!strcmp(answer, "no"))
								{
									code_selection = 6;
									p5->addActivity(code_selection);
									dt->getCurrentTime();
									p5->setEndSession(*dt);
									p5->add_object_to_binary_file();
									cout << endl << "End Session. Duration: " << p5->SessionDuration();
								}
								else throw new exception("Invalid choice");
						}

					}
					else
					{
						cout << endl << "Incorrect password";
						//recover password
						cout << endl << "Do you want to recover password?(yes/no)" << endl;
						strcpy(user_choice, "");
						cin.getline(user_choice, 4);
						if (!strcmp(user_choice, "yes"))
						{
							cout << endl << "Recovery email was send to your user email. Please check and come back later." << endl;
							cout << endl << endl << endl << "------------Private Email------------";
							cout << endl << "TO: " << usr2->getUserEmail() << ", FROM: PRODUCT_MARKETING_APP";
							cout << endl << "Hello, " << user_n << "! Your password is " << usr2->getUserPassword() << "." << endl;
							cout << "Bye bye!" << endl;
							cout << "------------Private Email------------" << endl;
						}
						else
							if (strcmp(user_choice, "no"))
								throw new exception("Invalid choice");
					}
				}
				else
				{
					//if not found in backup file
					cout << endl << "There is no user with this user_name" << endl;

					cout << endl << "Do you want to create a new user?(yes/no)" << endl;
					strcpy(user_choice, "");
					cin.getline(user_choice, 4);
					if (!strcmp(user_choice, "yes"))
					{
						cout << endl << "--Default user--";
						cout << endl << "user_name: default_user";
						cout << endl << "user_password: 12345678";
						cout << endl << "user_email: product_marketing@gmail.com";
						cout << endl << "----------------------------------" << endl;

						User* new_user = new User();

						//custom
						cout << endl << endl << "Or create a new one:" << endl;
						cout << endl << "user_name: "; cin >> USER_NAME;
						cout << endl << "user_password: "; cin >> PASSWORD;
						cout << endl << "user_email: "; cin >> EMAIL;
						new_user->setUserName(USER_NAME);
						new_user->setUserPassword(PASSWORD);
						new_user->setUserEmail(EMAIL);
						if (USER_NAME != "default_user")
						{
							cout << endl << "User created." << endl;
							cout << endl << USER_NAME;
							cout << endl << PASSWORD;
							cout << endl << EMAIL;
							new_user->add_object_to_binary_file();
						}
						else {
							cout << endl << "Log in next time." << endl;
						}

						new_user->~User();
					}
					else
					{
						if (strcmp(user_choice, "no"))
						{
							cout << endl << "Invalid choice." << endl;
						}
					}
				}
			}
			if (!strcmp(user_choice, "no"))
			{
				cout << endl << "Do you want to sign up?(yes/no)" << endl;
				strcpy(user_choice, "");
				cin.getline(user_choice, 4);

				if (strcmp(user_choice, "no") && strcmp(user_choice, "yes"))
				{
					cout << endl << "Invalid choice.";
				}
				else
				{
					if (!strcmp(user_choice, "yes"))
					{
						cout << endl << "Do you want to create a new user?(yes/no)" << endl;
						strcpy(user_choice, "");
						cin.getline(user_choice, 4);

						if (!strcmp(user_choice, "yes"))
						{
							User* new_user = new User();
							//custom
							cout << endl << "user_name(min 3 characters long): "; cin >> USER_NAME;
							cout << endl << "user_password(min 5 characters long): "; cin >> PASSWORD;
							cout << endl << "user_email(min 3 characters long): "; cin >> EMAIL;
							new_user->setUserName(USER_NAME);
							new_user->setUserPassword(PASSWORD);
							new_user->setUserEmail(EMAIL);
							if (USER_NAME != "default_user")
							{
								cout << *new_user;
								new_user->add_object_to_binary_file();
							}
							cout << endl << "User created. Please come back later" << endl;
							new_user->~User();
						}
						else
						{
							if (!strcmp(user_choice, "no"))
							{
								cout << endl << "-----------Default user----------";
								cout << endl << "user_name: default_user";
								cout << endl << "user_password: 12345678";
								cout << endl << "user_email: product_marketing@gmail.com";
								cout << endl << "----------------------------------" << endl;
								cout << endl << "Next time use default credentials. Please come back later." << endl;
							}
							if (strcmp(user_choice, "no"))
							{
								cout << endl << "Invalid choice." << endl;
							}

						}
					}
				}
			}

		}
	}
	else
	{
		if (strcmp(user_choice, "no"))
		{
			cout << endl << "Invalid choice.";
		}

		cout << endl << "Do you want to sign up?(yes/no)" << endl;
		strcpy(user_choice, "");
		cin.getline(user_choice, 4);

		if (strcmp(user_choice, "no") && strcmp(user_choice, "yes"))
		{
			cout << endl << "Invalid choice.";
		}
		else
		{
			if (!strcmp(user_choice, "yes"))
			{
				cout << endl << "Do you want to create a new user?(yes/no)" << endl;
				strcpy(user_choice, "");
				cin.getline(user_choice, 4);

				if (!strcmp(user_choice, "yes"))
				{
					User* new_user = new User();
					//custom
					cout << endl << "user_name(min 3 characters long): "; cin >> USER_NAME;
					cout << endl << "user_password(min 5 characters long): "; cin >> PASSWORD;
					cout << endl << "user_email(min 3 characters long): "; cin >> EMAIL;
					new_user->setUserName(USER_NAME);
					new_user->setUserPassword(PASSWORD);
					new_user->setUserEmail(EMAIL);
					if (USER_NAME != "default_user")
					{
						cout << endl << "User created." << endl;
						cout << *new_user;
						new_user->add_object_to_binary_file();
					}
					else
					{
						cout << endl << "Log in successful." << endl;
					}

					new_user->~User();
				}
				else
				{
					if (!strcmp(user_choice, "no"))
					{
						cout << endl << "-----------Default user----------";
						cout << endl << "user_name: default_user";
						cout << endl << "user_password: 12345678";
						cout << endl << "user_email: product_marketing@gmail.com";
						cout << endl << "----------------------------------" << endl;
						cout << endl << "Next time use default credentials. Please come back later." << endl;
					}
					if (strcmp(user_choice, "no"))
					{
						cout << endl << "Invalid choice." << endl;
					}

				}
			}
		}
		//if no, exit program
	}


	p1->~budgetAllocation();
	p2->~Expenses();
	p3->~Employee();
	p4->~User();
	p5->~User_Log_History();

	delete[] t;
	delete[] USER_NAME;
	delete[] PASSWORD;
	delete[] EMAIL;

}

