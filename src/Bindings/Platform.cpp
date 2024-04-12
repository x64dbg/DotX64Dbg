#include <cstdint>
#include <Shlobj.h>

#include "pluginsdk/bridgemain.h"
#include "Marshal.hpp"

#pragma comment(lib, "Shell32.lib")

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Dotx64Dbg::Native {

    namespace Detail {

        // Converts the browser filter to the format required by GetOpenFileNameW.
        // Example
        //   Input: ".cs (*.cs)|*.cs|All files (*.*)|*.*"
        //   Output: "*.cs (*.cs)\0*.cs\0All files (*.*)\0*.*\0\0"
        static std::wstring getBrowseFilter(const std::wstring& filter)
        {
            // Replace | with \0
            std::wstring result = filter;
            for (size_t i = 0; i < result.size(); i++)
            {
                if (result[i] == L'|')
                    result[i] = L'\0';
            }
            // Append terminator
            result.push_back(L'\0');
            return result;
        }
    }

    public ref class Platform
    {
    public:

        static System::String^ BrowseForFolder(System::String^ title)
        {
            const auto titleStr = interop::toUTF16(title);

            BROWSEINFOW bi{};
            bi.hwndOwner = GuiGetWindowHandle();
            bi.lpszTitle = titleStr.c_str();
            bi.lpfn = nullptr;
            bi.lParam = 0;
            bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;

            auto pidl = SHBrowseForFolderW(&bi);
            if (!pidl)
                return nullptr;

            wchar_t path[MAX_PATH]{};
            if (!SHGetPathFromIDListW(pidl, path))
                return nullptr;

            return gcnew System::String(path);
        }

        static System::String^ OpenFileBrowse(System::String^ title, System::String^ filter)
        {
            const auto titleStr = interop::toUTF16(title);
            const auto filterStr = Detail::getBrowseFilter(interop::toUTF16(filter));
            wchar_t path[1024]{};

            OPENFILENAMEW ofn{};
            ofn.lStructSize = sizeof(ofn);
            ofn.hInstance = GetModuleHandle(nullptr);
            ofn.hwndOwner = GuiGetWindowHandle();
            ofn.lpstrTitle = titleStr.c_str();
            ofn.lpstrFilter = filterStr.c_str();
            ofn.nFilterIndex = 1;
            ofn.lpstrFile = path;
            ofn.nMaxFile = sizeof(path) / sizeof(wchar_t);
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

            if (!GetOpenFileNameW(&ofn))
                return nullptr;

            return gcnew System::String(path);
        }

        static System::String^ SaveFileBrowse(System::String^ title, System::String^ filter)
        {
            const auto titleStr = interop::toUTF16(title);
            const auto filterStr = Detail::getBrowseFilter(interop::toUTF16(filter));
            wchar_t path[1024]{};

            OPENFILENAMEW ofn{};
            ofn.lStructSize = sizeof(ofn);
            ofn.hInstance = GetModuleHandle(nullptr);
            ofn.hwndOwner = GuiGetWindowHandle();
            ofn.lpstrTitle = titleStr.c_str();
            ofn.lpstrFilter = filterStr.c_str();
            ofn.nFilterIndex = 1;
            ofn.lpstrFile = path;
            ofn.nMaxFile = sizeof(path) / sizeof(wchar_t);
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

            if (!GetSaveFileNameW(&ofn))
                return nullptr;

            return gcnew System::String(path);
        }

        static void SetClipboardText(System::String^ text)
        {
            const auto textStr = interop::toUTF16(text);

            const auto size = (textStr.size() + 1) * sizeof(wchar_t);
            auto hMem = GlobalAlloc(GMEM_MOVEABLE, size);
            if (!hMem)
                return;

            auto pMem = GlobalLock(hMem);
            if (!pMem)
            {
                GlobalFree(hMem);
                return;
            }
            memcpy(pMem, textStr.data(), size);
            GlobalUnlock(hMem);

            if (!OpenClipboard(GuiGetWindowHandle()))
            {
                GlobalFree(hMem);
                return;
            }

            EmptyClipboard();
            SetClipboardData(CF_UNICODETEXT, hMem);
            CloseClipboard();
        }

        static void MessageBoxInfo(System::String^ text, System::String^ title)
        {
            const auto textStr = interop::toUTF16(text);
            const auto titleStr = title ? interop::toUTF16(title) : L"Information";
            MessageBoxW(GuiGetWindowHandle(), textStr.c_str(), titleStr.c_str(), MB_ICONINFORMATION);
        }

        static void MessageBoxError(System::String^ text, System::String^ title)
        {
            const auto textStr = interop::toUTF16(text);
            const auto titleStr = title ? interop::toUTF16(title) : L"Error";
            MessageBoxW(GuiGetWindowHandle(), textStr.c_str(), titleStr.c_str(), MB_ICONERROR);
        }
    };

}
