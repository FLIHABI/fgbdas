#ifndef DISASSEMBLER_HH
# define DISASSEMBLER_HH

# include <fstream>
# include <commons/tolkfile/tolk-file.hh>

void disassemble(std::shared_ptr<tolk::TolkFile>& file, std::ostream& os);

#endif /* end of include guard: DISASSEMBLER_HH */
