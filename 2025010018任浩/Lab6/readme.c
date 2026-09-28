#include <windows.h>

// 启动记事本notepad.exe，同时打开c:\readme.txt文件
int main()
{
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    // 初始化结构体并清零
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // CreateProcessA 的第二个参数必须是可写数组
    char cmdline[] = "notepad.exe C:\\readme.txt";

    CreateProcessA(
        NULL,               // 程序名传NULL，从命令行解析
        cmdline,            // 命令行参数
        NULL, NULL, FALSE, 0, NULL, NULL,
        &si,                // 启动信息
        &pi                 // 进程信息
    );