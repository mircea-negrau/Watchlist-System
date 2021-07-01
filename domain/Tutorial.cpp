//
// Created by Mircea on 3/27/2021.
//

#include <vector>
#include "Tutorial.h"

Tutorial::Tutorial() : title{}, presenter{}, length{minutes_seconds(0, 0)}, likes{0}, link{} {}

Tutorial::Tutorial(const string &new_title,
                   const string &new_presenter,
                   int minutes,
                   int seconds,
                   int new_likes,
                   const string &new_link) :
        title{new_title},
        presenter{new_presenter},
        length{minutes_seconds(minutes, seconds)},
        likes{new_likes},
        link{new_link} {}

Tutorial::Tutorial(const Tutorial &other) : title{other.title},
                                            presenter{other.presenter},
                                            likes{other.likes},
                                            length{other.length},
                                            link{other.link} {}

const string &Tutorial::get_title() const {
    return this->title;
}

const string &Tutorial::get_presenter() const {
    return this->presenter;
}

int Tutorial::get_likes() const {
    return this->likes;
}

minutes_seconds Tutorial::get_length() const {
    return this->length;
}

const string &Tutorial::get_link() const {
    return this->link;
}

void Tutorial::set_title(const string &new_title) {
    this->title = new_title;
}

void Tutorial::set_presenter(const string &new_presenter) {
    this->presenter = new_presenter;
}

void Tutorial::set_likes(int new_likes) {
    this->likes = new_likes;
}

void Tutorial::set_length(int new_minutes, int new_seconds) {
    this->length = minutes_seconds(new_minutes, new_seconds);
}

void Tutorial::set_link(const string &new_link) {
    this->link = new_link;
}

Tutorial &Tutorial::operator=(const Tutorial &other) = default;

bool Tutorial::operator==(const Tutorial &other) {
    if (this->link == other.link)
        return true;
    return false;
}

std::ostream &operator<<(std::ostream &output_stream, const Tutorial &tutorial) {
    output_stream << tutorial.title << "," << tutorial.presenter << ","
                  << tutorial.length.first << "," << tutorial.length.second << ","
                  << tutorial.likes << ","
                  << tutorial.link << "\n";
    return output_stream;
}

std::istream &operator>>(std::istream &input_stream, Tutorial &tutorial) {
    std::string line;
    std::getline(input_stream, line);
    line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
    std::vector<std::string> splitLine;
    int position = 0;
    while ((position = line.find(',')) != std::string::npos) {
        std::string token = line.substr(0, position);
        splitLine.push_back(token);
        line.erase(0, 1 + position);
    }
    if (splitLine.size() != 5)
        return input_stream;
    splitLine.push_back(line);
    tutorial.title = splitLine[0];
    tutorial.presenter = splitLine[1];
    tutorial.length.first = std::stoi(splitLine[2]);
    tutorial.length.second = std::stoi(splitLine[3]);
    tutorial.likes = std::stoi(splitLine[4]);
    tutorial.link = splitLine[5];
    return input_stream;
}
