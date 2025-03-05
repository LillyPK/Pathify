#include "Pathenator.h"
#include <iostream>
#include <windows.h>

std::wstring StringToWString(const std::string& str) {
    return std::wstring(str.begin(), str.end());
}

void AddToPath(const std::string& newPath, bool modifySystemPath) {
    HKEY hKey;
    const wchar_t* keyPath = modifySystemPath
        ? L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment"
        : L"Environment";

    if (RegOpenKeyExW(modifySystemPath ? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER,
        keyPath, 0, KEY_READ | KEY_WRITE, &hKey) != ERROR_SUCCESS) {
        std::cerr << "Error opening registry key." << std::endl;
        return;
    }

    wchar_t currentPath[32767];
    DWORD size = sizeof(currentPath);
    if (RegQueryValueExW(hKey, L"Path", nullptr, nullptr, (LPBYTE)currentPath, &size) != ERROR_SUCCESS) {
        std::cerr << "Error reading PATH variable." << std::endl;
        RegCloseKey(hKey);
        return;
    }

    std::wstring newFullPath = std::wstring(currentPath) + L";" + StringToWString(newPath);

    if (RegSetValueExW(hKey, L"Path", 0, REG_EXPAND_SZ, (BYTE*)newFullPath.c_str(),
        (newFullPath.size() + 1) * sizeof(wchar_t)) != ERROR_SUCCESS) {
        std::cerr << "Error writing PATH variable." << std::endl;
    }
    else {
        std::cout << "Successfully updated PATH!" << std::endl;
    }

    RegCloseKey(hKey);
    SendMessageTimeoutW(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)L"Environment", SMTO_ABORTIFHUNG, 5000, nullptr);
}
