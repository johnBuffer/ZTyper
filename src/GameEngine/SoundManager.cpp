#include "../../includes/GameEngine/SoundManager.h"

SoundManager::SoundManager():
    _masterVolume(100.f)
{

}

void SoundManager::addSound(sf::SoundBuffer& buffer, float volume)
{
    sf::Sound s(buffer);
    s.setVolume(volume*_masterVolume);
    _sounds.push_back(s);
    _sounds.back().play();
}

void SoundManager::update()
{
    _sounds.remove_if([](sf::Sound &s)     { return !s.getStatus(); });
}
