#ifndef TBLOCKSTORE_H
#define TBLOCKSTORE_H

#include <algorithm>
#include <cstdlib>
#include "ctime"
#include "TCommandStore.h"

class TBlockStore
{
    public:
        TBlockStore();
        TBlockStore(std::time_t timeStart, size_t defSize=10);

        ~TBlockStore();

        void addCommand(const std::string command);

        //  Вывод команд в поток
        void printCommands(std::ostream& out = std::cout) const;
        //  Очистка хранилища
        void clear();
        //  Число команд в хранилище
        size_t size() const;

        std::time_t getTimeStart() const;
        void setTimeStart(std::time_t newTime);

        unsigned long getID() const;
        TCommandStore   getCommandStore() const;
    protected:

    private:
        std::time_t                 _timeStart;
        unsigned long               _ID;
        TCommandStore               _store;
};

#endif // TBLOCKSTORE_H
