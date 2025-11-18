#include "parser.hpp"
#include <cassert>
#include <iostream>

Document parse_markup(std::istream &input) {
  Document doc;
  Block current;
  bool has_curr = false;
  std::string line;

  while (std::getline(input, line)) {
    if (line.rfind("@begin docs", 0) == 0) {
      // start docs
      assert(!has_curr);

      current = Block{};
      current.kind = Block::Kind::Docs;
      current.name.clear();
      current.text.clear();

      has_curr = true;

    } else if (line.rfind("@begin code", 0) == 0) {
      assert(!has_curr);

      current = Block{};
      current.kind = Block::Kind::Code;
      current.name.clear();
      current.text.clear();

      has_curr = true;

    } else if (line.rfind("@end ", 0) == 0) {
      // end block
      assert(has_curr);
      doc.blocks.push_back(std::move(current));
      has_curr = false;

    } else if (line.rfind("@text ", 0) == 0) {
      assert(has_curr);
      current.text += line.substr(6) + "\n";
    } else if (line == "@nl") {
      assert(has_curr);
      current.text += "\n";
    } else if (line.rfind("@defn ", 0) == 0) {
      // code chunk
      assert(current.name.empty());
      assert(has_curr);
      assert(current.kind == Block::Kind::Code);
      current.name = line.substr(6);
    } else if (line.rfind("@use ", 0) == 0) {
      // reference code chunk
    } else if (line == "@quote") {
      // start quoted code in doc chunk
    } else if (line == "@endquote") {
      // end quoted code
    } else if (line.rfind("@fatal", 0) == 0) {
      std::cerr << "noweb markup fatal: " << line << "\n";
    } else if (line.rfind("@literal ", 0) == 0) {
      // copy text to output
      current.text += line.substr(9) + "\n";
    }
  }
  if (has_curr) {
    doc.blocks.push_back(std::move(current));
    has_curr = false;
  }
  return doc;
}
