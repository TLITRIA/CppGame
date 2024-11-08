// GameMain.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>

#include "GameSkeleton.h"

#include "GameChapt1_Pong.h"
#include "GameChapt2_2D.h"


int main()
{
    std::cout << "Hello World!\n";
    GameChapt2_2D game;
    bool ret = game.Initialize();

    std::cout << (ret ? "success" : "false");
    if (ret)
    {
        game.RunLoop();
    }
    game.ShutDown();
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

/*
* Note：
* 在一对头文件和源文件快速切换的方式：ctrl+k>o
* 在多个标签页来回切换 ctrl+tab>tab
返回上一个编辑位置：Ctrl + - 这个快捷键会带你回到上一个编辑的位置。
前往下一个编辑位置：Ctrl + Shift + - 这个快捷键会带你前往下一个编辑的位置。
前往上一个浏览位置：Ctrl + Shift + F2 这个快捷键会带你回到上一个浏览的位置。
前往下一个浏览位置：Ctrl + F2 这个快捷键会带你前往下一个浏览的位置。
*/
