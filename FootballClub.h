//
// Created by maxim on 26.04.2020.
//

#ifndef COURSE_WORK_FOOTBALLCLUB_H
#define COURSE_WORK_FOOTBALLCLUB_H

#include "people/User.h"
#include <string>
#include <utility>

class FootballClub {
public:
private:
    class Footballer : public Human{
    public:
        Footballer(const std::string& f_name, const std::string& l_name, unsigned number, const std::string& position) :
        Human(f_name, l_name), _number(number){
            _position = position;
        };

        std::string get_first_name() override {
            return this->_first_name;
        }

        std::string get_last_name() override {
            return this->_last_name;
        }
    private:
        unsigned _number;
        std::string _position;
    };

    std::string title;
};


#endif //COURSE_WORK_FOOTBALLCLUB_H
