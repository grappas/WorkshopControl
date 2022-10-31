
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include "parsing.hpp"
#include "ParsedOptions.hpp"
#include "../extern/cxxopts/include/cxxopts.hpp"

using namespace std;


bool stirr_em_up( //funtion resolves collisions in lists. If mod appears on more than one list it gets popped
        vector<string>& subscribe,
        vector<string>& unsubscribe,
        vector<string>& sync,
        bool prefer_deletion
        )
{//{{{2
    bool isempty = sync.empty(); //sync switch (obsolete)

    //get rid of duplicates inside lists
    //
    sort(subscribe.begin(),subscribe.end());
    sort(unsubscribe.begin(),unsubscribe.end());
    sort(sync.begin(),sync.end());

    vector<string>::iterator it_subscribe = unique(subscribe.begin(),subscribe.end());
    vector<string>::iterator it_unsubscribe = unique(unsubscribe.begin(),unsubscribe.end());
    vector<string>::iterator it_sync = unique(sync.begin(),sync.end());

    subscribe.resize(distance(subscribe.begin(),it_subscribe));
    unsubscribe.resize(distance(unsubscribe.begin(),it_unsubscribe));
    sync.resize(distance(sync.begin(),it_sync));

    if (!sync.empty())// make sure that there's no duplicates between sync and subscribe
    {
        for (auto it = subscribe.begin();it != subscribe.end();it++)
        {
            for (auto ite = sync.begin(); ite != sync.end();)
            {
                if(*it == *ite)
                {
                    ite = sync.erase(ite);
                }
                else
                {
                    ite++;
                }
            }
        }
    }

    //merge subscibe and sync, sync no longer needed, as we already determined sync behaviour
    //
    vector<string> merged(subscribe.size() + sync.size());

    merge(
            subscribe.begin(),
            subscribe.end(),
            sync.begin(),
            sync.end(),
            merged.begin()
            );

    subscribe = merged;


    if(!prefer_deletion) // resolve duplicates between subscribe and unsubscribe
    {
        for (auto it = subscribe.begin();it != subscribe.end();it++){
            for (auto ite = unsubscribe.begin();ite != unsubscribe.end();){
                if (*it == *ite)
                {
                    ite = unsubscribe.erase(ite);
                }
                else
                {
                    ite++;
                }
            }
        }
    }
    else
    {
        for (auto it = unsubscribe.begin();it != unsubscribe.end();it++){
            for (auto ite = subscribe.begin();ite != subscribe.end();){
                if (*it == *ite)
                {
                    ite = subscribe.erase(ite);
                }
                else
                {
                    ite++;
                }
            }
        }
    }


    return !isempty; // switch for sync behaviour
}// 2}}}


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

bool parse_items_and_ommit( //resolves parsing errors i.e. mod 23445hfg gets popped from vector because we cannot be sure if 23445 is a proper mod
        char** argv,
        vector<string>& temp_itemid_vector,
        const cxxopts::Options options,
        const cxxopts::ParseResult result
        )
{
    if(temp_itemid_vector.size() == 0)
    {
        return false;
    }

    for (auto it = temp_itemid_vector.begin();it != temp_itemid_vector.end();){
        if( *it != to_string(stoull(*it)) )
        {
            cerr << "Error parsing Item: " << *it;
            if (result["ommit_parse_errors"].as<bool>())
            {
                cerr << " ommiting..." << endl;
                it = temp_itemid_vector.erase(it);
            }
            else
            {
                cerr << endl;
                print_usage(argv[0], options, EXIT_FAILURE);
            }
        }
        else
        {
            ++it;
        }
    }
    cerr << endl;
    return true;
}


