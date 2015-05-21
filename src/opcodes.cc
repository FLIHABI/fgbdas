#include <unordered_map>
#include <stdexcept>

#include "opcodes.hh"
#include "commons/asm/bytecodes.hh"

typedef void (*opcode_handler_type)(const std::vector<char>&,
                                    unsigned&,
                                    std::ostream&);

static int64_t read_64bits_operand(const std::vector<char>& vect, unsigned& index)
{
  if (index + 8 >= vect.size())
    throw std::invalid_argument("Cannot read value, expected an 8 byte operand");

  int64_t value = 0;

  for (int i = 0; i < 8; ++i)
    value |= ((unsigned char)vect[index + i] << (8 * i));

  index += 8;

  return value;
}

static int16_t read_16bits_operand(const std::vector<char>& vect, unsigned& index)
{
  if (index + 2 >= vect.size())
    throw std::invalid_argument("Cannot read value, expected a 2 byte operand");

  int16_t value = 0;

  for (int i = 0; i < 2; ++i)
    value |= ((unsigned char)vect[index + i] << (8 * i));

  index += 2;

  return value;
}

static unsigned char read_8bits_operand(const std::vector<char>& vect, unsigned& index)
{
  if (index + 1 >= vect.size())
    throw std::invalid_argument("Cannot read value, expected a 1 byte operand");

  return vect[index++];
}

static void halt_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "halt";
}

static void pop_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "pop";
}

static void push_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "push " << read_64bits_operand(v, i);
}

static void pushr_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "pushr " << read_16bits_operand(v, i);
}

static void popr_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "popr " << read_16bits_operand(v, i);
}

static void add_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "add";
}

static void sub_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "sub";
}

static void mul_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "mul";
}

static void div_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "div";
}

static void mod_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "mod";
}

static void and_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "and";
}

static void or_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "or";
}

static void xor_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "xor";
}

static void not_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "not";
}

static void shr_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "shr " << (unsigned)read_8bits_operand(v, i);
}

static void shl_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "shl " << (unsigned)read_8bits_operand(v, i);
}

static void cmp_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "cmp";
}

static void call_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "call " << read_16bits_operand(v, i);
}

static void callr_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "callr " << read_16bits_operand(v, i);
}

static void ret_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "ret";
}

static void jmp_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "jmp " << read_16bits_operand(v, i);
}

static void je_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "je " << read_16bits_operand(v, i);
}

static void jl_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "jl " << read_16bits_operand(v, i);
}

static void jg_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "jg " << read_16bits_operand(v, i);
}

static void jne_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "jne " << read_16bits_operand(v, i);
}

static void jle_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "jle " << read_16bits_operand(v, i);
}

static void jge_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "jge " << read_16bits_operand(v, i);
}

static void create_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "create " << read_16bits_operand(v, i);
}

static void delete_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  os << "delete";
}

static void setr_disass(const std::vector<char>& v, unsigned& i, std::ostream& os)
{
  int16_t reg = read_16bits_operand(v, i);
  int64_t value = read_64bits_operand(v, i);

  os << "setr " << reg << " " << value;
}

static std::unordered_map<unsigned char, opcode_handler_type>& get_handlers()
{
  static std::unordered_map<unsigned char, opcode_handler_type> handlers =
  {
    {OP_HALT, halt_disass},
    {OP_POP, pop_disass},
    {OP_PUSH, push_disass},
    {OP_PUSHR, pushr_disass},
    {OP_POPR, popr_disass},
    {OP_ADD, add_disass},
    {OP_SUB, sub_disass},
    {OP_MUL, mul_disass},
    {OP_DIV, div_disass},
    {OP_MOD, mod_disass},
    {OP_AND, and_disass},
    {OP_OR, or_disass},
    {OP_XOR, xor_disass},
    {OP_NOT, not_disass},
    {OP_SHR, shr_disass},
    {OP_SHL, shl_disass},
    {OP_CMP, cmp_disass},
    {OP_CALL, call_disass},
    {OP_CALLR, callr_disass},
    {OP_RET, ret_disass},
    {OP_JMP, jmp_disass},
    {OP_JE, je_disass},
    {OP_JL, jl_disass},
    {OP_JG, jg_disass},
    {OP_JNE, jne_disass},
    {OP_JLE, jle_disass},
    {OP_JGE, jge_disass},
    {OP_CREATE, create_disass},
    {OP_DELETE, delete_disass},
    {OP_SETR, setr_disass}
  };

  return handlers;
}

void handle_opcode( const std::vector<char>& bytecode,
                    unsigned& index,
                    std::ostream& os)
{
  auto handler = get_handlers().find(bytecode[index]);
  if (handler == get_handlers().end())
    throw std::invalid_argument("Bad opcode: "
        + std::to_string(bytecode[index]));

  handler->second(bytecode, index, os);
}
