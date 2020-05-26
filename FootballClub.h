//
// Created by maxim on 26.04.2020.
//

#ifndef COURSE_WORK_FOOTBALLCLUB_H
#define COURSE_WORK_FOOTBALLCLUB_H


#include "Human.h"
#include <list>
#include <algorithm>


// Class abstraction football club
class FootballClub {
public:
    // Composition of class footballer
    class Footballer : public Human{
    public:
        Footballer(cr_str name, const FootballClub * club, u_short number, cr_str position) :
                Human(name), _number(number) {
            if(!club) throw std::invalid_argument("Club pointer is empty");
            _club = club;
            _position = position;
        };

        // Method which return footballer's number
        [[nodiscard]] unsigned get_number() const {
            return _number;
        }

        // Method which return footballer's position
        [[nodiscard]] std::string get_position() const{
            return _position;
        }

        // Method which return pointer to footballer's club
        [[nodiscard]] const FootballClub *get_club() const{
            return _club;
        }

    protected:
        // Method for comparison footballers
        [[nodiscard]] bool _is_equals(const Human &other) const override{
            auto _other = dynamic_cast<const FootballClub::Footballer *>( &other);
            return (_other->_club->_name == this->_club->_name && this->_name ==
                                                                  _other->_name && this->_number == _other->_number);
        }

    private:

        std::string _position;
        const FootballClub * _club;
        u_short _number;
    };

    FootballClub(cr_str name, cr_str ground, cr_str league, std::size_t capacity);
    // Method which return club's name
    [[nodiscard]] std::string get_name() const;
    // Method which return club's ground name
    [[nodiscard]] std::string get_ground() const;
    // Method which return club's league name
    [[nodiscard]] std::string get_league() const;
    // Method which return club's capacity
    [[nodiscard]] std::size_t get_capacity() const;
    // Method which return club's footballers list
    [[nodiscard]] std::list<Footballer> get_footballers() const;
    // Method for adding footballer in club
    bool add_footballer(cr_str name, u_short number, cr_str position);
    // Method for erase footballer from club
    bool erase_footballer(u_short number);
    // Comparison operators
    bool operator==(const FootballClub &other){
        return _name == other._name && _footballers == other._footballers;
    }
    bool operator!=(const FootballClub &other){
        return !(*this == other);
    }

private:
    std::list<Footballer> _footballers;
    std::string _name;
    std::string _ground;
    std::string _league;
    std::size_t _capacity;

};


#endif //COURSE_WORK_FOOTBALLCLUB_H
