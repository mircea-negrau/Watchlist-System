//
// Created by Mircea on 3/27/2021.
//

#include "Repository.h"
#include <algorithm>

Repository::Repository() = default;

void Repository::add_tutorial(const Tutorial &tutorial) {
    auto iterator = std::find(this->data.begin(), this->data.end(), tutorial);
    if (iterator == this->data.end())
        this->data.push_back(tutorial);
    else
        throw RepositoryError("Tutorial already exists in the repository!\n");
}

void Repository::update_tutorial(Tutorial &tutorial) {
    for (auto &current_tutorial : this->data)
        if (current_tutorial == tutorial) {
            current_tutorial = tutorial;
            return;
        }
    throw RepositoryError("Tutorial is not found in the repository!\n");
}

void Repository::remove_tutorial(const Tutorial &tutorial) {
    auto iterator = std::find(this->data.begin(), this->data.end(), tutorial);
    if (iterator != this->data.end())
        this->data.erase(iterator);
    else
        throw RepositoryError("Tutorial is not found in the repository!\n");
}

vector Repository::get_all_tutorials() {
    return this->data;
}

std::string Repository::get_file_path() {
    return std::string();
}

unsigned long long Repository::get_size() {
    return data.size();
}
