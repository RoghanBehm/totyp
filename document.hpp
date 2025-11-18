#pragma once
#include <string>
#include <vector>
#include <iostream>

struct Block {
    enum class Kind { Docs, Code };

    Kind kind;              
    std::string name;     // empty for docs
    std::string text;     
};

struct Document {
    std::vector<Block> blocks;
};

inline const char* kind_to_string(Block::Kind k) {
    return k == Block::Kind::Docs ? "Docs" : "Code";
}

inline void dump_document(const Document& doc, std::ostream& out = std::cout) {
    out << "Document with " << doc.blocks.size() << " blocks\n\n";

    for (std::size_t i = 0; i < doc.blocks.size(); ++i) {
        const Block& b = doc.blocks[i];
        out << "===== Block " << i << " =====\n";
        out << "Kind: " << kind_to_string(b.kind) << "\n";
        if (b.kind == Block::Kind::Code) {
            out << "Name: " << (b.name.empty() ? "<unnamed>" : b.name) << "\n";
        }
        out << "----- Text -----\n";
        out << b.text;
        if (!b.text.empty() && b.text.back() != '\n') {
            out << '\n';
        }
        out << "================\n\n";
    }
}