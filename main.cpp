#include <iostream>
#include <string>
#include <sstream>
#include <thread>

#include <condition_variable>

#include "TConsole.h"
#include "TQueueMT.h"
#include "TCommandProcessor.h"
#include "TBlockProcessor.h"

//  Мютекс для упорядочивания вывода на консоль
std::mutex  mutexOutput;

//  Мютекс для упорядочивания обращения к очереди блоков
std::mutex  mutexQueue;

//  Условная переменная, чтобы вывод метрик шёл после вывода на консоль
std::condition_variable cond_var;

//  Функция для потока вывода в консоль
void threadConsoleFunction(bool& flagWorking,
    const std::string strID,
    TQueueMT<TBulk>& queue,
    size_t&      bulkCounter,
    size_t&      commandCounter){


    auto processQueue = [&bulkCounter, &commandCounter](TQueueMT<TBulk>& queue){
        //std::cout << "Console working" << std::endl;
        if(!queue.empty()){
            TBulk bulk(queue.pop_front());
            ++bulkCounter;

            bulk.printCommands(std::cout);
            commandCounter+=bulk.size();
        }
    };

    //  Работаем пока установлен флаг
    while(flagWorking)  processQueue(queue);

    //  Завершаемо бработку того, что успели накидать в очередь
    while(!queue.empty())   processQueue(queue);

    std::cout << strID << " bulks: " << bulkCounter << " commands: " << commandCounter << std::endl;

    cond_var.notify_one();
}

void threadFileFunction(bool& flagWorking, std::string strID, TQueueMT<TBulk>& queue){
    size_t      bulkCounter(0);
    size_t      commandCounter(0);

    auto processBlocks = [&bulkCounter, &commandCounter, &strID](TQueueMT<TBulk>& queue){
        //std::cout << "Console working" << std::endl;
        if(!queue.empty()){
            mutexQueue.lock();
            if(queue.empty()){
                mutexQueue.unlock();
                return;
            }

            TBulk store(queue.pop_front());
            mutexQueue.unlock();

            ++bulkCounter;

            std::string filename = strID + "_"
                                    + std::to_string(store.timeStart()) + "_"
                                    + std::to_string(rand());
            std::ofstream   ofile(filename);
            store.printCommands(ofile);
            commandCounter+=store.size();
        }
    };

    while(flagWorking) processBlocks(queue);

    while(!queue.empty()) processBlocks(queue);

    std::unique_lock<std::mutex> lk(mutexOutput);
    cond_var.wait(lk);
    std::cout << strID << " bulks: " << bulkCounter << " commands: " << commandCounter << std::endl;
    cond_var.notify_one();
}



int main(int argc, char** argv)
{
    //  Считываем размер блока
    if(argc<2){
        std::cerr << "Wrong arguments count. Using: bulk <bulk_size>"<< std::endl;
        return -1;
    }
    bool working(true);
    auto bulk_size(std::stoul(argv[1]));

    TQueueMT<TBulk> queueConsole;
    TQueueMT<TBulk> queueFile;

    size_t bulkCounter(0);
    size_t commandCounter(0);

    std::thread threadConsole(threadConsoleFunction,
                              std::ref(working),
                              "thread log",
                              std::ref(queueConsole),
                              std::ref(bulkCounter),
                              std::ref(commandCounter));
    std::thread threadFile1(threadFileFunction, std::ref(working), "thread file1", std::ref(queueFile));
    std::thread threadFile2(threadFileFunction, std::ref(working), "thread file2", std::ref(queueFile));

    //TConsole console(sstream);
    TConsole console(std::cin,std::ref(bulkCounter),std::ref(commandCounter));

    //  Добавляем обработчики
    //  Обработчик команд
    console.addObserver(std::make_shared<TCommandProcessor>(bulk_size, queueConsole, queueFile));

    //  Обработчик блоков
    console.addObserver(std::make_shared<TBlockProcessor>(queueConsole, queueFile));


    //  Обрабатываем ввод
    console.run();

    working = false;
    threadConsole.join();
    threadFile1.join();
    threadFile2.join();
    return 0;
}
