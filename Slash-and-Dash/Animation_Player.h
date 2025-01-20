#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

class Animation_Player {
private:
    float frame_duration;
    sf::Sprite* sp;
    std::vector<sf::Texture*> animation_textures;
    int current_frame;
    bool is_playing;
    bool loop;
    sf::Clock clock;

public:
    Animation_Player(sf::Sprite* sp, std::vector<sf::Texture*> tx, float frame_duration)
        : sp(sp), animation_textures(tx), frame_duration(frame_duration), current_frame(0), is_playing(false), loop(false) {
    }

    void update();
    void play(bool should_loop);
    void stop();
    void pause();
    bool isPlaying();
    void setFrameDuration(float duration);
};
