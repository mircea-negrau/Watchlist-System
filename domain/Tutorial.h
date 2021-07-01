//
// Created by Mircea on 3/27/2021.
//

#ifndef A45_915_NEGRAU_MIRCEA_TUTORIAL_H
#define A45_915_NEGRAU_MIRCEA_TUTORIAL_H

#include <string>
#include <iostream>

typedef std::string string;
typedef std::pair<int, int> minutes_seconds;

class Tutorial {
private:
    string title, presenter, link;
    int likes;
    minutes_seconds length;
public:

/// Default Constructor
    Tutorial();

/// Initialized Constructor
    Tutorial(const string &, const string &, int, int, int, const string &);

/// Copy Constructor
    Tutorial(const Tutorial &);

/// Title getter
    const string &get_title() const;

/// Presenter getter
    const string &get_presenter() const;

/// Likes getter
    int get_likes() const;

/// Length getter
    minutes_seconds get_length() const;

/// Link getter
    const string &get_link() const;

/// Title setter
    void set_title(const string &);

/// Presenter setter
    void set_presenter(const string &);

/// Likes setter
    void set_likes(int);

/// Length setter
    void set_length(int, int);

/// Link setter
    void set_link(const string &);

/// Operator '=' override
    Tutorial &operator=(const Tutorial &);

/// Operator '==' override
    bool operator==(const Tutorial &);

/// Output format
    friend std::ostream &operator<<(std::ostream &, const Tutorial &);

/// Input format
    friend std::istream &operator>>(std::istream &, Tutorial &);
};


#endif //A45_915_NEGRAU_MIRCEA_TUTORIAL_H
