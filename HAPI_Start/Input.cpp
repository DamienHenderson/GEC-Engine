#include "Input.hpp"

Input g_input;

Input::Input()
{
}


Input::~Input()
{
}

void Input::LoadMappings(const HAPISPACE::CHapiXMLNode & node)
{
	// make sure the node is actually an input mapping node
	if (node.GetName() == "Input")
	{
		HAPISPACE::CHapiXMLAttribute show_cursor;
		if (node.GetAttributeWithName("show_cursor", show_cursor))
		{
			HAPI.SetShowCursor(show_cursor.AsBool());
		}
		for (auto& iter : node.GetChildren()) 
		{
			if (iter->GetName() == "InputMap")
			{
				HAPISPACE::CHapiXMLAttribute mapping_type, name, code;
				
				bool res = iter->GetAttributeWithName("name", name);
				res = iter->GetAttributeWithName("code", code);
				res = iter->GetAttributeWithName("type", mapping_type);
				if (res)
				{
					if (mapping_type.AsString() == "Keyboard")
					{
						keyboard_mappings_.emplace(name.AsString(), code.AsInt());
					}
					else if (mapping_type.AsString() == "Mouse")
					{
						MouseButton btn = MouseButton::left;
						switch (code.AsInt())
						{
						case 0:
							btn = MouseButton::left;
							break;
						case 1:
							btn = MouseButton::middle;
							break;
						case 2:
							btn = MouseButton::right;
						case 3:
							btn = MouseButton::x_button_1;
							break;
						case 4:
							btn = MouseButton::x_button_2;
							break;
						default:
							// assert("Undefined mouse button id in mapping" && false);
							break;
						}
						mouse_mappings_.emplace(name.AsString(), btn);
					}
					else if (mapping_type.AsString() == "Controller_Digital")
					{
						controller_digital_mappings_.emplace(name.AsString(), code.AsInt());
					}
					else if (mapping_type.AsString() == "Controller_Analogue")
					{
						controller_analogue_mappings_.emplace(name.AsString(), code.AsInt());
					}
				}
			}
		}
	}
	return;
}

bool Input::GetKeyState(const std::string & alias)
{
	auto& iter = keyboard_mappings_.find(alias);

	if (iter != keyboard_mappings_.end())
	{
		const HAPISPACE::HAPI_TKeyboardData& data = HAPI.GetKeyboardData();

		return data.scanCode[iter->second];
	}

	// assert("Key alias not defined" && false);
	return false;
}

bool Input::GetKeyState(int key)
{
	const HAPISPACE::HAPI_TKeyboardData& data = HAPI.GetKeyboardData();

	return data.scanCode[key];
}

bool Input::GetMouseButtonState(const std::string & alias)
{
	auto& iter = mouse_mappings_.find(alias);

	if (iter != mouse_mappings_.end())
	{
		const HAPISPACE::HAPI_TMouseData& data = HAPI.GetMouseData();
		
		switch (iter->second)
		{
		case MouseButton::left:
			return data.leftButtonDown;
			break;
		case MouseButton::middle:
			return data.middleButtonDown;
			break;
		case MouseButton::right:
			return data.rightButtonDown;
			break;
		case MouseButton::x_button_1:
			return data.xButton1Down;
			break;
		case MouseButton::x_button_2:
			return data.xButton2Down;
			break;

		default:
			return false;
			break;
		}
		
	}

	//assert("Mouse button alias not defined" && false);
	return false;
}

bool Input::GetMouseButtonState(MouseButton button)
{
	const HAPISPACE::HAPI_TMouseData& data = HAPI.GetMouseData();
	
	switch (button)
	{
	case MouseButton::left:
		return data.leftButtonDown;
		break;
	case MouseButton::middle:
		return data.middleButtonDown;
		break;
	case MouseButton::right:
		return data.rightButtonDown;
		break;
	case MouseButton::x_button_1:
		return data.xButton1Down;
		break;
	case MouseButton::x_button_2:
		return data.xButton2Down;
		break;

	default:
		return false;
		break;
	}
	return false;
}

bool Input::GetControllerDigital(const std::string & alias, int controller_id)
{
	auto& iter = controller_digital_mappings_.find(alias);

	if (iter != controller_digital_mappings_.end())
	{
		const HAPISPACE::HAPI_TControllerData& data = HAPI.GetControllerData(controller_id);

		if (data.isAttached)
		{
			return data.digitalButtons[iter->second];
		}
		// assert("Controller not attached" && false);
		return false;
	}
	// assert("Controller digital button alias not defined" && false);
	return false;
}

bool Input::GetControllerDigital(int button, int controller_id)
{
	const HAPISPACE::HAPI_TControllerData& data = HAPI.GetControllerData(controller_id);

	if (data.isAttached)
	{
		return data.digitalButtons[button];
	}
	// assert("Controller not attached" && false);
	return false;
}

int Input::GetControllerAnalogue(const std::string & alias, int controller_id)
{
	auto& iter = controller_analogue_mappings_.find(alias);

	if (iter != controller_analogue_mappings_.end())
	{
		const HAPISPACE::HAPI_TControllerData& data = HAPI.GetControllerData(controller_id);

		if (data.isAttached)
		{
			// Handle deadzones here or require anyone using this function to handle deadzones themselves?
			// if handling deadzones here just return the value if not in deadzone or 0 if inside deadzone
			return data.analogueButtons[iter->second];
		}
		// assert("Controller not attached" && false);
		return false;
	}
	// assert("Controller analogue button alias not defined" && false);
	return false;
}

int Input::GetControllerAnalogue(int code, int controller_id)
{
	const HAPISPACE::HAPI_TControllerData& data = HAPI.GetControllerData(controller_id);

	if (data.isAttached)
	{
		// Handle deadzones here or require anyone using this function to handle deadzones themselves?
		// if handling deadzones here just return the value if not in deadzone or 0 if inside deadzone
		return data.analogueButtons[code];
	}
	// assert("Controller not attached" && false);
	return 0;
}

void Input::SetControllerRumble(int controller_id, HAPISPACE::WORD left, HAPISPACE::WORD right)
{
	HAPI.SetControllerRumble(controller_id, left, right);
}

vec2<int> Input::GetMousePosition()
{
	const HAPISPACE::HAPI_TMouseData mouse = HAPI.GetMouseData();

	return vec2<int>{mouse.x, mouse.y};
}

int Input::GetMouseWheel()
{
	const HAPISPACE::HAPI_TMouseData& data = HAPI.GetMouseData();

	return data.wheelMovement;
}

void Input::AddKeyAlias(const std::string & alias, int keycode)
{
	keyboard_mappings_.emplace(alias, keycode);
}

void Input::AddMouseButtonAlias(const std::string & alias, MouseButton button)
{
	mouse_mappings_.emplace(alias, button);
}

void Input::AddControllerDigitalAlias(const std::string & alias, int button)
{
	controller_digital_mappings_.emplace(alias, button);
}

void Input::AddControllerAnalogueAlias(const std::string & alias, int code)
{
	controller_analogue_mappings_.emplace(alias, code);
}
