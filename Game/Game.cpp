#include "Game.h"


SDL_Renderer* Game::m_Renderer = nullptr;
Game::Game()
{
	m_Window = nullptr;
	m_Renderer = nullptr;
  
	/*Set up Window*/
	m_Window = SDL_CreateWindow(
		"Super Game 2018",
		250,
		50,
		800,
		800,
		0
	);
	if (!m_Window) {
		//handle error 
	}
	/*END OF WINDOW SET UP*/


	


	/*SET UP RENDERER*/
	m_Renderer = SDL_CreateRenderer(
		m_Window,
		-1,
		0
	);
    if(!m_Renderer){
        printf("Renderer failed to be created");
    }
    SDL_PumpEvents();
    
    SDL_UpdateWindowSurface( m_Window );
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);


	//Set up text
	if (TTF_Init() == -1)
	{
		std::cout << "Text init failed :(";
	}

	Text = new text("KOMIKAP_.ttf", 100, "Hello!", { 255, 0, 0, 255 });

	sound = new soundManager();
	sound->playMusic("starwars.wav");

	world = new World();
}
void Game::paint() {
	SDL_RenderClear(m_Renderer);
	world->paint();
	
	Text->displaytext(400, 400);
    //SDL_Delay(10);
	SDL_RenderPresent(m_Renderer);
}
void Game::update() {
	world->update();
}
Game::~Game()
{
    world = nullptr;
	if (m_Renderer) {
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
	if (m_Window) {
		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;
	}
	if (Text)
	{
		delete Text; 
		Text = nullptr;
	}
	if (sound)
	{
		delete sound;
		sound = nullptr;
	}
}
