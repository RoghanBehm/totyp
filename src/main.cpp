#include <cassert>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#include "document.hpp"
#include "parser.hpp"
#include "emitter.hpp"

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cerr << "usage: noweb-typst <file> <code language>" << std::endl;
    return 1;
  }

  std::string filename = argv[1];
  std::string code_lang = argv[2];
  std::ifstream inputFile(filename);

  if (!inputFile.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return 1;
  }

  Document doc = parse_markup(inputFile);
  dump_document(doc);

  std::ofstream file("out.typ");
  
  // Rebuild .nw filename (hacky)
  std::size_t pos = filename.find_last_of('/');
  std::string nw_filename = (pos == std::string::npos) ? filename : filename.substr(pos + 1);
  if (nw_filename.size() >= 2) {
      nw_filename.replace(nw_filename.size() - 2, 2, "nw");
  }
 
  emit_typst(file, doc, code_lang, nw_filename);
  return 0;
}