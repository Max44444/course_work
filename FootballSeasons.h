#ifndef COURSE_WORK_SEASONS_H
#define COURSE_WORK_SEASONS_H


#include "News.h"
#include <memory>
#include <vector>
#include <memory>


// Class abstraction for football's season
class FootballSeasons {
public:
    // Composition of class Season
    class Season{
    public:
        explicit Season(cr_str name){
            if(name.empty()) throw std::invalid_argument("Season name can not be empty");
            _name = name;
            _is_ended = false;
        }

        Season(const Season &) = default;

        // Method for adding football match
        void add_match(const MatchResult *match){
            if(_is_ended) return;
            if(!match) throw std::invalid_argument("match is empty");
            matches.push_back(std::shared_ptr<const MatchResult>(match));
        }

        // Method which return const match list
        std::vector<std::shared_ptr<const MatchResult>> get_matches(){
            return matches;
        }

        // Method for close season
        bool close_season(){
            if(!_is_ended) return false;
            _is_ended = true;
            return true;
        }

        // Method closing check
        [[nodiscard]] bool is_ended() const {
            return _is_ended;
        }

        // Method which return season's name
        [[nodiscard]] std::string get_name() const{
            return _name;
        }

    private:
        std::vector<std::shared_ptr<const MatchResult>> matches;
        std::string _name;
        bool _is_ended;
    };

    FootballSeasons() = default;

    // Method for start season
    bool start_season(cr_str name){
        if(find_season(name)) return false;
        _seasons.emplace_back(std::make_shared<Season>(name));
        return true;
    }

    // Method which return seasons list
    std::vector<std::shared_ptr<Season>> get_seasons(){
        return _seasons;
    }

    // Method for searching season
    std::shared_ptr<Season> find_season(cr_str name){
        auto season = std::find_if(_seasons.begin(), _seasons.end(),
                [name](const std::shared_ptr<Season> &other){
            return name == other->get_name();
        });
        return season == _seasons.cend() ? nullptr : *season.base();
    }

private:
    std::vector<std::shared_ptr<Season>> _seasons;
};


#endif //COURSE_WORK_SEASONS_H
