#include "SubCommand.hh"
#include "SubCommandRegistory.hh"
#include <iostream>

namespace chameleon_tongue {

class Help: public SubCommand {
private:
	const SubCommandRegistory &registory;
public:
	Help(const SubCommandRegistory &registory)
	  : registory(registory) {}
	virtual void run(Environment &env, const Options::SubCommandArgs &args) override {
		std::cout << "Subcommands:\n";
		for (auto item: registory.get_subcommands()) {
			std::cout << "  " << item.first << std::endl;
		}
	}
};
}