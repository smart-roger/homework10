#include "TConsole.h"

TConsole::TConsole(std::istream& user_input):
    _input(user_input),
    _observers(),
    _totalLines(0),
    _totalBlocks(0),
    _totalCommands(0)
{
    //ctor
}

TConsole::~TConsole()
{
    std::cout << "Total lines: "<< _totalLines << "\tTotal blocks: " << _totalBlocks << "\tTotal commands: " << _totalCommands << std::endl;
}

void TConsole::run(){
    size_t          blockCounter(0);
    char            symbol;

    std::string command;
    while (std::getline(_input, command)){
        if(_input.fail())   break;
        ++_totalLines;

        if(command.empty())
                symbol = 0;
        else symbol = command.at(0);

        switch(symbol){
            //  Поступила команда начала блока
            case charType::blockStart: {
                    ++blockCounter;
                    std::for_each(_observers.begin(), _observers.end(),[command](auto ptrProcessor){
                        ptrProcessor->startBlock();
                        });
                    break;
                }
            //  Поступила команда окончания блока
            case charType::blockFinish: {
                    if(0<blockCounter) --blockCounter;
                    //  Что должно происходить при нарушении синтаксиса?
                    //else{}

                    if(0==blockCounter){
                    //  Если блок получен полностью - отправляем на обработку
                        ++_totalBlocks;

                    }

                    std::for_each(_observers.begin(), _observers.end(),[command](auto ptrProcessor){
                        ptrProcessor->finishBlock();
                        });

                    break;
                }
            default:{
                    //  Поступила команда
                    std::for_each(_observers.begin(), _observers.end(),[command](auto ptrProcessor){
                        ptrProcessor->handleCommand(command);
                        });

                    ++_totalCommands;
                    break;
                }
        }
    }

    _observers.clear();
}

void TConsole::addObserver(ptrObserver newObserver){
    if(nullptr == newObserver)  {
            std::cerr << "nullptr in addObserver!" << std::endl;
            return;
    }
    _observers.push_back(newObserver);
}
