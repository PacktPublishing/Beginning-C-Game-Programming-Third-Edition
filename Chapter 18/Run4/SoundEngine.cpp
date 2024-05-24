#include "SoundEngine.h"
#include <assert.h>

SoundEngine* SoundEngine::m_s_Instance = nullptr;
bool SoundEngine::mMusicIsPlaying = false;
Music SoundEngine::music;

SoundBuffer SoundEngine::m_ClickBuffer;
Sound SoundEngine::m_ClickSound;
SoundBuffer SoundEngine::m_JumpBuffer;
Sound SoundEngine::m_JumpSound;

SoundEngine::SoundEngine()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;

	m_ClickBuffer.loadFromFile("sound/click.wav");
	m_ClickSound.setBuffer(m_ClickBuffer);

	m_JumpBuffer.loadFromFile("sound/jump.wav");
	m_JumpSound.setBuffer(m_JumpBuffer);
}

void SoundEngine::playClick()
{
	m_ClickSound.play();
}

void SoundEngine::playJump()
{
	m_JumpSound.play();
}

void SoundEngine::startMusic()
{
	music.openFromFile("music/music.wav");
	m_s_Instance->music.play();
	m_s_Instance->music.setLoop(true);
	mMusicIsPlaying = true;
}

void SoundEngine::pauseMusic()
{
	m_s_Instance->music.pause();
	mMusicIsPlaying = false;
}

void SoundEngine::resumeMusic()
{
	m_s_Instance->music.play();
	mMusicIsPlaying = true;
}

void SoundEngine::stopMusic()
{
	m_s_Instance->music.stop();

	mMusicIsPlaying = false;
}
