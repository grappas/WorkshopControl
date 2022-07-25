#include "steamAppIdOpen.hpp"
#include "ParsedOptions.hpp"

using namespace std;


steamAppIdOpen::steamAppIdOpen()
{
    steam_appid.open(INP_FILE.c_str());

    if(!steam_appid.is_open())
    {
        steam_appid.close();
        steam_appid.open(INP_FILE.c_str(),ios::out);
        steam_appid.open(INP_FILE.c_str(),ios::in | ios::out | ios::binary);
    }
}
steamAppIdOpen::~steamAppIdOpen()
{
    steam_appid.close();
    remove(INP_FILE.c_str());
}
bool steamAppIdOpen::PopulateWithAppID(ParsedOptions& toparse)
{
    steam_appid << to_string(toparse.showAppID()) + "\n";
    return true;
}

