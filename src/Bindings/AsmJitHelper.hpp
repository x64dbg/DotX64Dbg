#pragma once

#include <string>
#include <optional>
#include <asmjit/asmjit.h>

namespace Dotx64Dbg
{
    inline std::optional<std::string> getAsmjitErrorString(asmjit::Error err)
    {
        auto code = static_cast<asmjit::ErrorCode>(err);
        switch (code)
        {
        case asmjit::ErrorCode::kErrorOk:
            return std::nullopt;
        case asmjit::ErrorCode::kErrorOutOfMemory:
            return "Out of Memory";
        case asmjit::ErrorCode::kErrorInvalidArgument:
            return "Invalid Argument";
        case asmjit::ErrorCode::kErrorInvalidState:
            return "Invalid State";
        case asmjit::ErrorCode::kErrorInvalidArch:
            return "Invalid Arch";
        case asmjit::ErrorCode::kErrorNotInitialized:
            return "Not Initialized";
        case asmjit::ErrorCode::kErrorAlreadyInitialized:
            return "Already Initialized";
        case asmjit::ErrorCode::kErrorFeatureNotEnabled:
            return "Feature not enabled";
        case asmjit::ErrorCode::kErrorTooManyHandles:
            return "Too many handles";
        case asmjit::ErrorCode::kErrorTooLarge:
            return "Too large";
        case asmjit::ErrorCode::kErrorNoCodeGenerated:
            return "No Code Generated";
        case asmjit::ErrorCode::kErrorInvalidDirective:
            return "Invalid Directive";
        case asmjit::ErrorCode::kErrorInvalidLabel:
            return "Invalid Label";
        case asmjit::ErrorCode::kErrorTooManyLabels:
            return "Too Many Labels";
        case asmjit::ErrorCode::kErrorLabelAlreadyBound:
            return "Label already bound";
        case asmjit::ErrorCode::kErrorLabelAlreadyDefined:
            return "Label already defined";
        case asmjit::ErrorCode::kErrorLabelNameTooLong:
            return "Label Name too long";
        case asmjit::ErrorCode::kErrorInvalidLabelName:
            return "Invalid Label name";
        case asmjit::ErrorCode::kErrorInvalidParentLabel:
            return "Invalid parent Label";
        case asmjit::ErrorCode::kErrorInvalidSection:
            return "Invalid Section";
        case asmjit::ErrorCode::kErrorTooManySections:
            return "Too Many Sections";
        case asmjit::ErrorCode::kErrorInvalidSectionName:
            return "Invalid Section Name";
        case asmjit::ErrorCode::kErrorTooManyRelocations:
            return "Too Many Relocations";
        case asmjit::ErrorCode::kErrorInvalidRelocEntry:
            return "Invalid Relocation Entry";
        case asmjit::ErrorCode::kErrorRelocOffsetOutOfRange:
            return "Relocatopm Offset Out Of Range";
        case asmjit::ErrorCode::kErrorInvalidAssignment:
            return "Invalid assignment";
        case asmjit::ErrorCode::kErrorInvalidInstruction:
            return "Invalid Instruction";
        case asmjit::ErrorCode::kErrorInvalidRegType:
            return "Invalid Reg Type";
        case asmjit::ErrorCode::kErrorInvalidRegGroup:
            return "Invalid Reg Group";
        case asmjit::ErrorCode::kErrorInvalidPhysId:
            return "Invalid Phys Id";
        case asmjit::ErrorCode::kErrorInvalidVirtId:
            return "Invalid Virt Id";
        case asmjit::ErrorCode::kErrorInvalidElementIndex:
            return "Invalid Element Index";
        case asmjit::ErrorCode::kErrorInvalidPrefixCombination:
            return "Invalid Prefix Combination";
        case asmjit::ErrorCode::kErrorInvalidLockPrefix:
            return "Invalid Lock Prefix";
        case asmjit::ErrorCode::kErrorInvalidXAcquirePrefix:
            return "Invalid XAcquire Prefix";
        case asmjit::ErrorCode::kErrorInvalidXReleasePrefix:
            return "Invalid XRelease Prefix";
        case asmjit::ErrorCode::kErrorInvalidRepPrefix:
            return "Invalid Rep Prefix";
        case asmjit::ErrorCode::kErrorInvalidRexPrefix:
            return "Invalid Rex Prefix";
        case asmjit::ErrorCode::kErrorInvalidExtraReg:
            return "Invalid Extra Reg";
        case asmjit::ErrorCode::kErrorInvalidKMaskUse:
            return "Invalid K Mask use";
        case asmjit::ErrorCode::kErrorInvalidKZeroUse:
            return "Invalid K Zero use";
        case asmjit::ErrorCode::kErrorInvalidBroadcast:
            return "Invalid Broadcast";
        case asmjit::ErrorCode::kErrorInvalidEROrSAE:
            return "Invalid ER or SAE";
        case asmjit::ErrorCode::kErrorInvalidAddress:
            return "Invalid Address";
        case asmjit::ErrorCode::kErrorInvalidAddressIndex:
            return "Invalid Address Index";
        case asmjit::ErrorCode::kErrorInvalidAddressScale:
            return "Invalid Address Scale";
        case asmjit::ErrorCode::kErrorInvalidAddress64Bit:
            return "InvalidAddress64Bit";
        case asmjit::ErrorCode::kErrorInvalidAddress64BitZeroExtension:
            return "Invalid Address 64 Bit Zero Extension";
        case asmjit::ErrorCode::kErrorInvalidDisplacement:
            return "Invalid Displacement";
        case asmjit::ErrorCode::kErrorInvalidSegment:
            return "Invalid Segment";
        case asmjit::ErrorCode::kErrorInvalidImmediate:
            return "Invalid Immediate";
        case asmjit::ErrorCode::kErrorInvalidOperandSize:
            return "Invalid Operand Size";
        case asmjit::ErrorCode::kErrorAmbiguousOperandSize:
            return "Ambiguous Operand Size";
        case asmjit::ErrorCode::kErrorOperandSizeMismatch:
            return "Operand Size mismatch";
        case asmjit::ErrorCode::kErrorInvalidOption:
            return "Invalid Option";
        case asmjit::ErrorCode::kErrorOptionAlreadyDefined:
            return "Option already defined";
        case asmjit::ErrorCode::kErrorInvalidTypeId:
            return "Invalid Type Id";
        case asmjit::ErrorCode::kErrorInvalidUseOfGpbHi:
            return "Invalid use Of GpbHi";
        case asmjit::ErrorCode::kErrorInvalidUseOfGpq:
            return "Invalid use Of Gpq";
        case asmjit::ErrorCode::kErrorInvalidUseOfF80:
            return "Invalid use Of F80";
        case asmjit::ErrorCode::kErrorNotConsecutiveRegs:
            return "Not Consecutive Regs";
        case asmjit::ErrorCode::kErrorIllegalVirtReg:
            return "Illegal Virt Reg";
        case asmjit::ErrorCode::kErrorTooManyVirtRegs:
            return "Too Many Virt Regs";
        case asmjit::ErrorCode::kErrorNoMorePhysRegs:
            return "No More Phys Regs";
        case asmjit::ErrorCode::kErrorOverlappedRegs:
            return "Overlapped Regs";
        case asmjit::ErrorCode::kErrorOverlappingStackRegWithRegArg:
            return "Overlapping Stack Reg With Reg Arg";
        case asmjit::ErrorCode::kErrorExpressionLabelNotBound:
            return "Expression Label Not Bound";
        case asmjit::ErrorCode::kErrorExpressionOverflow:
            return "Expression Overflow";
        case asmjit::ErrorCode::kErrorFailedToOpenAnonymousMemory:
            return "Failed to open anonymous Memory";
        }
        return std::nullopt;
    }
}
