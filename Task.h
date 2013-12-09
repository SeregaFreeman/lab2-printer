#ifndef TASK_H
#define TASK_H

#define NAME_MAX_LEN 64

typedef struct TaskTag {
	char name[NAME_MAX_LEN + 1]; // ��������
	int pageCount; // ���������� ������
	int arrivalTime; // ����� �����������
	int priority; // ���������
} Task;

#endif

