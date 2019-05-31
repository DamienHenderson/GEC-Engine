#pragma once
#include <unordered_map>
#include <string>

#include "Sprite.hpp"
#include "Types.hpp"
#include "FrameBuffer.hpp"
#include "Screen.hpp"
class Visualisation
{
public:
	Visualisation(s32& width, s32& height, const std::string& title);
	~Visualisation();
	/// Loads a sprite from an image located at the filename specified.
	/// Returns true if successful or false if unsuccessful.
	/// If the sprite has already been loaded this function will return true without loading it again
	bool LoadSprite(const std::string& filename, bool has_alpha);
	/// Renders a sprite to the internal framebuffer
	/// id must be a filepath to an already loaded texture
	/// returns true on success and false on failure
	bool RenderSprite(const std::string& id, const vec2<f32>& position);

	/// Renders the contents of the internal framebuffer to the screen
	/// Q: should this be automatically called in Update?
	void SwapBuffer() { scr_.Blit(fb_); }

	/// Calls update on the screen held by visualisation
	/// doesn't make sense for HAPI 
	/// but allows for some other API which requires window instances to be updated to be supported more easily
	bool Update() { return scr_.Update(); }

	/// Copy from existing framebuffer to internal framebuffer
	void Clear(const FrameBuffer& fb) { fb_.Clear(fb); }
	/// Clear internal framebuffer to arbitrary colour
	void Clear(u32 packed) { fb_.ClearThreaded(packed); }
	/// Clear internal framebuffer to greyscale colour
	void ClearGreyscale(u8 greyscale) { fb_.ClearGreyscale(greyscale); }
private:
	// use unique_ptr here instead of raw pointers?
	// unique_ptr makes sense since sprites will not be accessed from outside the visualisation class
	std::unordered_map<std::string, Sprite*> sprites_;
	Screen scr_;
	FrameBuffer fb_;

};

