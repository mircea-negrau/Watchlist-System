//
// Created by Mircea on 4/8/2021.
//

#include "FileRepository.h"
#include <fstream>
#include <algorithm>
#include <utility>


FileRepository::FileRepository() : file_path{} {}

FileRepository::FileRepository(string &path, string &method, string &save_path) : file_path{path},
                                                                                  save_method{method},
                                                                                  save_path{save_path + "." + method} {
    vector tutorials = this->read_from_file();
    this->save_to_file(tutorials);
}


FileRepository::FileRepository(string &path) : file_path{path},
                                               save_method{},
                                               save_path{} {}

vector FileRepository::read_from_file() {
    std::ifstream input_stream(this->file_path);
    vector tutorials;
    Tutorial current_tutorial;
    while (input_stream >> current_tutorial)
        if (std::find(tutorials.begin(), tutorials.end(), current_tutorial) == tutorials.end())
            tutorials.push_back(current_tutorial);
    input_stream.close();
    return tutorials;
}

void FileRepository::write_to_file(vector &tutorials) {
    std::ofstream output_stream(this->file_path);
    for_each(tutorials.begin(), tutorials.end(), [&output_stream](auto &t) { output_stream << t; });
}

void FileRepository::save_to_file(vector &tutorials) {
    if (this->save_method == "html")
        save_as_html(tutorials);
    else
        save_as_csv(tutorials);
}

void FileRepository::save_as_html(vector &tutorials) {
    std::ofstream output_stream(this->save_path);
    output_stream << "<!DOCTYPE html>\n"
                     "<html>\n"
                     "<head>\n"
                     "  <title>Tutorial Watchlist</title>\n"
                     "</head>\n"
                     "<body>\n"
                     "<table border=\"1\">"
                     "<tr>\n"
                     "  <td>Title</td>\n"
                     "  <td>Presenter</td>\n"
                     "  <td>Duration</td>\n"
                     "  <td>Likes</td>\n"
                     "  <td>Link</td>\n"
                     "</tr>\n";
    for_each(tutorials.begin(), tutorials.end(), [&output_stream](auto &t) {
        output_stream << "<tr>\n";
        output_stream << "<td>" << t.get_title() << "</td>\n";
        output_stream << "<td>" << t.get_presenter() << "</td>\n";
        auto length = t.get_length();
        output_stream << "<td>" << length.first << "m ";
        output_stream << length.second << "s</td>\n";
        output_stream << "<td>" << t.get_likes() << "</td>\n";
        output_stream << "<td>" << t.get_link() << "</td>\n";
        output_stream << "</tr>\n";
    });
    output_stream << "</table>\n"
                     "</body>\n"
                     "</html>";
}

void FileRepository::save_as_csv(vector &tutorials) {
    std::ofstream output_stream(this->save_path);
    for_each(tutorials.begin(), tutorials.end(), [&output_stream](auto &t) {
        output_stream << t;
    });
}

void FileRepository::add_tutorial(const Tutorial &tutorial) {
    auto tutorials = this->read_from_file();
    if (std::find(tutorials.begin(), tutorials.end(), tutorial) != tutorials.end())
        throw RepositoryError("Tutorial already exists in the repository!");
    tutorials.push_back(tutorial);
    this->write_to_file(tutorials);
    this->save_to_file(tutorials);
}

void FileRepository::update_tutorial(Tutorial &tutorial) {
    auto tutorials = this->read_from_file();
    auto iterator = std::find(tutorials.begin(), tutorials.end(), tutorial);
    Tutorial old_tutorial;
    if (iterator == tutorials.end())
        throw RepositoryError("Tutorial does not exist in the repository!");
    old_tutorial = *iterator;
    (*iterator) = tutorial;
    tutorial = old_tutorial;
    this->write_to_file(tutorials);
    this->save_to_file(tutorials);
}

void FileRepository::remove_tutorial(const Tutorial &tutorial) {
    auto tutorials = this->read_from_file();
    auto iterator = std::find(tutorials.begin(), tutorials.end(), tutorial);
    if (iterator == tutorials.end())
        throw RepositoryError("Tutorial does not exist in the repository!");
    tutorials.erase(iterator);
    this->write_to_file(tutorials);
    this->save_to_file(tutorials);
}

vector FileRepository::get_all_tutorials() {
    auto tutorials = this->read_from_file();
    return tutorials;
}

string FileRepository::get_file_path() {
    return this->save_path;
}

unsigned long long FileRepository::get_size() {
    return this->get_all_tutorials().size();
}
