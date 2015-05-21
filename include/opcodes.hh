#ifndef OPCODES_HH
# define OPCODES_HH

# include <fstream>
# include <vector>

void handle_opcode( const std::vector<char>& bytecode,
                    unsigned& index,
                    std::ostream& os);

#endif /* end of include guard: OPCODES_HH */
