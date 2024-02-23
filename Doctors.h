#pragma once
#include <string>
#include<vector>
#include<fstream>
using namespace std;


class Doctor
{
public:
	Doctor(string name, string specilazition) {
		this->name = name;
		this->specilazition = specilazition;

	}
	Doctor()
	{

	}
	string nm() {
		return this->name;
	}
	string get_specilazition()
	{
		return this->specilazition;
	}

private:
	string name;
	string specilazition;
};




class all_doctors
{
public:
	all_doctors()
	{
		try {
			int i,count=0;

			string n, s;
			ifstream file;
			file.open("Doctors.txt");
			file >> i;

			while (file >> n >> s)
			{
				count++;
				Doctor tmp = Doctor(n, s);
				this->all.push_back(tmp);
				this->number_of_doctors++;
			}
			if (i-count!=0)
			{
				string ex = "you have a broblematic input on: " + std::to_string(count + 1) + " line of doctors.txt file";
				throw(ex);
			}
			file.close();
		}
		catch (string ex) {
			cout << ex << endl;

		}
	}
	int get_nubmer_of_doctors() {
		return this->number_of_doctors;
	}
	vector<Doctor> get_doctors()
	{
		return this->all;
	}
	int get_index_of_doctor(string& doctor)
	{
		try
		{
			bool test = false;
			for (int i = 0; i < this->number_of_doctors; i++)
			{
				if (this->all[i].nm() == doctor)
				{
					test = true;
					return i;
				}
			}
			if (!test)
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
	~all_doctors() {
		this->all.clear();
	}
private:
	vector<Doctor> all;
	int number_of_doctors = 0;

};
