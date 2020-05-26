cmake_minimum_required(VERSION 3.15)
project(course_work)

set(CMAKE_CXX_STANDARD 17)

add_executable(course_work main.cpp Human.h
        Magazine.cpp Magazine.h FootballClub.cpp
        FootballClub.h News.cpp News.h
        MyEvent.h)