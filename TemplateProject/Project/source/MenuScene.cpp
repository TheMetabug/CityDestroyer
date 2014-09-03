#include "../include/MenuScene.hpp"

#include <UtH/Engine/UtHEngine.h>
#include <UtH/Platform/Debug.hpp> //WriteLog(...), works like printf.

// Main initialisation.
// Automatically called inside SceneManager.
bool MenuScene::Init()
{
	// Some shader must be loaded and set window to use it
	m_shader.LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	m_shader.Use();
	uthEngine.GetWindow().SetShader(&m_shader);

	return true;
}

// Main deinitialisation.
// Automatically called inside SceneManager.
bool MenuScene::DeInit()
{
	return true;
}

// Update loop. Gone trought once per frame.
bool MenuScene::Update(float dt)
{
	return true; // Update succeeded.
}

// Draw loop. All graphics are drawn during this loop.
bool MenuScene::Draw()
{
	return true; // Drawing succeeded.
}

//Default constructor for initialising constant variables.
MenuScene::MenuScene()
{

}
//Default deconstrutor.
MenuScene::~MenuScene()
{

}