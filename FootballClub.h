//
// Created by maxim on 26.04.2020.
//

#ifndef COURSE_WORK_FOOTBALLCLUB_H
#define COURSE_WORK_FOOTBALLCLUB_H

#include "people/User.h"

class FootballClub {
public:
private:
    std::string _name;
    std::string _ground;
    std::size_t capacity;
    std::string league;

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

        [[nodiscard]] unsigned get_number() const {
            return _number;
        }

        [[nodiscard]] std::string get_position(){
            return _position;
        }
    private:
        unsigned _number;
        std::string _position;
    };

    std::vector<Footballer> _footballers;
};


#endif //COURSE_WORK_FOOTBALLCLUB_H
