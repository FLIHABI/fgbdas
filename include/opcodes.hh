#ifndef OPCODES_HH
# define OPCODES_HH

# include <fstream>

void handle_opcode(unsigned char op, std::istream& is, std::ostream& os);

#endif /* end of include guard: OPCODES_HH */
