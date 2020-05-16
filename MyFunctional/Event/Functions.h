//
// Created by maxim on 12.05.2020.
//

#ifndef COURSE_WORK_FUNCTIONS_H
#define COURSE_WORK_FUNCTIONS_H


template<typename ...Args>
class AbstractFunction{
public:
    AbstractFunction() = default;
    AbstractFunction(const AbstractFunction<Args...> &) = default;

    virtual void operator()(Args...) const = 0;

    virtual bool operator==(const AbstractFunction& other) const{
        return _is_equals(other);
    }

    virtual bool operator!=(const AbstractFunction& other) const{
        return (*this == other);
    }

protected:
    virtual bool _is_equals(const AbstractFunction<Args...> &other) const = 0;
};


template<typename ...Args>
class Function : public AbstractFunction<Args...> {
public:
    explicit Function(void (*foo)(Args...)) :
            AbstractFunction<Args...>(){
        _f = foo;
    }

    void operator()(Args... arg) const override{
        _f(arg...);
    }

protected:
    bool _is_equals(const AbstractFunction<Args...> &other) const override {
        const auto _other = dynamic_cast<const Function<Args...>*>(&other);
        return (_other != nullptr && this->_f == _other->_f);
    }

private:
    void (*_f)(Args...);
};


template<class ObjType, typename...Args>
class ObjectFunction : public AbstractFunction<Args...>{
public:
    explicit ObjectFunction(const ObjType &obj, void (ObjType::*f)(Args...)) :
            AbstractFunction<Args...>(),
            _calling_object(const_cast<ObjType &>(obj)), _f(f){}

    void operator()(Args ...args) const override {
        (_calling_object.*_f)(args...);
    }

protected:
    bool _is_equals(const AbstractFunction<Args...> &other) const override {
        const auto _other = dynamic_cast<const ObjectFunction<ObjType, Args...>*>(&other);

        return (_other != nullptr && &this->_calling_object == &(_other->_calling_object)
                && this->_f == _other->_f);
    }

private:
    ObjType &_calling_object;

    void (ObjType::*_f)(Args...);
};


#endif //COURSE_WORK_FUNCTIONS_H
