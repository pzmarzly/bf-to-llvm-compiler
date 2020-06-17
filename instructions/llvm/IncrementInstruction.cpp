#include "DecrementInstruction.hpp"

#include <sstream>

using namespace variables;

namespace instructions::llvm {

std::string DecrementInstruction::Execute() {
  std::stringstream ss;
  ss << destination->GetName();
  ss << " = sub ";
  ss << LLVMVariable::TypeToString(destination->GetType());
  ss << " ";
  ss << source->GetName();
  ss << ", 1\n";
  return ss.str();
}

} // namespace instructions::llvm