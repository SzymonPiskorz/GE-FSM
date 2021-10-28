#include "../include/Game.h"

Game::Game() :
	m_gameIsRunning{ false }
{
	SDL_Init(SDL_INIT_VIDEO);

	m_window = SDL_CreateWindow("SFML to SDL",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);
	m_renderer = SDL_CreateRenderer(m_window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);

	m_texture = loadFromFile(PLAYER_SPRITES, m_renderer);
	if(m_texture == nullptr)
	{
		m_texture = loadFromFile(ERROR_SPRITES, m_renderer);
	}

	player_animated_sprite = new AnimatedSprite(m_texture);
	player = new Player(*player_animated_sprite);

	

}

Game::~Game()
{
	cleanUp();
}

void Game::run()
{

	m_gameIsRunning = true;
	SDL_Event e{};

	while (m_gameIsRunning)
	{
		processEvents(e);
		update();
		render();
	}

	cleanUp();
}

void Game::processEvents(SDL_Event t_e)
{
	// simple event loop
	while (SDL_PollEvent(&t_e) != 0)
	{
		if (t_e.type == SDL_QUIT)
		{
			m_gameIsRunning = false;
		}

		// checks if the escape key is pressed down
		if (t_e.type == SDL_KEYDOWN && t_e.key.keysym.sym == SDLK_ESCAPE)
		{
			m_gameIsRunning = false;
		}
		inputs(t_e);

		player->handleInput(input);
	}
}

void Game::update()
{
	player->update();
}

void Game::render()
{
	rendererDraw();
}

void Game::rendererDraw()
{
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0);
	SDL_RenderClear(m_renderer);

	player->getAnimatedSpriteFrame().render(0,0, m_renderer);

	SDL_RenderPresent(m_renderer);
}

void Game::cleanUp()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_window = nullptr;
	m_renderer = nullptr;

	SDL_DestroyTexture(m_texture);

	IMG_Quit();
	SDL_Quit();
}

