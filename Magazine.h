//
// Created by maxim on 17.04.2020.
//

#ifndef COURSE_WORK_MAGAZINE_H
#define COURSE_WORK_MAGAZINE_H

#include "stdafx.h"
#include "functional/News.h"
#include "MyFunctional/Event/MyEvent.h"
#include "FootballClub.h"
#include "people/Human.h"


class User;
class Admin;


class Magazine {
public:
    Magazine() = default;
    Magazine(const Magazine&) = default;
    ~Magazine();
    std::list<const News *> get_news(std::size_t quantity=0);
    std::vector<const FootballClub *> get_clubs_in(cr_str country);
    User *registration(cr_str name, cr_str password);
    [[nodiscard]] User *authorization(cr_str name, cr_str password) const;
    bool subscribe_user_to(const User *user, cr_str tag);

private:
    friend class Admin;
    class AdditionalOptions{
        friend class Magazine;

    public:
        bool add_news(const News &news, const std::initializer_list<std::string> &tags);
        bool delete_news(const News &news);
        bool add_club(cr_str country, cr_str name, cr_str ground, cr_str league, std::size_t capacity);
        bool erase_club(cr_str country, cr_str club);
        bool add_footballer_in(FootballClub *club, cr_str name, u_short number, cr_str position);
        bool erase_footballer_in(FootballClub *club, cr_str name, u_short number);

    private:
        const Magazine *_parent;
        std::list<const User *> _users;
        std::list<const News *> _news;
        std::map<std::string, std::vector<const FootballClub *>> _football_clubs;
        std::map<std::string, MyEvent<const News *>> _tags;
    };
    AdditionalOptions AdminOptions;
};


class User : public Human {
public:
    User(cr_str name, cr_str password, Magazine *magazine);
    virtual ~User() = default;
    bool subscribe_to(cr_str event);
    [[nodiscard]] std::list<const News *> get_my_news() const;

protected:
    friend class Magazine;

    Magazine *_magazine;
    std::list<const News *> _my_news{};
    std::string _password;
    [[nodiscard]] bool _is_equals(const Human &other) const override;
    void add_news(const News *news);
};


class Admin : public User{
public:
    Admin(cr_str name, cr_str password, Magazine *magazine): User(name, password, magazine){}
    ~Admin() override = default;
    bool add_news(const News &news, const std::initializer_list<std::string> &tags);
    bool delete_news(const News &news);
    bool add_club(cr_str country, cr_str name, cr_str ground, cr_str league, std::size_t capacity);
    bool erase_club(cr_str country, cr_str club);
    bool add_footballer_in(FootballClub *club, cr_str name, u_short number, cr_str position);
    bool erase_footballer_in(FootballClub *club, cr_str name, u_short number);
};


#endif //COURSE_WORK_MAGAZINE_H
