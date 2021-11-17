#pragma once 

#include <cstdint>
#include <utility>
#include <vector>

#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/_scriptapi_label.h"
#include "pluginsdk/_scriptapi_function.h"
#include "pluginsdk/_scriptapi_comment.h"

#include "Marshal.hpp"
#include <optional>

namespace Dotx64Dbg {

    namespace Detail
    {
        inline std::optional<Script::Label::LabelInfo> GetLabelInfo(System::UIntPtr addr)
        {
            auto va = reinterpret_cast<duint>(addr.ToPointer());

            Script::Label::LabelInfo info;
            if (Script::Label::GetInfo(va, &info))
            {
                return info;
            }

            return std::nullopt;
        }


        inline bool LabelIsTemporary(System::UIntPtr addr)
        {
            auto va = reinterpret_cast<duint>(addr.ToPointer());
            return Script::Label::IsTemporary(va);
        }

        inline std::optional<Script::Function::FunctionInfo> GetFuncInfo(System::UIntPtr addr)
        {
            auto va = reinterpret_cast<duint>(addr.ToPointer());

            Script::Function::FunctionInfo info;
            if (Script::Function::GetInfo(va, &info))
            {
                return info;
            }

            return std::nullopt;
        }

        inline std::optional<Script::Comment::CommentInfo> GetCommentInfo(System::UIntPtr addr)
        {
            auto va = reinterpret_cast<duint>(addr.ToPointer());

            Script::Comment::CommentInfo info;
            if (Script::Comment::GetInfo(va, &info))
            {
                return info;
            }

            return std::nullopt;
        }
    }

    public interface class Symbol
    {
    public:
        enum class Type
        {
            None = 0,
            Label,
            Function,
            Comment,
        };

        property Type SymbolType
        {
            virtual Type get();
        }

        property System::UIntPtr Address
        {
            virtual System::UIntPtr get();
        }

        property int Size
        {
            virtual int get();
        }

        property System::String^ Text
        {
            virtual System::String^ get();
        }
    };

