#include <iostream>
#include <boost/program_options.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <vector>
#include "select-im.hh"

namespace fs = boost::filesystem;
namespace po = boost::program_options;

namespace chameleon_tongue {

class options {
private:
	po::variables_map vm;
	po::options_description desc;
	std::string subcommand; //TODO
public:
	options(int argc, char* argv[]): desc("Options") {
		if (argc > 1) {
			subcommand = argv[1];
		}
/*
		desc.add_options()
			("help", "show this help message")
			("user", "user-level config")
			("system", "system-wide config");
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);
*/
	}

	bool is_help() {
		return subcommand == "help" || vm.count("help") > 0;
	}
	
	const std::string& get_subcommand() {
		return subcommand;
	}

	void print_help() {
		std::cout << desc << std::endl;
	}

	void verify() {
	}
};

/*
class config {
public:
	enum class level { AUTO, USER, SYSTEM } level;
	std::string 
};
*/

class input_method {
public:
	const std::string name;
	const std::string path;
	input_method(const std::string &name, const std::string &path)
		: name(name), path(path) {}
	input_method(const input_method& im)
		: name(im.name), path(im.path) {};
};

class environment {
private:
	std::vector<input_method*> ims;
public:
	environment() {
		ims.push_back(new input_method("inherited", "inherited"));
		fs::path profile_dir("/usr/lib/input-method/profile.d");
		fs::directory_iterator end;
		for (fs::directory_iterator itr(profile_dir); itr != end; itr++) {
			ims.push_back(
				new input_method(
					itr->path().leaf().string(), itr->path().string()));
		}
	}

	virtual ~environment() {
		for (auto im: ims) {
			delete im;
		}
	}

	const std::vector<input_method*> get_input_methods() {
		return ims;
	}
};

void list() {
	environment env;
	for (input_method* im: env.get_input_methods()) {
		std::cout << im->name << ":" << im->path << std::endl;
	}
}

//@arg end: valid if the selected number < end
int read_selection(int begin, int end) {
	int result;
	for (;;) {
		std::cout << "[" << begin << "-" << end - 1 << "]: ";
		bool ret = (std::cin >> result);
		if (ret && begin <= result && result < end) {
			break;
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return result;
}

void run_interactively() {
	environment env;
	std::vector<input_method*> ims = env.get_input_methods();
	for (int i = 0; i < ims.size(); i++) {
		auto im = ims[i];
		std::cout << i << " " << im->name << ": " << im->path << std::endl;
	}

	int sel = read_selection(0, ims.size());
	std::cout << "selected: " << sel << std::endl;

	std::string home_dir(std::getenv("HOME"));
	std::string config_dir(home_dir + "/.config/input-method");
	fs::path target_profile(config_dir + "/target");

	if (fs::exists(target_profile)) {
		// TODO error if target_profile is a real directory
		fs::remove(target_profile);
	}

	if (ims[sel]->name == "inherited") {
		// do nothing
	} else {
		if (!fs::exists(config_dir)) {
			fs::create_directories(config_dir);
		}
		fs::path profile(ims[sel]->path);
		fs::create_symlink(profile, target_profile);
	}
}

void save_config() {

}

}

using namespace chameleon_tongue;

int main(int argc, char* argv[]) {
	try {

		options opts(argc, argv);
		if (opts.is_help()) {
			opts.print_help();
			return 0;
		}

		opts.verify();
		
		const std::string &subcommand = opts.get_subcommand();
		if (subcommand == "autoselect") {
			autoselect();
		} else if (subcommand == "config") {
			run_interactively();
		} else if (subcommand == "list") {
			list();
		}
	} catch (std::exception &e) {
		std::cerr << "Error: ";
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
