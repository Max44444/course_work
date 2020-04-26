//
// Created by maxim on 17.04.2020.
//

#ifndef COURSE_WORK_HUMAN_H
#define COURSE_WORK_HUMAN_H

#include "../stdafx.h"

class Human {
public:
    Human(const std::string& f_name, const std::string& l_name){
        if(f_name.empty() || l_name.empty()) {
            std::string msg = __PRETTY_FUNCTION__;
            throw std::invalid_argument("First or last name in " + msg + " are empty\n");
        }
        _first_name = f_name;
        _last_name = l_name;
    }

    virtual std::string get_first_name() = 0;
    virtual std::string get_last_name() = 0;

protected:
    std::string _first_name;
    std::string _last_name;
};


#endif //COURSE_WORK_HUMAN_H
