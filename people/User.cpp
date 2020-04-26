//
// Created by maxim on 17.04.2020.
//

#include "User.h"


std::size_t User::quantity = 0;

User::User(const std::string& f_name, const std::string& l_name) : Human(f_name, l_name){
    ++quantity;
}

User::~User() {
    --quantity;
}

std::string User::get_first_name() {
    return _first_name;
}

std::string User::get_last_name() {
    return _last_name;
}
std::size_t User::get_quantity() {
    return  quantity;
}