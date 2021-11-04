#pragma once

#include <zydis/Zydis.h>
#include <cstdint>

namespace Dotx64Dbg::Internal {

    Instruction^ decodeInstruction(const ZydisDecoder* decoder, const uint8_t* buf, size_t len, uint64_t address);

}
