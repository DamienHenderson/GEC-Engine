#include "Sound.hpp"

Sound g_sound;

Sound::Sound()
{
}


Sound::~Sound()
{
}

void Sound::LoadSound(const std::string & name, const std::string & path)
{
	HAPI.LoadSound(path);

	sound_aliases_.emplace(name, path);
}

int Sound::PlaySound(const std::string & name, const HAPISPACE::HAPI_TSoundOptions & options)
{
	int instance_id{ 0 };
	auto& iter = sound_aliases_.find(name);

	if (iter != sound_aliases_.end())
	{
		HAPI.PlaySound(iter->second, options, instance_id);
	}

	
	return instance_id;
}

void Sound::SetSoundOptions(int id, const HAPISPACE::HAPI_TSoundOptions & options)
{
	HAPI.ChangePlayingSoundOptions(id, options);
}

void Sound::StopSound(int id, bool pause)
{
	HAPI.StopSound(id, pause);
}

int Sound::PlayMusic(const std::string & filename, const HAPISPACE::HAPI_TStreamedMediaOptions& options)
{
	int instance_id{ 0 };

	HAPI.PlayStreamedMedia(filename, options, instance_id);
	return instance_id;
}

void Sound::PlayMusic(int id)
{
	HAPI.PlayStreamedMedia(id);
}

void Sound::ReceiveMessage(Message * msg)
{
}
