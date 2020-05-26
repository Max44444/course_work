#ifndef UNTITLED2_DELEGATE_H
#define UNTITLED2_DELEGATE_H


#include <list>
#include <algorithm>
#include <memory>
#include <stdexcept>


// Abstract class wrapper for function
template<typename ...Args>
class AbstractFunction{
public:
    // Default Constructors
    AbstractFunction() = default;
    AbstractFunction(const AbstractFunction<Args...> &) = default;

    // Pure virtual operator to call a function
    virtual void operator()(Args...) const = 0;
    // Virtual operators '==' and '!=' which use method is_equals
    virtual bool operator==(const AbstractFunction& other) const;
    virtual bool operator!=(const AbstractFunction& other) const;

protected:
    // Virtual method is_equals which checks if equal objects
    virtual bool _is_equals(const AbstractFunction<Args...> &other) const = 0;
};

template<typename... Args>
bool AbstractFunction<Args...>::operator==(const AbstractFunction &other) const {
    return _is_equals(other);
}

template<typename... Args>
bool AbstractFunction<Args...>::operator!=(const AbstractFunction &other) const {
    return (*this == other);
}


// Class wrapper for functions and static methods
template<typename ...Args>
class Function : public AbstractFunction<Args...> {
public:
    explicit Function(void (*foo)(Args...));

    // Operator to cll function
    void operator()(Args... arg) const override;

protected:
    // Virtual method is_equals which checks if equal objects
    bool _is_equals(const AbstractFunction<Args...> &other) const override;

private:
    // Function pointer
    void (*_f)(Args...);
};

template<typename... Args>
Function<Args...>::Function(void (*foo)(Args...)) :
        AbstractFunction<Args...>(){
    if(foo == nullptr) throw std::invalid_argument("functions pointer is empty");
    _f = foo;
}

template<typename... Args>
void Function<Args...>::operator()(Args... arg) const {
    _f(arg...);
}

template<typename... Args>
bool Function<Args...>::_is_equals(const AbstractFunction<Args...> &other) const {
    const auto _other = dynamic_cast<const Function<Args...>*>(&other);
    return (_other != nullptr && this->_f == _other->_f);
}


// Class wrapper for not static method
template<class ObjType, typename...Args>
class ObjectFunction : public AbstractFunction<Args...>{
public:
    explicit ObjectFunction(const ObjType &obj, void (ObjType::*f)(Args...));

    // Operator to cll function
    void operator()(Args ...args) const override;

protected:
    // Virtual method is_equals which checks if equal objects
    bool _is_equals(const AbstractFunction<Args...> &other) const override;

private:
    // Caller
    ObjType &_calling_object;
    // Function pointer
    void (ObjType::*_f)(Args...);
};

template<class ObjType, typename... Args>
ObjectFunction<ObjType, Args...>::ObjectFunction(const ObjType &obj, void (ObjType::*f)(Args...)) :
        AbstractFunction<Args...>(),
        _calling_object(const_cast<ObjType &>(obj)){
    if(f == nullptr) throw std::invalid_argument("functions pointer is empty");
    _f = f;
}

template<class ObjType, typename... Args>
void ObjectFunction<ObjType, Args...>::operator()(Args... args) const {
    (_calling_object.*_f)(args...);
}

template<class ObjType, typename... Args>
bool ObjectFunction<ObjType, Args...>::_is_equals(const AbstractFunction<Args...> &other) const {
    const auto _other = dynamic_cast<const ObjectFunction<ObjType, Args...>*>(&other);

    return (_other != nullptr && &this->_calling_object == &(_other->_calling_object)
            && this->_f == _other->_f);
}


// Class for storage wrapper for functions with signature void(Args...)
template<typename ...Args>
class MyEvent{
public:
    MyEvent() = default;
    ~MyEvent(){ this->clear(); }

    // Operator to call functions
    void operator()(Args ... args) const;

    // Methods for adding functions to the end of the list
    bool push_back(void (*f)(Args...));
    bool push_back(const Function<Args...> &handler);
    template<class ObjType>
    bool push_back(const ObjType &object, void(ObjType::*f)(Args...));
    template<class ObjType>
    bool push_back(const ObjectFunction<ObjType, Args...> &handler);

