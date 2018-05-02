#ifndef TQUEUEMT_H
#define TQUEUEMT_H

#include <mutex>
#include <deque>

/*
    Класс для потокобезопасной очереди.
*/
template <typename T>
class TQueueMT
{
    public:
        TQueueMT():_mutex(), _queue(){};
        ~TQueueMT(){_mutex.unlock(); _queue.clear();};

        TQueueMT(const TQueueMT& other) = delete;
        /*!
            Метод добавления элемента в очередь
        */
        void push_back(T  val){
            std::lock_guard<std::mutex> lock(_mutex);
            _queue.push_back(val);
        };

        /*!
            Метод, получающий значение в начале очереди.
            Полученный элемент сразу удаляется из очереди.
        */
        T   pop_front(){
            std::lock_guard<std::mutex> lock(_mutex);
            if(_queue.empty())
                throw std::logic_error ("Trying pop_front. But queue is empty!");

            T result(_queue.front());
            _queue.pop_front();

            return result;
        }

        /*!
            Метод, возвращающий текущий размер очереди.
        */
        size_t  size() const{
            std::lock_guard<std::mutex> lock(_mutex);
            return _queue.size();
        }

        bool empty() const{
            std::lock_guard<std::mutex> lock(_mutex);
            return _queue.empty();
        }

    protected:

    private:
        //  Мютекс для синхронизации доступа
        mutable std::mutex      _mutex;
        //  Стандартный контейнер для реализации очереди
        std::deque<T>   _queue;
};

#endif // TQUEUEMT_H
