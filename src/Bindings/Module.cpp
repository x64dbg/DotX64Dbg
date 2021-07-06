#include <vector>
#include <cstdint>

#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_module.h"
#include "Register.hpp"
#include "pluginsdk/TitanEngine/TitanEngine.h"

#include <msclr/marshal.h>

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

        static duint GetSize(duint base)
        {
            return Script::Module::SizeFromAddr(base);
        }

        static System::String^ GetPath(duint base)
        {
            char modPath[4096]{};
            if (!Script::Module::PathFromAddr(base, modPath))
                return nullptr;

            return gcnew System::String(modPath);
        }

        static System::String^ GetName(duint base)
        {
            char modName[4096]{};
            if (!Script::Module::NameFromAddr(base, modName))
                return nullptr;

            return gcnew System::String(modName);
        }

        static duint GetEntrypoint(duint base)
        {
            return Script::Module::EntryFromAddr(base);
        }

        static int GetSectionCount(duint base)
        {
            return Script::Module::SectionCountFromAddr(base);
        }

        static Section^ GetSection(duint base, int index)
        {
            Script::Module::ModuleSectionInfo sect{};
            if (!Script::Module::SectionFromAddr(base, index, &sect))
                return nullptr;

            auto res = gcnew Section();
            res->Address = sect.addr;
            res->Size = sect.size;
            res->Name = gcnew System::String(sect.name);
            return res;
        }
    };
}
