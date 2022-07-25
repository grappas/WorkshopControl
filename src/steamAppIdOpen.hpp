#include <fstream>
#include <string>
#include "ParsedOptions.hpp"

using namespace std;

class steamAppIdOpen
{
    private:
        fstream steam_appid;
        const string INP_FILE = "steam_appid.txt";
    public:
        steamAppIdOpen();
        ~steamAppIdOpen();
        bool PopulateWithAppID(ParsedOptions& toparse);
};

