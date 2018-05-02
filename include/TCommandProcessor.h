#ifndef TCOMMANDPROCESSOR_H
#define TCOMMANDPROCESSOR_H

#include "TObserver.h"
#include "TQueueMT.h"
#include "TBulk.h"
#include <vector>
#include <string>

/*!
    Обработчик для потока команд "нулевого уровня
*/
class TCommandProcessor : public TObserver
{
    public:
        TCommandProcessor(size_t bulkSize, TQueueMT<TBulk>& queueConsole, TQueueMT<TBulk>& queueFile);
        virtual ~TCommandProcessor();

    protected:

        virtual void handleCommand(const std::string& command) override;
        virtual void startBlock()   override;
        virtual void finishBlock()  override;

        void checkStore();
    private:
        //  Размер блока для вывода
        size_t  _bulkSize;
        //  Счётчик открытых блоков
        size_t  _blockCounter;
        TBulk   _store;

        TQueueMT<TBulk>&   _queueConsole;
        TQueueMT<TBulk>&   _queueFile;
};

#endif // TCOMMANDPROCESSOR_H
