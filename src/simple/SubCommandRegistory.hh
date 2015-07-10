#ifndef SUBCOMMANDREGISTORY_HH
#define SUBCOMMANDREGISTORY_HH

#include <map>

namespace chameleon_tongue {

class SubCommandRegistory {
private:
	std::map<std::string, SubCommand*> subcommands;
public:
	const std::map<std::string, SubCommand*>& get_subcommands() const {
		return subcommands;
	}
	
	SubCommand* find_subcommand(const std::string &name) {
		auto itr = subcommands.find(name);
		if (itr == subcommands.end()) {
			// unknown command
			return subcommands["help"];
		} else {
			return itr->second;
		}
	}

	void add(const std::string &name, SubCommand* subcommand) {
		subcommands[name] = subcommand;
	}
	
	~SubCommandRegistory() {
		for (auto item: subcommands) {
			delete item.second;
		}
	}
};

}
#endif