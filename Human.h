//
// Created by maxim on 17.04.2020.
//

#ifndef COURSE_WORK_HUMAN_H
#define COURSE_WORK_HUMAN_H


#include <iostream>

using cr_str = const std::string &;

class Human {
public:
    // Constructor
    explicit Human(cr_str f_name){
        if(f_name.empty()) {
            throw std::invalid_argument("Name is empty\n");
        }
        _name = f_name;
    }

    // operators for comparison objects
    bool operator ==(const Human &other) const{
        return _is_equals(other);
    }

    bool operator !=(const Human &other) const{
        return !_is_equals(other);
    }

    // Method which return human's name
    [[nodiscard]] virtual std::string get_name() const {
        return _name;
    }

protected:
    std::string _name;

    // Method for comparison
    [[nodiscard]] virtual bool _is_equals(const Human &other) const = 0;
};


#endif //COURSE_WORK_HUMAN_H
