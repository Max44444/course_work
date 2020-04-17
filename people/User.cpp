//
// Created by maxim on 17.04.2020.
//

#include "User.h"

#include <utility>
#include <stdexcept>
#include <iostream>

std::size_t User::quantity = 0;

User::User(std::string f_name, std::string l_name){
    try {
        if(f_name.empty() || l_name.empty())
            throw std::invalid_argument("First or last name are empty\n");
    }
    catch (const std::invalid_argument &ex){
        std::cerr << "Invalid argument: " << ex.what() << std::endl;
    }


    this->__first_name = std::move(f_name);
    this->__last_name = std::move(l_name);
    ++quantity;
}

User::~User() {
    --quantity;
}

std::string User::get_first_name() {
    return __first_name;
}

std::string User::get_last_name() {
    return __last_name;
}
std::size_t User::get_quantity() {
    return  quantity;
}