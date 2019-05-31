#pragma once
#include <unordered_map>
#include <string>

// TODO: forward declaration

#include "Image.hpp"
#include "Types.hpp"
#include "FrameBuffer.hpp"
#include "Screen.hpp"
#include "Camera.hpp"

class Message;
class Sprite;



class Visualisation
{
public:
	Visualisation() {};
	Visualisation(s32& width, s32& height, const std::string& title, bool fullscreen = false);
	~Visualisation();
	bool Initialise(s32& width, s32& height, const std::string& title, bool fullscreen = false);

	/// Create a sprite from an instance of the image class
	bool CreateSprite(const Image& img, const std::string& name, bool has_alpha, int x_frames = 1, int y_frames = 1);
	/// Loads a sprite from an image located at the filename specified.
	/// Returns true if successful or false if unsuccessful.
	/// If the sprite has already been loaded this function will return true without loading it again
	bool LoadSprite(const std::string& filename, bool has_alpha, int x_frames = 1, int y_frames = 1);
	/// Loads a sprite from an image located at the filename specified.
	/// Adds the image with the specified identifier for later access
	/// Returns true if successful or false if unsuccessful.
	/// If the sprite has already been loaded this function will return true without loading it again
	bool LoadSprite(const std::string& filename, const std::string& identifier, bool has_alpha, int x_frames = 1, int y_frames = 1);
	/// Renders a sprite to the internal framebuffer
	/// id must be a filepath to an already loaded texture
	/// returns true on success and false on failure
	/// TODO: Multithreading
	bool RenderSprite(const std::string& id, const vec2<f32>& position, int frame = 0);

	bool RenderSpriteToFrameBuffer(const std::string& id, const vec2<f32>& position, int frame, FrameBuffer& fb);

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
	void ClearGreyscale(u8 greyscale) { fb_.ClearGreyscaleThreaded(greyscale); }

	void MoveCamera(const vec2<f32>& delta);

	const Camera& GetCamera() const { return camera_; }

	rect<s32> GetScreenDimensions() const 
	{
		// the stored fb is always the size of the screen
		return fb_.GetRect(); 
	}

	void ReceiveMessage(Message* msg);
private:
	// use unique_ptr here instead of raw pointers?
	// unique_ptr makes sense since sprites will not be accessed from outside the visualisation class
	std::unordered_map<std::string, Sprite*> sprites_;
	Screen scr_;
	FrameBuffer fb_;
	
	Camera camera_;
};

