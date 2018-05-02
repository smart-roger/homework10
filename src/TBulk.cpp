#include "TBulk.h"

TBulk::TBulk():_commands(), _timeStart(){
    //ctor
}

TBulk::~TBulk()
{
    //dtor
}

void TBulk::addCommand(std::string strCommand){
    if ( empty() )
        _timeStart = time(nullptr);
    _commands.push_back(strCommand);
}

void TBulk::printCommands(std::ostream& out) const{
    std::string output("bulk:");

    std::for_each(_commands.begin(), _commands.end(),
             [&output](auto command){output+= command+",";});
    output.resize(output.length()-1);
    out << output << std::endl;
}

void TBulk::clear(){
    _commands.clear();
    _timeStart = 0;
}

size_t TBulk::size() const{
    return _commands.size();
}

bool TBulk::empty() const{
    return _commands.empty();
}

std::time_t TBulk::timeStart() const{
    return _timeStart;
}
