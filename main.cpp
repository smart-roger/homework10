#include <iostream>
#include <string>
#include <sstream>
#include <thread>

#include "TConsole.h"
#include "TQueueMT.h"
#include "TCommandProcessor.h"
#include "TCommandStore.h"
#include "TBlockProcessor.h"

//  Мютекс для упорядочивания вывода на консоль
std::mutex  mutexOutput;
//  Мютекс для упорядочивания обращения к очереди блоков
std::mutex  mutexQueue;

//  Функция для потока вывода в консоль
void threadConsoleFunction(bool& flagWorking, const std::string strID, queueStore& queue){
    size_t      bulkCounter(0);
    size_t      commandCounter(0);

    auto processQueue = [&bulkCounter, &commandCounter](queueStore& queue){
        //std::cout << "Console working" << std::endl;
        if(!queue.empty()){
            TCommandStore store(queue.pop_front());
            ++bulkCounter;

            {
                std::lock_guard<std::mutex> lock(mutexOutput);
                store.printCommands(std::cout);
            }
            commandCounter+=store.size();
        }
    };

    //  Работаем пока установлен флаг
    while(flagWorking)  processQueue(queue);

    //  Завершаемо бработку того, что успели накидать в очередь
    while(!queue.empty())   processQueue(queue);

    std::lock_guard<std::mutex> lock(mutexOutput);
    std::cout << strID << " bulks: " << bulkCounter << " commands: " << commandCounter << std::endl;
}

void threadFileFunction(bool& flagWorking, std::string strID, queueBlocks& queue){
    size_t      bulkCounter(0);
    size_t      commandCounter(0);

    auto processBlocks = [&bulkCounter, &commandCounter, &strID](queueBlocks& queue){
        //std::cout << "Console working" << std::endl;
        if(!queue.empty()){
            mutexQueue.lock();
            if(queue.empty()){
                mutexQueue.unlock();
                return;
            }

            TBlockStore store(queue.pop_front());
            mutexQueue.unlock();

            ++bulkCounter;

            std::string filename = strID + "_"
                                    + std::to_string(store.getTimeStart()) + "_"
                                    + std::to_string(store.getID());
            std::ofstream   ofile(filename);
            store.printCommands(ofile);
            commandCounter+=store.size();
        }
    };

    while(flagWorking) processBlocks(queue);

    while(!queue.empty()) processBlocks(queue);

    std::lock_guard<std::mutex> lock(mutexOutput);
    std::cout << strID << " bulks: " << bulkCounter << " commands: " << commandCounter << std::endl;
}



int main(int argc, char** argv)
{

    /*std::stringstream sstream;
    //sstream << "" <<std::endl;
    sstream << "{" <<std::endl;
    sstream << "cmd1" <<std::endl;
    sstream << "cmd2" <<std::endl;
    sstream << "{" <<std::endl;
    sstream << "cmd3" <<std::endl;
    sstream << "cmd4" <<std::endl;
    sstream << "}" <<std::endl;
    sstream << "cmd5" <<std::endl;
    sstream << "cmd6" <<std::endl;
    sstream << "}" <<std::endl;
    sstream << "cmd7" <<std::endl;
    sstream << "cmd8" <<std::endl;
    sstream << "{" <<std::endl;
    sstream << "cmd11" <<std::endl;
    sstream << "cmd12" <<std::endl;
    sstream << "{" <<std::endl;
    sstream << "cmd13" <<std::endl;
    sstream << "cmd14" <<std::endl;
    sstream << "}" <<std::endl;
    sstream << "cmd15" <<std::endl;
    sstream << "cmd16" <<std::endl;
    sstream << "}" <<std::endl;
    sstream << "cmd17" <<std::endl;
    sstream << "cmd18" <<std::endl;
    sstream << "{" <<std::endl;
    sstream << "cmd21" <<std::endl;
    sstream << "cmd22" <<std::endl;
    sstream << "{" <<std::endl;
    sstream << "cmd23" <<std::endl;
    sstream << "cmd24" <<std::endl;
    sstream << "}" <<std::endl;
    sstream << "cmd25" <<std::endl;
    sstream << "cmd26" <<std::endl;
    sstream << "}" <<std::endl;
    sstream << "cmd27" <<std::endl;
    sstream << "cmd28" <<std::endl;
    sstream << "" <<std::endl;*/
    //  Считываем размер блока
    //std::cout << argc << std::endl;
    if(argc<2){
        std::cerr << "Wrong arguments count. Using: bulk <bulk_size>"<< std::endl;
        return -1;
    }
    bool working(true);
    auto bulk_size(std::stoul(argv[1]));
    //std::cout << bulk_size << std::endl;

    queueStore    queueConsole;
    queueBlocks   queueForBlocks;

    std::thread threadConsole(threadConsoleFunction, std::ref(working), "thread log", std::ref(queueConsole));
    std::thread threadFile1(threadFileFunction, std::ref(working), "thread file1", std::ref(queueForBlocks));
    std::thread threadFile2(threadFileFunction, std::ref(working), "thread file2", std::ref(queueForBlocks));

    //  Подготавливаем ввод

    //TConsole console(sstream);
    TConsole console(std::cin);

    //  Добавляем обработчики
    //  Обработчик команд
    console.addObserver(std::make_shared<TCommandProcessor>(bulk_size, queueConsole));

    //  Обработчик блоков
    console.addObserver(std::make_shared<TBlockProcessor>(queueConsole, queueForBlocks));


    //  Обрабатываем ввод
    console.run();

    working = false;
    threadConsole.join();
    threadFile1.join();
    threadFile2.join();
    return 0;
}
