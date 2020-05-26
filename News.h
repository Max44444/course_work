//
// Created by maxim on 06.05.2020.
//

#ifndef COURSE_WORK_NEWS_H
#define COURSE_WORK_NEWS_H


#include <ctime>
#include <ostream>
#include <string>
#include <iomanip>


using cr_str = const std::string &;


// Class News
class News {
public:
    // Method which return title
    [[nodiscard]] std::string get_tittle() const;
    // Method which return publication date;
    [[nodiscard]] std::tm *get_publication_date() const;
    bool operator==(const News &other){ return is_equals(other);}
    bool operator!=(const News &other){ return !(*this == other);}

protected:
    explicit News(cr_str title);
    News(const News &);
    [[nodiscard]] virtual bool is_equals(const News &other) const;
    // output operator
    friend std::ostream& operator <<(std::ostream &out, const News &news);
    std::string _title;
    std::tm *_publication_date;
};


// Class for storage News with paragraph
class Article : public virtual News{
public:
    Article(cr_str title, cr_str paragraph);
    Article(const Article &);
    // Method which return paragraph
    [[nodiscard]] std::string get_paragraph() const;

protected:
    [[nodiscard]] bool is_equals(const News &other) const override;
    std::string _paragraph;
};


// Class for storage match announcement
class MatchAnnouncement : public virtual News{
public:
    MatchAnnouncement(cr_str title, tm *date, const std::pair<std::string, std::string> &commands, cr_str season);
    MatchAnnouncement(const MatchAnnouncement &);
    // Method which return event date;
    [[nodiscard]] std::tm* get_event_date() const;
    // Method which return commands names
    [[nodiscard]] std::pair<std::string, std::string> get_commands() const;
    // Method which return season name
    [[nodiscard]] std::string get_season_name() const;

protected:
    [[nodiscard]] bool is_equals(const News &other) const override;
    std::pair<std::string, std::string> _commands;
    std::string _season;
    std::tm* _event_date;
};


// Class for storage match result
class MatchResult : public Article, public MatchAnnouncement{
public:
    MatchResult(cr_str tittle, cr_str paragraph, MatchAnnouncement *match,
                const std::pair<u_short, u_short> &score);
    MatchResult(const MatchResult &);
    // Method which return score
    [[nodiscard]] std::pair<u_short, u_short> get_score() const;
private:
    [[nodiscard]] bool is_equals(const News &other) const override;
    std::pair<u_short, u_short> _score;
};


#endif //COURSE_WORK_NEWS_H
