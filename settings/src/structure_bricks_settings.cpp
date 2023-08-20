#include <SFML/Graphics.hpp>
#include <cstdint>
#include <memory>
#include <cassert>
#include <fstream>

#include "structure_bricks_settings.hpp"

namespace ar {

StructureBricksSettings::StructureBricksSettings()
    : m_bricks_structure_1 {
        {1,1,1,1,1,1,1,1,1,1,1},
        {2,2,2,13,13,13,2,2,2,2,2},
        {6,6,6,6,6,10,12,6,6,6,6},
        {7,14,7,7,7,7,7,13,7,7,14},
        {4,4,4,4,4,4,14,4,4,4,4},
        {13,13,13,11,3,3,3,3,13,13,13}
    }
    , m_bricks_structure_2 {
        {7,0,0,0,0,0,0,0,0,0,0},
        {7,6,0,0,0,0,0,0,0,0,0},
        {7,6,3,0,0,0,0,0,0,0,0},
        {7,6,3,2,0,0,0,0,0,0,0},
        {7,14,3,2,4,0,0,0,0,0,0},
        {7,6,3,12,4,14,0,0,0,0,0},
        {7,6,13,2,4,3,7,0,0,0,0},
        {7,13,3,2,4,3,7,13,0,0,0},
        {13,6,3,2,4,3,13,9,3,0,0},
        {7,6,3,2,13,13,7,9,3,6,0},
        {1,1,1,1,1,1,1,1,1,1,0}
    }
    , m_bricks_structure_3 {
        {3,3,3,3,3,3,3,3,3,3,3},
        {0,0,0,0,0,0,0,0,0,0,0},
        {7,7,7,14,13,7,7,10,7,7,7},
        {0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,13,13,2,2,2,2,2,2},
        {0,0,0,0,0,0,0,0,0,0,0},
        {7,7,7,7,7,7,7,7,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,4,4,4,4,4,4,4,12},
        {0,0,0,0,0,0,0,0,0,0,0},
        {6,6,6,7,7,7,7,7,13,13,13},
        {0,0,0,0,0,0,0,0,0,0,0},
        {13,13,13,14,6,6,6,6,6,6,6},
        {0,0,0,0,0,0,0,0,0,0,0},
        {2,2,2,2,2,11,2,2,2,14,2}
    }
    , m_bricks_structure_4 {
        {7,6,5,4,3,0,4,2,3,4,5},
        {6,5,10,3,2,0,13,3,13,13,13},
        {5,4,3,2,1,0,3,4,5,6,7},
        {4,3,2,1,4,0,4,5,6,7,8},
        {3,2,1,4,5,0,5,6,7,14,9},
        {2,1,13,13,13,0,8,7,8,9,2},
        {1,4,5,6,7,0,7,8,9,2,1},
        {12,5,6,7,8,0,13,13,13,1,4},
        {5,6,7,8,9,0,9,2,1,4,5},
        {6,7,8,9,2,0,2,1,4,5,6},
        {7,11,13,13,13,0,1,4,14,6,7},
        {8,9,14,3,5,0,4,5,6,7,8},
        {9,2,3,5,6,0,5,11,7,8,9},
        {2,3,5,6,7,0,6,7,8,9,2}
    }
    , m_bricks_structure_5 {
        {0,0,0,0,2,9,8,0,0,0,0},
        {0,0,0,2,9,8,0,3,0,0,0},
        {0,0,0,9,1,0,10,4,0,0,0},
        {0,0,9,1,0,3,4,13,8,0,0},
        {0,0,1,0,3,4,13,8,1,0,0},
        {0,0,0,14,4,13,8,1,11,0,0},
        {0,0,3,4,13,8,1,4,2,0,0},
        {0,0,4,13,8,1,4,2,6,0,0},
        {0,0,13,8,9,4,14,6,12,0,0},
        {0,0,0,9,4,2,6,7,0,0,0},
        {0,0,0,4,2,6,7,10,0,0,0},
        {0,0,0,0,6,7,3,0,0,0,0}
    }
    , m_bricks_structure_6 {
        {0,0,0,13,0,0,0,13,0,0,0},
        {0,0,0,0,2,0,2,0,0,0,0},
        {0,0,0,0,2,0,2,0,0,0,0},
        {0,0,0,13,13,13,13,13,0,0,0},
        {0,0,0,13,13,13,13,13,0,0,0},
        {0,0,13,13,1,13,1,13,13,0,0},
        {0,0,13,13,1,13,1,13,13,0,0},
        {0,13,13,13,13,13,13,13,13,13,0},
        {0,13,13,13,13,13,13,13,13,13,0},
        {0,13,0,13,13,14,13,13,0,13,0},
        {0,13,0,13,0,0,0,13,0,13,0},
        {0,13,0,13,0,0,0,13,0,13,0},
        {0,0,0,0,13,0,13,0,0,0,0},
        {0,0,0,0,13,0,13,0,0,0,0}
    }
{
    write_structure();
}

StructureBricksSettings& StructureBricksSettings::get_instance()
{
    static StructureBricksSettings instance;    
    return instance;  
}

void StructureBricksSettings::write_structure()
{
    std::ofstream outfile("level_structures/level-1.dat", std::ios::binary);
    if (!outfile) {
        assert(!"Wrong file");
    }
    uint8_t len_rows = 6;
    outfile.write(reinterpret_cast<const char*>(&len_rows), sizeof(len_rows));
    uint8_t len_col = 11;
    outfile.write(reinterpret_cast<const char*>(&len_col), sizeof(len_col));

    outfile.write(reinterpret_cast<const char*>(m_bricks_structure_1), sizeof(m_bricks_structure_1));
        
    std::ofstream outfile2("level_structures/level-2.dat", std::ios::binary);
    if (!outfile2) {
        assert(!"Wrong file");
    }
    uint8_t len_rows_2 = 11;
    outfile2.write(reinterpret_cast<const char*>(&len_rows_2), sizeof(len_rows_2));
    uint8_t len_col_2 = 11;
    outfile2.write(reinterpret_cast<const char*>(&len_col_2), sizeof(len_col_2));

    outfile2.write(reinterpret_cast<const char*>(m_bricks_structure_2), sizeof(m_bricks_structure_2));
    outfile2.close();
        
    std::ofstream outfile3("level_structures/level-3.dat", std::ios::binary);
    if (!outfile3) {
        assert(!"Wrong file");
    }
    uint8_t len_rows_3 = 15;
    outfile3.write(reinterpret_cast<const char*>(&len_rows_3), sizeof(len_rows_3));
    uint8_t len_col_3 = 11;
    outfile3.write(reinterpret_cast<const char*>(&len_col_3), sizeof(len_col_3));

    outfile3.write(reinterpret_cast<const char*>(m_bricks_structure_3), sizeof(m_bricks_structure_3));
    outfile3.close();

    std::ofstream outfile4("level_structures/level-4.dat", std::ios::binary);
    if (!outfile4) {
        assert(!"Wrong file");
    }
    uint8_t len_rows_4 = 14;
    outfile4.write(reinterpret_cast<const char*>(&len_rows_4), sizeof(len_rows_4));
    uint8_t len_col_4 = 11;
    outfile4.write(reinterpret_cast<const char*>(&len_col_4), sizeof(len_col_4));

    outfile4.write(reinterpret_cast<const char*>(m_bricks_structure_4), sizeof(m_bricks_structure_4));
    outfile4.close();

    std::ofstream outfile5("level_structures/level-5.dat", std::ios::binary);
    if (!outfile5) {
        assert(!"Wrong file");
    }
    uint8_t len_rows_5 = 12;
    outfile5.write(reinterpret_cast<const char*>(&len_rows_5), sizeof(len_rows_5));
    uint8_t len_col_5 = 11;
    outfile5.write(reinterpret_cast<const char*>(&len_col_5), sizeof(len_col_5));

    outfile5.write(reinterpret_cast<const char*>(m_bricks_structure_5), sizeof(m_bricks_structure_5));
    outfile5.close();

    std::ofstream outfile6("level_structures/level-6.dat", std::ios::binary);
    if (!outfile6) {
        assert(!"Wrong file");
    }
    uint8_t len_rows_6 = 14;
    outfile6.write(reinterpret_cast<const char*>(&len_rows_6), sizeof(len_rows_6));
    uint8_t len_col_6 = 11;
    outfile6.write(reinterpret_cast<const char*>(&len_col_6), sizeof(len_col_6));

    outfile6.write(reinterpret_cast<const char*>(m_bricks_structure_6), sizeof(m_bricks_structure_6));
    outfile6.close();
}

} // namespace ar
