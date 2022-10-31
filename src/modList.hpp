#include "modProperties.hpp"
#include <vector>

class modList
{
    private:
        vector<modProperties> list; //how about redesigning modProperties cless?
                                    //is there any space for sub,unsub,etc.?
                                    //parse installed mods and store it's state?
                                    //prepare it for update :thonk: ?
        //UGCQueryHandle_t handle;
        //handle to result
        //SteamAPICall_t result
        //if true handle to details
        //SteamUGCDetails_t details

    public:
        modList(const ParsedOptions toparse); //lets populate list of modProperties here.
                                              //only parse querried info from SteamAPI
                                              //throw list of mods and hope for the best
                                              //check if there's any errors
};
