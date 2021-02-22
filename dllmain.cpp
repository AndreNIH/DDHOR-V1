// dllmain.cpp : Defines the entry point for the DLL application.
#define WIN32_LEAN_AND_MEAN
#include "pch.h"
#include "Hooks/GJBaseGameLayer.h"
#include "Hooks/PlayLayer.h"
#include "Hooks/PlayerObject.h"
#include "Hooks/MenuLoaders/LevelPage.h"

#include <cocos2d.h>
#include "Engine/SharedBot.h"
#include "Overlay/graphics.h"

#include <Minhook/MinHook.h>

#pragma comment(lib,"Libs/minhook.x32.lib")

void ioLoop() {

    std::cout <<
        "1)Start Recording\n"
        "2)Stop Recording\n"
        "3)Start playback\n"
        "4)Stop playback\n"
        "5)Exit\n\n";

    for (;;) {
        int choice = 0;
        std::cout << ">>";
        std::cin >> choice;
        std::cin.ignore(1000, '\n');
        std::string name;
        switch (choice) {
        case 1:
            BotManager::shared()->setStage(BotStage::RECORDING);
            break;
        case 2:
            std::cout << "Name:";
            std::getline(std::cin, name);
            
            BotManager::shared()->saveRecording(name);
            BotManager::shared()->setStage(BotStage::IDLE);

            break;
        case 3:
            std::cout << "Name:";
            std::getline(std::cin, name);
            if (BotManager::shared()->loadRecording(name))
                BotManager::shared()->setStage(BotStage::PLAYING);
            else std::cout << "Error\n";
            break;
        case 4:
            BotManager::shared()->setStage(BotStage::IDLE);
            break;
        case 5:
            return;
        default:
            break;
        };
    
    }
}
DWORD WINAPI my_thread(void* hModule) {
    AllocConsole();
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
    freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
    MH_Initialize();
    
    //Bot Essentials
    Hook::GJBaseGameLayer::memInit();
    Hook::PlayLayer::memInit();
    Hook::PlayerObject::memInit();
    
    //User Interface 
    OverlayGraphics::initialize();

    MH_EnableHook(MH_ALL_HOOKS);
    ioLoop();

    
    //This line will dettach your DLL when executed. Remove if needed
    OverlayGraphics::uninitilize();
    MH_Uninitialize();
    FreeConsole();
    FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(hModule), 0);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0x1000, my_thread, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

