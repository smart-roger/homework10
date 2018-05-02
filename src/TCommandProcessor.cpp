#include "TCommandProcessor.h"

TCommandProcessor::TCommandProcessor(size_t bulkSize, TQueueMT<TBulk>& queueOut, TQueueMT<TBulk>& queueFile):
    TObserver(),
    _bulkSize(bulkSize),
    _blockCounter(0),
    _store(),
    _queueConsole(queueOut),
    _queueFile(queueFile)
{
    //ctor
}

TCommandProcessor::~TCommandProcessor()
{
    //Если окончен ввод - надо вывести накопленные команды
    if(!_store.empty()){
        _queueConsole.push_back(_store);
        _queueFile.push_back(_store);
    }
    _store.clear();
}

void TCommandProcessor::startBlock(){

    if((0==_blockCounter) && !_store.empty()){
        _queueConsole.push_back(_store);
        _queueFile.push_back(_store);
        _store.clear();
    }

    ++_blockCounter;
}

void TCommandProcessor::finishBlock(){

    if(0<_blockCounter) --_blockCounter;
    //  Что должно происходить при нарушении синтаксиса?
    //else{}
    /*if(0==_blockCounter)
        _queue.push_back("}");*/
}

void TCommandProcessor::handleCommand(const std::string& command){
    if(0==_blockCounter){
        _store.addCommand(command);
        checkStore();
    }
}

void TCommandProcessor::checkStore(){
    if(_bulkSize == _store.size()){
        _queueConsole.push_back(_store);
        _queueFile.push_back(_store);
        _store.clear();
    }
}
