#pragma once

#include "Mnemonic.hpp"
#include "Instruction.Operand.hpp"
#include "Instruction.Operands.hpp"
#include "Instruction.EFlags.hpp"

namespace Dotx64Dbg {

    public ref struct InstructionMeta
    {
    public:
        Mnemonic _Mnemonic;
        EFlags FlagsRead;
        EFlags FlagsModified;
        EFlags FlagsUndefined;
        array<OperandAccess>^ Access;
        array<OperandVisibility>^ Visibility;
        array<IOperand^>^ Operands;

        InstructionMeta(Mnemonic mnemonic,
            uint16_t flagsRead,
            uint16_t flagsModified,
            uint16_t flagsUndefined,
            array<OperandAccess>^ access,
            array<OperandVisibility>^ vis,
            array<IOperand^>^ operands)
        {
            _Mnemonic = mnemonic;
            FlagsRead = (EFlags)flagsRead;
            FlagsModified = (EFlags)flagsModified;
            FlagsUndefined = (EFlags)flagsUndefined;
            Access = access;
            Visibility = vis;
            Operands = operands;
        }

        System::String^ ToString() override
        {
            System::String^ res = gcnew System::String("{\n");

            System::String^ line = nullptr;
            System::String^ fmt = nullptr;

            fmt = gcnew System::String("    Mnemonic = {0},\n");
            line = String::Format(fmt, _Mnemonic);
            res = String::Concat(res, line);

            fmt = gcnew System::String("    Flags = {{ Read = {{{0}}}, Write = {{{1}}}, Undefined = {{{2}}} }},\n");
            line = String::Format(fmt, FlagsRead, FlagsModified, FlagsUndefined);
            res = String::Concat(res, line);

            fmt = gcnew System::String("    Operands = {{\n");
            line = String::Format(fmt);
            res = String::Concat(res, line);

            for (int i = 0; i < Access->Length; i++)
            {
                if (Visibility[i] == OperandVisibility::Invalid)
                    break;

                if (Operands[i] == Operand::None)
                {
                    fmt = gcnew System::String("        [{0}] = {{ Operand = %ARG%, Access = {{{1}}}, Visibility = {2} }},\n");
                    line = String::Format(fmt, i, Access[i], Visibility[i]);
                    res = String::Concat(res, line);
                }
                else
                {
                    fmt = gcnew System::String("        [{0}] = {{ Operand = {1}, Access = {{{2}}}, Visibility = {3} }},\n");
                    line = String::Format(fmt, i, Operands[i], Access[i], Visibility[i]);
                    res = String::Concat(res, line);
                }
            }

            fmt = gcnew System::String("    }},\n");
            line = String::Format(fmt);
            res = String::Concat(res, line);

            fmt = gcnew System::String("}}");
            line = String::Format(fmt);
            res = String::Concat(res, line);

            return res;
        }
    };

