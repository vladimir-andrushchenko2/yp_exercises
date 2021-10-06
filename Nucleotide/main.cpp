#include <cassert>
#include <cstddef>
#include <cstdint>
#include <string>
#include <array>

using namespace std;
using namespace std::string_literals;

struct Nucleotide {
    char symbol;
    size_t position;
    int chromosome_num;
    int gene_num;
    bool is_marked;
    char service_info;
};

const std::array<char, 4> symbols = {
       'A',
       'T',
       'G',
       'C'
};

const std::array<bool, 2> marks = {
        true,
        false
};

struct CompactNucleotide {
    uint32_t position;
    char service_info;
    uint8_t chromosome_num:6;
    uint8_t symbol:2;
    uint16_t gene_num:15;
    uint8_t is_marked:1;
};


//inline bool operator==(const Nucleotide& lhs, const Nucleotide& rhs) {
//    return (lhs.Symbol == rhs.Symbol)
//           && (lhs.Position == rhs.Position)
//           && (lhs.ChromosomeNum == rhs.ChromosomeNum)
//           && (lhs.GeneNum == rhs.GeneNum)
//           && (lhs.IsMarked == rhs.IsMarked)
//           && (lhs.ServiceInfo == rhs.ServiceInfo);
//}

CompactNucleotide Compress(const Nucleotide& n) {
    CompactNucleotide result{};

    result.position = n.position;
    result.service_info = n.service_info;
    result.chromosome_num = n.chromosome_num;

    for (const auto& s : symbols) {
        if (s == n.symbol)
            break;
        ++result.symbol;
    }

    result.gene_num = n.gene_num;

    if (n.is_marked) {
        result.is_marked = 0;
    } else {
        result.is_marked = 1;
    }

    return result;
}


Nucleotide Decompress(const CompactNucleotide& cn) {
    Nucleotide result{};

    result.position = cn.position;
    result.service_info = cn.service_info;
    result.chromosome_num = cn.chromosome_num;
    result.symbol = symbols.at(cn.symbol);
    result.gene_num = cn.gene_num;
    result.is_marked = marks.at(cn.is_marked);

    return result;
}

static_assert(sizeof(CompactNucleotide) <= 8, "Your CompactNucleotide is not compact enough");
static_assert(alignof(CompactNucleotide) == 4, "Don't use '#pragma pack'!");
bool operator==(const Nucleotide& lhs, const Nucleotide& rhs) {
    return (lhs.symbol == rhs.symbol) && (lhs.position == rhs.position) && (lhs.chromosome_num == rhs.chromosome_num)
        && (lhs.gene_num == rhs.gene_num) && (lhs.is_marked == rhs.is_marked) && (lhs.service_info == rhs.service_info);
}
void TestSize() {
    assert(sizeof(CompactNucleotide) <= 8);
}
void TestCompressDecompress() {
    Nucleotide source;
    source.symbol = 'T';
    source.position = 1'000'000'000;
    source.chromosome_num = 48;
    source.gene_num = 1'000;
    source.is_marked = true;
    source.service_info = '!';

    CompactNucleotide compressedSource = Compress(source);
    Nucleotide decompressedSource = Decompress(compressedSource);

    assert(source == decompressedSource);
}

int main() {
    TestSize();
    TestCompressDecompress();
}
