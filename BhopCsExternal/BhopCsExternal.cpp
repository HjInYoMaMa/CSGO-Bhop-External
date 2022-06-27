#include <iostream>
#include <windows.h>
#include <vector>
#include "MemMan.h"
#include "Console.h"
namespace con = JadedHoboConsole;

MemMan MemClass;

//Offsets
struct gameOffsets
{
    DWORD lPlayer = 0xDBF4CC;
    DWORD fJump = 0x52858A8;
    DWORD flags = 0x104;
}offsets;

//Values
struct values
{
    DWORD localPlayer;
    DWORD process;
    DWORD gameModule;
    BYTE flag;
}val;

int main()
{
    SetConsoleTitleA("Pill poppin' in the club with my whole crew");
    val.process = MemClass.getProcess("csgo.exe"); //Getting process
    val.gameModule = MemClass.getModule(val.process, "client.dll");

    //What we will see in the console after process is found lmao
    std::cout << con::fg_white << "[" << con::fg_green << "+" << con::fg_white << "]" << con::fg_magenta << " Billionaire Boys Club, sweater is brand new\n" << con::fg_white;
    std::cout << "[" << con::fg_green << "+" << con::fg_white << "]" << con::fg_magenta << " Press space to bhop\n\n" << con::fg_white;

    std::cout << "[" << con::fg_green << "+" << con::fg_white << "]" << con::fg_magenta << " Build: June 27\n" << con::fg_white;
    std::cout << "[" << con::fg_green << "+" << con::fg_white << "]" << con::fg_magenta << " Made by hj.#0010\n" << con::fg_white;

    val.localPlayer = MemClass.readMem<DWORD>(val.gameModule + offsets.lPlayer);

    if (val.localPlayer == NULL)
    while (val.localPlayer == NULL)
        val.localPlayer = MemClass.readMem<DWORD>(val.gameModule + offsets.lPlayer);

    while (true)
    {
        val.flag = MemClass.readMem<BYTE>(val.localPlayer + offsets.flags);

        if (GetAsyncKeyState(VK_SPACE) && val.flag & (1 << 0))
            MemClass.writeMem<DWORD>(val.gameModule + offsets.fJump, 6);

        Sleep(1);
    }
    return 0;
}