#pragma once
#include <string>
#include<fstream>
#include<vector>

using namespace std;


class Time
{
public:

	 Time operator +(int min)
	{
		Time sum = Time(this->hour + ((this->minute + min) / 60), (this->minute + min) % 60);

		return sum;
	}

	Time(int hour, int minute)
	{
		try
		{
			if (hour >= 0 && minute >= 0 && hour < 24 && minute < 60)
			{
				this->hour = hour;
				this->minute = minute;
			}
			else
			{
				string ex = "invalid time input";
				throw(ex);
			}
		}
		catch (string ex)
		{
			cout << ex << endl;
		}
		
	}
	bool operator <(Time t1)
	{
		if (t1.hour > this->hour || (this->hour == t1.hour && this->minute < t1.minute))
		{
			return true;
		}
		return false;
	}
	Time()
	{
		hour = 0;
		minute = 0;
	}
	int get_hour()
	{
		return hour;
	}
	int get_minute()
	{
		return minute;
	}
private:
	int hour;
	int minute;

};

class patient
{

public:
	patient(string name, string problem, int level, string day, Time start, Time end, int time_for_treatment) {
		try
		{
			if (level > 0 && level <= 5 && time_for_treatment>0) {
				this->name = name;
				this->day_of_potential_visit = day;
				this->end_of_interval = end;
				this->problem = problem;
				this->start_of_interval = start;
				this->seriousnes = level;
				this->time_for_treatment = time_for_treatment;
			}
			else
			{
				string ex = "invalid input";
				throw(ex);
			}
		}
		catch (string ex)
		{
			cout << ex << endl;
		}
	
	}
	string get_name()
	{
		return this->name;
	}
	int get_level()
	{
		return this->seriousnes;
	}
	string get_problem()
	{
		return this->problem;
	}
	Time get_start()
	{
		return this->start_of_interval;
	}
	Time get_end()
	{
		return this->end_of_interval;
	}
	int get_dur()
	{
		return this->time_for_treatment;
	}
	string get_day()
	{
		return this->day_of_potential_visit;
	}
private:
	string name;
	string problem;
	int seriousnes;
	string day_of_potential_visit;
	Time start_of_interval;
	Time end_of_interval;
	int time_for_treatment;

};

class all_patients
{

public:
	all_patients() {
		
		try {
			int num_pat;
			string name, problem, line, time1, time2;
			int level;
			string day;
			Time start, end;
			int h1, m1, h2, m2, treatment;
			ifstream file;
			file.open("Patients.txt");
			int i = 0;
			file >> num_pat;
			while (file >> name >> problem >> level >> day >> time1 >> time2 >> treatment)
			{
				i++;
				h1 = (time1[0] - '0') * 10 + (time1[1] - '0');
				h2 = (time2[0] - '0') * 10 + (time2[1] - '0');
				m1 = (time1[3] - '0') * 10 + (time1[4] - '0');
				m2 = (time2[3] - '0') * 10 + (time2[4] - '0');
				start = Time(h1, m1);
				end = Time(h2, m2);
				if (end < start)
				{
					string ex = "invalid input of time. your start time is greater than end time. exception detected in patients.txt on line: " + std::to_string(i+1);
					throw(ex);
				}
				if (treatment <= 0 || level < 0 || level>5)
				{
					string ex = "wrong input of treatment time or level on line: "+std::to_string(i+1)+" in patients.txt";
					throw(ex);
				}
				patient tmp = patient(name, problem, level, day, start, end, treatment);
				this->all.push_back(tmp);
				this->number_of_patients++;
			}
			if (num_pat - i != 0)
			{
				string ex = "faulty input not able to read in patients.txt file on line: " + std::to_string(i + 2);
				throw(ex);
			}
			file.close();
		}
		catch(string ex) {
			cout << ex << endl;

		}
	}

	int get_number_of_patients()
	{
		return this->number_of_patients;
	}
	vector<patient> patients() {
		return this->all;
	}
	~all_patients()
	{
		this->all.clear();
	}
private:
	vector<patient> all;
	int number_of_patients = 0;

};

