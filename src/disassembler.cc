#include <iostream>
#include <iomanip>

#include "disassembler.hh"
#include "opcodes.hh"

void disassemble(std::shared_ptr<tolk::TolkFile>& file, std::ostream& os)
{
  std::map<unsigned, unsigned> functions;
  for (const std::pair<unsigned, tolk::Function>& entry : file->get_functable().get_table())
    functions[entry.second.offset] = entry.first;

  for (unsigned i = 0; i < file->get_bytecode().size(); ++i)
  {
    try
    {
      auto iter = functions.find(i);
      if (iter != functions.end())
        os << "       \t[Function " << iter->second << "]" << std::endl;

      os << std::setfill('0') << std::setw(6) << i << "|\t";
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
