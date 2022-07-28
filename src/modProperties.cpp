#include "modProperties.hpp"

modProperties::modProperties(PublishedFileId_t const parsedItemID)
{
    auto to_parse = parsedItemID;
    auto const handle = SteamUGC()->CreateQueryUGCDetailsRequest(&to_parse,1);

    if (handle == k_UGCQueryHandleInvalid)
    {
        cerr << "exception in modProperties constructor(" << parsedItemID << "): SteamUGC()->CreateQueryUGCDetailsRequest returned invalid handle\n";
        exit (EXIT_FAILURE);
    }

    auto const result = SteamUGC()->SendQueryUGCRequest(handle);

    if (result == k_uAPICallInvalid)
    {
        SteamUGC()->ReleaseQueryUGCRequest(handle);
        cerr << "exception in modProperties constructor(" << parsedItemID << "): SteamUGC()->SendQueryUGCRequest returned invalid call\n";
        exit (EXIT_FAILURE);
    }
    else
    {
        SteamUGCDetails_t details;
        SteamUGC()->GetQueryUGCResult(handle, 1, &details);
        item_name = details.m_rgchTitle;
        remote_time_stamp = details.m_rtimeUpdated;
    }

    SteamUGC()->GetItemInstallInfo(parsedItemID, nullptr, nullptr, 1 , &local_time_stamp);

}

modProperties::~modProperties()
{

}
