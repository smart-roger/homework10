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
    ����� ��� ���������� ����� ������ �� �������
*/
class TConsole
{
    public:
        enum charType{blockStart='{',blockFinish='}'};

        TConsole() = delete;

        TConsole(std::istream& user_input);
        ~TConsole();
        /*!
            �����,����������� ���� ��������� �����
        */
        void run();

        /*! ����� ����������� �����������*/
        void addObserver(ptrObserver newObserver);

    protected:

    private:
        //  ����� ��� �����
        std::istream& _input;

        //  ����������� ��� ������
        std::vector <ptrObserver>   _observers;

        size_t  _totalLines;
        size_t  _totalBlocks;
        size_t  _totalCommands;
};

#endif // TCONSOLE_H
