#include <clocale>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <cstdio>
#include "Printer.h"

#define FILE_NAME "tasks.txt"
#define BUF_SIZE 1024

using namespace std;

// Объявлние сигнатур функций
Task **readTasksFromFile(const char *fileName, int *tasksCount);
void sortByArrivalTime(Task **tasks, int tasksCount);
void startClock(Printer *printer, Task **tasks, int tasksCount);
void printStatistics(Statistics statistics);

int main()
{
    setlocale(LC_ALL, "rus");

    cout << "Чтение задач из файла " << FILE_NAME << ":\n";
    int tasksCount;
    Task **tasks = readTasksFromFile(FILE_NAME, &tasksCount);
    if (tasksCount)
    {
        cout << "  Прочитано записей: " << tasksCount << endl;
        sortByArrivalTime(tasks, tasksCount);
        Printer *printer = new Printer(); // создание объекта принтера
        startClock(printer, tasks, tasksCount);

        // Освобождение памяти
        delete [] tasks;
        tasks = 0;
    }
    else
    {
        cout << "  В файле не содержится ни одной задачи.\n";
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

        // Подсчет количества записей в файле
        while (!feof(file))
        {
            // Каждая запись располагается на 4 строках
            bool isExists =
                fgets(buffer, BUF_SIZE, file) != 0 &&
                fgets(buffer, BUF_SIZE, file) != 0 &&
                fgets(buffer, BUF_SIZE, file) != 0 &&
                fgets(buffer, BUF_SIZE, file) != 0;

            if (isExists)
                ++(*tasksCount);

            fgets(buffer, BUF_SIZE, file); // чтение пробельной строки
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
                    buffer[strlen(buffer) - 1] = '\0'; // затирание символа '\n'
                strncpy(task->name, buffer, NAME_MAX_LEN + 1);

                fscanf(file, "%d%d%d", &task->pageCount, &task->arrivalTime, &task->priority);

                tasks[index++] = task;

                fgets(buffer, BUF_SIZE, file); // символа '\n'
                fgets(buffer, BUF_SIZE, file); // чтение пробельной строки
            }
        }

        fclose(file);
    }

    return tasks;
}

// Функция сортирует задачи в порядке времени их поступления
void sortByArrivalTime(Task **tasks, int tasksCount)
{
    // Сортировка вставками
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

// Функция передает задачи на печать в зависимости от времени их поступления (принимает массив задач, отсортированных в порядке времени их поступления)
void startClock(Printer *printer, Task **tasks, int tasksCount)
{
    int time = 0; // время считается от нуля
    int lastTaskArrivalTime = tasks[tasksCount - 1]->arrivalTime; // время поступления последней задачи

    // Время будет отсчитываться, пока не наступит время поступления последней задачи, а также пока принтер не завершит работу
    while (time <= lastTaskArrivalTime || printer->isBusy())
    {
        // Отправка принтеру тех задач, время которых пришло
        for (int i = 0; i < tasksCount; i++)
        {
            if (tasks[i]->arrivalTime == time)
                printer->print(tasks[i]); // отправка
        }

        cout << "*********************************************************************\n";
        cout << "  ТЕКУЩЕЕ ВРЕМЯ: " << time << endl << endl;

        Task *currentTask = printer->getCurrentTask();
        if (currentTask == 0)
        {
            cout << "  ПРИНТЕР ПРОСТАИВАЕТ\n";
        }
        else
        {
            cout << "  НАЗВАНИЕ ТЕКУЩЕЙ ЗАДАЧИ: " << currentTask->name << endl;
            cout << "  КОЛИЧЕСТВО ЛИСТОВ ТЕКУЩЕЙ ЗАДАЧИ: " << currentTask->pageCount << endl;
            cout << "  ВРЕМЯ ПОСТУПЛЕНИЯ ТЕКУЩЕЙ ЗАДАЧИ: " << currentTask->arrivalTime << endl;
            cout << "  ПРИОРИТЕТ ТЕКУЩЕЙ ЗАДАЧИ: " << currentTask->priority << endl;
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
    cout << "Статистика:\n";
    cout << "  время работы принтера: " << statistics.workTime << endl;
    cout << "  время простоя принтера: " << statistics.idleTime << endl;
    cout << "  средняя длина очереди: " << statistics.queueAverageLength << endl;
    cout << "  максимальная длина очереди: " << statistics.queueMaxLength << endl;
}
