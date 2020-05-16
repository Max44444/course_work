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

std::string News::get_tittle() const {
    return _title;
}

std::tm *News::get_publication_date() const {
    return _publication_date;
}


Article::Article(cr_str title, cr_str &paragraph) : News(title) {
    if(paragraph.empty()) throw std::invalid_argument("Paragraph is empty");
    _paragraph = paragraph;
}

std::string Article::get_paragraph() const {
    return _paragraph;
}

MatchAnnouncement::MatchAnnouncement(cr_str title, tm *date, const std::pair<std::string, std::string> &commands)
: News(title){
    _event_date = date;
    if(commands.first.empty() || commands.second.empty()) throw std::invalid_argument("Command is empty");
    _commands = commands;
}

std::tm* MatchAnnouncement::get_event_date() const {
    return _event_date;
}

std::pair<std::string, std::string> MatchAnnouncement::get_commands() const {
    return _commands;
}

MatchResult::MatchResult(const std::string &title, const std::string &paragraph, const MatchAnnouncement& match,
                         const std::pair<u_short, u_short> &score)
                         : News(title), Article(title, paragraph),
                         MatchAnnouncement(title, match.get_event_date(), match.get_commands()){
    _score = score;
}

std::pair<u_short, u_short> MatchResult::get_score() const {
    return _score;
}
