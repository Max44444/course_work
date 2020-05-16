//
// Created by maxim on 26.04.2020.
//

#ifndef COURSE_WORK_FOOTBALLCLUB_H
#define COURSE_WORK_FOOTBALLCLUB_H

#include "people/Human.h"

class FootballClub {
    class Footballer;
public:
    FootballClub(cr_str name, cr_str ground, cr_str league, std::size_t capacity);
    [[nodiscard]] std::string get_name() const;
    [[nodiscard]] std::string get_ground() const;
    [[nodiscard]] std::string get_league() const;
    [[nodiscard]] std::size_t get_capacity() const;
    [[nodiscard]] std::list<Footballer> get_footballers() const;
    bool add_footballer(cr_str name, u_short number, cr_str position);
    bool erase_footballer(u_short number);
    bool operator==(const FootballClub &other){
        return _name == other._name && _footballers == other._footballers;
    }

private:
    std::string _name;
    std::string _ground;
    std::string _league;
    std::size_t _capacity;
    std::list<Footballer> _footballers;

    class Footballer : public Human{
    public:
        Footballer(cr_str name, const FootballClub * club, u_short number, cr_str position) :
                Human(name), _number(number), _club(club){
            _position = position;
        };

        [[nodiscard]] const FootballClub* get_club(){
            return this->_club;
        }

        [[nodiscard]] unsigned get_number() const {
            return _number;
        }

        [[nodiscard]] std::string get_position() const{
            return _position;
        }

    private:
        bool _is_equals(const Human &other) const override{
            auto _other = dynamic_cast<const FootballClub::Footballer *>( &other);
            return (_other->_club->_name == this->_club->_name && this->_name ==
            _other->_name && this->_number == _other->_number);
        }

        const FootballClub * _club;
        u_short _number;
        std::string _position;
    };
};


#endif //COURSE_WORK_FOOTBALLCLUB_H
