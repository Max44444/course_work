//
// Created by maxim on 06.05.2020.
//

#ifndef COURSE_WORK_NEWS_H
#define COURSE_WORK_NEWS_H


#include "../stdafx.h"
#include <ctime>



/*
struct Date{
    u_int hour{}, minutes{}, seconds{},
    day{}, month{}, year{};
    [[nodiscard]] tm *parse_to_announcement_date() const{
        time_t t = time(nullptr);
        tm *time_info = localtime(&t);
        if(time_info->tm_year <= year - 1900) {
            if (time_info->tm_mon <= month) {
                if (time_info->tm_mday <= day) {
                    throw std::invalid_argument("date format is wrong");
                }
            }
        }
        time_info->tm_year = year - 1900;
        time_info->tm_mon = month;
        time_info->tm_mday = day;
        time_info->tm_hour = hour;
        time_info->tm_min = minutes;
        time_info->tm_sec = seconds;
        mktime(time_info);
        return time_info;
    }

    static Date parse_from_time_to_date(tm* time_info){
        Date d{};
        d.seconds = time_info->tm_sec;
        d.minutes = time_info->tm_min;
        d.hour = time_info->tm_hour;
        d.day = time_info->tm_mday;
        d.month = time_info->tm_mon;
        d.year = time_info->tm_year + 1900;
        return d;
    }
};*/


class News {
public:
    explicit News(cr_str title);
    [[nodiscard]] std::string get_tittle() const;
    [[nodiscard]] std::tm *get_publication_date() const;
    virtual ~News() = default;

protected:
    std::string _title;
    std::tm *_publication_date;
};


class Article : public virtual News{
public:
    Article(cr_str title, cr_str paragraph);
    [[nodiscard]] std::string get_paragraph() const;
    ~Article() override = default;;

protected:
    std::string _paragraph;
};


class MatchAnnouncement : public virtual News{
public:
    MatchAnnouncement(cr_str title, tm *date, const std::pair<std::string, std::string> &commands);
    [[nodiscard]] std::tm* get_event_date() const;
    [[nodiscard]] std::pair<std::string, std::string> get_commands() const;
    ~MatchAnnouncement() override = default;

protected:
    std::tm* _event_date;
    std::pair<std::string, std::string> _commands;
};


class MatchResult : public Article, public MatchAnnouncement{
public:
    MatchResult(cr_str tittle, cr_str paragraph, const MatchAnnouncement& match,
                const std::pair<u_short, u_short> &score);
    [[nodiscard]] std::pair<u_short, u_short> get_score() const;
private:
    std::pair<u_short, u_short> _score;
};


#endif //COURSE_WORK_NEWS_H
