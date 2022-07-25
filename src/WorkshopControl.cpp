#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "../_deps/steamworkssdk-src/include/steam/isteamapps.h"
#include "../_deps/steamworkssdk-src/include/steam/steam_api.h"
#include <chrono>
#include <string>
#include <thread>
#include <getopt.h>
#include "Filesystem.hpp"
#include "steamAppIdOpen.hpp"
#include "otherFunctions.hpp"
#include "ParsedOptions.hpp"

using namespace std;



int main(int argc, char* argv[])
{
    ParsedOptions toparse;
    steamAppIdOpen open_app_id;

    ParseInputOptions(argc,argv,toparse);

    open_app_id.PopulateWithAppID(toparse);

    if (!SteamAPI_Init())
    {
        cerr << "Is your Steam Client running? Have you passed right AppID?\n\n";
        return 1;
    }

    SteamAPI_Shutdown();

    //if (argc < 5) {

    //cerr << "Steam Workshop Control by Kun.\n\nSimple program to subscribe/download or unsubscribe Steam Workshop content.\n\nUsage:\n\n[-s|-u] [-w|-nw] [AppID] [ItemID]\n\n\t-s\tSubscribe content\n\t-u\tUnsubscribe content\n\t-w\tWait for download\n\t-nw\tDo not wait for download.\n\n";
    //returnj 1;
    ////help page
    //}

    //string strItemID(argv[3]);
    //char *end;
    //const PublishedFileId_t myAppID = (uint64)(strtoull(argv[3], &end, 10)); //meant to be stored in steam_appid.txt


    //const string INP_FILE = "steam_appid.txt"; // this file is required for steam_api.dll
    //fstream steam_appid;
    //steam_appid.open(INP_FILE.c_str());
    //steam_appid << myAppID;
    //steam_appid.close();


    //if (!SteamAPI_Init())
    //{
    //cerr << "Is your Steam Client running? Have you passed right AppID?\n\n";
    //return 1;
    //}
    //if (strcmp(argv[1],"-s") == 0) //subscribing item
    //{
    //for (unsigned int i = 4; i < argc; i++)
    //{
    //if (!SteamUGC()->SubscribeItem((uint64)(strtoull(argv[i], &end, 10))))
    //{
    //cerr << "Do you mind passing right ItemID?\n\n";
    //}
    //cout << "Item " << (uint64)(strtoull(argv[i], &end, 10)) << " subscribed!\n\n";
    //}

    //if (strcmp(argv[2], "-w") == 0)
    //{
    //for (unsigned int j = 4; j < (argc); j++)
    //{
    //this_thread::sleep_for(chrono::milliseconds(1000));
    //for (unsigned int i = 4; i < argc; i++)
    //{
    //this_thread::sleep_for(chrono::milliseconds(50));
    //if (SteamUGC()->GetItemState((uint64)(strtoull(argv[i], &end, 10))) & k_EItemStateDownloading)
    //{
    //cout << "\nDownloading item " << (uint64)(strtoull(argv[i], &end, 10)) << endl;
    //while (SteamUGC()->GetItemState((uint64)(strtoull(argv[i], &end, 10))) != 5)
    //{
    //this_thread::sleep_for(chrono::milliseconds(100));
    //}
    //cout << "Item downloaded!\n\n";
    //}
    //else {
    //cout << "\nItem " << (uint64)(strtoull(argv[i], &end, 10)) << " already downloaded" << endl;
    //}
    //}
    //}
    //}

    //}
    //else if (strcmp(argv[1], "-u") == 0) //unsubscribing item
    //{
    //for (unsigned int i = 4; i < argc; i++)
    //{
    //if (!SteamUGC()->UnsubscribeItem((uint64)(strtoull(argv[i], &end, 10))))
    //{
    //cerr << "Do you mind passing right ItemID?\n\n";
    //}
    //cout << "Item " << (uint64)(strtoull(argv[i], &end, 10)) << " unsubscribed.\n\n";
    //}
    //}

    //SteamAPI_Shutdown();

    //fstream myyfile; //clearing steam_appid.txt
    //myyfile.open(INP_FILE.c_str(), fstream::out | fstream::trunc);
    //myyfile.close();

    return 0;
}

