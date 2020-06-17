//
// Created by chenh on 6/16/2020.
//

#ifndef COURSEPROJECT_EXCEPTION_H
#define COURSEPROJECT_EXCEPTION_H

#include <string>
#include <exception>

namespace mat {

    class Exception : public std::exception {
    public:
        explicit Exception(std::string msg) : msg(std::move(msg)) {

        }

        const char *what() const noexcept override {
            return msg.c_str();
        }

    private:
        std::string msg{};
    };

}
#endif //COURSEPROJECT_EXCEPTION_H
