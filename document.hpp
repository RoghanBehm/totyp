#include <string>
#include <vector>

struct Block {
    enum class Kind { Docs, Code };

    Kind kind;              
    std::string name;     // empty for docs
    std::string text;     
};

struct Document {
    std::vector<Block> blocks;
};
