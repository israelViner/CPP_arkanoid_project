#ifndef TOP_HIGE_SCORE_H
#define TOP_HIGE_SCORE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <utility>
#include <string>
#include <array>

namespace ar {

void write_top_scores(std::vector<std::pair<std::string, uint32_t>> const& scores_list);
std::vector<std::pair<std::string, uint32_t>> read_top_scores();
std::string list_top_scores(std::vector<std::pair<std::string, uint32_t>> const& scores_list);

void diaplay_top_scores(sf::RenderWindow& screen, uint32_t score);

std::vector<std::pair<std::string, uint32_t>> update_top_10(sf::RenderWindow& screen, std::vector<std::pair<std::string, uint32_t>>& scores_list, uint32_t score, sf::Sprite const& background);

} // namespace ar

#endif