#include <iostream>

#include "disassembler.hh"
#include "opcodes.hh"

void disassemble(std::istream& is, std::ostream& os)
{
  unsigned char op;

  while ((is >> op))
  {
    try
    {
      handle_opcode(op, is, os);
      os << std::endl;
    }
    catch(std::exception& e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
      std::exit(1);
    }
  }
}
