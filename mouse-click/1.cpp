#include <windows.h>
#include <stdio.h>
// 全局区模拟，无需获取目标窗口的句柄，但还是在应用层，无法避免被侦测和禁用

int main()
{
    printf("开始模拟按键\n");
    for (int i = 0; ; i++)
    {
    SHORT key;
    UINT mappedkey;
    INPUT input = { 0 };
    key = VkKeyScan('w');
    mappedkey = MapVirtualKey(LOBYTE(key), 0);
    input.type = INPUT_KEYBOARD;
    input.ki.dwFlags = KEYEVENTF_SCANCODE;
    input.ki.wScan = mappedkey;

        SendInput(1, &input, sizeof(input));
        input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
        Sleep(1000);
        SendInput(1, &input, sizeof(input));
    }
    return 0;
}
