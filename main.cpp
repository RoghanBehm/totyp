#include "document.hpp"
#include "parser.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "usage: noweb-typst <file>\n";
  }

  std::string filename = argv[1];
  std::ifstream inputFile(filename);

  if (!inputFile.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return 1;
  }

  Document doc = parse_markup(inputFile);
  dump_document(doc);
  return 0;
}