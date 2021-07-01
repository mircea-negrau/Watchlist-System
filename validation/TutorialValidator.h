//
// Created by Mircea on 4/8/2021.
//

#ifndef A67_915_NEGRAU_MIRCEA_TUTORIALVALIDATOR_H
#define A67_915_NEGRAU_MIRCEA_TUTORIALVALIDATOR_H

#include <string>
#include <regex>
#include <stdexcept>

typedef std::string string;

class TutorialValidator {
public:
    static void is_valid_tutorial(const string &, const string &, int, int, int, const string &);
    
    static void is_valid_title(const string &);

    static void is_valid_presenter(const string &);

    static void is_valid_link(const string &);

    static void is_valid_amount_of_likes(int);

    static void is_valid_minute_length(int);

    static void is_valid_seconds_length(int);
};


#endif //A67_915_NEGRAU_MIRCEA_TUTORIALVALIDATOR_H
