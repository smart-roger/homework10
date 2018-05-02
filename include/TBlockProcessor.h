#ifndef TBLOCKPROCESSOR_H
#define TBLOCKPROCESSOR_H

#include <TObserver.h>
#include "TBulk.h"
#include "TQueueMT.h"
#include <ctime>
#include <fstream>

class TBlockProcessor : public TObserver
{
    public:
        TBlockProcessor(TQueueMT<TBulk>& queueConsole, TQueueMT<TBulk>& queueForBlocks);
        virtual ~TBlockProcessor();

    protected:
        virtual void handleCommand(const std::string& command) override;
        virtual void startBlock()   override;
        virtual void finishBlock()  override;

        void logBlock();

    private:
        //  Очередь для вывода на консоль
        TQueueMT<TBulk>& _queueConsole;
        //  Очередь для вывода блоков в файл
        TQueueMT<TBulk>& _queueFile;
        //  Счётчик блоков
        size_t          _blockCounter;

        //  Текущий накопитель команд блока
        TBulk   _store;
};

#endif // TBLOCKPROCESSOR_H
