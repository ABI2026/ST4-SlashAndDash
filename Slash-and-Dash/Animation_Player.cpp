#include "Animation_Player.h"

void Animation_Player::update() {
    if (!is_playing || animation_textures.empty()) { return; }

    if (clock.getElapsedTime().asSeconds() > frame_duration) {
        current_frame = (current_frame + 1) % animation_textures.size();
        sp->setTexture(*animation_textures[current_frame]);
        clock.restart();

        if (!loop && current_frame == animation_textures.size() - 1) {
            stop();
        }
    }
}

void Animation_Player::play(bool should_loop) {
    if (animation_textures.empty()) {
        return;
    }
    is_playing = true;
    loop = should_loop;
    clock.restart();
}

void Animation_Player::stop() {
    is_playing = false;
    current_frame = 0;
}

void Animation_Player::pause() {
    is_playing = false;
}

bool Animation_Player::isPlaying() {
    return is_playing;
}

void Animation_Player::setFrameDuration(float duration) {
    frame_duration = duration;
}

bool Animation_Player::isFinished() {
    return !is_playing && !loop && current_frame == animation_textures.size() - 1;
}
