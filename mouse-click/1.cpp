#include <windows.h>
#include <stdio.h>
// ȫ����ģ�⣬�����ȡĿ�괰�ڵľ������������Ӧ�ò㣬�޷����ⱻ���ͽ���

int main()
{
    printf("��ʼģ�ⰴ��\n");
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
