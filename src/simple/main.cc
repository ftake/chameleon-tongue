#include <iostream>

#include <vector>
#include <map>
#include "SubCommand.hh"
#include "AutoSelect.hh"
#include "Environment.hh"
#include "List.hh"
#include "Help.hh"
#include "Config.hh"
#include "Version.hh"
#include "Options.hh"






/*
class config {
public:
	enum class level { AUTO, USER, SYSTEM } level;
	std::string 
};
*/


//@arg end: valid if the selected number < end
/*
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
*/

/*
void run_interactively() {
	std::vector<input_method*> ims = env.get_input_methods();
	for (int i = 0; i < ims.size(); i++) {
		auto im = ims[i];
		std::cout << i << " " << im->name << ": " << im->path << std::endl;
	}

	int sel = read_selection(0, ims.size());
	std::cout << "selected: " << sel << std::endl;

	// TODO check XDG_CONFIG_HOME 
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
*/


using namespace chameleon_tongue;

int main(int argc, char* argv[]) {
	try {

		Options opts(argc, argv);
		
		const std::string &subcommand_name = opts.get_subcommand();
		Environment env;
		SubCommandRegistory registory;
		registory.add("autoselect", new AutoSelect());
		registory.add("help", new Help(registory));
		registory.add("list", new List());
		registory.add("config", new Config());
		registory.add("version", new Version());
		SubCommand* subcommand = registory.find_subcommand(subcommand_name);
		subcommand->run(env, opts.get_subcommand_args());
		
	} catch (std::exception &e) {
		std::cerr << "Error: ";
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
