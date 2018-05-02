#ifndef TBULK_H
#define TBULK_H

#include <iostream>
#include <ctime>
#include <vector>
#include <string>

#include <algorithm>

class TBulk
{
    public:
        TBulk();
        ~TBulk();

    //  Добавление команды в хранилище
    void addCommand(std::string strCommand);

    //  Вывод команд в поток
    void printCommands(std::ostream& out = std::cout) const;

    //  Очистка хранилища
    void clear();

    //  Число команд в хранилище
    size_t size() const;

    //  Проверка наличия элементов в хранилище
    bool empty() const;

    std::time_t timeStart() const;

    private:

    //  Команды, помещённые в блок
    std::vector<std::string> _commands;
    std::time_t _timeStart;
};

#endif // TBULK_H
