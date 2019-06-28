#ifndef TOPMOST_HPP
#define TOPMOST_HPP

#include "Constant.hpp"

#include <Windows.h>
#include <TlHelp32.h>

#include <chrono>
#include <thread>
#include <vector>

namespace TopMost
{
using namespace std::chrono_literals;

struct MakeTop {
    std::vector<HWND> children;
    std::thread setter;
    bool runnable;

    static constexpr std::chrono::seconds term = 1s;

    MakeTop(bool runThread = Constant::TOP_MOST_RUNTHREAD) : 
        children(GetChildWindowHandle()), setter(), runnable(false)
    {
        SetChildWindowsTopMost();
        if (runThread) {
            RunThread();
        }
    }

    ~MakeTop() {
        if (runnable) {
            runnable = false;
            setter.join();
        }
    }

    void RunThread() {
        if (Constant::DEBUG) {
            std::cout << "[*] number of child windows: " << children.size() << std::endl;
        }

        runnable = true;
        setter = std::thread([this]() {
            while (runnable) {
                std::this_thread::sleep_for(term);

                HWND hWnd = GetTopWindow(NULL);
                static std::string blacklist[] = {
                    "MSCTFIME UI", "Default IME", ""
                };

                while (hWnd != NULL) {
                    if (std::find(children.begin(), children.end(), hWnd) != children.end()) {
                        break;
                    }

                    constexpr size_t bufsize = 1024;
                    wchar_t wtext[bufsize] = { 0, };
                    int read = GetWindowTextW(hWnd, wtext, bufsize);

                    std::string text(wtext, wtext + read);
                    if (std::find(blacklist, std::end(blacklist), text) == std::end(blacklist)) {
                        UpdateChildWindows();
                        SetChildWindowsTopMost();
                        
                        if (Constant::DEBUG) {
                            std::cout << "[*] find: " << text << " / number of child windows: " << children.size() << std::endl;
                        }
                        break;
                    }

                    hWnd = GetWindow(hWnd, GW_HWNDNEXT);
                }
            }
        });
    }

    void SetChildWindowsTopMost() {
        for (HWND hWnd : children) {
            SetTopMost(hWnd);
        }
    }

    void UpdateChildWindows() {
        std::vector<HWND> vec = GetChildWindowHandle();
        for (HWND hWnd : vec) {
            if (std::find(children.begin(), children.end(), hWnd) == children.end()) {
                children.push_back(hWnd);
            }
        }
    }

    static void SetTopMost(HWND hWnd) {
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }

    static std::vector<HWND> GetChildWindowHandle() {
        std::pair<DWORD, std::vector<HWND>> pair;
        pair.first = GetCurrentProcessId();

        BOOL bResult = EnumWindows([](HWND hWnd, LPARAM lpParam) {
            DWORD dwPid;
            auto param = reinterpret_cast<std::pair<DWORD, std::vector<HWND>>*>(lpParam);
            if (GetWindowThreadProcessId(hWnd, &dwPid) && dwPid == param->first) {
                param->second.push_back(hWnd);
            }
            return TRUE;
            }, reinterpret_cast<LPARAM>(&pair));

        return pair.second;
    }
};
}

#endif