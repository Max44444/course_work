#ifndef COURSE_WORK_MAGAZINE_H
#define COURSE_WORK_MAGAZINE_H

#include "News.h"
#include "MyEvent.h"
#include "FootballClub.h"
#include "Human.h"
#include "FootballSeasons.h"
#include <map>


class User;


// Base program class
class Magazine {
public:
    Magazine() = default;
    Magazine(const Magazine&);

    // =========================*Methods for work with users*=============================
    // Method for user registration
    std::shared_ptr<User> registration(cr_str name, cr_str password);
    // Method for user authorization
    [[nodiscard]] std::shared_ptr<User> authorization(cr_str name, cr_str password) const;
    // Methods for subscribe users to something
    bool subscribe_user_to(const User *user, const std::shared_ptr<FootballClub> &club);
    bool subscribe_user_to(const User *user, const FootballClub::Footballer &footballer);

    // =========================*Methods for getting information*=========================
    // Method which return news list
    std::list<const News *> get_news();
    // Method which return football clubs list
    std::vector<std::shared_ptr<FootballClub>> get_clubs_in(cr_str country);
    // Method which return seasons list
    [[nodiscard]] FootballSeasons get_seasons() const;
    // Method which return country
    std::vector<std::string> get_countries();

    // =========================*Methods for refactor information*========================
    // Method for adding news
    bool add_news(const News *news, const std::initializer_list<std::string> &tags);
    // Method for erase news
    bool delete_news(const News &news);
    // Method for adding football club
    bool add_club(cr_str country, cr_str name, cr_str ground, cr_str league, std::size_t capacity);
    // Method for erase football club
    bool erase_club(cr_str country, cr_str club);
    // Method for adding footballer in club
    bool add_footballer_in(const std::shared_ptr<const FootballClub>& club, cr_str name, u_short number, cr_str position);
    // Method for erase footballer from club
    bool erase_footballer_in(const std::shared_ptr<const FootballClub>& club, cr_str name, u_short number);
    // Method which start season
    bool start_season(cr_str name);
    // Method which closed season
    bool close_season(const FootballSeasons::Season &);

private:
    std::map<std::string, std::vector<std::shared_ptr<FootballClub>>> _football_clubs;
    std::map<std::string, MyEvent<const News *>> _tags;
    std::list<std::shared_ptr<User>> _users;
    std::list<const News *> _news;
    FootballSeasons _seasons_list;

};


// Class User
class User : public Human {
public:
    User(cr_str name, cr_str password, Magazine *magazine);
    // Methods for user registration
    bool subscribe_to(const std::shared_ptr<FootballClub> &club);
    bool subscribe_to(const FootballClub::Footballer &footballer);
    // Method which return user's news
    [[nodiscard]] std::list<const News *> get_my_news() const;

protected:
    friend class Magazine;

    std::list<const News *> _my_news{};
    std::string _password;
    Magazine *_magazine;

    [[nodiscard]] bool _is_equals(const Human &other) const override;
    void add_news(const News *news);
};


#endif //COURSE_WORK_MAGAZINE_H
