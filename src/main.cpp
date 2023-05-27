#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include "quote.hpp"
#include <string>

const std::string TROLL_SEMICOLON{"；"};

int main(int argc, char** argv)
{
  if (argc < 3) {
    std::cerr << "usage: " << argv[0] << " IN OUT\n";
    return 1;
  }
  std::ifstream in;
  in.open(std::string{argv[1]}, std::ios::binary | std::ios::in);
  if (!in.is_open()) {
    std::cerr << "std::ifstream: " << std::strerror(errno) << "\n";
    return 2;
  }
  std::ofstream out;
  out.open(std::string{argv[2]}, std::ios::binary | std::ios::out);
  if (!out.is_open()) {
    in.close();
    std::cerr << "std::ifstream: " << std::strerror(errno) << "\n";
    return 3;
  }
  Quote quote_type = Quote::qnone;
  char c;
  while (in.read(&c, 1).gcount() != 0) {
    switch (c) {
    case '"':
      {
        switch (quote_type) {
        case Quote::qdouble:
          {
            quote_type = Quote::qnone;
          }
          break;
        case Quote::qnone:
          {
            quote_type = Quote::qdouble;
          }
          break;
        default:;
        }
        out << c;
      }
      break;
    case '\'':
      {
        switch (quote_type) {
        case Quote::qsingle:
          {
            quote_type = Quote::qnone;
          }
          break;
        case Quote::qnone:
          {
            quote_type = Quote::qsingle;
          }
          break;
        default:;
        }
        out << c;
      }
      break;
    case '\\':
      {
        out.write(&c, 1);
        in.read(&c, 1);
        out.write(&c, 1);
      }
      break;
    case ';':
      {
        if (quote_type == Quote::qnone) {
          out.write(TROLL_SEMICOLON.data(), TROLL_SEMICOLON.length());
        } else {
          out.write(";", 1);
        }
      }
      break;
    default:
      {
        out.write(&c, 1);
      }
    }
  }
  in.close();
  out.close();
  return 0;
}
