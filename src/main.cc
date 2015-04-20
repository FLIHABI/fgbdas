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

  if (argc == 2)
  {
    std::ifstream input(argv[1]);

    if (!input)
    {
      std::cerr << "Cannot open file: '" << argv[1] << "'" << std::endl;
      return 1;
    }

    disassemble(input, std::cout);

    input.close();
  }
  else
    disassemble(std::cin, std::cout);

  return 0;
}
