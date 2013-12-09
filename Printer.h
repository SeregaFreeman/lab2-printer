#ifndef PRINTER_H
#define PRINTER_H

#include "Task.h"
#include "Queue.h"

typedef struct PrinterStateTag {
	Task *currTask; // задача, выполняемая принтером в данный момент
} PrinterState;

typedef struct StatisticsTag {
	int workTime; // время работы принтера
	int idleTime; // время простоя принтера
	double queueAverageLength; // средняя длина очереди
	int queueMaxLength; // максимальная длина очереди
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

