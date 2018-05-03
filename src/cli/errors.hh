#include <string>
#include <boost/filesystem/operations.hpp>

std::string format_filesystem_error_msg(const std::string &message, const boost::filesystem::filesystem_error &e);
std::string format_fstream_error_msg(const std::string &message, const std::string &path, const std::system_error &e);