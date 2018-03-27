#ifndef TCOMMANDPROCESSOR_H
#define TCOMMANDPROCESSOR_H

#include "TObserver.h"
#include "TQueueMT.h"
#include "TCommandStore.h"
#include <vector>
#include <string>

using queueStore = TQueueMT<TCommandStore>;

/*!
    Обработчик для потока команд "нулевого уровня
*/
class TCommandProcessor : public TObserver
{
    public:
        TCommandProcessor(size_t bulkSize, queueStore& queueOut);
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
        TCommandStore   _store;
        //  Хранилище для команд
        queueStore&   _queue;
};

#endif // TCOMMANDPROCESSOR_H
