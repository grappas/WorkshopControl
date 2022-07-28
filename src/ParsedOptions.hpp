#pragma once
#include "../_deps/steamworkssdk-src/include/steam/steam_api.h"

class ParsedOptions
{

    private:
        bool subscribe;
        bool unsubscribe;
        bool wait_or_not;
        bool myAppIDpresent;
        AppId_t myAppID;
        PublishedFileId_t* toSubscribeItemIDs;
        PublishedFileId_t* toUnsubscribeItemIDs;
    public:
        ParsedOptions();
        ~ParsedOptions();
        bool SetSubscribe();
        bool SetUnsubscribe();
        bool SetWait();
        AppId_t& SetAppID();
        bool SetmyAppIDpresent();
        bool checkSubscribe();
        bool checkUnsubscribe();
        bool checkmyAppID();
        bool populateItemIDs(char* list, bool subscribe);
        AppId_t showAppID();
};
