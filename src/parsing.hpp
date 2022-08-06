
#include "ParsedOptions.hpp"
#include "../extern/cxxopts/include/cxxopts.hpp"



bool stirr_em_up( //funtion resolves collisions in lists. If mod appears on more than one list it gets popped
        vector<string>& subscribe,
        vector<string>& unsubscribe,
        vector<string>& sync,
        bool prefer_deletion
        );

void print_usage (
        const char *name,
        const cxxopts::Options options,
        const int exitcode
        );

bool parse_items_and_ommit(
        char ** argv,
        vector<string>& temp_itemid_vector,
        const cxxopts::Options options,
        const cxxopts::ParseResult result
        );

bool parse_input_options (
        const int argc,
        char **argv,
        ParsedOptions& toparse
        );

