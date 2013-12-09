#ifndef PRINTER_H
#define PRINTER_H

#include "Task.h"
#include "Queue.h"

typedef struct PrinterStateTag {
	Task *currTask; // ������, ����������� ��������� � ������ ������
} PrinterState;

typedef struct StatisticsTag {
	int workTime; // ����� ������ ��������
	int idleTime; // ����� ������� ��������
	double queueAverageLength; // ������� ����� �������
	int queueMaxLength; // ������������ ����� �������
} Statistics;

class Printer
{
public:
	Printer();
	~Printer();

	void changeTime();
	void print(Task *task);
	bool isBusy() const;
	Task *getCurrentTask() const;
	Statistics getStatistics() const;
private:
	Queue *queue;
	PrinterState state;
	Statistics statistics;
	int time;
};

#endif

