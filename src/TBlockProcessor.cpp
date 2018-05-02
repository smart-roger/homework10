#include "TBlockProcessor.h"

TBlockProcessor::TBlockProcessor(TQueueMT<TBulk>& queueForConsole, TQueueMT<TBulk>& queueForBlocks):
    TObserver(),
    _queueConsole(queueForConsole),
    _queueFile(queueForBlocks),
    _blockCounter(0),
    _store()
{
    //ctor
}

 TBlockProcessor::~TBlockProcessor()
{
    //dtor
}

void TBlockProcessor::startBlock(){
    ++_blockCounter;
}

void TBlockProcessor::finishBlock(){

    if(0<_blockCounter) --_blockCounter;
    //  „то должно происходить при нарушении синтаксиса?
    //else{}

    if(0==_blockCounter){
            logBlock();
            _store.clear();
    }
}

void TBlockProcessor::handleCommand(const std::string& command){
    if(0<_blockCounter)
        _store.addCommand(command);

    //   оманды обрабатываютс€ в другом наблюдателе.
    //  else{}
}

void TBlockProcessor::logBlock(){
    _queueConsole.push_back(_store);
    _queueFile.push_back(_store);
}
