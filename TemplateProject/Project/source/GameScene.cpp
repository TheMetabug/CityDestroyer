#include <GameScene.hpp>

using namespace uth;

//Initialisation
bool GameScene::Init()
{
	//Shader must be loaded and set window to use it
	m_shader.LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	m_shader.Use();
	uthEngine.GetWindow().SetShader(&m_shader);
	uthEngine.SetClearColor(0, 0, 1); //Clear colour
	//PUT INIT FUNCTIONS HERE




	//END INIT FUNCTIONS
	return true; // Init succeeded.
}
//Update functions
bool GameScene::Update(float dt)
{
	m_player.Update(dt);
	return true; // Update succeeded.
}
//Draw functions
bool GameScene::Draw()
{
	m_player.Draw();
	return true; // Drawing succeeded.
}

//Deinitialisation
bool GameScene::DeInit()
{
	return true;
}
//Default constructor for initialising constant variables.
GameScene::GameScene()
{

}
//Default deconstrutor.
GameScene::~GameScene()
{

}