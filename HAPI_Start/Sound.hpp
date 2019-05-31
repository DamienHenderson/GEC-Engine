#pragma once

#include <HAPI_lib.h>
#include <HAPI_Types.h>

#include <unordered_map>
#include <string>

class Message;

class Sound
{
public:
	Sound();
	~Sound();

	void LoadSound(const std::string& name, const std::string& path);

	int  PlaySound(const std::string& name, const HAPISPACE::HAPI_TSoundOptions& options);

	void SetSoundOptions(int id, const HAPISPACE::HAPI_TSoundOptions& options);

	void StopSound(int id, bool pause = false);

	int  PlayMusic(const std::string& filename, const HAPISPACE::HAPI_TStreamedMediaOptions& options);
	
	void PlayMusic(int id);

	void ReceiveMessage(Message* msg);
private:
	std::unordered_map<std::string, std::string> sound_aliases_;
};

extern Sound g_sound;

