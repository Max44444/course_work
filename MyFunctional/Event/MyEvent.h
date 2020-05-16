//
// Created by maxim on 13.05.2020.
//

#ifndef COURSE_WORK_MYEVENT_H
#define COURSE_WORK_MYEVENT_H


#include "Functions.h"
#include <algorithm>
#include <list>


template<typename ...Args>
class MyEvent{
public:
    MyEvent() = default;

    ~MyEvent(){
        this->clear();
    }

    void operator()(Args ... args) const {
        for (AbstractFunction<Args...> *el : _handlers) {
            (*el)(args...);
        }
    }

    bool push_back(void (*f)(Args...)){
        return _insert_base_function(new Function<Args...>(f));
    }

    bool push_back(const Function<Args...> &handler){
        return _insert_base_function(new Function<Args...>(handler));
    }

    template<class ObjType>
    bool push_back(const ObjType &object, void(ObjType::*f)(Args...)){
        return _insert_base_function(new ObjectFunction<ObjType, Args...>(object, f));
    }

    template<class ObjType>
    bool push_back(const ObjectFunction<ObjType, Args...> &handler){
        return _insert_base_function(new ObjectFunction<ObjType, Args...>(handler));
    }

    bool erase(void (*f)(Args...)){
        return _delete_base_function(Function<Args...>(f));
    }

    template<class ObjType>
    bool erase(const ObjType &object, void (ObjType::*f)(Args...)){
        return _delete_base_function(ObjectFunction<ObjType, Args...>(object, f));
    }

    void clear(){
        for(AbstractFunction<Args...> *el : _handlers){
            delete el;
        }
        _handlers.clear();
    }

private:
    std::list<AbstractFunction<Args...> *> _handlers;

    bool _insert_base_function(AbstractFunction<Args...> *handler){
        if(_find_handler(*handler) == _handlers.end()){
            _handlers.push_back(handler);
            return true;
        }
        return false;
    }

    bool _delete_base_function(const AbstractFunction<Args...> &handler){
        if(auto iter = _find_handler(handler); iter != _handlers.end()){
            auto *removed_handler = *iter;
            _handlers.erase(iter);
            delete removed_handler;
            return true;
        }
        return false;
    }

    typename std::list<AbstractFunction<Args...>*>::const_iterator
    _find_handler(const AbstractFunction<Args...> &handler) const {
        return std::find_if(_handlers.cbegin(), _handlers.cend(),
                            [&handler](const AbstractFunction<Args...>* el){
                                return (*el == handler);
                            });
    }
};


#endif //COURSE_WORK_MYEVENT_H
