//
// Created by maxim on 26.04.2020.
//

#include "FootballClub.h"


FootballClub::FootballClub(cr_str name, cr_str ground, cr_str league, std::size_t capacity) {
    _name = name;
    _ground = ground;
    _league = league;
    _capacity = capacity;
}

std::string FootballClub::get_name() const {
    return _name;
}

std::string FootballClub::get_ground() const {
    return _ground;
}

std::string FootballClub::get_league() const {
    return _league;
}

std::size_t FootballClub::get_capacity() const {
    return _capacity;
}

std::list<FootballClub::Footballer> FootballClub::get_footballers() const {
    return _footballers;
}

bool FootballClub::add_footballer(cr_str name, u_short number, cr_str position) {
    if(std::find(_footballers.cbegin(), _footballers.cend(),
            Footballer(name, this, number, position)) != _footballers.cend())
        return false;
    _footballers.emplace_back(name, this, number, position);
    return true;
}

bool FootballClub::erase_footballer(u_short number) {
    auto it = std::find_if(_footballers.cbegin(), _footballers.cend(),
            [&number](const Footballer &f){
                return f.get_number() == number;
            });
    if(it == _footballers.cend()) return false;
    _footballers.erase(it);
    return true;
}
