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

        ref class Export
        {
        public:
            System::UIntPtr Rva;
            System::UIntPtr Va;
            System::String^ DecoratedName;
            System::String^ UndecoratedName;
            System::String^ ForwarderName;
            int Ordinal;
        };

        ref class Import
        {
        public:
            System::UIntPtr Rva;
            System::UIntPtr Va;
            System::String^ DecoratedName;
            System::String^ UndecoratedName;
            int Ordinal;
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
            auto nameStr = interop::toUTF8(name);
            return Script::Module::BaseFromName(nameStr.c_str());
        }

        static duint FindByAddress(System::UIntPtr addr)
        {
            auto va = static_cast<duint>(addr.ToUInt64());

            return Script::Module::BaseFromAddr(va);
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

            return interop::stringFromUTF8(modPath);
        }

        static System::String^ GetName(System::UIntPtr base)
        {
            auto va = static_cast<duint>(base.ToUInt64());

            char modName[4096]{};
            if (!Script::Module::NameFromAddr(va, modName))
                return nullptr;

            return interop::stringFromUTF8(modName);
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
            res->Name = interop::stringFromUTF8(sect.name);
            return res;
        }

        static array<Export^>^ GetExports(System::UIntPtr base)
        {
            auto va = static_cast<duint>(base.ToUInt64());

            BridgeList<Script::Module::ModuleExport> list;

            Script::Module::ModuleInfo mod{};
            mod.base = va;

            if (!Script::Module::GetExports(&mod, &list))
                return nullptr;

            auto res = gcnew array<Export^>(list.Count());
            for (int i = 0; i < list.Count(); i++)
            {
                const auto& info = list[i];

                auto entry = gcnew Export();
                entry->Rva = System::UIntPtr(static_cast<uintptr_t>(info.rva));
                entry->Va = System::UIntPtr(static_cast<uintptr_t>(info.va));
                entry->DecoratedName = interop::stringFromUTF8(info.name);
                entry->UndecoratedName = interop::stringFromUTF8(info.undecoratedName);
                entry->ForwarderName = interop::stringFromUTF8(info.forwardName);
                entry->Ordinal = (int)info.ordinal;

                res[i] = entry;
            }

            return res;
        }

        static array<Import^>^ GetImports(System::UIntPtr base)
        {
            auto va = static_cast<duint>(base.ToUInt64());

            BridgeList<Script::Module::ModuleImport> list;

            Script::Module::ModuleInfo mod{};
            mod.base = va;

            if (!Script::Module::GetExports(&mod, &list))
                return nullptr;

            auto res = gcnew array<Import^>(list.Count());
            for (int i = 0; i < list.Count(); i++)
            {
                const auto& info = list[i];

                auto entry = gcnew Import();
                entry->Rva = System::UIntPtr(static_cast<uintptr_t>(info.iatRva));
                entry->Va = System::UIntPtr(static_cast<uintptr_t>(info.iatVa));
                entry->DecoratedName = interop::stringFromUTF8(info.name);
                entry->UndecoratedName = interop::stringFromUTF8(info.undecoratedName);
                entry->Ordinal = (int)info.ordinal;

                res[i] = entry;
            }

            return res;
        }
    };
}
