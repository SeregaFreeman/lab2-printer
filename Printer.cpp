#include "Printer.h"

Printer::Printer()
{
	queue = new Queue();

	state.currTask = 0; // задача, выполняемая принтером в данный момент

	statistics.workTime = 0; // время работы принтера
	statistics.idleTime = 0; // время простоя принтера
	statistics.queueAverageLength = 0; // средняя длина очереди
	statistics.queueMaxLength = 0;  // максимальная длина очереди

	time = 0;
}

Printer::~Printer()
{
	delete queue;
	queue = 0;
}

void Printer::changeTime()
{
	if (state.currTask == 0 && queue->getCount() > 0) // если принтер свободен и в очереди есть задачи
		state.currTask = queue->dequeue(); // получение задачи

	if (state.currTask != 0) { // если есть задача для выполнения
		--state.currTask->pageCount; // печать одного листа

		if (state.currTask->pageCount <= 0) { // если задача выполнена (все листы напечатаны)
			delete state.currTask;  // освобождение памяти, занимаемой структурой, описывающей задачу
			state.currTask = 0;
		}

		++statistics.workTime; // время работы принтера
	}
	else {
		++statistics.idleTime; // время простоя принтера
	}

	++time;

	statistics.queueAverageLength += queue->getCount(); // средняя длина очереди
	if (statistics.queueMaxLength < queue->getCount())
		statistics.queueMaxLength = queue->getCount();

	if (state.currTask == 0 && queue->getCount() > 0) { // если принтер свободен и в очереди есть задачи
		state.currTask = queue->dequeue();
	}
}

void Printer::print(Task *task)
{
	if (task != 0) {
		if (queue->getCount() == 0 && state.currTask == 0) { // если очередь пуста и принтер свободен
			state.currTask = task; // задача отправляется принтеру сразу (минуя очередь)
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
