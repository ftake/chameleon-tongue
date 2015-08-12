#include "Environment.hh"

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/log/trivial.hpp>
#include <fstream>

namespace fs = boost::filesystem;

namespace chameleon_tongue {

using namespace std;

fs::path find_from_system_conf_dirs(const std::string &name) {
	char* p_xdg_config_dirs = std::getenv("XDG_CONFIG_DIRS");
	vector<string> dirs;
	if (p_xdg_config_dirs != nullptr) {
		string delimitter(":");
		boost::algorithm::split(dirs, p_xdg_config_dirs, boost::is_any_of(delimitter));
	}
	
	dirs.push_back("/etc");
	
	for (std::string& dir: dirs) {
		fs::path sys_config_dir_(dir + "/input-method/" + name);
		if (fs::exists(sys_config_dir_)) {
			return std::move(sys_config_dir_);
		}
	}
	
	// "name" does not exist
	return fs::path(dirs[0] + "/input-method/" + name);
}

fs::path find_from_user_conf_dir(const std::string &name) {
	char* p_xdg_config_home = std::getenv("XDG_CONFIG_HOME");
	stringstream filename;
	
	if (p_xdg_config_home != nullptr) {
		filename << p_xdg_config_home;
	} else {
		// if XDG_CONFIG_HOME is not defined
		// then application should use "~/.config/"
		const char *p_home = std::getenv("HOME");
		if (p_home == nullptr) {
			//TODO
			p_home = "";
		}
		filename << p_home << "/.config";
	}
	
	filename << "/input-method/" << name;
	return fs::path(filename.str());
}

namespace pt = boost::property_tree;

Environment::Environment() {
	// load system config
	load_config();
	
	// load input methods
	ims.push_back(new InputMethod("inherited", "inherited"));
	fs::path profile_dir("/usr/lib/input-method/profile.d");
	fs::directory_iterator end;
	for (fs::directory_iterator itr(profile_dir); itr != end; itr++) {
		ims.push_back(
			new InputMethod(
				itr->path().leaf().string(), itr->path().string()));
	}
}

void Environment::load_config() {
	const fs::path system_config_file = find_from_system_conf_dirs("im.conf");
	BOOST_LOG_TRIVIAL(info) << "system-level conf file: " << system_config_file.string();
	
	if (fs::exists(system_config_file)) {
		//TODO: try catch
		ifstream is(system_config_file.string());
		pt::ini_parser::read_ini(is, system_config);
	} else {
		BOOST_LOG_TRIVIAL(info) << "file not found: " << system_config_file;
	}
	
	const fs::path user_config_file = find_from_user_conf_dir("im.conf");
	
	BOOST_LOG_TRIVIAL(info) << "user-level conf file: " << user_config_file.string();
	if (fs::exists(user_config_file)) {
		//TODO: try catch
		ifstream is(user_config_file.string());
		pt::ini_parser::read_ini(is, user_config);
	} else {
		BOOST_LOG_TRIVIAL(info) << "file not found: " << user_config_file;
	}
}

void Environment::set_config_val(const std::string &key, const std::string &value, bool is_global) {
	//TODO support global option
	user_config.put(key, value);
	// write to file
	const fs::path config_file = find_from_user_conf_dir("im.conf");
	BOOST_LOG_TRIVIAL(info) << "write config to: " << config_file;
	ofstream os(config_file.string());
	pt::ini_parser::write_ini(os, user_config);
}

static void print_tree_rec(const pt::ptree &tree, const string &path) {
	if (tree.empty()) {
		cout << path.substr(1) << "=" << tree.data() << endl;
		return;
	}
	
	for (auto &p: tree) {
		print_tree_rec(p.second, path + "." + p.first);
	}
}

void Environment::list_config() {
	print_tree_rec(user_config, "");
}

}