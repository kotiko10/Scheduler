// Hospital_visit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include"Timatable.h"
#include"Patients.h"
#include"Doctors.h"
#include"output.h"
using namespace std;


int main()
{

    //reading from files doctor and patients
    all_patients p = all_patients();
    all_doctors d = all_doctors();
    vector<patient> all = p.patients();
    int s = d.get_nubmer_of_doctors();
    //creating table for timetable 
    string*** table;
    Function_dump::create_table(table, s);
    Timatable t1 = Timatable(table);

    cout << "Creating schedule for doctors..." << endl;
    //using for loop to go from doctor to doctor and create each of them timetable
    for (int i = 0; i < d.get_nubmer_of_doctors(); i++)
    {
        string spec = d.get_doctors()[i].get_specilazition();
        vector<patient> problem = Function_dump::excat_problem(all,spec);
        vector<Doctor> a = d.get_doctors();
        vector<Doctor> grouped = Function_dump::group_by_speciality(a, spec);
        Function_dump::create_schedule_for_doctor(t1, grouped, problem, d);
       
    }
    all.clear();
    cout << "Created... starting output..." << endl;
    //outputing the anwser in .xlx format
    output::Output_Final_state(t1,d);
    //destruct all classes, vectors and arrays we have. the destructors will be called automaticly in the end of the prorgam.
  /*  p.~all_patients();
    d.~all_doctors();
    t1.~Timatable();
    */
   // Function_dump::destroy_tabale(table); this function is not neede because t1 destorys tabe as well becaus ethey have same memory adress
    system("pause");
   
    return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
