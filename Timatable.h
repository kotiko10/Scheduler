#pragma once

#include<string>
#include"Doctors.h"
#include "Patients.h"

using namespace std;



class Timatable
{
public:
	Timatable(string*** Table)
	{
		this->Table = Table;
	}
	void change_state(Time& start, Time& Finish, string& day, string& doctor, int & docindex,string &pt_name)
	{
		this->number_of_patients_admitted++;
		int d = this->day(day);
		int st = start.get_hour() * 60 + start.get_minute();
		int fin = Finish.get_hour() * 60 + Finish.get_minute();
		for (int i = st; i <= fin; i++)
		{
			this->Table[d][i][docindex] = pt_name;
		}

	}
	bool check_if_avalaible(Time& start, Time end, int dur, string day, all_doctors& doc, string doctor)
	{
		int d = this->day(day);
		int d1 = doc.get_index_of_doctor(doctor);
		int st = start.get_hour() * 60 + start.get_minute();
		int fin = end.get_hour() * 60 + end.get_minute();
		for (int i = st; i <= fin; i++)
		{
			bool test = true;
			for (int j = i; j <= i + dur; j++)
			{
				string temp = this->Table[d][j][d1];
				if (temp!="open")
				{
					test = false;
					break;
				}
			}
			if (test)
			{
				start = Time((i) / 60, (i) % 60);
				return true;
			}
		}
		return false;
	}
	int day(string& day)
	{
		try
		{
			
			for (int i = 0; i < 7; i++)
			{
				if (day == this->days[i])
				{
					
					return i;
				}
			}
			string ex = "inavlid day";
			throw (ex);
		}
		catch (string ex)
		{
			cout << ex << endl;
		}
		
		
	}

	string day(int &i){
		try {
			return days[i];
		}
		catch (int ex)
		{
			cout<< "error number greater than 7 or less than 0"<<endl;
		}
	}
	string*** readTable()
	{
		return this->Table;
	 }
	string state(int& i, int& j, int& k)
	{
		try
		{
			return Table[i][j][k];
		}
		catch (const std::exception&)
		{
			cout << "out of bounds of the table" << endl;
		}
	}
	~Timatable()
	{
		if (Table[0][0][0] != "")
		{
			cout << "Table is destructed" << endl;
			for (int i = 0; i < 7; i++)
			{
				for (int j = 0; j < 1440; j++)
				{
					delete[] this->Table[i][j];
				}
				delete[] this->Table[i];
			}
			delete[] this->Table;
		}
	}
private:
	int number_of_patients_admitted = 0;
	string days[7] = { "Mon", "Tue","Wed","Thu","Fri","Sat","Sun" };
	string*** Table;
	
	
};


static class Function_dump
{
public:
	static void destroy_tabale(string *** &Table) {
		
			for (int i = 0; i < 7; i++)
			{
				for (int j = 0; j < 1440; j++)
				{
					delete[] Table[i][j];
				}
				delete[] Table[i];
			}
			delete[] Table;
		
	}
	static void sort_patients_by_level(vector<patient>& v) {
		for (int i = 0; i < v.size(); i++)
		{

			for (int j = i + 1; j < v.size(); j++)
			{
				if (v[i].get_level() > v[j].get_level())
				{
					patient temp = v[i];
					v[i] = v[j];
					v[j] = temp;
				}
			}
		}


	}
	static void create_schedule_for_doctor(Timatable& t1, vector<Doctor> &doctor, vector<patient>& patients_with_this_problems, all_doctors &d)
	{
		sort_patients_by_level(patients_with_this_problems);
		for (int i = patients_with_this_problems.size() - 1; i >= 0; i--)
		{
			int j = 0;
			Time st = patients_with_this_problems[i].get_start();
			Time interval_end = patients_with_this_problems[i].get_end();
			string day = patients_with_this_problems[i].get_day();
			
			while (j < doctor.size())
			{
				string name = doctor[j].nm();
				if (t1.check_if_avalaible(st, interval_end, patients_with_this_problems[i].get_dur(), day, d, name))
				{
					Time end = st + patients_with_this_problems[i].get_dur();
					int index = d.get_index_of_doctor(name);
					string pt_name = patients_with_this_problems[i].get_name();
					t1.change_state(st, end, day, name, index, pt_name);
					break;
				}
				j++;
			}
		}

	}
	static vector<patient> excat_problem(vector<patient>& v, string &problem)
	{
		vector<patient> sorted;
		for (int i = 0; i < v.size(); i++)
		{
			if (v[i].get_problem() == problem)
				sorted.push_back(v[i]);
		}
		return sorted;
	}
	static vector<Doctor> group_by_speciality(vector<Doctor> & d,string &spec)
	{
		vector<Doctor> s;
		for (int i = 0; i < d.size(); i++)
		{
			if (d[i].get_specilazition() == spec)
			{
				s.push_back(d[i]);
			}
		}
		return s;
	}
	static Time tm(int i)
	{
		Time res = Time(i / 60, i % 60);
		return res;
	}
	static void create_table(string***& table, int& s)
	{

		table = new string** [7];
		for (int i = 0; i < 7; i++)
		{
			table[i] = new string* [1440];
			for (int j = 0; j < 1440; j++) {
				table[i][j] = new string[s];
			}
		}
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 1440; j++)
			{
				for (int k = 0; k < s; k++) {
					table[i][j][k] = "open";
				}
			}
		}
	}

};
