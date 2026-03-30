/**
 * @file palettedata.h
 * @brief Contains palette definitions and helper functions for color palettes.
 *
 * This file defines the available color palette types and provides functions
 * for retrieving palette names and their associated RGBA color values.
 * These palettes are used by the ColorPalette widget to display selectable colors.
 *
 * Team: Green Goombas
 * @authors Charles Adair, Armando Carrillo, Parker Hollingsed, Brady Nelson, Lindsey Reese, Kent Wilkison
 * @date 3-29-2026
 */

#ifndef PALETTEDATA_H
#define PALETTEDATA_H

#include <string>
#include <vector>

/**
 * @brief Enum representing the available color palettes.
 *
 * Each palette corresponds to a predefined set of RGBA colors.
 */
enum class PaletteType
{
    Default,
    ArtDecoGold,
    RetroPastel,
    SixtiesPop,
    SeventiesEarth,
    EightiesNeon,
};

/**
 * @brief Returns all available palette types.
 *
 * This is useful for loading the palette dropdown menu.
 *
 * @return A vector containing all palette types.
 */
std::vector<PaletteType> getAllPaletteTypes();

/**
 * @brief Returns the display name for a given palette type.
 *
 * This is used for showing readable names in the UI dropdown.
 *
 * @param type The palette type.
 * @return The name of the palette.
 */
std::string getPaletteName(PaletteType type);

/**
 * @brief Returns the RGBA color set for a given palette type.
 *
 * Each color is represented as a vector of four integers:
 * {red, green, blue, alpha}
 *
 * @param type The palette type.
 * @return A vector of RGBA colors.
 */
std::vector<std::vector<int>> getPaletteColors(PaletteType type);

/**
 * @brief Returns the display names for the colors in a given palette.
 *
 * These names can be used as button tooltips when the user hovers
 * over a preset color.
 *
 * @param type The palette type.
 * @return A vector of color names in the same order as the palette colors.
 */
std::vector<std::string> getPaletteColorNames(PaletteType type);

#endif // PALETTEDATA_H