    public ref class Symbols
    {
    public:
        /// Label
        /////////////////////////////////////////////////////////////////////////////
        ref class Label : public Symbol
        {
            System::UIntPtr _address;
            uint32_t _rva;

        public:
            [System::Flags]
            enum class Attribs
            {
                None = 0,
                Manual = (1 << 0),
                Temporary = (1 << 1),
            };

        internal:
            Label(System::UIntPtr address, uint32_t rva)
            {
                _address = address;
                _rva = rva;
            }

        public:
            property Symbol::Type SymbolType
            {
                virtual Symbol::Type get()
                {
                    return Symbol::Type::Label;
                }
            }

            property System::UIntPtr Address
            {
                virtual System::UIntPtr get()
                {
                    return _address;
                }
            }

            property uint32_t RVA
            {
                virtual uint32_t get()
                {
                    return _rva;
                }
            }

            property int Size
            {
                virtual int get()
                {
                    return 0;
                }
            }

            property System::String^ Text
            {
                virtual System::String^ get()
                {
                    if (auto info = Detail::GetLabelInfo(_address))
                    {
                        return interop::stringFromUTF8(info->text);
                    }
                    return nullptr;
                }
            }

            property System::String^ Module
            {
                virtual System::String^ get()
                {
                    if (auto info = Detail::GetLabelInfo(_address))
                    {
                        return interop::stringFromUTF8(info->mod);
                    }
                    return nullptr;
                }
            }

            property Attribs Attributes
            {
                Attribs get()
                {
                    Attribs res = Attribs::None;

                    if (auto info = Detail::GetLabelInfo(_address))
                    {
                        if (info->manual)
                            res = static_cast<Attribs>(static_cast<uint32_t>(res) | static_cast<uint32_t>(Attribs::Manual));

                        if (Detail::LabelIsTemporary(_address))
                            res = static_cast<Attribs>(static_cast<uint32_t>(res) | static_cast<uint32_t>(Attribs::Temporary));
                    }

                    return res;
                }
            }

            static Symbols::Label^ Get(System::UIntPtr address)
            {
                auto va = reinterpret_cast<duint>(address.ToPointer());

                Script::Label::LabelInfo info;
                if (Script::Label::GetInfo(va, &info))
                {
                    Label^ res = gcnew Label(address, static_cast<uint32_t>(info.rva));
                    return res;
                }

                return nullptr;
            }

            static bool Set(System::UIntPtr address, System::String^ name, Symbols::Label::Attribs attribs)
            {
                auto va = reinterpret_cast<duint>(address.ToPointer());

                auto nameStr = interop::toUTF8(name);
                bool manual = (attribs & Symbols::Label::Attribs::Manual) != Symbols::Label::Attribs::None;

                // NOTE: Temporary is not supported until the https://github.com/x64dbg/x64dbg/pull/2695 is merged.
                bool temporary = (attribs & Label::Attribs::Manual) != Symbols::Label::Attribs::None;

                return Script::Label::Set(va, nameStr.c_str(), manual, temporary);
            }

            static bool Remove(System::UIntPtr address)
            {
                auto va = reinterpret_cast<duint>(address.ToPointer());

                return Script::Label::Delete(va);
            }
        };

    public:
        /// Function
        /////////////////////////////////////////////////////////////////////////////
        ref class Function : public Symbol
        {
            System::UIntPtr _address;
            uint32_t _rva;

        internal:
            Function(System::UIntPtr address, uint32_t rva)
            {
                _address = address;
            }

        public:
            property Symbol::Type SymbolType
            {
                virtual Symbol::Type get()
                {
                    return Symbol::Type::Function;
                }
            }

            property System::UIntPtr Address
            {
                virtual System::UIntPtr get()
                {
                    return _address;
                }
            }

            property uint32_t RVA
            {
                virtual uint32_t get()
                {
                    return _rva;
                }
            }

            property int Size
            {
                virtual int get()
                {
                    if (auto info = Detail::GetFuncInfo(_address))
                    {
                        return static_cast<int>(info->rvaEnd - info->rvaStart);
                    }
                    return 0;
                }
            }

            property System::String^ Text
            {
                virtual System::String^ get()
                {
                    return gcnew System::String("<function>");
                }
            }

            property System::String^ Module
            {
                virtual System::String^ get()
                {
                    if (auto info = Detail::GetFuncInfo(_address))
                    {
                        return interop::stringFromUTF8(info->mod);
                    }
                    return nullptr;
                }
            }

            static Symbols::Function^ Get(System::UIntPtr address)
            {
                if (auto info = Detail::GetFuncInfo(address))
                {
                    Symbols::Function^ res = gcnew Symbols::Function(address, info->rvaStart);
                    return res;
                }
                return nullptr;
            }

            static bool Set(System::UIntPtr startAddress, System::UIntPtr endAddress, bool manual)
            {
                auto startVA = reinterpret_cast<duint>(startAddress.ToPointer());
                auto endVA = reinterpret_cast<duint>(startAddress.ToPointer());

                return Script::Function::Add(startVA, endVA, manual, 0);
            }

            static bool Remove(System::UIntPtr address)
            {
                auto va = reinterpret_cast<duint>(address.ToPointer());
                return Script::Function::Delete(va);
            }
        };

    public:
        /// Comment
        /////////////////////////////////////////////////////////////////////////////
        ref class Comment : public Symbol
        {
            System::UIntPtr _address;
            uint32_t _rva;

        internal:
            Comment(System::UIntPtr address, uint32_t rva)
            {
                _address = address;
            }

        public:
            property Symbol::Type SymbolType
            {
                virtual Symbol::Type get()
                {
                    return Symbol::Type::Comment;
                }
            }

            property System::UIntPtr Address
            {
                virtual System::UIntPtr get()
                {
                    return _address;
                }
            }

            property uint32_t RVA
            {
                virtual uint32_t get()
                {
                    return _rva;
                }
            }

            property int Size
            {
                virtual int get()
                {
                    return 0;
                }
            }

            property System::String^ Text
            {
                virtual System::String^ get()
                {
                    if (auto cmtInfo = Detail::GetCommentInfo(_address))
                    {
                        return interop::stringFromUTF8(cmtInfo->text);
                    }
                    return nullptr;
                }
            }

            property System::String^ Module
            {
                virtual System::String^ get()
                {
                    if (auto info = Detail::GetCommentInfo(_address))
                    {
                        return interop::stringFromUTF8(info->mod);
                    }
                    return nullptr;
                }
            }

            static Symbols::Comment^ Get(System::UIntPtr address)
            {
                if (auto info = Detail::GetCommentInfo(address))
                {
                    Symbols::Comment^ res = gcnew Symbols::Comment(address, info->rva);
                    return res;
                }
                return nullptr;
            }

            static bool Set(System::UIntPtr address, System::String^ text, bool manual)
            {
                auto va = reinterpret_cast<duint>(address.ToPointer());

                auto textStr = interop::toUTF8(text);
                return Script::Comment::Set(va, textStr.c_str(), manual);
            }

            static bool Remove(System::UIntPtr address)
            {
                auto va = reinterpret_cast<duint>(address.ToPointer());
                return Script::Comment::Delete(va);
            }
        };
    };

}
