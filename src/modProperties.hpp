
#include "../_deps/steamworkssdk-src/include/steam/steam_api.h"
#include "ParsedOptions.hpp"
#include <string>
#include <string.h>
#include <iostream>

using namespace std;

class modProperties
{
    private:

        PublishedFileId_t ItemID; // for list to resolve
        uint32 what_state; //done by -> this
        uint32 local_time_stamp; // done by -> this
        uint32 remote_time_stamp; // for list to resolve
        string item_name; // for list to resolve
        bool is_installed; // for list to resolve or done by -> this
        bool armed_for_uninstall; // for list to resolve
        bool armed_for_install; // for list to resolve
        bool proper_item; // for list to resolve
                          // see: modList.hpp
        bool selfPopulator(const PublishedFileId_t parsedItemID);

    public:

        modProperties(bool ommit_item_errors /*populate then with data*/);
        modProperties(const PublishedFileId_t parsedItemID, bool ommit_item_errors); //triggered on list parsing ommit_item_errors
                                                                                     //careful - 250ms per item!!!
        ~modProperties();
        void print_properties();

};
