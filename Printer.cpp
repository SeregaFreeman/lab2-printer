#include "Printer.h"

Printer::Printer()
{
	queue = new Queue();

	state.currTask = 0; // ������, ����������� ��������� � ������ ������

	statistics.workTime = 0; // ����� ������ ��������
	statistics.idleTime = 0; // ����� ������� ��������
	statistics.queueAverageLength = 0; // ������� ����� �������
	statistics.queueMaxLength = 0;  // ������������ ����� �������

	time = 0;
}

Printer::~Printer()
{
	delete queue;
	queue = 0;
}

void Printer::changeTime()
{
	if (state.currTask == 0 && queue->getCount() > 0) // ���� ������� �������� � � ������� ���� ������
		state.currTask = queue->dequeue(); // ��������� ������

	if (state.currTask != 0) { // ���� ���� ������ ��� ����������
		--state.currTask->pageCount; // ������ ������ �����

		if (state.currTask->pageCount <= 0) { // ���� ������ ��������� (��� ����� ����������)
			delete state.currTask;  // ������������ ������, ���������� ����������, ����������� ������
			state.currTask = 0;
		}

		++statistics.workTime; // ����� ������ ��������
	}
	else {
		++statistics.idleTime; // ����� ������� ��������
	}

	++time;

	statistics.queueAverageLength += queue->getCount(); // ������� ����� �������
	if (statistics.queueMaxLength < queue->getCount())
		statistics.queueMaxLength = queue->getCount();

	if (state.currTask == 0 && queue->getCount() > 0) { // ���� ������� �������� � � ������� ���� ������
		state.currTask = queue->dequeue();
	}
}

void Printer::print(Task *task)
{
	if (task != 0) {
		if (queue->getCount() == 0 && state.currTask == 0) { // ���� ������� ����� � ������� ��������
			state.currTask = task; // ������ ������������ �������� ����� (����� �������)
		}
		else {
			queue->enqueue(task);
		}
	}
}

bool Printer::isBusy() const
{
	return queue->getCount() > 0 || state.currTask != 0;
}

Task *Printer::getCurrentTask() const
{
	return state.currTask;
}

Statistics Printer::getStatistics() const
{
	Statistics s = statistics;
	s.queueAverageLength /= time;
	return s;
}
