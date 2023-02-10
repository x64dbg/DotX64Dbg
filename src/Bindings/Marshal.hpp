#pragma once

#include <string>

#pragma push_macro("_CRT_WINDOWS")
#define _CRT_WINDOWS
#include <msclr\marshal.h>
#pragma pop_macro("_CRT_WINDOWS")

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

namespace interop {

    using namespace System;
    using namespace System::Runtime::InteropServices;

    inline std::string toUTF8(System::String^ str)
    {
        msclr::interop::marshal_context oMarshalContext;

        const wchar_t* cstr = oMarshalContext.marshal_as<const wchar_t*>(str);

        const auto bytesRequired = WideCharToMultiByte(CP_UTF8, 0, cstr, -1, nullptr, 0, nullptr, nullptr);
        if (bytesRequired == 0)
            return {};

        std::string buf;
        buf.resize(bytesRequired);

        const auto bytesCopied = WideCharToMultiByte(CP_UTF8, 0, cstr, -1, &buf[0], bytesRequired, nullptr, nullptr);
        if (bytesRequired == 0)
            return {};

        // std::string has explicit null termination.
        while (buf.size() > 0 && buf.back() == '\0')
            buf.pop_back();

        return buf;
    }

    inline System::String^ stringFromUTF8(const char* str)
    {
        return Marshal::PtrToStringUTF8(System::IntPtr((void*)str));
    }
}
