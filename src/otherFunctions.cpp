
#include <iostream>
#include "otherFunctions.hpp"
#include "ParsedOptions.hpp"
#include "../extern/cxxopts/include/cxxopts.hpp"

using namespace std;

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

    exit (EXIT_FAILURE);
}

bool ParseInputOptions (int argc, char **argv, ParsedOptions& toparse)
{
    cxxopts::Options options("WorkshopControl", "Simple tool for managing your subscriptions in Steam Workshop");

    options.add_options()
        ("h,help", "Show this message.")
        ("a,appid", "AppID of an app to work with. This switch is mandatory.")
        ("s,subscribe", "\"<ItemIDs>\" Subscribe content.")
        ("u,unsubscribe", "\"<ItemIDs>\" Unsubscribe content.")
        ("w,wait", "Wait for download.")
        ;



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
