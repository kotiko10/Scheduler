#pragma once
#include<Aspose.Cells.h>
#include"Timatable.h"
#include"Doctors.h"
using namespace Aspose;


//creating class for output
static class output {

public:
	static void Output_Final_state(Timatable &Final,all_doctors &doc)
	{
		//usign aspose.cells 
		string ***Final_state=Final.readTable();
		boost::intrusive_ptr<IWorkbook> wb = Factory::CreateIWorkbook();
		intrusive_ptr<IWorksheetCollection> wsc = wb->GetIWorksheets();
		intrusive_ptr<IWorksheet> ws = wsc->GetObjectByIndex(0);
		intrusive_ptr<ICells> cells = ws->GetICells();
		intrusive_ptr<ICell> cell = cells->GetObjectByIndex(0, 0);
		intrusive_ptr<String> str = new String("Doctors/hours");

		cell->PutValue(str);
		//creating 7 different  excel file fr 7 days of the week
		for (int j = 0; j < 7; j++)
		{
			//creating columns for doctors
			for (int u = 0; u < doc.get_nubmer_of_doctors(); u++)
			{
				str = new String(doc.get_doctors()[u].nm().c_str());
				cell = cells->GetObjectByIndex(u + 1, 0);
				cell->SetValue(str);

				//480 is number for 8 oclock and 22*60 would be bumber for 22 hour
				for (int i = 480; i <= 22*60; i++)
				{
					cell = cells->GetObjectByIndex(0, i-479);
					Function_dump dump;
					Time out = dump.tm(i);
					string s = std::to_string(out.get_hour());
					s.append(":");
					s.append(std::to_string(out.get_minute()));
					str = new String(s.c_str());
					cell->PutValue(str);
					cell = cells->GetObjectByIndex(u + 1, i - 479);
					str = new String(Final.state(j, i, u).c_str());
					/*if (Final.state(j, i, u))
					{
						str = new String("Open");
					}
					else
					{
						str = new String("closed");
					}*/

					cell->SetValue(str);	
				}
			}
			intrusive_ptr<String> resultPath = new String(Final.day(j).c_str());
			wb->Save(resultPath->StringAppend(new String(".xlsx")));	
		}
	}
};