#include <clocale>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <cstdio>
#include "Printer.h"

#define FILE_NAME "tasks.txt"
#define BUF_SIZE 1024

using namespace std;

// ��������� �������� �������
Task **readTasksFromFile(const char *fileName, int *tasksCount);
void sortByArrivalTime(Task **tasks, int tasksCount);
void startClock(Printer *printer, Task **tasks, int tasksCount);
void printStatistics(Statistics statistics);

int main()
{
    setlocale(LC_ALL, "rus");

    cout << "������ ����� �� ����� " << FILE_NAME << ":\n";
    int tasksCount;
    Task **tasks = readTasksFromFile(FILE_NAME, &tasksCount);
    if (tasksCount)
    {
        cout << "  ��������� �������: " << tasksCount << endl;
        sortByArrivalTime(tasks, tasksCount);
        Printer *printer = new Printer(); // �������� ������� ��������
        startClock(printer, tasks, tasksCount);

        // ������������ ������
        delete [] tasks;
        tasks = 0;
    }
    else
    {
        cout << "  � ����� �� ���������� �� ����� ������.\n";
    }

    return 0;
}

Task **readTasksFromFile(const char *fileName, int *tasksCount)
{
    Task **tasks = 0;
    *tasksCount = 0;

    FILE *file = fopen(fileName, "r");

    if (file != 0)
    {
        char buffer[BUF_SIZE];

        // ������� ���������� ������� � �����
        while (!feof(file))
        {
            // ������ ������ ������������� �� 4 �������
            bool isExists =
                fgets(buffer, BUF_SIZE, file) != 0 &&
                fgets(buffer, BUF_SIZE, file) != 0 &&
                fgets(buffer, BUF_SIZE, file) != 0 &&
                fgets(buffer, BUF_SIZE, file) != 0;

            if (isExists)
                ++(*tasksCount);

            fgets(buffer, BUF_SIZE, file); // ������ ���������� ������
        }

        if (*tasksCount > 0)
        {
            rewind(file);

            tasks = new Task *[*tasksCount];
            int index = 0;

            while (!feof(file))
            {
                Task *task = new Task();

                fgets(buffer, BUF_SIZE, file);
                if (buffer[strlen(buffer) - 1] == '\n')
                    buffer[strlen(buffer) - 1] = '\0'; // ��������� ������� '\n'
                strncpy(task->name, buffer, NAME_MAX_LEN + 1);

                fscanf(file, "%d%d%d", &task->pageCount, &task->arrivalTime, &task->priority);

                tasks[index++] = task;

                fgets(buffer, BUF_SIZE, file); // ������� '\n'
                fgets(buffer, BUF_SIZE, file); // ������ ���������� ������
            }
        }

        fclose(file);
    }

    return tasks;
}

// ������� ��������� ������ � ������� ������� �� �����������
void sortByArrivalTime(Task **tasks, int tasksCount)
{
    // ���������� ���������
    for (int i = 0; i < tasksCount - 1; i++)
    {
        for (int j = i + 1; j < tasksCount; j++)
        {
            if (tasks[j]->arrivalTime < tasks[i]->arrivalTime)
            {
                Task *task = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = task;
            }
        }
    }
}

// ������� �������� ������ �� ������ � ����������� �� ������� �� ����������� (��������� ������ �����, ��������������� � ������� ������� �� �����������)
void startClock(Printer *printer, Task **tasks, int tasksCount)
{
    int time = 0; // ����� ��������� �� ����
    int lastTaskArrivalTime = tasks[tasksCount - 1]->arrivalTime; // ����� ����������� ��������� ������

    // ����� ����� �������������, ���� �� �������� ����� ����������� ��������� ������, � ����� ���� ������� �� �������� ������
    while (time <= lastTaskArrivalTime || printer->isBusy())
    {
        // �������� �������� ��� �����, ����� ������� ������
        for (int i = 0; i < tasksCount; i++)
        {
            if (tasks[i]->arrivalTime == time)
                printer->print(tasks[i]); // ��������
        }

        cout << "*********************************************************************\n";
        cout << "  ������� �����: " << time << endl << endl;

        Task *currentTask = printer->getCurrentTask();
        if (currentTask == 0)
        {
            cout << "  ������� �����������\n";
        }
        else
        {
            cout << "  �������� ������� ������: " << currentTask->name << endl;
            cout << "  ���������� ������ ������� ������: " << currentTask->pageCount << endl;
            cout << "  ����� ����������� ������� ������: " << currentTask->arrivalTime << endl;
            cout << "  ��������� ������� ������: " << currentTask->priority << endl;
        }
        cout << "*********************************************************************\n";

        printer->changeTime();

        Statistics s = printer->getStatistics();
        printStatistics(s);

        cout << endl << endl;

        ++time;
    }
}

void printStatistics(Statistics statistics)
{
    cout << "����������:\n";
    cout << "  ����� ������ ��������: " << statistics.workTime << endl;
    cout << "  ����� ������� ��������: " << statistics.idleTime << endl;
    cout << "  ������� ����� �������: " << statistics.queueAverageLength << endl;
    cout << "  ������������ ����� �������: " << statistics.queueMaxLength << endl;
}
