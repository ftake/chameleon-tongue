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
            ("list,l", "list all config variables");
        hidden_options.add_options()
            ("key-value", value< std::vector<std::string> >(), "key and value");
            
        desc.add(options).add(hidden_options);
            
        positional_options_description pd;
        pd.add("key-value", 2);
        
        store(command_line_parser(args.argc, args.argv).options(desc).positional(pd).run(), vm);
        notify(vm);
        
        bool has_get = vm.count("get") >= 1;
        bool has_set = vm.count("set") >= 1;
        
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
        
        if (has_get && has_set) {
            throw std::logic_error("only either of --get or --set can be specified");
        }
        
        if (has_get) {
            const std::vector<std::string> &keyvalue = vm["key-value"].as<std::vector<std::string>>();
            std::string key = keyvalue[0];
            std::cout << env.get_config_val(key) << std::endl;
        } else if (has_set) {
            const std::vector<std::string> &keyvalue = vm["key-value"].as<std::vector<std::string>>();
            std::string key = keyvalue[0];
            std::string value = keyvalue[1];
            env.set_config_val(key, value, false);
        }
    }
};

}