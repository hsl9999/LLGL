/*
 * AMD64Assembler.h
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2018 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef LLGL_AMD64_ASSEMBLER_H
#define LLGL_AMD64_ASSEMBLER_H


#include "AMD64Register.h"
#include "../../JITCompiler.h"
#include <vector>
#include <cstdint>


namespace LLGL
{

namespace JIT
{


// AMD64 (a.k.a. x86_64) assembly code generator.
class AMD64Assembler final : public JITCompiler
{

    public:
    
        void Begin() override;
        void End() override;

    private:

        bool IsLittleEndian() const override;
        void WriteFuncCall(const void* addr, const JITCallConv conv, bool farCall) override;

    private:

        void WriteREXOpt(const Reg reg, bool defaultsTo64Bit = false);
    
        void PushReg(const Reg srcReg);
        void PushImm8(std::uint8_t byte);
        void PushImm16(std::uint16_t word);
        void PushImm32(std::uint32_t dword);

        void PopReg(const Reg dstReg);

        void MovReg(const Reg dstReg, const Reg srcReg);
        void MovRegImm32(const Reg dstReg, std::uint32_t dword);
        void MovRegImm64(const Reg dstReg, std::uint64_t qword);
        void MovMemImm32(const Reg dstMemReg, std::uint32_t dword, std::uint32_t offset);
        void MovMemReg(const Reg dstMemReg, const Reg srcReg, std::uint32_t offset);

        void AddImm32(const Reg dst, std::uint32_t dword);
        void SubImm32(const Reg dst, std::uint32_t dword);
        void DivReg(const Reg src);

        void CallNear(const Reg reg);

        void RetNear(std::uint16_t word = 0);
        void RetFar(std::uint16_t word = 0);
    
        #if 1//TESTING
        void _ForceExcep();
        #endif
    
    private:
    
        std::uint32_t localStack_ = 0;
    
};


} // /namespace JIT

} // /namespace LLGL


#endif



// ================================================================================
