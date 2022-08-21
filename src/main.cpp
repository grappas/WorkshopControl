#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "../_deps/steamworkssdk-src/include/steam/steam_api.h"
#include <chrono>
#include <string>
#include <thread>
#include "steamAppIdOpen.hpp"
#include "parsing.hpp"
#include "ParsedOptions.hpp"
#include "modProperties.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    cerr << endl;
    ParsedOptions toparse;
    steamAppIdOpen open_app_id;

    parse_input_options(argc,argv,toparse);

    open_app_id.PopulateWithAppID(toparse);

    if (!SteamAPI_Init())
    {
        cerr << "Is your Steam Client running? Have you passed right AppID?\n\n";
        return 1;
    }

    modProperties chuj(463939057,true);
    chuj.print_properties();

    //subskrybowanie
    //SteamUGC()->SubscribeItem(PublishedFileId_t nPublishedFileID);

    //odsubskrybowanie
    //SteamUGC()->UnsubscribeItem(PublishedFileId_t nPublishedFileID);
    //
    //pobieranie (ostrożnie!!! pierw zasubskrybuj)
    //SteamUGC()->DownloadItem(PublishedFileId_t nPublishedFileID, bool bHighPriority)
    //
    //usuwanie (TAK SAMO JAK POBIERANIE!!!)
    //SteamUGC()->DeleteItem(PublishedFileId_t nPublishedFileID)
    //PublishedFileId_t
    //informacje o pobieraniu
    //SteamUGC()->GetItemDownloadInfo(PublishedFileId_t nPublishedFileID, uint64 *punBytesDownloaded, uint64 *punBytesTotal)
    //
    //bieżące informacje o modzie na dysku
    //SteamUGC()->GetItemInstallInfo(PublishedFileId_t nPublishedFileID, uint64 *punSizeOnDisk, char *pchFolder, uint32 cchFolderSize, uint32 *punTimeStamp)
    //
    //zwraca stan moda (czy się pobiera itd.)
    //
    //SteamUGC()->GetItemState(PublishedFileId_t nPublishedFileID)
    //
    //lista zainstalowanych
    //
    //SteamUGC()->GetSubscribedItems(PublishedFileId_t *pvecPublishedFileID, uint32 cMaxEntries)
    //SteamUGC()->GetQueryUGCResult(UGCQueryHandle_t handle, uint32 index, SteamUGCDetails_t *pDetails)
    //SteamUGC()->CreateQueryUGCDetailsRequest(PublishedFileId_t *pvecPublishedFileID, uint32 unNumPublishedFileIDs)

        // jak widać
    //SteamUGC()->GetNumSubscribedItems();
    //
    SteamAPI_Shutdown();

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

    return 0;
}

