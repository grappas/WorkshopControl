
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
        uint32 what_state; //done
        uint32 local_time_stamp; // done
        uint32 remote_time_stamp;
        string item_name; //done
        bool proper_item;

    public:

        modProperties(const PublishedFileId_t parsedItemID, bool ommit_item_errors);
        ~modProperties();
        void print_properties();

};
