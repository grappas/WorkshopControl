
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "otherFunctions.hpp"
#include "ParsedOptions.hpp"
#include "../extern/cxxopts/include/cxxopts.hpp"

using namespace std;

void print_usage (
        const char *name,
        const cxxopts::Options options,
        const int exitcode
        )
{
    cerr << options.help() << endl
        << name
        << endl
        << endl;

    exit (exitcode);
}

bool ParseInputOptions (
        const int argc,
        char **argv,
        ParsedOptions& toparse
        )
{
    cxxopts::Options options("WorkshopControl", "Simple tool for managing your subscriptions in Steam Workshop");

    options.add_options()
        ("h,help", "Show this message.")
        ("f,force_download", "Checks for updates of already subscibed content. If it is not up to date, begins download. To use with --subscribe or --sync switches.", cxxopts::value<bool>()->default_value("false"))
        ("F,force_deletion", "Sometimes Steam leaves content undeleted after unsubscription. With this switch app will try to force deletion. To use with --sync and --unsubscribe switches.", cxxopts::value<bool>()->default_value("false"))
        ("p,prefer_deletion", "By default in case of usage both subscription and unsubsription, if both lists contains the same itemID program will prefer to keep or subscribe that item. By arming this switch you will invert this behaviour.", cxxopts::value<bool>()->default_value("false"))
        ("w,wait", "Wait for download and show progress.", cxxopts::value<bool>()->default_value("false"))
        ("o,ommit_parse_errors", "Turn this switch on if you want to continue job even with <itemIDs> parse errors.", cxxopts::value<bool>()->default_value("false"))
        ("O,ommit_item_errors", "Turn this switch on if you want to continue job even with <itemIDs> steam API errors (i.e. wrong itemID).", cxxopts::value<bool>()->default_value("false"))
        ("j,json", "Prints JSON output containing states of an each item.", cxxopts::value<bool>()->default_value("false"))
        ("appid", "AppID of an app to work with. This switch is mandatory.", cxxopts::value<string>()->default_value("0"))
        ("s,subscribe", "\"<ItemIDs>\" Subscribe content.", cxxopts::value<vector<string>>() )
        ("u,unsubscribe", "\"<ItemIDs>\" Unsubscribe content.", cxxopts::value<vector<string>>() )
        ("S,sync", "\"<ItemIDs>\" Subscribes missing content, unsubscribes content not passed on the list.\nAt least one of three mentioned above have to be armed for app to work.", cxxopts::value<vector<string>>() )
        ;

    options.parse_positional({"appid"});
    options.positional_help("<appid> [-s item1,item2,...|-S item1,item2,...|-u item1,item2,...]");

    auto result = options.parse(argc,argv);

    string appid_as_string = result["appid"].as<string>();

    PublishedFileId_t appid_as_ull = stoull(appid_as_string);

    if (appid_as_string != to_string(appid_as_ull))
    {
        cerr << "AppID incorrect." << endl;
        print_usage(argv[0], options, EXIT_FAILURE);
    }
    else if (appid_as_ull == 0)
    {
        cerr << "You must pass an AppID." << endl;
        print_usage(argv[0], options, EXIT_FAILURE);
    }
    else
    {
        toparse.SetAppID() = appid_as_ull;
    }


    vector<string> temp_itemid_vector = result["subscribe"].as<vector<string>>();

    for (auto it = temp_itemid_vector.begin();it != temp_itemid_vector.end();){
        if( *it != to_string(stoull(*it)) )
        {
            cout << "Error parsing Item: " << *it;
            if (result["ommit_parse_errors"].as<bool>())
            {
                cout << " ommiting..." << endl;
                it = temp_itemid_vector.erase(it);
            }
            else
            {
                cout << endl;
                print_usage(argv[0], options, EXIT_FAILURE);
            }
        }
        else
        {
            ++it;
        }
    }



    //int c;

    //while (true){
        //static struct option long_options[] =
        //{
            //{"help", no_argument, 0, 'h'},
            //{"unsubscribe", required_argument, 0, 'u'},
            //{"subscribe", required_argument, 0, 's'},
            //{"appid", required_argument, 0, 'a'},
            //{"wait", no_argument, 0, 'w'},
            //{0,0,0,0}
        //};

        //int option_index = 0;

        //c = getopt_long(argc,argv, "h:s:u:a:w:", long_options, &option_index);

        //if (c == -1)
            //break;

        //switch (c)
        //{

            //case 0:
                //[> If this option set a flag, do nothing else now. <]
                //if (long_options[option_index].flag != 0)
                    //break;
                //printf ("option %s", long_options[option_index].name);
                //if (optarg)
                    //printf (" with arg %s", optarg);
                //printf ("\n");
                //break;

            //case 'h':
                //print_usage(argv[0]);
                //break;

            //case 'w':
                //toparse.SetWait();
                //break;

            //case 'u':
                //toparse.SetUnsubscribe();
                //toparse.populateItemIDs(optarg, false);
                //break;

            //case 's':
                //toparse.SetSubscribe();
                //toparse.populateItemIDs(optarg, true);
                //break;

            //case 'a':
                //if (optarg[0] == '-')
                //{
                    //printf ("Error: -%c: option requires an argument\n", c);
                    //print_usage(argv[0]);
                //}
                //if ((toparse.SetAppID() = strtoull (optarg, nullptr, 10)) == 0)
                //{
                    //printf("Error: -%c: invalid AppID\n", c);
                    //print_usage(argv[0]);
                //}
                //toparse.SetmyAppIDpresent();
                //break;

            //case '?':
                //[> getopt_long already printed an error message. <]
            //case ':':
            //default:
                //print_usage(argv[0]);
        //}
    //}

    if (!(toparse.checkSubscribe() || toparse.checkUnsubscribe()))
    {
        std::cout << "\nThere's no job given.\n";
        print_usage(argv[0], options, EXIT_FAILURE);
    }

    return true;
}
