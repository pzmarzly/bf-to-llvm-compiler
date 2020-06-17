#pragma once

#include "Compiler.hpp"
#include "instructions/llvm/LLVMInstruction.hpp"
#include "variables/LLVMCountedVariable.hpp"
#include "variables/LLVMVariable.hpp"

#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace ins = instructions::llvm;

class LLVMCompiler : public Compiler {
  std::vector<std::unique_ptr<instructions::llvm::LLVMInstruction>>
      instructions;
  variables::LLVMVariable tape_ptr{"i8**", "tape_ptr"};

  template <typename InstructionType, typename... Args>
  void Emit(Args... args) {
    instructions.push_back(std::make_unique<InstructionType>(args...));
  }

public:
  void HandlePrint() override {
    auto dereferenced_tape =
        std::make_shared<variables::LLVMCountedVariable>("i8*");
    auto cell_value = std::make_shared<variables::LLVMCountedVariable>("i8");
    Emit<ins::LoadInstruction>(dereferenced_tape, tape_ptr);
    Emit<ins::LoadInstruction>(cell_value, dereferenced_tape);
    Emit<ins::CallPutchar>(cell_value);
  }

  virtual void HandleRead() = 0;
  virtual void HandleIncrement() = 0;
  virtual void HandleDecrement() = 0;
  virtual void HandleMoveLeft() = 0;
  virtual void HandleMoveRight() = 0;
  virtual void HandleLoopBegin() = 0;
  virtual void HandleLoopEnd() = 0;
};