#pragma once
#include "../_deps/steamworkssdk-src/include/steam/steam_api.h"
#include <vector>
#include <string>

using namespace std;

enum class jobType
{
    subscribe,
    unsubscribe,
    sync
};

class ParsedOptions
{
    private:
        bool force_download;
        bool force_deletion;
        bool wait_or_not;
        bool ommit_item_errors;
        bool json;
        bool json_installed_only;
        AppId_t myAppID;
        vector<PublishedFileId_t> toSubscribeItemIDs;
        vector<PublishedFileId_t> toUnsubscribeItemIDs;
        vector<PublishedFileId_t> toSyncItemIDs;
    public:
        ParsedOptions();
        ~ParsedOptions();
        AppId_t& SetAppID();
        bool checkmyAppID();
        bool populateItemIDs(char* list, jobType jobName );
        bool SetWait();
        vector<PublishedFileId_t>& whatList(jobType jobName);
        AppId_t showAppID();
        bool populateItemIDs(
                const vector<string> list_to_parse,
                jobType jobName
        );
};
