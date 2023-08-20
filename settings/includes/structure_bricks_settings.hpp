#ifndef STRUCTURE_TEXTURE_SETTINGS_H
#define STRUCTURE_TEXTURE_SETTINGS_H

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <memory>
#include <unordered_map>

#include "brick_types_enum.hpp"

namespace ar {

class StructureBricksSettings
{
public:
    StructureBricksSettings(StructureBricksSettings const&) = delete;
    StructureBricksSettings const& operator=(StructureBricksSettings const&) = delete;

    static StructureBricksSettings& get_instance();
  
private:
    StructureBricksSettings();
    
    void write_structure();

private:    
    uint8_t m_bricks_structure_1[6][11];
    uint8_t m_bricks_structure_2[11][11];
    uint8_t m_bricks_structure_3[15][11];
    uint8_t m_bricks_structure_4[14][11];
    uint8_t m_bricks_structure_5[12][11];
    uint8_t m_bricks_structure_6[14][11];
};

} // namespace ar

#endif