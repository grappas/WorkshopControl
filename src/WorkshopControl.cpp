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
#include <filesystem>
#include <experimental/filesystem>
#include "Filesystem.hpp"
#include "ParsedOptions.hpp"

using namespace std;

class FileOpen
{

    private:
        fstream steam_appid;
        const string INP_FILE = "steam_appid.txt";
    public:
        FileOpen()
        {
            steam_appid.open(INP_FILE.c_str());

            if(!steam_appid.is_open())
            {
                steam_appid.close();
                steam_appid.open(INP_FILE.c_str(),ios::out);
                steam_appid.open(INP_FILE.c_str(),ios::in | ios::out | ios::binary);
            }
        }
        ~FileOpen()
        {
            steam_appid.close();
            remove(INP_FILE.c_str());
        }
        bool PopulateWithAppID(ParsedOptions& toparse)
        {
            cout << toparse.showAppID() << endl;
            steam_appid << to_string(toparse.showAppID()) + "\n";
            return true;
        }

};

void print_usage ( char *name )
{
    cerr
        << "\nSteam Workshop Control.\n\n"

        << "Simple tool to subscribe/download or unsubscribe Steam Workshop content.\n\n"

        << "Usage:\n\n"

        << "[-w] -a <AppID> [-s \"<ItemIDs>\"] [-u \"<ItemIDs>\"]\n\n"

        << "\t-h|--help\t\t\tPrints this message\n"
        << "\t-a|--appid <AppID>\t\tAppID of an app to work with.\n"
        << "\t\t\t\t\tThis switch is mandatory.\n"
        << "\t-s|--subscribe \"<ItemIDs>\"\tSubscribe content\n"
        << "\t-u|--unsubscribe \"<ItemIDs>\"\tUnsubscribe content\n"
        << "\t-w|--wait\t\t\tWait for download\n\n"

        << name
        << std::endl
        << std::endl;
}

bool ParseInputOptions (int argc, char **argv, ParsedOptions& toparse)
{
    int c;

    while (true){
        static struct option long_options[] =
        {
            {"help", no_argument, 0, 'h'},
            {"unsubscribe", required_argument, 0, 'u'},
            {"subscribe", required_argument, 0, 's'},
            {"appid", required_argument, 0, 'a'},
            {"wait", no_argument, 0, 'w'},
            {0,0,0,0}
        };

        int option_index = 0;

        c = getopt_long(argc,argv, "h:s:u:a:w:", long_options, &option_index);

        if (c == -1)
            break;

        switch (c)
        {

            case 0:
                /* If this option set a flag, do nothing else now. */
                if (long_options[option_index].flag != 0)
                    break;
                printf ("option %s", long_options[option_index].name);
                if (optarg)
                    printf (" with arg %s", optarg);
                printf ("\n");
                break;

            case 'h':
                print_usage(argv[0]);
                break;

            case 'w':
                toparse.SetWait();
                break;

            case 'u':
                toparse.SetUnsubscribe();
                toparse.populateItemIDs(optarg, false);
                break;

            case 's':
                toparse.SetSubscribe();
                toparse.populateItemIDs(optarg, true);
                break;

            case 'a':
                if (optarg[0] == '-')
                {
                    printf ("Error: -%c: option requires an argument\n", c);
                    print_usage(argv[0]);
                }
                if ((toparse.SetAppID() = strtoull (optarg, nullptr, 10)) == 0)
                {
                    printf("Error: -%c: invalid AppID\n", c);
                    print_usage(argv[0]);
                }
                toparse.SetmyAppIDpresent();
                break;

            case '?':
                /* getopt_long already printed an error message. */
            case ':':
            default:
                print_usage(argv[0]);
        }
    }

    if (!toparse.checkmyAppID())
    {
        std::cout << "\nNo AppID given.\n";
        print_usage(argv[0]);
    }
    else if (!(toparse.checkSubscribe() || toparse.checkUnsubscribe()))
    {
        std::cout << "\nThere's no job given.\n";
        print_usage(argv[0]);
    }


    return true;
}


int main(int argc, char* argv[])
{
    ParsedOptions toparse;
    FileOpen open_app_id;

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