    ref class InstructionMetaData
    {
        static initonly array<InstructionMeta^>^ InstrMetaTable = gcnew array<InstructionMeta^>
        {
            gcnew InstructionMeta(
                Mnemonic::Invalid,
                0x0000, 0x0000, 0x0000,
                gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Aaa,
                    0x0000, 0x0011, 0x08c4,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Aad,
                    0x0000, 0x00c4, 0x0811,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Aam,
                    0x0000, 0x00c4, 0x0811,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Aas,
                    0x0000, 0x0011, 0x08c4,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Adc,
                    0x0001, 0x011F, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::ReadWrite, OperandAccess::Read, OperandAccess::ReadWrite, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Explicit, OperandVisibility::Explicit, OperandVisibility::Hidden, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operands::EFlags, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Adcx,
                    0x0001, 0x0001, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Add,
                    0x0000, 0x011F, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::ReadWrite, OperandAccess::Read, OperandAccess::Write, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Explicit, OperandVisibility::Explicit, OperandVisibility::Hidden, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operands::EFlags, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Addpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Addps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Addsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Addss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Addsubpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Addsubps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Adox,
                    0x0800, 0x0800, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Aesdec,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Aesdeclast,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Aesenc,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Aesenclast,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Aesimc,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Aeskeygenassist,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::And,
                    0x0000, 0x011B, 0x0004,
                    gcnew array<OperandAccess> { OperandAccess::ReadWrite, OperandAccess::Read, OperandAccess::Write, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Explicit, OperandVisibility::Explicit, OperandVisibility::Hidden, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operands::EFlags, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Andn,
                    0x0000, 0x00c0, 0x0014,
                    gcnew array<OperandAccess> { OperandAccess::ReadWrite, OperandAccess::Read, OperandAccess::Write, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Explicit, OperandVisibility::Explicit, OperandVisibility::Hidden, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operands::EFlags, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Andnpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Andnps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Andpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Andps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Arpl,
                    0x0000, 0x0040, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Bextr,
                    0x0000, 0x0040, 0x0094,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Blcfill,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Blci,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Blcic,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Blcmsk,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Blcs,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Blendpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Blendps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Blendvpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Blendvps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Blsfill,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Blsi,
                    0x0000, 0x00c1, 0x0014,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Blsic,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Blsmsk,
                    0x0000, 0x0081, 0x0014,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Blsr,
                    0x0000, 0x00c1, 0x0014,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Bndcl,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Bndcn,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Bndcu,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Bndldx,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Bndmk,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Bndmov,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Bndstx,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Bound,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Bsf,
                    0x0000, 0x0040, 0x0895,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Bsr,
                    0x0000, 0x0040, 0x0895,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Bswap,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Bt,
                    0x0000, 0x0001, 0x0894,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Btc,
                    0x0000, 0x0001, 0x0894,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Btr,
                    0x0000, 0x0001, 0x0894,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Bts,
                    0x0000, 0x0001, 0x0894,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Bzhi,
                    0x0000, 0x00c1, 0x0014,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Call,
                    0x0000, 0x0000, 0x08d5,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cbw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cdq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cdqe,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Clac,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Clc,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cld,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cldemote,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Clevict0,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Clevict1,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Clflush,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Clflushopt,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Clgi,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cli,
                    0x0000, 0x0200, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Clrssbsy,
                    0x0000, 0x0001, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Clts,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Clwb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Clzero,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmc,
                    0x0001, 0x0001, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmovb,
                    0x0001, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmovbe,
                    0x0041, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmovl,
                    0x0880, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmovle,
                    0x08c0, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmovnb,
                    0x0001, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmovnbe,
                    0x0041, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmovnl,
                    0x0880, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmovnle,
                    0x08c0, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmovno,
                    0x0800, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmovnp,
                    0x0004, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmovns,
                    0x0080, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmovnz,
                    0x0040, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmovo,
                    0x0800, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmovp,
                    0x0004, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmovs,
                    0x0080, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmovz,
                    0x0040, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmp,
                    0x0000, 0x011F, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::Read, OperandAccess::Read, OperandAccess::Write, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Explicit, OperandVisibility::Explicit, OperandVisibility::Hidden, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operands::EFlags, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmppd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmpps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmpsb,
                    0x0400, 0x08d5, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmpsd,
                    0x0400, 0x08d5, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmpsq,
                    0x0400, 0x08d5, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmpss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmpsw,
                    0x0400, 0x08d5, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmpxchg,
                    0x0000, 0x08d5, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmpxchg16b,
                    0x0000, 0x0040, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cmpxchg8b,
                    0x0000, 0x0040, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Comisd,
                    0x0000, 0x0045, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Comiss,
                    0x0000, 0x0045, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cpuid,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::ReadWrite, OperandAccess::Write, OperandAccess::Write, OperandAccess::Write, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Hidden, OperandVisibility::Hidden, OperandVisibility::Hidden, OperandVisibility::Hidden, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { gcnew Operand::OpReg(Register::Eax), gcnew Operand::OpReg(Register::Ebx), gcnew Operand::OpReg(Register::Ecx), gcnew Operand::OpReg(Register::Edx), Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cqo,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Crc32,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvtdq2pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvtdq2ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvtpd2dq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvtpd2pi,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvtpd2ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvtpi2pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvtpi2ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvtps2dq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvtps2pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvtps2pi,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvtsd2si,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvtsd2ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvtsi2sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvtsi2ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvtss2sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvtss2si,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvttpd2dq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvttpd2pi,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvttps2dq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvttps2pi,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvttsd2si,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cvttss2si,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cwd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Cwde,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Daa,
                    0x0000, 0x00d5, 0x0800,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Das,
                    0x0000, 0x00d5, 0x0800,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Dec,
                    0x0000, 0x08d4, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Delay,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Div,
                    0x0000, 0x0000, 0x08d5,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Divpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Divps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Divsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Divss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Dppd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Dpps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Emms,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Encls,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Enclu,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Enclv,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Endbr32,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Endbr64,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Enqcmd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Enqcmds,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Enter,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Extractps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Extrq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::F2xm1,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fabs,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fadd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Faddp,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fbld,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fbstp,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fchs,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fcmovb,
                    0x0001, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fcmovbe,
                    0x0041, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fcmove,
                    0x0040, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fcmovnb,
                    0x0001, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fcmovnbe,
                    0x0041, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fcmovne,
                    0x0040, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fcmovnu,
                    0x0004, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fcmovu,
                    0x0004, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fcom,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fcomi,
                    0x0000, 0x0045, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fcomip,
                    0x0000, 0x0045, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fcomp,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fcompp,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fcos,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fdecstp,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fdisi8087_nop,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fdiv,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fdivp,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fdivr,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fdivrp,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Femms,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Feni8087_nop,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Ffree,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Ffreep,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fiadd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Ficom,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Ficomp,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fidiv,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fidivr,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fild,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fimul,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fincstp,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fist,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fistp,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fisttp,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fisub,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fisubr,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fld,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fld1,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fldcw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fldenv,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fldl2e,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fldl2t,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fldlg2,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fldln2,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fldpi,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fldz,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fmul,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fmulp,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fnclex,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fninit,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fnop,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fnsave,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fnstcw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fnstenv,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fnstsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fpatan,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fprem,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fprem1,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fptan,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Frndint,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Frstor,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fscale,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fsetpm287_nop,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fsin,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fsincos,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fsqrt,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fst,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fstp,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fstpnce,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fsub,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fsubp,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fsubr,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fsubrp,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Ftst,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fucom,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fucomi,
                    0x0000, 0x0045, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fucomip,
                    0x0000, 0x0045, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fucomp,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fucompp,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fwait,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fxam,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fxch,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fxrstor,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fxrstor64,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fxsave,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fxsave64,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fxtract,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fyl2x,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Fyl2xp1,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Getsec,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Gf2p8affineinvqb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Gf2p8affineqb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Gf2p8mulb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Haddpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Haddps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Hlt,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Hsubpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Hsubps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Idiv,
                    0x0000, 0x0000, 0x08d5,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Imul,
                    0x0000, 0x0881, 0x0054,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::In,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Inc,
                    0x0000, 0x08d4, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Incsspd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Incsspq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Insb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Insd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Insertps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Insertq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Insw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Int,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Int1,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Int3,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Into,
                    0x0800, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Invd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Invept,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Invlpg,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Invlpga,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Invpcid,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Invvpid,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Iret,
                    0x0000, 0x0000, 0x08d5,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Iretd,
                    0x0000, 0x0000, 0x08d5,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Iretq,
                    0x0000, 0x0000, 0x08d5,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jb,
                    0x0001, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jbe,
                    0x0041, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jcxz,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jecxz,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jknzd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jkzd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jl,
                    0x0880, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jle,
                    0x08c0, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jmp,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jnb,
                    0x0001, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jnbe,
                    0x0041, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jnl,
                    0x0880, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jnle,
                    0x08c0, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jno,
                    0x0800, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jnp,
                    0x0004, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jns,
                    0x0080, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jnz,
                    0x0040, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jo,
                    0x0800, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jp,
                    0x0004, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jrcxz,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Js,
                    0x0080, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Jz,
                    0x0040, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kaddb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kaddd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kaddq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kaddw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kand,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kandb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kandd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kandn,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kandnb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kandnd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kandnq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kandnr,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kandnw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kandq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kandw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kconcath,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kconcatl,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kextract,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kmerge2l1h,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kmerge2l1l,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kmov,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kmovb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kmovd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kmovq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kmovw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Knot,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Knotb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Knotd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Knotq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Knotw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kor,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Korb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kord,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Korq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kortest,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kortestb,
                    0x0000, 0x0041, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kortestd,
                    0x0000, 0x0041, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kortestq,
                    0x0000, 0x0041, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kortestw,
                    0x0000, 0x0041, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Korw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kshiftlb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kshiftld,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kshiftlq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kshiftlw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kshiftrb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kshiftrd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kshiftrq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kshiftrw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Ktestb,
                    0x0000, 0x0041, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Ktestd,
                    0x0000, 0x0041, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Ktestq,
                    0x0000, 0x0041, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Ktestw,
                    0x0000, 0x0041, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kunpckbw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kunpckdq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kunpckwd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kxnor,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kxnorb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kxnord,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kxnorq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kxnorw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kxor,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kxorb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kxord,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kxorq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Kxorw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lahf,
                    0x00d5, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lar,
                    0x0000, 0x0040, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lddqu,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Ldmxcsr,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lds,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lea,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Leave,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Les,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lfence,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lfs,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lgdt,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lgs,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lidt,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lldt,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Llwpcb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lmsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lodsb,
                    0x0400, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lodsd,
                    0x0400, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lodsq,
                    0x0400, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lodsw,
                    0x0400, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Loop,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Loope,
                    0x0040, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Loopne,
                    0x0040, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lsl,
                    0x0000, 0x0040, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Ltr,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lwpins,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lwpval,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Lzcnt,
                    0x0000, 0x0041, 0x0894,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Maskmovdqu,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Maskmovq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Maxpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Maxps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Maxsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Maxss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Mfence,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Minpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Minps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Minsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Minss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Monitor,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Monitorx,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Montmul,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Mov,
                    0x0000, 0x0000, 0x08d5,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movapd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movaps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movbe,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movddup,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movdir64b,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movdiri,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movdq2q,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movdqa,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movdqu,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movhlps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movhpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movhps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movlhps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movlpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movlps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movmskpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movmskps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movntdq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movntdqa,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movnti,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movntpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movntps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movntq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movntsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movntss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movq2dq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movsb,
                    0x0400, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movsd,
                    0x0400, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movshdup,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movsldup,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movsq,
                    0x0400, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movsw,
                    0x0400, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movsx,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movsxd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movupd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movups,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Movzx,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Mpsadbw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Mul,
                    0x0000, 0x0801, 0x00d4,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Mulpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Mulps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Mulsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Mulss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Mulx,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Mwait,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Mwaitx,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Neg,
                    0x0000, 0x08d5, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Nop,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Not,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Or,
                    0x0000, 0x00c4, 0x0010,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Orpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Orps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Out,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Outsb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Outsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Outsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pabsb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pabsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pabsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Packssdw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Packsswb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Packusdw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Packuswb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Paddb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Paddd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Paddq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Paddsb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Paddsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Paddusb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Paddusw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Paddw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Palignr,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pand,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pandn,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pause,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pavgb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pavgusb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pavgw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pblendvb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pblendw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pclmulqdq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pcmpeqb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pcmpeqd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pcmpeqq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pcmpeqw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pcmpestri,
                    0x0000, 0x08c1, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pcmpestrm,
                    0x0000, 0x08c1, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pcmpgtb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pcmpgtd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pcmpgtq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pcmpgtw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pcmpistri,
                    0x0000, 0x08c1, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pcmpistrm,
                    0x0000, 0x08c1, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pconfig,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pdep,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pext,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pextrb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pextrd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pextrq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pextrw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pf2id,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pf2iw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pfacc,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pfadd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pfcmpeq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pfcmpge,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pfcmpgt,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pfcpit1,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pfmax,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pfmin,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pfmul,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pfnacc,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pfpnacc,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pfrcp,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pfrcpit2,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pfrsqit1,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pfsqrt,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pfsub,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pfsubr,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Phaddd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Phaddsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Phaddw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Phminposuw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Phsubd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Phsubsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Phsubw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pi2fd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pi2fw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pinsrb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pinsrd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pinsrq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pinsrw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmaddubsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmaddwd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmaxsb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmaxsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmaxsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmaxub,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmaxud,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmaxuw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pminsb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pminsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pminsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pminub,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pminud,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pminuw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmovmskb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmovsxbd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmovsxbq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmovsxbw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmovsxdq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmovsxwd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmovsxwq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmovzxbd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmovzxbq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmovzxbw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmovzxdq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmovzxwd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmovzxwq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmuldq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmulhrsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmulhrw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmulhuw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmulhw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmulld,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmullw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pmuludq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pop,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Popa,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Popad,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Popcnt,
                    0x0000, 0x0040, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Popf,
                    0x0000, 0x0fd5, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Popfd,
                    0x0000, 0x0fd5, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Popfq,
                    0x0000, 0x0fd5, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Por,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Prefetch,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Prefetchnta,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Prefetcht0,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Prefetcht1,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Prefetcht2,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Prefetchw,
                    0x0000, 0x0000, 0x08d5,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Prefetchwt1,
                    0x0000, 0x0000, 0x08d5,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Psadbw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pshufb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pshufd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pshufhw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pshuflw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pshufw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Psignb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Psignd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Psignw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pslld,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pslldq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Psllq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Psllw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Psrad,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Psraw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Psrld,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Psrldq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Psrlq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Psrlw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Psubb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Psubd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Psubq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Psubsb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Psubsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Psubusb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Psubusw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Psubw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pswapd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Ptest,
                    0x0000, 0x0041, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Ptwrite,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Punpckhbw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Punpckhdq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Punpckhqdq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Punpckhwd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Punpcklbw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Punpckldq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Punpcklqdq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Punpcklwd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Push,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pusha,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pushad,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pushf,
                    0x0fd5, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pushfd,
                    0x0fd5, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pushfq,
                    0x0fd5, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Pxor,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rcl,
                    0x0801, 0x0801, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rcpps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rcpss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rcr,
                    0x0801, 0x0801, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rdfsbase,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rdgsbase,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rdmsr,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rdpid,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rdpkru,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rdpmc,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rdpru,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rdrand,
                    0x0000, 0x0001, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rdseed,
                    0x0000, 0x0001, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rdsspd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rdsspq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rdtsc,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rdtscp,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Ret,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rol,
                    0x0000, 0x0801, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Ror,
                    0x0000, 0x0801, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rorx,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Roundpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Roundps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Roundsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Roundss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rsm,
                    0x0000, 0x0000, 0x08d5,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rsqrtps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rsqrtss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Rstorssp,
                    0x0000, 0x0001, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sahf,
                    0x0000, 0x00d5, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Salc,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sar,
                    0x0000, 0x08d5, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sarx,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Saveprevssp,
                    0x0000, 0x0001, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sbb,
                    0x0001, 0x08d5, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::ReadWrite, OperandAccess::Read, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Explicit, OperandVisibility::Explicit, OperandVisibility::Hidden, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, gcnew Operand::OpReg(Register::EFlags), Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Scasb,
                    0x0400, 0x08d5, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Scasd,
                    0x0400, 0x08d5, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Scasq,
                    0x0400, 0x08d5, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Scasw,
                    0x0400, 0x08d5, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Setb,
                    0x0001, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Setbe,
                    0x0041, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Setl,
                    0x0880, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Setle,
                    0x08c0, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Setnb,
                    0x0001, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Setnbe,
                    0x0041, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Setnl,
                    0x0880, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Setnle,
                    0x08c0, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Setno,
                    0x0800, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Setnp,
                    0x0004, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Setns,
                    0x0080, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Setnz,
                    0x0040, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Seto,
                    0x0800, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Setp,
                    0x0004, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sets,
                    0x0080, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Setssbsy,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Setz,
                    0x0040, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sfence,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sgdt,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sha1msg1,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sha1msg2,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sha1nexte,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sha1rnds4,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sha256msg1,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sha256msg2,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sha256rnds2,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Shl,
                    0x0000, 0x08d5, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::ReadWrite, OperandAccess::Read, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Explicit, OperandVisibility::Explicit, OperandVisibility::Hidden, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, gcnew Operand::OpReg(Register::EFlags), Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Shld,
                    0x0000, 0x08c5, 0x0010,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Shlx,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Shr,
                    0x0000, 0x08d5, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::ReadWrite, OperandAccess::Read, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Explicit, OperandVisibility::Explicit, OperandVisibility::Hidden, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, gcnew Operand::OpReg(Register::EFlags), Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Shrd,
                    0x0000, 0x08c5, 0x0010,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Shrx,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Shufpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Shufps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sidt,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Skinit,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sldt,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Slwpcb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Smsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Spflt,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sqrtpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sqrtps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sqrtsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sqrtss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Stac,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Stc,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Std,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Stgi,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sti,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Stmxcsr,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Stosb,
                    0x0400, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::Write, OperandAccess::Read, OperandAccess::ReadWrite, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Hidden, OperandVisibility::Hidden, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operands::WordPtr(Register::Hdi), Operands::Al, Operands::Reg(Register::Hdi), Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Stosd,
                    0x0400, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::Write, OperandAccess::Read, OperandAccess::ReadWrite, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Hidden, OperandVisibility::Hidden, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operands::WordPtr(Register::Hdi), Operands::Ax, Operands::Reg(Register::Hdi), Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Stosq,
                    0x0400, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::Write, OperandAccess::Read, OperandAccess::ReadWrite, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Hidden, OperandVisibility::Hidden, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operands::WordPtr(Register::Hdi), Operands::Ax, Operands::Reg(Register::Hdi), Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Stosw,
                    0x0400, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::Write, OperandAccess::Read, OperandAccess::ReadWrite, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Hidden, OperandVisibility::Hidden, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operands::WordPtr(Register::Hdi), Operands::Ax, Operands::Reg(Register::Hdi), Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Str,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sub,
                    0x0000, 0x011F, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::ReadWrite, OperandAccess::Read, OperandAccess::Write, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Explicit, OperandVisibility::Explicit, OperandVisibility::Hidden, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operands::EFlags, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Subpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Subps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Subsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Subss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Swapgs,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Syscall,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sysenter,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sysexit,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Sysret,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::T1mskc,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Test,
                    0x0000, 0x00c4, 0x0010,
                    gcnew array<OperandAccess> { OperandAccess::Read, OperandAccess::Read, OperandAccess::Write, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Explicit, OperandVisibility::Explicit, OperandVisibility::Hidden, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operands::EFlags, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Tpause,
                    0x0000, 0x0001, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Tzcnt,
                    0x0000, 0x0041, 0x0894,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Tzcnti,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Tzmsk,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Ucomisd,
                    0x0000, 0x0045, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Ucomiss,
                    0x0000, 0x0045, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Ud0,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Ud1,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Ud2,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Umonitor,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Umwait,
                    0x0000, 0x0001, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Unpckhpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Unpckhps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Unpcklpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Unpcklps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::V4fmaddps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::V4fmaddss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::V4fnmaddps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::V4fnmaddss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vaddnpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vaddnps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vaddpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vaddps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vaddsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vaddsetsps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vaddss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vaddsubpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vaddsubps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vaesdec,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vaesdeclast,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vaesenc,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vaesenclast,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vaesimc,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vaeskeygenassist,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Valignd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Valignq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vandnpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vandnps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vandpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vandps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vblendmpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vblendmps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vblendpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vblendps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vblendvpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vblendvps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vbroadcastf128,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vbroadcastf32x2,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vbroadcastf32x4,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vbroadcastf32x8,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vbroadcastf64x2,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vbroadcastf64x4,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vbroadcasti128,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vbroadcasti32x2,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vbroadcasti32x4,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vbroadcasti32x8,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vbroadcasti64x2,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vbroadcasti64x4,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vbroadcastsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vbroadcastss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcmppd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcmpps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcmpsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcmpss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcomisd,
                    0x0000, 0x0045, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcomiss,
                    0x0000, 0x0045, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcompresspd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcompressps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtdq2pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtdq2ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtfxpntdq2ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtfxpntpd2dq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtfxpntpd2udq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtfxpntps2dq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtfxpntps2udq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtfxpntudq2ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtne2ps2bf16,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtneps2bf16,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtpd2dq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtpd2ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtpd2qq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtpd2udq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtpd2uqq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtph2ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtps2dq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtps2pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtps2ph,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtps2qq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtps2udq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtps2uqq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtqq2pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtqq2ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtsd2si,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtsd2ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtsd2usi,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtsi2sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtsi2ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtss2sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtss2si,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtss2usi,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvttpd2dq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvttpd2qq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvttpd2udq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvttpd2uqq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvttps2dq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvttps2qq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvttps2udq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvttps2uqq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvttsd2si,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvttsd2usi,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvttss2si,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvttss2usi,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtudq2pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtudq2ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtuqq2pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtuqq2ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtusi2sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vcvtusi2ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vdbpsadbw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vdivpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vdivps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vdivsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vdivss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vdpbf16ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vdppd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vdpps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Verr,
                    0x0000, 0x0040, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Verw,
                    0x0000, 0x0040, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vexp223ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vexp2pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vexp2ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vexpandpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vexpandps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vextractf128,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vextractf32x4,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vextractf32x8,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vextractf64x2,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vextractf64x4,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vextracti128,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vextracti32x4,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vextracti32x8,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vextracti64x2,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vextracti64x4,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vextractps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfixupimmpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfixupimmps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfixupimmsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfixupimmss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfixupnanpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfixupnanps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmadd132pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmadd132ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmadd132sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmadd132ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmadd213pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmadd213ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmadd213sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmadd213ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmadd231pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmadd231ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmadd231sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmadd231ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmadd233ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmaddpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmaddps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmaddsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmaddss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmaddsub132pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmaddsub132ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmaddsub213pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmaddsub213ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmaddsub231pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmaddsub231ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmaddsubpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmaddsubps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsub132pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsub132ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsub132sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsub132ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsub213pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsub213ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsub213sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsub213ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsub231pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsub231ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsub231sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsub231ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsubadd132pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsubadd132ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsubadd213pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsubadd213ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsubadd231pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsubadd231ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsubaddpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsubaddps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsubpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsubps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsubsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfmsubss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmadd132pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmadd132ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmadd132sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmadd132ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmadd213pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmadd213ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmadd213sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmadd213ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmadd231pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmadd231ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmadd231sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmadd231ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmaddpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmaddps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmaddsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmaddss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmsub132pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmsub132ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmsub132sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmsub132ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmsub213pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmsub213ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmsub213sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmsub213ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmsub231pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmsub231ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmsub231sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmsub231ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmsubpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmsubps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmsubsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfnmsubss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfpclasspd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfpclassps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfpclasssd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfpclassss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfrczpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfrczps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfrczsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vfrczss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgatherdpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgatherdps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgatherpf0dpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgatherpf0dps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgatherpf0hintdpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgatherpf0hintdps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgatherpf0qpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgatherpf0qps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgatherpf1dpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgatherpf1dps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgatherpf1qpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgatherpf1qps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgatherqpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgatherqps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgetexppd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgetexpps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgetexpsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgetexpss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgetmantpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgetmantps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgetmantsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgetmantss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgf2p8affineinvqb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgf2p8affineqb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgf2p8mulb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgmaxabsps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgmaxpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgmaxps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgminpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vgminps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vhaddpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vhaddps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vhsubpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vhsubps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vinsertf128,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vinsertf32x4,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vinsertf32x8,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vinsertf64x2,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vinsertf64x4,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vinserti128,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vinserti32x4,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vinserti32x8,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vinserti64x2,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vinserti64x4,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vinsertps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vlddqu,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vldmxcsr,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vloadunpackhd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vloadunpackhpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vloadunpackhps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vloadunpackhq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vloadunpackld,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vloadunpacklpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vloadunpacklps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vloadunpacklq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vlog2ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmaskmovdqu,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmaskmovpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmaskmovps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmaxpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmaxps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmaxsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmaxss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmcall,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmclear,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmfunc,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vminpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vminps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vminsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vminss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmlaunch,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmload,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmmcall,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovapd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovaps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovddup,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovdqa,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovdqa32,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovdqa64,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovdqu,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovdqu16,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovdqu32,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovdqu64,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovdqu8,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovhlps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovhpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovhps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovlhps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovlpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovlps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovmskpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovmskps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovnrapd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovnraps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovnrngoapd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovnrngoaps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovntdq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovntdqa,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovntpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovntps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovshdup,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovsldup,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovupd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmovups,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmpsadbw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmptrld,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmptrst,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmread,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmresume,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmrun,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmsave,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmulpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmulps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmulsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmulss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmwrite,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmxoff,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vmxon,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vorpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vorps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vp2intersectd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vp2intersectq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vp4dpwssd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vp4dpwssds,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpabsb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpabsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpabsq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpabsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpackssdw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpacksswb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpackstorehd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpackstorehpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpackstorehps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpackstorehq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpackstoreld,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpackstorelpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpackstorelps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpackstorelq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpackusdw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpackuswb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpadcd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpaddb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpaddd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpaddq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpaddsb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpaddsetcd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpaddsetsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpaddsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpaddusb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpaddusw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpaddw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpalignr,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpand,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpandd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpandn,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpandnd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpandnq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpandq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpavgb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpavgw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpblendd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpblendmb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpblendmd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpblendmq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpblendmw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpblendvb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpblendw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpbroadcastb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpbroadcastd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpbroadcastmb2q,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpbroadcastmw2d,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpbroadcastq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpbroadcastw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpclmulqdq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmov,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpeqb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpeqd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpeqq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpeqw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpestri,
                    0x0000, 0x08c1, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpestrm,
                    0x0000, 0x08c1, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpgtb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpgtd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpgtq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpgtw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpistri,
                    0x0000, 0x08c1, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpistrm,
                    0x0000, 0x08c1, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpltd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpub,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpud,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpuq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpuw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcmpw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcomb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcomd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcompressb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcompressd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcompressq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcompressw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcomq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcomub,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcomud,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcomuq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcomuw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpcomw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpconflictd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpconflictq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpdpbusd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpdpbusds,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpdpwssd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpdpwssds,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vperm2f128,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vperm2i128,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermf32x4,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermi2b,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermi2d,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermi2pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermi2ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermi2q,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermi2w,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermil2pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermil2ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermilpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermilps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermt2b,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermt2d,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermt2pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermt2ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermt2q,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermt2w,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpermw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpexpandb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpexpandd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpexpandq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpexpandw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpextrb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpextrd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpextrq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpextrw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpgatherdd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpgatherdq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpgatherqd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpgatherqq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphaddbd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphaddbq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphaddbw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphaddd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphadddq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphaddsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphaddubd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphaddubq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphaddubw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphaddudq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphadduwd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphadduwq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphaddw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphaddwd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphaddwq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphminposuw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphsubbw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphsubd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphsubdq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphsubsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphsubw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vphsubwd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpinsrb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpinsrd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpinsrq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpinsrw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vplzcntd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vplzcntq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmacsdd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmacsdqh,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmacsdql,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmacssdd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmacssdqh,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmacssdql,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmacsswd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmacssww,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmacswd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmacsww,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmadcsswd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmadcswd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmadd231d,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmadd233d,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmadd52huq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmadd52luq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmaddubsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmaddwd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmaskmovd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmaskmovq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmaxsb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmaxsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmaxsq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmaxsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmaxub,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmaxud,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmaxuq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmaxuw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpminsb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpminsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpminsq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpminsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpminub,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpminud,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpminuq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpminuw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovb2m,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovd2m,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovdb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovdw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovm2b,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovm2d,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovm2q,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovm2w,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovmskb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovq2m,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovqb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovqd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovqw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovsdb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovsdw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovsqb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovsqd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovsqw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovswb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovsxbd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovsxbq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovsxbw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovsxdq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovsxwd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovsxwq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovusdb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovusdw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovusqb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovusqd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovusqw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovuswb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovw2m,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovwb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovzxbd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovzxbq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovzxbw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovzxdq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovzxwd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmovzxwq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmuldq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmulhd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmulhrsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmulhud,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmulhuw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmulhw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmulld,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmullq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmullw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmultishiftqb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpmuludq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpopcntb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpopcntd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpopcntq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpopcntw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpor,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpord,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vporq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpperm,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vprefetch0,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vprefetch1,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vprefetch2,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vprefetche0,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vprefetche1,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vprefetche2,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vprefetchenta,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vprefetchnta,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vprold,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vprolq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vprolvd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vprolvq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vprord,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vprorq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vprorvd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vprorvq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vprotb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vprotd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vprotq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vprotw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsadbw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsbbd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsbbrd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpscatterdd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpscatterdq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpscatterqd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpscatterqq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshab,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshad,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshaq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshaw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshlb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshld,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshldd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshldq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshldvd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshldvq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshldvw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshldw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshlq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshlw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshrdd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshrdq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshrdvd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshrdvq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshrdvw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshrdw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshufb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshufbitqmb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshufd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshufhw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpshuflw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsignb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsignd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsignw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpslld,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpslldq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsllq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsllvd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsllvq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsllvw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsllw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsrad,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsraq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsravd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsravq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsravw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsraw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsrld,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsrldq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsrlq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsrlvd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsrlvq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsrlvw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsrlw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsubb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsubd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsubq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsubrd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsubrsetbd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsubsb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsubsetbd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsubsw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsubusb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsubusw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpsubw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpternlogd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpternlogq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vptest,
                    0x0000, 0x0041, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vptestmb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vptestmd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vptestmq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vptestmw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vptestnmb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vptestnmd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vptestnmq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vptestnmw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpunpckhbw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpunpckhdq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpunpckhqdq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpunpckhwd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpunpcklbw,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpunpckldq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpunpcklqdq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpunpcklwd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpxor,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpxord,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vpxorq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrangepd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrangeps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrangesd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrangess,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrcp14pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrcp14ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrcp14sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrcp14ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrcp23ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrcp28pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrcp28ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrcp28sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrcp28ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrcpps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrcpss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vreducepd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vreduceps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vreducesd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vreducess,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrndfxpntpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrndfxpntps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrndscalepd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrndscaleps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrndscalesd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrndscaless,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vroundpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vroundps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vroundsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vroundss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrsqrt14pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrsqrt14ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrsqrt14sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrsqrt14ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrsqrt23ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrsqrt28pd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrsqrt28ps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrsqrt28sd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrsqrt28ss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrsqrtps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vrsqrtss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vscalefpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vscalefps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vscalefsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vscalefss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vscaleps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vscatterdpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vscatterdps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vscatterpf0dpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vscatterpf0dps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vscatterpf0hintdpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vscatterpf0hintdps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vscatterpf0qpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vscatterpf0qps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vscatterpf1dpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vscatterpf1dps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vscatterpf1qpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vscatterpf1qps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vscatterqpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vscatterqps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vshuff32x4,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vshuff64x2,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vshufi32x4,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vshufi64x2,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vshufpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vshufps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vsqrtpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vsqrtps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vsqrtsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vsqrtss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vstmxcsr,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vsubpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vsubps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vsubrpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vsubrps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vsubsd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vsubss,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vtestpd,
                    0x0000, 0x0041, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vtestps,
                    0x0000, 0x0041, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vucomisd,
                    0x0000, 0x0045, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vucomiss,
                    0x0000, 0x0045, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vunpckhpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vunpckhps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vunpcklpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vunpcklps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vxorpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vxorps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vzeroall,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Vzeroupper,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Wbinvd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Wrfsbase,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Wrgsbase,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Wrmsr,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Wrpkru,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Wrssd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Wrssq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Wrussd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Wrussq,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xabort,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xadd,
                    0x0000, 0x08d5, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xbegin,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xchg,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xcrypt_cbc,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xcrypt_cfb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xcrypt_ctr,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xcrypt_ecb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xcrypt_ofb,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xend,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xgetbv,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xlat,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xor,
                    0x0000, 0x011B, 0x0004,
                    gcnew array<OperandAccess> { OperandAccess::ReadWrite, OperandAccess::Read, OperandAccess::Write, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Explicit, OperandVisibility::Explicit, OperandVisibility::Hidden, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operands::EFlags, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xorpd,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xorps,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xrstor,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xrstor64,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xrstors,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xrstors64,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xsave,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xsave64,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xsavec,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xsavec64,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xsaveopt,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xsaveopt64,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xsaves,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xsaves64,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xsetbv,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xsha1,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xsha256,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xstore,
                    0x0000, 0x0000, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),
                gcnew InstructionMeta(
                    Mnemonic::Xtest,
                    0x0000, 0x0040, 0x0000,
                    gcnew array<OperandAccess> { OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None, OperandAccess::None },
                    gcnew array<OperandVisibility> { OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid, OperandVisibility::Invalid },
                    gcnew array<IOperand^> { Operand::None, Operand::None, Operand::None, Operand::None, Operand::None }
            ),

        };

    public:

        static InstructionMeta^ get(Mnemonic mnemonic)
        {
            auto idx = static_cast<int>(mnemonic);
            if (idx >= InstrMetaTable->Length)
                return nullptr;

            auto entry = InstrMetaTable[idx];
            return entry;
        }

        static inline bool isControlFlow(Mnemonic mnemonic)
        {
            switch (mnemonic)
            {
            case Mnemonic::Call:
            case Mnemonic::Ret:
            case Mnemonic::Iret:
            case Mnemonic::Iretd:
            case Mnemonic::Iretq:
            case Mnemonic::Jmp:
            case Mnemonic::Jb:
            case Mnemonic::Jbe:
            case Mnemonic::Jcxz:
            case Mnemonic::Jecxz:
            case Mnemonic::Jknzd:
            case Mnemonic::Jkzd:
            case Mnemonic::Jl:
            case Mnemonic::Jle:
            case Mnemonic::Jnb:
            case Mnemonic::Jnbe:
            case Mnemonic::Jnl:
            case Mnemonic::Jnle:
            case Mnemonic::Jno:
            case Mnemonic::Jnp:
            case Mnemonic::Jns:
            case Mnemonic::Jnz:
            case Mnemonic::Jo:
            case Mnemonic::Jp:
            case Mnemonic::Jrcxz:
            case Mnemonic::Js:
            case Mnemonic::Jz:
                return true;
            }
            return false;
        }

        static inline bool isCondControlFlow(Mnemonic mnemonic)
        {
            switch (mnemonic)
            {
            case Mnemonic::Jb:
            case Mnemonic::Jbe:
            case Mnemonic::Jcxz:
            case Mnemonic::Jecxz:
            case Mnemonic::Jknzd:
            case Mnemonic::Jkzd:
            case Mnemonic::Jl:
            case Mnemonic::Jle:
            case Mnemonic::Jnb:
            case Mnemonic::Jnbe:
            case Mnemonic::Jnl:
            case Mnemonic::Jnle:
            case Mnemonic::Jno:
            case Mnemonic::Jnp:
            case Mnemonic::Jns:
            case Mnemonic::Jnz:
            case Mnemonic::Jo:
            case Mnemonic::Jp:
            case Mnemonic::Jrcxz:
            case Mnemonic::Js:
            case Mnemonic::Jz:
                return true;
            }
            return false;
        }

        static inline bool IsCall(Mnemonic mnemonic)
        {
            switch (mnemonic)
            {
            case Mnemonic::Call:
                return true;
            }
            return false;
        }

        static inline bool isRet(Mnemonic mnemonic)
        {
            switch (mnemonic)
            {
            case Mnemonic::Ret:
            case Mnemonic::Iret:
            case Mnemonic::Iretd:
            case Mnemonic::Iretq:
                return true;
            }
            return false;
        }
    };

}