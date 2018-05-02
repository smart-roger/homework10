#ifndef TCONSOLE_H
#define TCONSOLE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
#include <ctime>

#include "TObserver.h"
#include "TQueueMT.h"
/*!
    Класс для реализации приёма данных из консоли
*/
class TConsole
{
    public:
        enum charType{blockStart='{',blockFinish='}'};

        TConsole() = delete;

        TConsole(std::istream& user_input, size_t& bulkCounter, size_t& commandCounter);
        ~TConsole();
        /*!
            Метод,запускающий цикл обработки ввода
        */
        void run();

        /*! Метод добавляющий обработчики*/
        void addObserver(ptrObserver newObserver);

    protected:

    private:
        //  Поток для ввода
        std::istream& _input;

        //  Обработчики для команд
        std::vector <ptrObserver>   _observers;

        size_t  _totalLines;
        size_t&  _totalBlocks;
        size_t&  _totalCommands;
};

#endif // TCONSOLE_H
