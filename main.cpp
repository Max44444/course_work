#include <iostream>
#include "Magazine.h"
#include <cstdlib>

using namespace std;
Magazine get_mag();

int get_value(std::initializer_list<int> values);
std::shared_ptr<User> initialized(Magazine &);

int main() {
    auto mag = get_mag();
    auto user = initialized(mag);
    while(true) {
        std::cout << "Choose operation:\n"
                  << "\t1 - Get news list\n"
                  << "\t2 - Get my recommendation\n"
                  << "\t3 - Get command list\n"
                  << "\t4 - exit\n";
        auto res = get_value({1, 2, 3, 4});
        if (res == 1) {
            for (auto el : mag.get_news())
                std::cout << (*el) << std::endl;
        } else if (res == 2) {
            for (auto el : user->get_my_news())
                std::cout << (*el) << std::endl;
        } else if (res == 3) {
            std::cout << "Enter country number\n";
            auto c = mag.get_countries();
            for (int i = 1; i <= c.size(); ++i) {
                std::cout << i << " - " << c[i - 1] << std::endl;
            }
            while (true) {
                std::cin >> res;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                } else if (res > 0 && res <= c.size()) {
                    break;
                }
            }
            auto clubs = mag.get_clubs_in(c[res - 1]);
            for (int i = 1; i < clubs.size(); ++i) {
                std::cout << i << " = " << clubs[i - 1]->get_name() << std::endl;
            }
            std::cout << "1 - subscribe to command\n";
            std::cout << "2 - get footballers\n";
            std::cout << "3 - exit\n";
            res = get_value({1, 2, 3});
            if (res != 3) {
                std::cout << "Enter club number\n";
                int res2{};
                while (true) {
                    std::cin >> res2;
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(32767, '\n');
                    } else if (res2 > 0 && res2 <= clubs.size()) {
                        break;
                    }
                }
                if (res == 1) {
                    user->subscribe_to(clubs[res2 - 1]);
                } else {
                    for (const auto &el : clubs[res2 - 1]->get_footballers())
                        std::cout << el.get_name() << ' ' << el.get_number() << ' ' << el.get_position() << std::endl;
                }
            }
        } else
            return 0;
        std::cout << std::endl;
    }
}

int get_value(std::initializer_list<int> values){
    while(true) {
        int a;
        std::cin >> a;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
        }
        else{
            for(auto el : values){
                if(a == el){
                    return a;
                }
            }
        }
        std::cout << "Wrong operation!!!\nPlease try again" << std::endl;
    }
}

std::shared_ptr<User> initialized(Magazine &mag){
    while(true) {
        cout << "Choose operation:\n"
             << "\t1 - Registration\n"
             << "\t2 - Authorization\n"
             << "\t3 - exit\n";
        int res = get_value({1, 2, 3});
        if(res == 3) std::exit(0);

        string name, password;
        std::cin.ignore(32767, '\n');
        cout << "name : ";
        getline(cin, name);
        cout << "password : ";
        getline(cin, password);
        std::shared_ptr<User> user = nullptr;

        try {
            switch (res) {
                case 1:
                    user = mag.registration(name, password);
                    break;
                case 2:
                    user = mag.authorization(name, password);
                    break;
                default:
                    break;
            }
        }
        catch (std::invalid_argument &er) {
            std::cout << er.what() << std::endl;
        }

        if(user != nullptr) return user;
        std::cout << "Error data, try again\n\n";
    }
}

