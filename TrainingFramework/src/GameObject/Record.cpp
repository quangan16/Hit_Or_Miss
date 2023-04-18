#include "Record.h"

#include <memory>
#include <fstream>
#include <iostream>

#include "Timer.h"

Record::Record()
{
	this->record.clear();
	this->LoadRecord();
}

void Record::AddRecord(std::shared_ptr<Timer> recordTime)
{
	if(record.size()<4)
	{
		this->record.push_back(recordTime);
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			if (recordTime->GetTimeInMinutes() > record[i]->GetTimeInMinutes())
			{
				record.push_back(recordTime);
				SortRecord();
				record.resize(3);
				
			}
			
			else if(recordTime->GetTimeInMinutes() == record[i]->GetTimeInMinutes() && recordTime->GetTimeInSeconds() > record[i]->GetTimeInSeconds())
			{
				record.push_back(recordTime);
				SortRecord();
				record.resize(3);
			}else
			{
				SortRecord();
				record.resize(3);
				return;
			}
		}
		
	}
	
	
	
	
}

void Record::SaveRecord()
{
	std::ofstream outFile("game_records.txt", std::ofstream::trunc);

	if (outFile.is_open())
	{
		// Loop through each Timer object in the record vector
		for (const auto& timer : record)
		{
			// Get the game time data from the Timer object
			

			// Write the game time data to the file
			outFile << "Game Time (minutes): " << timer->GetTimeInMinutes() << "\n";
			outFile << "Game Time (seconds): " << timer->GetTimeInSeconds() << "\n\n";
		}

		// Close the file
		outFile.close();
	}
	outFile.close();
	ResetRecord();
}

std::vector<std::shared_ptr<Timer>> Record::GetRecord()
{
	return record;
}

void Record::RemoveRecord()
{
}

void Record::ResetRecord()
{
	this->record.clear();
}

void Record::SortRecord()
{
	// Sort the records vector using a lambda comparator that compares record times
	std::sort(record.begin(), record.end(), [](const std::shared_ptr<Timer>& a, const std::shared_ptr<Timer>& b) {
		if (a->GetTimeInMinutes() > b->GetTimeInMinutes()) {
			return true;
		}
		else if (a->GetTimeInMinutes() < b->GetTimeInMinutes()) {
			return false;
		}
		else {
			return a->GetTimeInSeconds() > b->GetTimeInSeconds();
		}
		});
}

void Record::LoadRecord()
{
	std::ifstream inFile("game_records.txt");

	if (inFile.is_open())
	{
		// Loop through the file line-by-line
		std::string line;
		while (getline(inFile, line))
		{
			// Check if the line starts with "Game Time (minutes): "
			size_t minutesPos = line.find("Game Time (minutes): ");
			if (minutesPos != std::string::npos)
			{
				// Extract the minutes value from the line
				int minutesValue = stoi(line.substr(minutesPos + 21));

				// Read the next line (should be "Game Time (seconds): ")
				getline(inFile, line);

				// Extract the seconds value from the line
				int secondsValue = stoi(line.substr(21));

				// Create a new Timer object and add it to the record vector
				std::shared_ptr<Timer> timer(new Timer());
				timer->SetTime(minutesValue, secondsValue);
				this->record.push_back(timer);
			}
		}

		// Close the file
		inFile.close();
	}
	inFile.close();

}

void Record::DisplayRecord()
	{
		for(const auto &i : record)
		{
			std::cout << (i)->GetTimeInMinutes()<<" " <<(i)->GetTimeInSeconds()<< std::endl;
		}
	}