bool parse_input_options (
        const int argc,
        char **argv,
        ParsedOptions& toparse
        )
{//{{{1
    cxxopts::Options options("WorkshopControl", "Simple tool for managing your subscriptions in Steam Workshop");

    options.add_options() // add options < cpu heavy {{{2
        ("h,help", "Show this message.")
        ("f,force_download", "Checks for updates of already subscibed content. If it is not up to date, begins download. To use with --subscribe or --sync switches.", cxxopts::value<bool>()->default_value("false"))
        ("F,force_deletion", "Sometimes Steam leaves content undeleted after unsubscription. With this switch app will try to force deletion. To use with --sync and --unsubscribe switches.", cxxopts::value<bool>()->default_value("false"))
        ("p,prefer_deletion", "By default in case of usage both subscription and unsubsription, if both lists contains the same itemID program will prefer to keep or subscribe that item. By arming this switch you will invert this behaviour.", cxxopts::value<bool>()->default_value("false"))
        ("w,wait", "Wait for download and show progress.", cxxopts::value<bool>()->default_value("false"))
        ("o,ommit_parse_errors", "Turn this switch on if you want to continue job even with <itemIDs> parse errors.", cxxopts::value<bool>()->default_value("false"))
        ("O,ommit_item_errors", "Turn this switch on if you want to continue job even with <itemIDs> Steam API errors (i.e. wrong itemID).", cxxopts::value<bool>()->default_value("false"))
        ("j,json", "Prints JSON output containing states of an each passed item. By arming this, app will simulate only.", cxxopts::value<bool>()->default_value("false"))
        ("J,json_installed_only", "Prints JSON output containing states of an installed items.", cxxopts::value<bool>()->default_value("false"))
        ("appid", "AppID of an app to work with. This switch is mandatory.", cxxopts::value<string>()->default_value("0"))
        ("s,subscribe", "Subscribe content.", cxxopts::value<vector<string>>() )
        ("u,unsubscribe", "\"<ItemIDs>\" Unsubscribe content.", cxxopts::value<vector<string>>() )
        ("S,sync", "\"<ItemIDs>\" Subscribes missing content, unsubscribes remaining, downloaded content not passed on the list. Please note that passing this argument makes --subscribe behaving like sync.\nAt least one of three mentioned above have to be armed for app to work. Pass itemIDs separated by commas.", cxxopts::value<vector<string>>() )
        ;
// add options < close 2}}}
    options.parse_positional({"appid"});
    options.positional_help("<appid> [-s item1,item2,...|-S item1,item2,...|-u item1,item2,...]");
    options.allow_unrecognised_options();

    auto result = options.parse(argc,argv);

    bool tosync = result.count("sync");

    if (result.count("help"))
        print_usage(argv[0], options, EXIT_SUCCESS);

    if (result.unmatched().size() != 0)
    {
        cerr << "Unrecognized arguments: ";
        for ( string n:result.unmatched())
        {
            cerr << n << " ";
        }
        cerr << endl << endl;
        print_usage(argv[0], options, EXIT_FAILURE);
    }

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

        vector<string> temp_itemid_vector_subscribe;
        vector<string> temp_itemid_vector_unsubscribe;
        vector<string> temp_itemid_vector_sync;

    if ( result.count("subscribe"))
        temp_itemid_vector_subscribe = result["subscribe"].as<vector<string>>();
    if ( result.count("unsubscribe"))
        temp_itemid_vector_unsubscribe = result["unsubscribe"].as<vector<string>>();
    if ( result.count("sync"))
        temp_itemid_vector_sync = result["sync"].as<vector<string>>();

    if (
            !(
                parse_items_and_ommit(
                    argv,
                    temp_itemid_vector_subscribe,
                    options,
                    result
                    ) ||
                parse_items_and_ommit(
                    argv,
                    temp_itemid_vector_unsubscribe,
                    options,
                    result
                    ) ||
                parse_items_and_ommit(
                    argv,
                    temp_itemid_vector_sync,
                    options,
                    result
                    )
                )
            )
            {
                cerr << "No job given." << endl;
                print_usage(argv[0], options, EXIT_SUCCESS);
            }

    stirr_em_up(
            temp_itemid_vector_subscribe,
            temp_itemid_vector_unsubscribe,
            temp_itemid_vector_sync,
            result["prefer_deletion"].as<bool>()
            );

    cerr.setf(ios::boolalpha);
    cerr << "Subscribe: " << toparse.populateItemIDs(temp_itemid_vector_subscribe,jobType::subscribe) << endl;
    cerr << "Unsubscribe: " << toparse.populateItemIDs(temp_itemid_vector_unsubscribe,jobType::unsubscribe) << endl;

    if(tosync)
    {
        if(result.count("prefer_deletion"))
        {
            cerr << "Caution! Sync is armed.\n";
        }
        else
        {
            cerr << "Caution! Sync is armed. --unsubscribe argument ignored.\n";
        }
    }

    toparse.setTheRest(result, tosync);

    cerr << endl;

    return true;
}//1}}}
