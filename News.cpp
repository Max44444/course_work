//
// Created by maxim on 06.05.2020.
//

#include "News.h"


News::News(cr_str title) {
    if(title.empty()) throw std::invalid_argument("title is empty");
    _title = title;
    time_t t = time(nullptr);
    _publication_date = localtime(&t);
}

News::News(const News &other) : News(other._title) {
    this->_publication_date = other._publication_date;
}

std::string News::get_tittle() const {
    return _title;
}

std::tm *News::get_publication_date() const {
    return _publication_date;
}

bool News::is_equals(const News &other) const {
    return (this->_title == other._title && this->_publication_date == other._publication_date);
}


Article::Article(cr_str title, cr_str &paragraph) : News(title) {
    if(paragraph.empty()) throw std::invalid_argument("Paragraph is empty");
    _paragraph = paragraph;
}

Article::Article(const Article &other) : Article(other._title, other._paragraph) {
    this->_publication_date = other._publication_date;
}

std::string Article::get_paragraph() const {
    return _paragraph;
}

bool Article::is_equals(const News &other) const {
    auto el = dynamic_cast<const Article *>(&other);
    return (el != nullptr && this->_title == el->_title &&
            this->_publication_date == el->_publication_date
            && this->_paragraph == el->_paragraph);
}


MatchAnnouncement::MatchAnnouncement(cr_str title, tm *date, const std::pair<std::string,
        std::string> &commands, cr_str season)
        : News(title){
    _event_date = date;
    if(commands.first.empty() || commands.second.empty()) throw std::invalid_argument("Command is empty");
    _commands = commands;
    _season = season;
}

MatchAnnouncement::MatchAnnouncement(const MatchAnnouncement &other) :
        MatchAnnouncement(other._title, other._event_date, other._commands, other._season){
    this->_publication_date = other._publication_date;
}

std::tm* MatchAnnouncement::get_event_date() const {
    return _event_date;
}

std::pair<std::string, std::string> MatchAnnouncement::get_commands() const {
    return _commands;
}

std::string MatchAnnouncement::get_season_name() const {
    return _season;
}

bool MatchAnnouncement::is_equals(const News &other) const {
    auto el = dynamic_cast<const MatchAnnouncement *>(&other);
    return (el != nullptr && this->_title == el->_title
            && this->_publication_date == el->_publication_date
            && this->_commands == el->_commands
            && this->_season == el->_season);
}

MatchResult::MatchResult(const std::string &title, const std::string &paragraph, MatchAnnouncement *match,
                         const std::pair<u_short, u_short> &score)
        : News(title), Article(title, paragraph),
          MatchAnnouncement(match->get_tittle(), match->get_event_date(),
                            match->get_commands(), match->get_season_name()){
    _score = score;
}

MatchResult::MatchResult(const MatchResult &other) :
        News(other._title), Article(other._title, other._paragraph),
        MatchAnnouncement(other._title, other._event_date,
                          other._commands, other._season){
    this->_score = other._score;
    this->_publication_date = other._publication_date;
}

std::pair<u_short, u_short> MatchResult::get_score() const {
    return _score;
}

bool MatchResult::is_equals(const News &other) const {
    auto el = dynamic_cast<const MatchResult *>(&other);
    return (el != nullptr && this->_title == el->_title
            && this->_publication_date == el->_publication_date
            && this->_score == el->_score
            && this->_paragraph == el->_paragraph
            && this->_commands == el->_commands
            && this->_season == el->_season);
}


std::ostream& operator <<(std::ostream &out, const News &news){
    if(dynamic_cast<const MatchResult *>(&news) != nullptr) {
        auto *other = dynamic_cast<const MatchResult *>(&news);
        out << std::asctime(other->get_publication_date()) << other->get_tittle() << "\n"
            << other->get_commands().first << "\tvs \t" << other->get_commands().second << '\n'
            << std::setw(other->get_commands().first.size()) << other->get_score().first << "\t : \t"
            << other->get_score().second << '\n'
            << std::asctime(other->get_event_date())
            << other->get_paragraph() << std::endl;
    }
    else if(dynamic_cast<const MatchAnnouncement *>(&news) != nullptr){
        auto *other = dynamic_cast<const MatchAnnouncement *>(&news);
        out << std::asctime(other->get_publication_date()) << other->get_tittle() << "\n"
            << other->get_commands().first << "\tvs \t" << other->get_commands().second << '\n'
            << std::setw(other->get_commands().first.size()) << '-' << "\t : \t-\n"
            << std::asctime(other->get_event_date()) << std::endl;
    }
    else if(dynamic_cast<const Article *>(&news) != nullptr){
        auto *other = dynamic_cast<const Article *>(&news);
        out << std::asctime(other->get_publication_date()) << other->get_tittle() << "\n"
            << '\t' << other->get_paragraph() << std::endl;
    }
    else{
        out << "News was deleted by Admin" << std::endl;
    }
    return out;
}
