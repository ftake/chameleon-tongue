#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/optional.hpp>
#include <boost/log/trivial.hpp>

namespace chameleon_tongue {

class InputMethod {
public:
	const std::string name;
	const std::string path;
	InputMethod(const std::string &name, const std::string &path)
		: name(name), path(path) {}
	InputMethod(const InputMethod& im)
		: name(im.name), path(im.path) {};
};

class Environment {
private:
	std::vector<InputMethod*> ims;
	boost::property_tree::ptree system_config;
	boost::property_tree::ptree user_config;
	std::string user_target_profile_path;
	
	void load_config();
public:
	Environment();

	virtual ~Environment() {
		for (auto im: ims) {
			delete im;
		}
	}

	const std::vector<InputMethod*> get_input_methods() const {
		return ims;
	}
	
	void select_input_method(InputMethod* im);
	
	std::string get_config_val(const std::string &key) {
		if (const auto user_val = user_config.get_optional<std::string>(key)) {
			BOOST_LOG_TRIVIAL(info) << "get '" << key << "' from user-level config";
			return *user_val;
		} else if (const auto system_val = system_config.get_optional<std::string>(key)) {
			BOOST_LOG_TRIVIAL(info) << "get '" << key << "' from system-level config";
			return *system_val;
		} else {
			BOOST_LOG_TRIVIAL(info) << "undefined config: " << key;
			return "";
		}
	}
	
	void set_config_val(const std::string &key, const std::string &value, bool is_global);
	void list_config();
};

}

#endif