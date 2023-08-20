#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <utility>
#include <string>
#include <algorithm>
#include <cassert>

#include "top_high_score.hpp"
#include "evevt_tools.hpp"
#include "graphic_tools.hpp"
#include "audio.hpp"
#include "audio_icon.hpp"
#include "fonts_settings.hpp"
#include "texture_settings.hpp"

namespace ar
{

void write_top_scores(std::vector<std::pair<std::string, uint32_t>> const &scores_list)
{
    std::ofstream outfile("top10.dat", std::ios::binary);
    if (!outfile) {
        assert(!"Wrong outfile");
    }

    for (auto const &score : scores_list) {
        uint32_t len_name = static_cast<uint32_t>(score.first.size());
        outfile.write(reinterpret_cast<const char *>(&len_name), sizeof(len_name));
        outfile.write(score.first.data(), len_name);
        outfile.write(reinterpret_cast<const char *>(&score.second), sizeof(score.second));
    }

    outfile.close();
}

std::vector<std::pair<std::string, uint32_t>> read_top_scores()
{
    std::vector<std::pair<std::string, uint32_t>> read_data;

    std::ifstream infile("top10.dat", std::ios::binary);
    if (infile) {
        while (infile.good()) {
            uint32_t len_name;
            infile.read(reinterpret_cast<char *>(&len_name), sizeof(len_name));
            std::string name;
            name.resize(len_name);
            infile.read(&name[0], len_name);
            uint32_t score;
            infile.read(reinterpret_cast<char *>(&score), sizeof(score));
            read_data.emplace_back(std::move(name), score);
        }

        read_data.pop_back();
        infile.close();
    }

    return read_data;
}

std::string list_top_scores(std::vector<std::pair<std::string, uint32_t>> const &scores_list)
{
    std::string default_name = "-------------\t0\n\n";

    auto it = scores_list.begin();
    auto end_it = scores_list.end();

    std::string str;
    int counter = 1;
    while (it != end_it && counter < 11) {
        str += std::to_string(counter) + ". " + it->first + ":\t" + std::to_string(it->second) + "\n\n";
        ++it;
        ++counter;
    }

    while (counter <= 10) {
        str += std::to_string(counter) + ". " + default_name;
        ++counter;
    }

    return str;
}

std::vector<std::pair<std::string, uint32_t>> update_top_10(sf::RenderWindow &screen, std::vector<std::pair<std::string, uint32_t>> &scores_list, uint32_t score, sf::Sprite const &background)
{
    if (scores_list.empty() || scores_list.size() < 9 || score > scores_list[9].second) {
        FontsSettings &fonts_settings = FontsSettings::get_instance();
        std::shared_ptr<sf::Font> font = fonts_settings.get_font_1();
        sf::Text text("Enter your name: ", *font, 40);
        center_text(text, sf::Vector2u(screen.getSize().x / 2, screen.getSize().y / 2));

        sf::String player_input_display;
        sf::Text text1(player_input_display, *font, 40);
        center_text(text1, sf::Vector2u((screen.getSize().x / 2) - 80, (screen.getSize().y / 2) + 50));

        std::string playerInput;

        while (true) {
            text1.setString(player_input_display);
            screen.clear();
            screen.draw(background);
            screen.draw(text);
            screen.draw(text1);
            screen.display();

            sf::Event event;
            while (screen.pollEvent(event)) {
                if (event.type == sf::Event::TextEntered) {
                    playerInput += event.text.unicode;
                    player_input_display += event.text.unicode;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                    player_input_display.clear();
                    while (!playerInput.empty()) {
                        playerInput.pop_back();
                    }
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                break;
            }
        }

        std::pair<std::string, uint32_t> new_score = std::make_pair(playerInput, score);
        scores_list.push_back(new_score);
        std::sort(scores_list.begin(), scores_list.end(), [](std::pair<std::string, uint32_t> a, std::pair<std::string, uint32_t> b)
                    { return a.second > b.second; });
        if (scores_list.size() > 10) {
            scores_list.pop_back();
        }

        write_top_scores(scores_list);
    }

    return scores_list;
}

void diaplay_top_scores(sf::RenderWindow &screen, uint32_t score)
{
    Audio &audio = Audio::get_instance();
    audio.play_background(8);
    AudioIcon &audio_icon = AudioIcon::get_instance();

    std::shared_ptr<TextureSettings> settings = TextureSettings::get_instance();
    std::shared_ptr<sf::Sprite> background = settings->get_sprite_background(screen, 4);

    std::vector<std::pair<std::string, uint32_t>> top_scores_vec = read_top_scores();
    top_scores_vec = update_top_10(screen, top_scores_vec, score, *background);
    std::string list_top = list_top_scores(top_scores_vec);

    FontsSettings &fonts_settings = FontsSettings::get_instance();
    std::shared_ptr<sf::Font> font = fonts_settings.get_font_2();
    sf::Text text("top 10 high score: ", *font, 60);
    center_text(text, sf::Vector2u(screen.getSize().x / 2, screen.getSize().y * 2 / 10));
    sf::Text text1(list_top, *font, 25);
    center_text(text1, sf::Vector2u(screen.getSize().x / 2, screen.getSize().y * 6 / 10));
    sf::Clock clock;

    while (true)
    {
        if (audio.is_mute(clock)) {
            audio_icon.set_icon_texture();
        }
        if (is_game_close(screen) || (is_any_key_pressed() && clock.getElapsedTime().asSeconds() > 0.2)) {
            break;
        }

        screen.draw(*background);
        screen.draw(text);
        screen.draw(text1);
        screen.draw(audio_icon.draw());
        screen.display();
        screen.clear();
    }
}

} // namespace ar