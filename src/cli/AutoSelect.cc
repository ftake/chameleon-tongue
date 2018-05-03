#include "AutoSelect.hh"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <string>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem.hpp>

namespace chameleon_tongue {

static const char* default_locale = "en_US";
static const char* locale_dir = "/usr/lib/input-method/locale.d/";

using namespace std;
namespace fs = boost::filesystem;

static const char* get_lang() {
    auto vars = {"LC_ALL", "LC_CTYPE", "LANG"};
    for (auto var: vars) {
        auto val = getenv(var);
        if (val != nullptr) {
            return val;
        }
    }
    return default_locale;
}

void AutoSelect::run(Environment &env, const Options::SubCommandArgs &args) {
    vector<string> subdirs;
    auto lang = get_lang();
    subdirs.push_back(lang);
    for (int i = strlen(lang); i >= 0; i--) {
        if (lang[i] == '@' || lang[i] == '.' || lang[i] == '_') {
            string subdir(lang, i);
            subdirs.push_back(subdir);
        }
    }
    
    for (auto subdir: subdirs) {
        fs::path subdir_path(locale_dir + subdir);
        if (fs::is_directory(subdir_path)) {
            vector<fs::path> ims;
            copy(fs::directory_iterator(subdir_path), fs::directory_iterator(), back_inserter(ims));
            if (ims.empty()) {
                continue;
            }
            sort(ims.begin(), ims.end());
            //TODO: implement debug mode to dump all the candidates
            cout << ims[0].c_str() << endl;
        }
    }
}

std::string AutoSelect::get_description() const {
    return "select an input method according to the current locale and configuration";
}
}