#include "TBlockStore.h"

TBlockStore::TBlockStore():_timeStart(0), _ID(rand()), _store(0){

}

TBlockStore::TBlockStore(std::time_t timeStart, size_t defSize):
        _timeStart(timeStart),
        _ID(rand()),
        _store(defSize){

}


TBlockStore::~TBlockStore()
{
    //dtor
}

void TBlockStore::addCommand(const std::string command){
    _store.addCommand(command);
}

std::time_t TBlockStore::getTimeStart() const{
    return _timeStart;
}

unsigned long TBlockStore::getID() const{
    return _ID;
}

void TBlockStore::setTimeStart(std::time_t newTime){
    _timeStart = newTime;
}

void TBlockStore::printCommands(std::ostream& out) const{
    _store.printCommands(out);
}

TCommandStore   TBlockStore::getCommandStore() const{
    return _store;
}

void TBlockStore::clear(){
    _store.clear();
}

size_t TBlockStore::size() const{
    return _store.size();
}
