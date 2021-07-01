//
// Created by Mircea on 4/8/2021.
//

#include "TutorialValidator.h"
#include "Exceptions.h"

void TutorialValidator::is_valid_tutorial(const string &title,
                                          const string &presenter,
                                          int minutes, int seconds,
                                          int likes,
                                          const string &link) {
    string errors;
    try {
        is_valid_title(title);
    } catch (ValidationError &error) {
        errors += error.what();
    }
    try {
        is_valid_presenter(presenter);
    } catch (ValidationError &error) {
        errors += error.what();
    }
    try {
        is_valid_minute_length(minutes);
    } catch (ValidationError &error) {
        errors += error.what();
    }
    try {
        is_valid_seconds_length(seconds);
    } catch (ValidationError &error) {
        errors += error.what();
    }
    try {
        is_valid_amount_of_likes(likes);
    } catch (ValidationError &error) {
        errors += error.what();
    }
    try {
        is_valid_link(link);
    } catch (ValidationError &error) {
        errors += error.what();
    }
    if (!errors.empty())
        throw ValidationError(errors.c_str());
}

void TutorialValidator::is_valid_title(const string &title) {
    if (title.empty())
        throw ValidationError("Title cannot be empty\n");
    if (title.size() > 30)
        throw ValidationError("Title cannot be longer than 30 characters!\n");
}

void TutorialValidator::is_valid_presenter(const string &presenter) {
    if (presenter.empty())
        throw ValidationError("Presenter cannot be empty!\n");
    if (presenter.size() > 30)
        throw ValidationError("Presenter cannot be longer than 30 characters!\n");
}

void TutorialValidator::is_valid_link(const string &link) {
    if (!std::regex_match(link, std::regex("^www\\.[a-zA-Z0-9]+\\..+")))
        throw ValidationError("Invalid link!\n");
}

void TutorialValidator::is_valid_amount_of_likes(int likes) {
    if (likes < 0)
        throw ValidationError("Likes cannot be a negative number!\n");
}

void TutorialValidator::is_valid_minute_length(int minutes) {
    if (minutes < 0)
        throw ValidationError("Minutes cannot be a negative integer!\n");
}

void TutorialValidator::is_valid_seconds_length(int seconds) {
    if (seconds < 0 || seconds >= 60)
        throw ValidationError("Seconds have to be an integer between 0 and 59!\n");
}
