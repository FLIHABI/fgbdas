#include <commons/tolkfile/tolk-file.hh>
#include <iostream>

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
    std::shared_ptr<tolk::TolkFile> ptr = tolk::TolkFile::load(argv[1]);

    disassemble(ptr, std::cout);
  }

  return 0;
}
