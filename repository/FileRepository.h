//
// Created by Mircea on 4/8/2021.
//

#ifndef A67_915_NEGRAU_MIRCEA_FILEREPOSITORY_H
#define A67_915_NEGRAU_MIRCEA_FILEREPOSITORY_H

#include "VirtualRepository.h"

class FileRepository : public VirtualRepository {
private:
    string file_path, save_method, save_path;

    vector read_from_file();

    void write_to_file(vector &tutorials);

    void save_to_file(vector &tutorials);

    void save_as_html(vector &tutorials);

    void save_as_csv(vector &tutorials);

public:
    FileRepository();

    explicit FileRepository(std::string &, std::string &, std::string &);

    explicit FileRepository(std::string &);

    void add_tutorial(const Tutorial &) override;

    void update_tutorial(Tutorial &) override;

    void remove_tutorial(const Tutorial &) override;

    vector get_all_tutorials() override;

    string get_file_path() override;

    unsigned long long get_size() override;
};


#endif //A67_915_NEGRAU_MIRCEA_FILEREPOSITORY_H
