#include "errors.hh"

std::string format_filesystem_error_msg(const std::string &message, const boost::filesystem::filesystem_error &e) {
    std::string msg(message + "\n" + e.code().message());
    if (!e.path1().empty()) {
        msg += ": \"" + e.path1().string() + "\"";
    }
    if (!e.path2().empty()) {
        msg += ", \"" + e.path2().string() + "\"";
    }
    return msg;
}

std::string format_fstream_error_msg(const std::string &message, const std::string &path, const std::system_error &e) {
    std::string msg(message + "\n" + e.code().message());
    msg += ": \"" + path + "\"";
    return msg;    
}