#include <unordered_map>
#include <stdexcept>

#include "opcodes.hh"
#include "commons/asm/bytecodes.hh"

typedef void (*opcode_handler_type)(std::istream&, std::ostream&);

static long long read_long(std::istream& is)
{
  char buff[8] = {0};

  if (!is.read(buff, 8))
    throw std::invalid_argument("Cannot read value, expected an 8 byte operand");

  long long value = 0;

  for (int i = 0; i < 8; ++i)
    value |= ((unsigned char)buff[i] << (8 * i));

  return value;
}

static short read_short(std::istream& is)
{
  char buff[2] = {0};

  if (!is.read(buff, 2))
    throw std::invalid_argument("Cannot read value, expected a 2 byte operand");

  short value = 0;

  for (int i = 0; i < 2; ++i)
    value |= ((unsigned char)buff[i] << (8 * i));

  return value;
}

static unsigned char read_byte(std::istream& is)
{
  char c;

  if (!is.read(&c, 1))
    throw std::invalid_argument("Cannot read value, expected a 1 byte operand");

  return c;
}

static void halt_disass(std::istream& is, std::ostream& os)
{
  os << "halt";
}

static void pop_disass(std::istream& is, std::ostream& os)
{
  os << "pop";
}

static void push_disass(std::istream& is, std::ostream& os)
{
  os << "push " << read_long(is);
}

static void pushr_disass(std::istream& is, std::ostream& os)
{
  os << "pushr " << read_short(is);
}

static void popr_disass(std::istream& is, std::ostream& os)
{
  os << "popr " << read_short(is);
}

static void add_disass(std::istream& is, std::ostream& os)
{
  os << "add";
}

static void sub_disass(std::istream& is, std::ostream& os)
{
  os << "sub";
}

static void mul_disass(std::istream& is, std::ostream& os)
{
  os << "mul";
}

static void div_disass(std::istream& is, std::ostream& os)
{
  os << "div";
}

static void mod_disass(std::istream& is, std::ostream& os)
{
  os << "mod";
}

static void and_disass(std::istream& is, std::ostream& os)
{
  os << "and";
}

static void or_disass(std::istream& is, std::ostream& os)
{
  os << "or";
}

static void xor_disass(std::istream& is, std::ostream& os)
{
  os << "xor";
}

static void not_disass(std::istream& is, std::ostream& os)
{
  os << "not";
}

static void shr_disass(std::istream& is, std::ostream& os)
{
  os << "shr " << (unsigned)read_byte(is);
}

static void shl_disass(std::istream& is, std::ostream& os)
{
  os << "shl " << (unsigned)read_byte(is);
}

static void cmp_disass(std::istream& is, std::ostream& os)
{
  os << "cmp";
}

static void call_disass(std::istream& is, std::ostream& os)
{
  os << "call " << read_short(is);
}

static void callr_disass(std::istream& is, std::ostream& os)
{
  os << "callr " << read_short(is);
}

static void ret_disass(std::istream& is, std::ostream& os)
{
  os << "ret";
}

static void jmp_disass(std::istream& is, std::ostream& os)
{
  os << "jmp " << read_short(is);
}

static void je_disass(std::istream& is, std::ostream& os)
{
  os << "je " << read_short(is);
}

static void jl_disass(std::istream& is, std::ostream& os)
{
  os << "jl " << read_short(is);
}

static void jg_disass(std::istream& is, std::ostream& os)
{
  os << "jg " << read_short(is);
}

static void jne_disass(std::istream& is, std::ostream& os)
{
  os << "jne " << read_short(is);
}

static void jle_disass(std::istream& is, std::ostream& os)
{
  os << "jle " << read_short(is);
}

static void jge_disass(std::istream& is, std::ostream& os)
{
  os << "jge " << read_short(is);
}

static void create_disass(std::istream& is, std::ostream& os)
{
  os << "create " << read_short(is);
}

static void delete_disass(std::istream& is, std::ostream& os)
{
  os << "delete";
}

static void setr_disass(std::istream& is, std::ostream& os)
{
  short reg = read_short(is);
  long long value = read_long(is);

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

void handle_opcode(unsigned char op, std::istream& is, std::ostream& os)
{
  auto handler = get_handlers().find(op);
  if (handler == get_handlers().end())
    throw std::invalid_argument("Bad opcode: " + std::to_string(op));

  handler->second(is, os);
}
