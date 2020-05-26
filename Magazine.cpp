#include "Magazine.h"


std::list<const News *> Magazine::get_news() {
    return _news;
}

std::vector<std::shared_ptr<FootballClub>> Magazine::get_clubs_in(cr_str country) {
    auto it = _football_clubs.find(country);
    if(it == _football_clubs.end()){
        return std::vector<std::shared_ptr<FootballClub>>(0);
    }
    else{
        return it->second;
    }
}

std::shared_ptr<User> Magazine::registration(cr_str name, cr_str password) {
    if(authorization(name, password) == nullptr){
        auto user = std::make_shared<User>(name, password, this);
        _users.push_back(user);
        return user;
    } else{
        return nullptr;
    }
}

std::shared_ptr<User> Magazine::authorization(cr_str name, cr_str password) const {
    auto it = std::find_if(_users.begin(), _users.end(),
                           [&name, &password](const std::shared_ptr<User> &user){
                               return (user->_name == name && user->_password == password);
                           });
    return it == _users.cend() ? nullptr : *it;
}

bool Magazine::subscribe_user_to(const User *user, const std::shared_ptr<FootballClub> &club) {
    auto tag = club->get_name();
    auto it = _tags.find(tag);
    if(it != _tags.end()){
        it->second.push_back(*(user), &User::add_news);
        return true;
    }
    return false;
}

bool Magazine::subscribe_user_to(const User *user, const FootballClub::Footballer &footballer) {
    auto tag = footballer.get_club()->get_name() + "_" + footballer.get_name() + "_"
               + std::to_string(footballer.get_number());
    auto it = _tags.find(tag);
    if(it != _tags.end()){
        it->second.push_back(*(user), &User::add_news);
        return true;
    }
    return false;
}

FootballSeasons Magazine::get_seasons() const {
    return _seasons_list;
}


bool Magazine::add_news(const News *news, const std::initializer_list<std::string> &tags) {
    if(auto res = dynamic_cast<const MatchResult *>(news); res != nullptr){
        auto season = _seasons_list.find_season(res->get_season_name());
        if(season == nullptr) throw std::invalid_argument("Can not find season");
        if(season->is_ended()) throw std::invalid_argument("This season was ended");
        season->add_match(res);
    }
    for(const auto &el : tags){
        auto it = _tags.find(el);
        if(it == _tags.end()){
            throw std::invalid_argument("tags list is not correct");
        }
    }
    _news.push_back(news);

    for(const auto &el : tags){
        _tags[el](news);
    }
    return true;
}

bool Magazine::delete_news(const News &news) {
    auto it = std::find(_news.cbegin(), _news.cend(), &news);
    if(it == _news.end()){
        return false;
    }
    _news.erase(it);
    return true;
}

bool Magazine::add_club(cr_str country, cr_str name, cr_str ground, cr_str league, std::size_t capacity) {
    if(std::find_if(_football_clubs[country].cbegin(), _football_clubs[country].cend(),
                    [&name](const std::shared_ptr<const FootballClub> &other){
                        return name == other->get_name();
                    }) == _football_clubs[country].cend()) {
        _football_clubs[country].push_back(std::make_shared<FootballClub>(name, ground, league, capacity));
        _tags.emplace(name, MyEvent<const News *>());
        return true;
    }
    return false;
}

bool Magazine::erase_club(cr_str country, cr_str club) {
    auto it = std::find_if(_football_clubs[country].cbegin(), _football_clubs[country].cend(),
                           [&club](const std::shared_ptr<const FootballClub> &other){
                               return (club == other->get_name());
                           });
    if(it == _football_clubs[country].end()){
        return false;
    }
    _football_clubs[country].erase(it);
    _tags.erase(club);
    return true;
}

bool Magazine::add_footballer_in(const std::shared_ptr<const FootballClub>& club,
                                 const std::string &name, u_short number,const std::string &position) {
    if(const_cast<FootballClub *>(club.get())->add_footballer(name, number, position)){
        std::string tmp = club->get_name() + "_" + name + "_" + std::to_string(number);
        _tags.emplace(tmp, MyEvent<const News *>());
        return true;
    }
    return false;
}

bool Magazine::erase_footballer_in(const std::shared_ptr<const FootballClub>& club, cr_str name, u_short number) {
    if(const_cast<FootballClub *>(club.get())->erase_footballer(number)){
        std::string tmp = club->get_name() + "_" + name + "_" + std::to_string(number);
        _tags.erase(tmp);
        return true;
    }
    return false;
}

Magazine::Magazine(const Magazine &) {
    for(auto *el : _news){
        delete el;
    }
    _news.clear();
}

bool Magazine::start_season(cr_str name) {
    return _seasons_list.start_season(name);
}

bool Magazine::close_season(const FootballSeasons::Season &season) {
    auto s = _seasons_list.find_season(season.get_name());
    return s->close_season();
}

std::vector<std::string> Magazine::get_countries() {
    std::vector<std::string> res;//(_football_clubs.size());
    for(const auto &el : _football_clubs)
        res.push_back(el.first);
    return res;
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

bool User::subscribe_to(const std::shared_ptr<FootballClub> &club) {
    return _magazine->subscribe_user_to(this, club);
}

bool User::subscribe_to(const FootballClub::Footballer &footballer) {
    return _magazine->subscribe_user_to(this, footballer);
}

void User::add_news(const News *news) {
    _my_news.push_back(news);
}
