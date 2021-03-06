#pragma once

#include <exception>
#include <zmq.h>
#include "error.hpp"

namespace boost {
namespace asio {
namespace zmq {

class exception : public std::exception {
private:
    int errno_;

public:
    exception() : errno_(zmq_errno()) {}

    const char* what() const noexcept { return zmq_strerror(errno_); }

    system::error_code get_code() const
    {
        return error::make_error_code(static_cast<error::zmq_error>(errno_));
    }
};

}  // namespace zmq
}  // namespace asio
}  // namespace boost