    // Function erase methods
    bool erase(void (*f)(Args...));
    bool erase(const Function<Args...> &handler);
    template<class ObjType>
    bool erase(const ObjType &object, void (ObjType::*f)(Args...));
    template<class ObjType>
    bool erase(const ObjectFunction<ObjType, Args...> &handler);

    // Method for erase all functions
    void clear(){ _handlers.clear(); }

private:
    // List of wrapper objects
    std::list<std::shared_ptr<AbstractFunction<Args...>>> _handlers;

    // Methods for adding some functions to the end of the list
    bool _insert_base_function(AbstractFunction<Args...> *handler);

    // Method for erase some function
    bool _delete_base_function(const AbstractFunction<Args...> &handler);

    // Find method
    typename std::list<std::shared_ptr<AbstractFunction<Args...>>>::const_iterator
    _find_handler(const AbstractFunction<Args...> &handler) const;
};

template<typename... Args>
void MyEvent<Args...>::operator()(Args... args) const {
    for (const std::shared_ptr<AbstractFunction<Args...>> &el : _handlers) {
        (*el)(args...);
    }
}

template<typename... Args>
bool MyEvent<Args...>::push_back(void (*f)(Args...)) {
    if(f == nullptr) return false;
    return _insert_base_function(new Function<Args...>(f));
}

template<typename... Args>
bool MyEvent<Args...>::push_back(const Function<Args...> &handler) {
    return _insert_base_function(new Function<Args...>(handler));
}

template<typename... Args>
template<class ObjType>
bool MyEvent<Args...>::push_back(const ObjType &object, void (ObjType::*f)(Args...)) {
    if(f == nullptr) return false;
    return _insert_base_function(new ObjectFunction<ObjType, Args...>(object, f));
}

template<typename... Args>
template<class ObjType>
bool MyEvent<Args...>::push_back(const ObjectFunction<ObjType, Args...> &handler) {
    return _insert_base_function(new ObjectFunction<ObjType, Args...>(handler));
}

template<typename... Args>
bool MyEvent<Args...>::erase(void (*f)(Args...)) {
    if(f == nullptr) return false;
    return _delete_base_function(Function<Args...>(f));
}

template<typename... Args>
bool MyEvent<Args...>::erase(const Function<Args...> &handler) {
    if(!handler) return false;
    return _delete_base_function(handler);
}

template<typename... Args>
template<class ObjType>
bool MyEvent<Args...>::erase(const ObjType &object, void (ObjType::*f)(Args...)) {
    if(f == nullptr) return false;
    return _delete_base_function(ObjectFunction<ObjType, Args...>(object, f));
}

template<typename... Args>
template<class ObjType>
bool MyEvent<Args...>::erase(const ObjectFunction<ObjType, Args...> &handler){
    if(!handler) return false;
    return _delete_base_function(handler);
}

template<typename... Args>
bool MyEvent<Args...>::_insert_base_function(AbstractFunction<Args...> *handler) {
    if(_find_handler(*handler) == _handlers.end()){
        _handlers.push_back(static_cast<std::shared_ptr<AbstractFunction<Args...>>>(handler));
        return true;
    }
    return false;
}

template<typename... Args>
bool MyEvent<Args...>::_delete_base_function(const AbstractFunction<Args...> &handler) {
    if(auto iter = _find_handler(handler); iter != _handlers.end()){
        _handlers.erase(iter);
        return true;
    }
    return false;
}

template<typename... Args>
typename std::list<std::shared_ptr<AbstractFunction<Args...>>>::const_iterator
MyEvent<Args...>::_find_handler(const AbstractFunction<Args...> &handler) const {
    return std::find_if(_handlers.cbegin(), _handlers.cend(),
                        [&handler](const std::shared_ptr<AbstractFunction<Args...>> &el){
                            return (*el == handler);
                        });
}


#endif //UNTITLED2_DELEGATE_H
