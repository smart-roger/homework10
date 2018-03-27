#ifndef TCOMMANDSTORE_H
#define TCOMMANDSTORE_H

#include <iostream>
#include <string>
#include <vector>

#include <algorithm>

#include "TStore.h"

/*!
    Класс для хранения команд и их вывода.
*/
class TCommandStore:public TStore
{
    public:
        TCommandStore() = delete;
        TCommandStore(size_t size);
        virtual ~TCommandStore();

        //  Добавление команды в хранилище
        virtual void addCommand(std::string strCommand) override;

        //  Вывод команд в поток
        void printCommands(std::ostream& out = std::cout) const override;
        //  Очистка хранилища
        virtual void clear() override;
        //  Число команд в хранилище
        virtual size_t size() const override;
        //  Проверка наличия элементов в хранилище
        virtual bool empty() const;

    protected:

    private:
        //  Команды, помещённые в хранилище
        std::vector<std::string> _commands;
};

#endif // TCOMMANDSTORE_H
