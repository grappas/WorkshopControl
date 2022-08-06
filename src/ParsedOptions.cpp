
#include <cstdlib>
#include "../_deps/steamworkssdk-src/include/steam/steam_api.h"
#include "ParsedOptions.hpp"

ParsedOptions::ParsedOptions()
{
    force_download = false;
    force_deletion = false;
    ommit_item_errors = false;
    json = false;
    json_installed_only = false;
    wait_or_not = false;
    toSubscribeItemIDs.clear();
    toUnsubscribeItemIDs.clear();
    toSyncItemIDs.clear();
}
ParsedOptions::~ParsedOptions()
{
}

bool ParsedOptions::SetWait()
{
    wait_or_not = true;
    return true;
}

AppId_t& ParsedOptions::SetAppID()
{
    return myAppID;
}

vector<PublishedFileId_t>& ParsedOptions::whatList(jobType jobName)
{
    if (jobName == jobType::subscribe)
    {
        return toSubscribeItemIDs;
    }
    else if (jobName == jobType::unsubscribe)
    {
        return toUnsubscribeItemIDs;
    }
    else
    {
        return toSyncItemIDs;
    }
}

//interface for checking bool states:
//

bool ParsedOptions::populateItemIDs(
        const vector<string> list_to_parse,
        jobType jobName
        )
{
    if(list_to_parse.size() == 0)
    {
        return false;
    }
    else
    {
        for (unsigned int i = 0; i < list_to_parse.size() ; i++)
            whatList(jobName).push_back(stoull(list_to_parse[i]));
    }

    return true;
}

AppId_t ParsedOptions::showAppID()
{
    return myAppID;
}

