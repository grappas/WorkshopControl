
#include "../_deps/steamworkssdk-src/include/steam/steam_api.h"
#include "ParsedOptions.hpp"
#include <string>
#include <string.h>
#include <iostream>

using namespace std;

class modProperties
{
    private:

        PublishedFileId_t ItemID;
        uint32 local_time_stamp;
        uint32 remote_time_stamp;
        string item_name;

    public:

        modProperties(PublishedFileId_t const parsedItemID);
        ~modProperties();

};
