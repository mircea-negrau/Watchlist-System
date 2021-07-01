//
// Created by Mircea on 4/8/2021.
//

#ifndef A67_915_NEGRAU_MIRCEA_EXCEPTIONS_H
#define A67_915_NEGRAU_MIRCEA_EXCEPTIONS_H

#include <stdexcept>
#include <string>


class ValidationError : public std::runtime_error {
public:
    ValidationError(const char* what) : runtime_error{what} {}
};


class RepositoryError : public std::runtime_error {
public:
    RepositoryError(const char* what) : runtime_error{what} {}
};


class ServiceError : public std::runtime_error {
public:
    ServiceError(const char* what) : runtime_error{what} {}
};


#endif //A67_915_NEGRAU_MIRCEA_EXCEPTIONS_H
