cmake_minimum_required(VERSION 3.15)
project(course_work)

set(CMAKE_CXX_STANDARD 17)

add_executable(course_work main.cpp people/Human.h
        Magazine.cpp Magazine.h stdafx.h FootballClub.cpp
        FootballClub.h functional/News.cpp functional/News.h
        MyFunctional/Event/Functions.h MyFunctional/Event/MyEvent.h)