void Game::inputs(SDL_Event t_e)
{

				
	if(t_e.type == SDL_KEYDOWN) // Deal with KeyPressed
	{
		// Died Event
		if (t_e.key.keysym.sym == SDLK_d) {
			DEBUG_MSG("gpp::Events::Event::DIED_EVENT");
			input.setCurrent(gpp::Events::Event::DIED_EVENT);
		}
		// Revieved Event
		else if (t_e.key.keysym.sym == SDLK_r) {
			DEBUG_MSG("gpp::Events::Event::REVIVED_EVENT");
			input.setCurrent(gpp::Events::Event::REVIVED_EVENT);
		}
		// Running attack
		else if (t_e.key.keysym.sym == SDLK_z 
			&& 
			t_e.key.keysym.sym == SDLK_RIGHT 
			||
			t_e.key.keysym.sym == SDLK_RIGHT 
			&& 
			t_e.key.keysym.sym == SDLK_z
			)
		{
			DEBUG_MSG("gpp::Events::Event::ATTACK_START");
			input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
		}
		// Attack
		else if (t_e.key.keysym.sym == SDLK_z)
		{
			DEBUG_MSG("gpp::Events::Event::ATTACK_START_EVENT");
			input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
		}
		// Throw attack
		else if (t_e.key.keysym.sym == SDLK_x 
			&& 
			t_e.key.keysym.sym == SDLK_RIGHT
			||
			t_e.key.keysym.sym == SDLK_RIGHT 
			&& 
			t_e.key.keysym.sym == SDLK_x
			)
		{
			DEBUG_MSG("gpp::Events::Event::THROW_START_EVENT");
			input.setCurrent(gpp::Events::Event::THROW_START_EVENT);
		}
		// Throw Attack
		else if (t_e.key.keysym.sym == SDLK_x)
		{
			DEBUG_MSG("gpp::Events::Event::THROW_START_EVENT");
			input.setCurrent(gpp::Events::Event::THROW_START_EVENT);
		}
		// Run Right
		else if (t_e.key.keysym.sym == SDLK_RIGHT)
		{
			DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
			input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
		}
		// Climb Up
		else if (t_e.key.keysym.sym == SDLK_UP)
		{
			DEBUG_MSG("gpp::Events::Event::MOVE_UP_START_EVENT");
			input.setCurrent(gpp::Events::Event::MOVE_UP_START_EVENT);
		}
		// Climb Down
		else if (t_e.key.keysym.sym == SDLK_DOWN)
		{
			DEBUG_MSG("gpp::Events::Event::MOVE_DOWN_START_EVENT");
			input.setCurrent(gpp::Events::Event::MOVE_DOWN_START_EVENT);
		}
		// Hit Bottom of Ladder Event
		else if (t_e.key.keysym.sym == SDLK_c)
		{
			DEBUG_MSG("gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT");
			input.setCurrent(gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT);
		}
		// Hit Top of Ladder Event
		else if (t_e.key.keysym.sym == SDLK_t)
		{
			DEBUG_MSG("gpp::Events::Event::HIT_LADDER_TOP_EVENT");
			input.setCurrent(gpp::Events::Event::HIT_LADDER_TOP_EVENT);
		}
		// Jump Run
		if (t_e.key.keysym.sym == SDLK_SPACE
			&& 
			t_e.key.keysym.sym == SDLK_RIGHT
			||
			t_e.key.keysym.sym == SDLK_RIGHT 
			&& 
			t_e.key.keysym.sym == SDLK_SPACE
			)
		{
			DEBUG_MSG("gpp::Events::Event::JUMP_UP_EVENT");
			input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
		}
		// Jump Event
		else if (t_e.key.keysym.sym == SDLK_SPACE)
		{
			DEBUG_MSG("gpp::Events::Event::JUMP_UP_EVENT");
			input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
		}
		// Running Slide
		else if (t_e.key.keysym.sym == SDLK_DOWN 
			&& 
			t_e.key.keysym.sym == SDLK_RIGHT
			||
			t_e.key.keysym.sym == SDLK_RIGHT 
			&& 
			t_e.key.keysym.sym == SDLK_DOWN
			)
		{
			DEBUG_MSG("gpp::Events::Event::SLIDE_EVENT");
			input.setCurrent(gpp::Events::Event::SLIDE_EVENT);
		}
		// Hit Ground Event
		else if (t_e.key.keysym.sym == SDLK_h)
		{
			DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
			input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
		}
		// Jump Attack Event
		else if (t_e.key.keysym.sym == SDLK_h)
		{
			DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
			input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
		}
		// Jump Throw Attack Event
		else if (t_e.key.keysym.sym == SDLK_h)
		{
			DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
			input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
		}
	}		
	else if(t_e.type == SDL_KEYUP) // Deal with KeyReleased
	{
		// Run and Stop Attack
		if (t_e.key.keysym.sym == SDLK_z 
			&& 
			t_e.key.keysym.sym == SDLK_RIGHT)
		{
			DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
			input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
		}
		// Stop Attack
		else if(t_e.key.keysym.sym == SDLK_z)
		{
			DEBUG_MSG("gpp::Events::Event::ATTACK_STOP_EVENT");
			input.setCurrent(gpp::Events::Event::ATTACK_STOP_EVENT);
		}
		// Run and Stop Throw Attack
		else if (t_e.key.keysym.sym == SDLK_x
			&&
			t_e.key.keysym.sym == SDLK_RIGHT)
		{
			DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
			input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
		}
		// Stop Throw Attack
		else if (t_e.key.keysym.sym == SDLK_x)
		{
			DEBUG_MSG("gpp::Events::Event::THROW_STOP_EVENT");
			input.setCurrent(gpp::Events::Event::THROW_STOP_EVENT);
		}
		// Stop Running Right
		else if (t_e.key.keysym.sym == SDLK_RIGHT)
		{
			DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_STOP_EVENT");
			input.setCurrent(gpp::Events::Event::RUN_RIGHT_STOP_EVENT);
		}
		// Stop Slide
		else if (t_e.key.keysym.sym == SDLK_DOWN 
			&&
			t_e.key.keysym.sym == SDLK_RIGHT)
		{
			DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
			input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
		}
		// Stop Moving Up
		else if (t_e.key.keysym.sym == SDLK_UP)
		{
			DEBUG_MSG("gpp::Events::Event::MOVE_UP_STOP_EVENT");
			input.setCurrent(gpp::Events::Event::MOVE_UP_STOP_EVENT);
		}
		// Stop Moving Down
		else if (t_e.key.keysym.sym == SDLK_DOWN)
		{
			DEBUG_MSG("gpp::Events::Event::MOVE_DOWN_STOP_EVENT");
			input.setCurrent(gpp::Events::Event::MOVE_DOWN_STOP_EVENT);
		}
	}
	else
	{
		DEBUG_MSG("gpp::Events::Event::NONE");
		input.setCurrent(gpp::Events::Event::NONE);
				
	}
}