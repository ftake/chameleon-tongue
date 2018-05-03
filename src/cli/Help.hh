#include "SubCommand.hh"
#include "SubCommandRegistory.hh"
#include <iostream>
#include <ios>
#include <iomanip>

namespace po = boost::program_options;

namespace chameleon_tongue {

class Help: public SubCommand {
private:
    const SubCommandRegistory &registory;
public:
    Help(const SubCommandRegistory &registory)
      : registory(registory) {}

    virtual void run(Environment &env, const Options::SubCommandArgs &args) override {
        switch (args.argc) {
        case 0:
            // for `im-settings --help`
        case 1:
            print_help(std::cout);
            break;
        case 2: {
            auto sub_command = registory.find_subcommand(args.argv[1]);
            sub_command->print_help(std::cout);
            break;
        }
        default:
            throw std::logic_error("too many parameters are specified.");
        }
    }

    virtual std::string get_description() const override {
        return "print this help message";
    }

    virtual void print_help(std::ostream &out) const override {
        out << "Subcommands:\n";
        for (auto item: registory.get_subcommands()) {
            out << "  " << std::left << std::setw(16) << item.first
                << item.second->get_description() << std::endl;
        }
    }
};
}