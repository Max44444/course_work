//
// Created by maxim on 17.04.2020.
//

#ifndef COURSE_WORK_USER_H
#define COURSE_WORK_USER_H

#include "Human.h"

class User : public Human {
public:
    User(const std::string &f_name, const std::string &l_name);
    ~User();

    std::string get_first_name() override;
    std::string get_last_name() override;

    static std::size_t get_quantity();
private:
    static std::size_t quantity;
};


#endif //COURSE_WORK_USER_H
