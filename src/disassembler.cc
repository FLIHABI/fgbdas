#include <iostream>

#include "disassembler.hh"
#include "opcodes.hh"

void disassemble(std::shared_ptr<tolk::TolkFile>& file, std::ostream& os)
{
  for (unsigned i = 0; i < file->get_bytecode().size(); ++i)
  {
    try
    {
      handle_opcode(file->get_bytecode(), i, os);
      os << std::endl;
    }
    catch(std::exception& e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
      std::exit(1);
    }
  }
}
