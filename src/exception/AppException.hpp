#include "../dahua/DahuaCamera.hpp"
//
// Created by jzb on 2020/3/31.
//

#ifndef MEDIPATHSCANNER_APPEXCEPTION_HPP
#define MEDIPATHSCANNER_APPEXCEPTION_HPP

struct AppException : public std::exception {
    const std::string s;

    const char *what() const throw() {
        return s.c_str();
    }
};

struct DahuaCameraDiscoveryException : public AppException {
    const char *what() const throw() {
        return "discovery device fail.";
    }
};

#endif //MEDIPATHSCANNER_APPEXCEPTION_HPP
