#include <iostream>
#include <fstream>

#include "disassembler.hh"

int main(int argc, char *argv[])
{
  if (argc > 2)
  {
    std::cerr << "Usage: " << argv[0] << " [<input>]" << std::endl;
    return 1;
  }

  std::ifstream input;
  if (argc == 2)
  {
    input.open(argv[1]);

    if (!input)
    {
      std::cerr << "Cannot open file: '" << argv[1] << "'" << std::endl;
      return 1;
    }
  }

  disassemble(argc == 2 ? input : std::cin, std::cout);
  return 0;
}
