
#include <cstdlib>
#include "../_deps/steamworkssdk-src/include/steam/steam_api.h"
#include "ParsedOptions.hpp"

ParsedOptions::ParsedOptions()
{
    subscribe = false;
    unsubscribe = false;
    wait_or_not = false;
    myAppIDpresent = false;
    toSubscribeItemIDs = nullptr;
    toUnsubscribeItemIDs = nullptr;
}
ParsedOptions::~ParsedOptions()
{
    delete toUnsubscribeItemIDs;
    delete toSubscribeItemIDs;
}
bool ParsedOptions::SetSubscribe()
{
    subscribe = true;
    return true;
}
bool ParsedOptions::SetUnsubscribe()
{
    unsubscribe = true;
    return true;
}

bool ParsedOptions::SetWait()
{
    wait_or_not = true;
    return true;
}

PublishedFileId_t& ParsedOptions::SetAppID()
{
    return myAppID;
}
bool ParsedOptions::SetmyAppIDpresent()
{
    myAppIDpresent = true;
    return true;
}

//interface for checking bool states:
//
bool ParsedOptions::checkSubscribe()
{
    return subscribe;
}

bool ParsedOptions::checkUnsubscribe()
{
    return unsubscribe;
}
bool ParsedOptions::checkmyAppID()
{
    return myAppIDpresent;
}

bool ParsedOptions::populateItemIDs(char* list, bool subscribe)
{
    char *end = (char *) malloc(sizeof(list));
    char *end_backup = end;
    strcpy(end,list);
    size_t what_size_of_list = 0;
    while (end[0] != '\0')
    {
        strtoull(end, &end, 10);
        what_size_of_list++;
    }

    free(end_backup);
    end = nullptr;
    end = (char *) malloc(sizeof(list));
    end_backup = end;
    strcpy(end,list);

    if (subscribe)
    {
        toSubscribeItemIDs = new uint64[what_size_of_list];
        for (size_t i = 0 ; i < what_size_of_list ; i++)
        {
            toSubscribeItemIDs[i] = strtoull(end, &end, 10);
        }
    }

    else // unsubscribe
    {
        toUnsubscribeItemIDs = new uint64[what_size_of_list];
        for (size_t i = 0 ; i < what_size_of_list ; i++)
        {
            toUnsubscribeItemIDs[i] = strtoull(end, &end, 10);
        }
    }

    free(end_backup);
    return true;
}

PublishedFileId_t ParsedOptions::showAppID()
{
    return myAppID;
}

