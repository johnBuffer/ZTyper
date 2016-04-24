#ifndef SOUNDMANAGER_H_INCLUDED
#define SOUNDMANAGER_H_INCLUDED

#include <SFML/Audio.hpp>
#include <list>

class SoundManager
{
public:
    SoundManager();
    void setMasterVolume(float vol) {_masterVolume = vol;}
    void addSound(sf::SoundBuffer& buffer, float volume=1.f);
    void update();

private:
    float                _masterVolume;
    std::list<sf::Sound> _sounds;
};

#endif // SOUNDMANAGER_H_INCLUDED
