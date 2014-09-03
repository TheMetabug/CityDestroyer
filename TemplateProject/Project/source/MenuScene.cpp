#include "../include/MenuScene.hpp"
#include "../include/ProtoScene.hpp"

#include <UtH/Engine/UtHEngine.h>
#include <UtH/Platform/Input.hpp>
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Platform/Debug.hpp> //WriteLog(...), works like printf.

using namespace uth;

// Main initialisation.
// Automatically called inside SceneManager.
bool MenuScene::Init()
{
	// Some shader must be loaded and set window to use it
	m_shader.LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	m_shader.Use();
	uthEngine.GetWindow().SetShader(&m_shader);
	

	m_startButton = new GameObject();
	m_startButton->AddComponent(new Sprite(umath::vector4(1, 1, 0, 1), umath::vector2(256, 128)));

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
	if (uthInput.Keyboard.IsKeyDown(uth::Keyboard::Space) /*|| uth::InputEvent::TAP*/)
	{
		uthSceneM.GoToScene(1);
		WriteLog("Start game...");
	}

	return true; // Update succeeded.
}

// Draw loop. All graphics are drawn during this loop.
bool MenuScene::Draw()
{
	uthEngine.GetWindow().Clear(0, 0, 0, 1);
	m_startButton->Draw(uthEngine.GetWindow());
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