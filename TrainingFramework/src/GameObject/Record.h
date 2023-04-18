#pragma once
#include <list>
#include <memory>
#include <queue>

class Timer;

class Record
{
private:
	std::vector<std::shared_ptr<Timer>> record;
public:
	Record();
	void AddRecord(std::shared_ptr<Timer> recordTime);
	void SaveRecord();
	void LoadRecord();
	void RemoveRecord();
	void ResetRecord();
	void SortRecord();
	void LoadRecored();

};

