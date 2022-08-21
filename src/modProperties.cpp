#include "modProperties.hpp"
#include <cstdio>
#include <cstring>

modProperties::modProperties(const PublishedFileId_t parsedItemID, bool ommit_item_errors)
{
    ItemID = parsedItemID;
    PublishedFileId_t item_id[1];
    item_id[0] = ItemID;
    auto const handle = SteamUGC()->CreateQueryUGCDetailsRequest(item_id,1);

    if (handle == k_UGCQueryHandleInvalid)
    {
        cerr << "exception in modProperties constructor(" << parsedItemID << "): SteamUGC()->CreateQueryUGCDetailsRequest returned invalid handle.";
        if(!ommit_item_errors)
        {
            cerr << endl;
            exit (EXIT_FAILURE);
        }
        else
        {
            cerr << " Ommitting..." << endl;
            proper_item = false;
        }
    }

    auto const result = SteamUGC()->SendQueryUGCRequest(handle);

    if (result == k_uAPICallInvalid)
    {
        SteamUGC()->ReleaseQueryUGCRequest(handle);
        cerr << "exception in modProperties constructor(" << parsedItemID << "): SteamUGC()->SendQueryUGCRequest returned invalid call\n";
        if(!ommit_item_errors)
        {
            cerr << endl;
            exit (EXIT_FAILURE);
        }
        else
        {
            cerr << " Ommitting..." << endl;
            proper_item = false;
        }
    }
    else
    {
        proper_item = true;
        SteamUGCDetails_t details;
        SteamUGC()->GetQueryUGCResult(handle, 0, &details);
        item_name.assign(details.m_rgchTitle,k_cchPublishedDocumentTitleMax);
        remote_time_stamp = details.m_rtimeUpdated;
    }

    SteamUGC()->GetItemInstallInfo(parsedItemID, nullptr, nullptr, 1 , &local_time_stamp);
    what_state = SteamUGC()->GetItemState(ItemID);

}

modProperties::~modProperties()
{

}

void modProperties::print_properties()
{

    if (proper_item) {
        cerr << "ItemID: " << ItemID << endl
            << "State: " << what_state << endl
            << "local_time_stamp: " << local_time_stamp << endl
            << "remote_time_stamp: " << local_time_stamp << endl
            << "item_name: " << item_name << endl
            ;
    }
    else {
        cerr << "Item: " << ItemID << " incorrect." << endl;
    }
}
