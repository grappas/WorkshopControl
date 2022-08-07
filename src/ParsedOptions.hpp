#pragma once
#include "../_deps/steamworkssdk-src/include/steam/steam_api.h"
#include "../extern/cxxopts/include/cxxopts.hpp"
#include <vector>
#include <string>

using namespace std;

enum class jobType
{
    subscribe,
    unsubscribe,
};

class ParsedOptions
{
    private:
        bool force_download;
        bool force_deletion;
        bool wait;
        bool ommit_item_errors;
        bool json;
        bool json_installed_only;
        bool sync;
        AppId_t myAppID;
        vector<PublishedFileId_t> toSubscribeItemIDs;
        vector<PublishedFileId_t> toUnsubscribeItemIDs;
    public:
        ParsedOptions();
        ~ParsedOptions();
        AppId_t& SetAppID();
        bool checkmyAppID();
        vector<PublishedFileId_t>& whatList(jobType jobName);
        AppId_t showAppID();
        bool populateItemIDs(
                const vector<string> list_to_parse,
                jobType jobName
        );
        bool setTheRest(const cxxopts::ParseResult result, const bool tosync);
};
