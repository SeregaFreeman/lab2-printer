#ifndef TASK_H
#define TASK_H

#define NAME_MAX_LEN 64

typedef struct TaskTag {
	char name[NAME_MAX_LEN + 1]; // название
	int pageCount; // количество листов
	int arrivalTime; // время поступления
	int priority; // приоритет
} Task;

#endif

