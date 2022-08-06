
#include "ParsedOptions.hpp"

ParsedOptions::ParsedOptions()
{
    force_download = false;
    force_deletion = false;
    ommit_item_errors = false;
    json = false;
    json_installed_only = false;
    wait = false;
    toSubscribeItemIDs.clear();
    toUnsubscribeItemIDs.clear();
    toSyncItemIDs.clear();
}
ParsedOptions::~ParsedOptions()
{
    toSyncItemIDs.clear();
    toSubscribeItemIDs.clear();
    toUnsubscribeItemIDs.clear();
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

bool ParsedOptions::setTheRest(const cxxopts::ParseResult result)
{
    force_download = result["force_download"].as<bool>();
    force_deletion = result["force_deletion"].as<bool>();
    ommit_item_errors = result["ommit_item_errors"].as<bool>();
    json = result["json"].as<bool>();
    json_installed_only = result["json_installed_only"].as<bool>();
    wait = result["wait"].as<bool>();
    return true;
}
