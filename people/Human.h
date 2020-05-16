//
// Created by maxim on 17.04.2020.
//

#ifndef COURSE_WORK_HUMAN_H
#define COURSE_WORK_HUMAN_H

#include "../stdafx.h"

class Human {
public:
    explicit Human(const std::string& f_name){
        if(f_name.empty()) {
            std::string msg = __PRETTY_FUNCTION__;
            throw std::invalid_argument("Name in " + msg + " is empty\n");
        }
        _name = f_name;
    }

    bool operator ==(const Human &other) const{
        return _is_equals(other);
    }

    bool operator !=(const Human &other) const{
        return !_is_equals(other);
    }

    [[nodiscard]] virtual std::string get_name() const {
        return _name;
    }

protected:
    std::string _name;

    virtual bool _is_equals(const Human &other) const = 0;
};


#endif //COURSE_WORK_HUMAN_H