Magazine get_mag(){
    Magazine mag;
    mag.add_club("Ukraine", "Dynamo", "NSC Olimpiyskiy",
                  "Ukrainian Premier League", 70050);
    auto clubs = mag.get_clubs_in("Ukraine");
    mag.add_footballer_in(clubs[0], "Heorhiy Bushchan", 1, "GK");
    mag.add_footballer_in(clubs[0], "Denys Popov", 4, "DF");
    mag.add_footballer_in(clubs[0], "Serhiy Sydorchuk", 5, "MF");
    mag.add_footballer_in(clubs[0], "Mohammed Kadiri", 6, "MF");
    mag.add_footballer_in(clubs[0], "Benjamin Verbic", 7, "MF");
    mag.add_footballer_in(clubs[0], "Volodymyr Shepelyev", 8, "MF");
    mag.add_footballer_in(clubs[0], "Fran Sol", 9, "FW");
    mag.add_footballer_in(clubs[0], "Mykola Shaparenko", 10, "MF");
    mag.add_footballer_in(clubs[0], "Heorhiy Tsitaishvili", 11, "MF");
    mag.add_footballer_in(clubs[0], "Carlos de Pena", 14, "MF");
    mag.add_footballer_in(clubs[0], "Viktor Tsyhankov", 15, "MF");
    mag.add_footballer_in(clubs[0], "Vitaliy Mykolenko", 16, "DF");
    mag.add_footballer_in(clubs[0], "Oleksandr Andriyevskyi", 18, "MF");
    mag.add_footballer_in(clubs[0], "Oleksandr Karavayev", 20, "DF");
    mag.add_footballer_in(clubs[0], "Josip Pivaric", 23, "DF");
    mag.add_footballer_in(clubs[0], "Mykyta Burda", 26, "DF");
    mag.add_footballer_in(clubs[0], "Yevhen Isayenko", 27, "FW");
    mag.add_footballer_in(clubs[0], "Vitaliy Buyalskyi", 29, "MF");
    mag.add_footballer_in(clubs[0], "Artem Shabanov", 30, "DF");
    mag.add_footballer_in(clubs[0], "Vladyslav Kucheruk", 31, "GK");
    mag.add_footballer_in(clubs[0], "Ibrahim Kargbo Jr.", 32, "FW");
    mag.add_footballer_in(clubs[0], "Nazariy Rusyn", 70, "FW");
    mag.add_footballer_in(clubs[0], "Denys Boyko", 71, "GK");
    mag.add_footballer_in(clubs[0], "Benito", 77, "MF");
    mag.add_footballer_in(clubs[0], "Tomasz Kedziora", 94, "DF");
    mag.add_footballer_in(clubs[0], "Mikkel Duelund", 99, "MF");
    mag.add_club("Italy", "Juventus", "Juventus Stadium",
                  "Serie A", 41507);
    clubs = mag.get_clubs_in("Italy");
    mag.add_footballer_in(clubs[0], "Wojciech Szczęsny", 1, "GK");
    mag.add_footballer_in(clubs[0], "Mattia De Sciglio", 2, "DF");
    mag.add_footballer_in(clubs[0], "Giorgio Chiellini", 3, "DF");
    mag.add_footballer_in(clubs[0], "Matthijs de Ligt", 4, "DF");
    mag.add_footballer_in(clubs[0], "Miralem Pjanic", 5, "MF");
    mag.add_footballer_in(clubs[0], "Sami Khedira", 6, "MF");
    mag.add_footballer_in(clubs[0], "Cristiano Ronaldo", 7, "FW");
    mag.add_footballer_in(clubs[0], "Aaron Ramsey", 8, "MF");
    mag.add_footballer_in(clubs[0], "Paulo Dybala", 10, "FW");
    mag.add_footballer_in(clubs[0], "Douglas Costa", 11, "FW");
    mag.add_footballer_in(clubs[0], "Alex Sandro", 12, "DF");
    mag.add_footballer_in(clubs[0], "Danilo", 13, "DF");
    mag.add_footballer_in(clubs[0], "Blaise Matuidi", 14, "MF");
    mag.add_footballer_in(clubs[0], "Juan Cuadrado", 16, "MF");
    mag.add_footballer_in(clubs[0], "Leonardo Bonucci", 19, "DF");
    mag.add_footballer_in(clubs[0], "Gonzalo Higuaín", 21, "FW");
    mag.add_footballer_in(clubs[0], "Daniele Rugani", 24, "DF");
    mag.add_footballer_in(clubs[0], "Adrien Rabiot", 25, "MF");
    mag.add_footballer_in(clubs[0], "Merih Demiral", 28, "DF");
    mag.add_footballer_in(clubs[0], "Rodrigo Bentancur", 30, "MF");
    mag.add_footballer_in(clubs[0], "Carlo Pinsoglio", 31, "GK");
    mag.add_footballer_in(clubs[0], "Federico Bernardeschi", 33, "FW");
    mag.add_footballer_in(clubs[0], "Gianluigi Buffon", 77, "GK");
    mag.add_news(new Article("Dynamo", "Football club Dynamo was added in this magazine"), {});
    mag.add_news(new Article("Juventus", "Football club Juventus was added in this magazine"), {});
    auto us = mag.registration("Maxim", "qwerty");
    us->subscribe_to(mag.get_clubs_in("Ukraine")[0]);
    mag.start_season("UEFA");
    mag.add_news(new MatchAnnouncement("Match Dynamo-Juventus",
            new tm{0, 0, 20, 7, 1, 121}, {"Dynamo",
                                                     "Juventus"}, "UEFA"), {"Dynamo", "Juventus"});
    return mag;
}