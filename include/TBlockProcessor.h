#ifndef TBLOCKPROCESSOR_H
#define TBLOCKPROCESSOR_H

#include <TObserver.h>
#include "TCommandStore.h"
#include "TBlockStore.h"
#include "TQueueMT.h"
#include <ctime>
#include <fstream>

//  Очередь блоков
using queueBlocks = TQueueMT<TBlockStore>;


class TBlockProcessor : public TObserver
{
    public:
        TBlockProcessor(TQueueMT<TCommandStore>& queueConsole, queueBlocks& queueForBlocks);
        virtual ~TBlockProcessor();

    protected:
        virtual void handleCommand(const std::string& command) override;
        virtual void startBlock()   override;
        virtual void finishBlock()  override;

        void logBlock();

    private:
        //  Очередь для вывода на консоль
        TQueueMT<TCommandStore>&     _queueConsole;
        //  Очередь для вывода блоков в файл
        queueBlocks&                _queueBlocks;
        //  Счётчик блоков
        size_t          _blockCounter;
        //  Время начала блока
        std::time_t     _timeStart;
        //  Текущий накопитель команд блока
        TBlockStore   _store;
};

#endif // TBLOCKPROCESSOR_H
