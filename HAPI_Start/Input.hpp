#pragma once

#include <HAPI_lib.h>
#include <HAPI_InputCodes.h>

#include <unordered_map>
#include <string>
#include <cassert>

#include "Types.hpp"

enum class MouseButton
{
	left,
	middle,
	right,
	x_button_1,
	x_button_2
};
class Input
{
public:
	Input();
	~Input();

	

	/// Load a set of input mappings from an xml node
	void LoadMappings(const HAPISPACE::CHapiXMLNode& node);

	bool GetKeyState(const std::string& alias);
	bool GetKeyState(int key);

	bool GetMouseButtonState(const std::string& alias);
	bool GetMouseButtonState(MouseButton button);

	vec2<int> GetMousePosition();
	int GetMouseWheel();

	bool GetControllerDigital(const std::string& alias, int controller_id);
	bool GetControllerDigital(int button, int controller_id);

	int GetControllerAnalogue(const std::string& alias, int controller_id);
	int GetControllerAnalogue(int code, int controller_id);
	
	void SetControllerRumble(int controller_id, HAPISPACE::WORD left, HAPISPACE::WORD right);

	
	void AddKeyAlias(const std::string& alias, int keycode);

	void AddMouseButtonAlias(const std::string& alias, MouseButton button);

	void AddControllerDigitalAlias(const std::string& alias, int button);

	void AddControllerAnalogueAlias(const std::string& alias, int code);

private:
	std::unordered_map<std::string, int> keyboard_mappings_;
	std::unordered_map<std::string, MouseButton> mouse_mappings_;
	std::unordered_map<std::string, int> controller_digital_mappings_;
	std::unordered_map<std::string, int> controller_analogue_mappings_;

};

extern Input g_input;


