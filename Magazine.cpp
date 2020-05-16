//
// Created by maxim on 17.04.2020.
//

#include "Magazine.h"



Magazine::~Magazine() {
    for(auto *el : AdminOptions._users){
        delete el;
    }
    AdminOptions._users.clear();
}

std::list<const News  *> Magazine::get_news(std::size_t quantity) {
    return AdminOptions._news;
}

std::vector<const FootballClub *> Magazine::get_clubs_in(cr_str country) {
    auto it = AdminOptions._football_clubs.find(country);
    if(it == AdminOptions._football_clubs.end()){
        return std::vector<const FootballClub *>(0);
    }
    else{
        return it->second;
    }
}


User *Magazine::registration(cr_str name, cr_str password) {
    if(authorization(name, password) == nullptr){
        auto *user = new User(name, password, this);
        AdminOptions._users.push_back(user);
        return user;
    } else{
        return nullptr;
    }
}

User *Magazine::authorization(cr_str name, cr_str password) const {
    auto it = std::find_if(AdminOptions._users.cbegin(), AdminOptions._users.cend(),
            [&name, &password](const User *user){
                return (user->_name == name && user->_password == password);
            });
    return it == AdminOptions._users.cend() ? nullptr : const_cast<User *>(*it);
}

bool Magazine::subscribe_user_to(const User *user, const std::string &tag) {
    auto it = AdminOptions._tags.find(tag);
    if(it != AdminOptions._tags.end()){
        it->second.push_back(*user, &User::add_news);
        return true;
    }
    return false;
}


bool Magazine::AdditionalOptions::add_news(const News &news, const std::initializer_list<std::string> &tags) {
    std::list<MyEvent<const News *>> events;
    for(const auto &el : tags){
        auto it = _tags.find(el);
        if(it == _tags.end()){
            throw std::invalid_argument("tags list is not correct");
            return false;
        }
        events.push_back(it->second);
    }
    for(const auto& el : events){
        el(&news);
    }
    return true;
}

bool Magazine::AdditionalOptions::delete_news(const News &news) {
    auto it = std::find(_news.cbegin(), _news.cend(), &news);
    if(it == _news.end()){
        return false;
    }
    delete *it;
    _news.erase(it);
    return true;
}

bool Magazine::AdditionalOptions::add_club(cr_str country, cr_str name, cr_str ground,
                                           cr_str league, std::size_t capacity) {
    if(std::find_if(_football_clubs[country].cbegin(), _football_clubs[country].cend(),
                    [&name](const FootballClub* other){
                        return name == other->get_name();
                    }) == _football_clubs[country].cend()) {
        _football_clubs[country].push_back(new FootballClub(name, ground, league, capacity));
        _tags.emplace(name, MyEvent<const News *>());
        return true;
    }
    return false;
}

bool Magazine::AdditionalOptions::erase_club(cr_str country, cr_str club) {
    auto it = std::find_if(_football_clubs[country].cbegin(), _football_clubs[country].cend(),
                        [&club](const FootballClub *other){
                            return (club == other->get_name());
                        });
    if(it == _football_clubs[country].end()){
        return false;
    }
    _football_clubs[country].erase(it);
    _tags.erase(club);
    return true;
}

bool Magazine::AdditionalOptions::add_footballer_in(FootballClub *club,
        const std::string &name, u_short number,const std::string &position) {
    if(club->add_footballer(name, number, position)){
        std::string tmp = club->get_name() + "_" + name + "_" + std::to_string(number);
        _tags.emplace(tmp, MyEvent<const News *>());
        return true;
    }
    return false;
}

bool Magazine::AdditionalOptions::erase_footballer_in(FootballClub *club, cr_str name, u_short number) {
    if(club->erase_footballer(number)){
        std::string tmp = club->get_name() + "_" + name + "_" + std::to_string(number);
        _tags.erase(tmp);
        return true;
    }
    return false;
}


User::User(cr_str name, cr_str password, Magazine *magazine)
        : Human(name) {
    if(password.empty()) throw std::invalid_argument("password can not be empty");
    _password = password;
    if(magazine == nullptr) throw std::invalid_argument("Magazine is empty");
    _magazine = magazine;
}

bool User::_is_equals(const Human &other) const {
    const auto _other = dynamic_cast<const User*>(&other);
    return (_other != nullptr && this->_name == _other->_name && this->_password == _other->_password);
}

std::list<const News *> User::get_my_news() const {
    return _my_news;
}

bool User::subscribe_to(cr_str event) {
    return _magazine->subscribe_user_to(this, event);
}

void User::add_news(const News *news) {
    _my_news.push_back(news);
}

bool Admin::add_news(const News &news, const std::initializer_list<std::string> &tags) {
    return _magazine->AdminOptions.add_news(news, tags);
}

bool Admin::delete_news(const News &news) {
    return _magazine->AdminOptions.delete_news(news);
}

bool Admin::add_club(const std::string &country, const std::string &name, const std::string &ground,
                     const std::string &league, std::size_t capacity) {
    return _magazine->AdminOptions.add_club(country, name, ground, league, capacity);
}

bool Admin::erase_club(const std::string &country, const std::string &club) {
    return _magazine->AdminOptions.erase_club(country, club);
}

bool
Admin::add_footballer_in(FootballClub *club, const std::string &name, u_short number, const std::string &position) {
    return _magazine->AdminOptions.add_footballer_in(club, name, number, position);
}

bool Admin::erase_footballer_in(FootballClub *club, const std::string &name, u_short number) {
    return _magazine->AdminOptions.erase_footballer_in(club, name, number);
}
