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
    value |= (buff[i] << (8 * i));

  return value;
}

static short read_short(std::istream& is)
{
  char buff[2] = {0};

  if (!is.read(buff, 2))
    throw std::invalid_argument("Cannot read value, expected a 2 byte operand");

  short value = 0;

  for (int i = 0; i < 2; ++i)
    value |= (buff[i] << (8 * i));

  return value;
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
  os << "shr";
}

static void shl_disass(std::istream& is, std::ostream& os)
{
  os << "shl";
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
  };

  return handlers;
}

void handle_opcode(unsigned char op, std::istream& is, std::ostream& os)
{
  if (get_handlers().find(op) == get_handlers().end())
    throw std::invalid_argument("Bad opcode: " + std::to_string(op));

  get_handlers().at(op)(is, os);
}
