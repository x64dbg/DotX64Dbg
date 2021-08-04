#include <vector>
#include <cstdint>

#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_module.h"
#include "Register.hpp"
#include "pluginsdk/TitanEngine/TitanEngine.h"

#include "Marshal.hpp"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Dotx64Dbg::Native
{
    public ref class Module
    {
    public:
        ref class Section
        {
        public:
            System::String^ Name;
            duint Address;
            duint Size;
        };

        static array<duint>^ GetAll()
        {
            BridgeList<Script::Module::ModuleInfo> list;

            if (!Script::Module::GetList(&list))
                return nullptr;

            auto res = gcnew array<duint>(list.Count());
            for (int i = 0; i < list.Count(); i++)
            {
                res[i] = list[i].base;
            }
            return res;
        }

        static duint GetMain()
        {
            return Script::Module::GetMainModuleBase();
        }

        static duint FindByName(System::String^ name)
        {
            msclr::interop::marshal_context oMarshalContext;

            const char* cstr = oMarshalContext.marshal_as<const char*>(name);

            return Script::Module::BaseFromName(cstr);
        }

        static duint GetSize(System::UIntPtr base)
        {
            auto va = static_cast<duint>(base.ToUInt64());
            return Script::Module::SizeFromAddr(va);
        }

        static System::String^ GetPath(System::UIntPtr base)
        {
            auto va = static_cast<duint>(base.ToUInt64());

            char modPath[4096]{};
            if (!Script::Module::PathFromAddr(va, modPath))
                return nullptr;

            return gcnew System::String(modPath);
        }

        static System::String^ GetName(System::UIntPtr base)
        {
            auto va = static_cast<duint>(base.ToUInt64());

            char modName[4096]{};
            if (!Script::Module::NameFromAddr(va, modName))
                return nullptr;

            return gcnew System::String(modName);
        }

        static duint GetEntrypoint(System::UIntPtr base)
        {
            auto va = static_cast<duint>(base.ToUInt64());

            return Script::Module::EntryFromAddr(va);
        }

        static int GetSectionCount(System::UIntPtr base)
        {
            auto va = static_cast<duint>(base.ToUInt64());

            return Script::Module::SectionCountFromAddr(va);
        }

        static Section^ GetSection(System::UIntPtr base, int index)
        {
            auto va = static_cast<duint>(base.ToUInt64());

            Script::Module::ModuleSectionInfo sect{};
            if (!Script::Module::SectionFromAddr(va, index, &sect))
                return nullptr;

            auto res = gcnew Section();
            res->Address = sect.addr;
            res->Size = sect.size;
            res->Name = gcnew System::String(sect.name);
            return res;
        }
    };
}
