#ifndef TSTORE_H
#define TSTORE_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//  Базоый класс для хранилища
class TStore
{
    public:
    TStore(){};
    virtual ~TStore(){};

    //  Добавление команды в хранилище
    virtual void addCommand(std::string command) =0;

    //  Вывод команд в поток
    virtual void printCommands(std::ostream& out = std::cout) const =0;

    //  Очистка хранилища
    virtual void clear() = 0;

    //  Число команд в хранилище
    virtual size_t size() const =0;
};

#endif // TSTORE_H
