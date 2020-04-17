//
// Created by maxim on 17.04.2020.
//

#ifndef COURSE_WORK_HUMAN_H
#define COURSE_WORK_HUMAN_H

#include <string>

class Human {
public:
    virtual std::string get_first_name() = 0;
    virtual std::string get_last_name() = 0;
protected:
    std::string __first_name;
    std::string __last_name;
};


#endif //COURSE_WORK_HUMAN_H
