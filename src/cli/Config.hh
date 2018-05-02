#include "SubCommand.hh"
#include "Environment.hh"
#include <iostream>
#include <vector>

#include <boost/program_options.hpp>

namespace chameleon_tongue {

class Config: public SubCommand {
private:
    boost::program_options::variables_map vm;
    boost::program_options::options_description desc;
public:
    void run(Environment &env, const Options::SubCommandArgs &args) override {
        using namespace    boost::program_options;
        boost::program_options::options_description options("Options");
        boost::program_options::options_description hidden_options("Hidden options");
        
        options.add_options()
            ("help",  "show this help message")
            ("get", "get the value of the specified config")
            ("set", "set the value of the specified config")
            ("list,l", "list all config variables")
            ("system", "set system wide config (used with --set)");
        hidden_options.add_options()
            ("key", value<std::string>(), "key")
            ("value", value<std::string>(), "value");
            
        desc.add(options).add(hidden_options);
            
        positional_options_description pd;
        pd.add("key", 1);
        pd.add("value", 1);
        
        store(command_line_parser(args.argc, args.argv).options(desc).positional(pd).run(), vm);
        notify(vm);
        
        bool has_get = vm.count("get") >= 1;
        bool has_set = vm.count("set") >= 1;
        auto has_system = vm.count("system") >= 1;
        
        if (vm.count("help") >= 1) {
            std::cout << "im-settings --set key value" << std::endl;
            std::cout << "im-settings --get key" << std::endl;
            
            std::cout << options;
            return;
        }
        
        if (vm.count("list") >= 1) {
            env.list_config();
            return;
        }
        
        // --set or --get
        if ((has_get && has_set) || (!has_get && !has_set)) {
            throw std::logic_error("only either of --get or --set can be specified");
        }

        if (vm.count("key") == 0) {
            throw std::logic_error("key is not specified");
        }
        
        auto key = vm["key"].as<std::string>();

        if (has_get) {
            std::cout << env.get_config_val(key) << std::endl;
        } else if (has_set) {
            if (vm.count("value") == 0) {
                throw std::logic_error("value is not specified");
            }
            auto value = vm["value"].as<std::string>();
            env.set_config_val(key, value, has_system);
        }
    }
};

}