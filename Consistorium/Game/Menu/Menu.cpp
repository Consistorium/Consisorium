#include <iostream>

#include "Menu.h"
#include "../Game.h"
#include "MouseButtonEnum.h"
#include "UI/Button.h"

bool userQuit = false;

void displayButtonOnScreen(Button &button, SDL_Surface* surface);
void* startButtonClickHandler(SDL_Window*  window);
void* exitButtonClickHandler();

Menu::Menu(SDL_Window * window)
	:Window(window)
{
}

void Menu::handleMouseClick(SDL_Event e)
{
	if ((MouseButton)e.button.button == MouseButton::Left)
	{
		std::cout << "Clicked at: " << e.button.x << " " << e.button.y << std::endl;
		for (size_t i = 0; i < buttons_.size(); i++)
		{
			SDL_Point clickPosition;
			clickPosition.x = e.button.x;
			clickPosition.y = e.button.y;
			if (SDL_PointInRect(&clickPosition, &buttons_[i]->getBounds()))
			{
				buttons_[i]->click(window_);
			}
		}
	}
}

void Menu::CreateButtons()
{
	auto badButton = new Button(0, 150, DEFAULT_BTN_MODEL_NAME, "Start Game");

	int middleX = windowSurface_->clip_rect.w / 2;
	int buttonX = middleX - badButton->getBounds().w / 2;

	auto startButton = new Button(buttonX, 150, DEFAULT_BTN_MODEL_NAME, "Start Game");
	startButton->setOnClick(&startButtonClickHandler);

	auto tutorialButton = new Button(buttonX, 250, DEFAULT_BTN_MODEL_NAME, "Tutorial");

	auto exitButton = new Button(buttonX, 350, DEFAULT_BTN_MODEL_NAME, "Exit");
	exitButton->setOnClick(&exitButtonClickHandler);

	buttons_.push_back(startButton);
	buttons_.push_back(tutorialButton);
	buttons_.push_back(exitButton);
}

void Menu::Init()
{
	// Initialize SDL_ttf library
	if (TTF_Init() != 0)
	{
		std::cerr << "TTF_Init() Failed: " << TTF_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}

	CreateButtons();
}

void Menu::Run()
{
	Init();

	SDL_Surface* background = IMG_Load("background.png");
	SDL_BlitSurface(background, nullptr, windowSurface_, nullptr);

	SDL_Event e;

	while (true)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				handleMouseClick(e);
			}
		}

		if (userQuit)
		{
			return;
		}

		for (size_t i = 0; i < buttons_.size(); i++)
		{
			displayButtonOnScreen(*buttons_[i], windowSurface_);
		}

		SDL_UpdateWindowSurface(window_);
	}
}

Menu::~Menu()
{
}

void* startButtonClickHandler(SDL_Window*  window)
{
	Game game(window);
	game.Run();
	return nullptr;
}

void* exitButtonClickHandler()
{
	userQuit = true;
	return nullptr;
}

void displayButtonOnScreen(Button &button, SDL_Surface* surface)
{
	SDL_BlitSurface(button.getModel(), &button.getModel()->clip_rect, surface, &button.getBounds());

	// Load a font
	TTF_Font *font;
	font = TTF_OpenFont("FreeSans.ttf", 24);
	if (font == NULL)
	{
		std::cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << std::endl;
		TTF_Quit();
		return;
	}

	SDL_Color text_color = { 255, 255, 255 };
	SDL_Surface *buttonText = TTF_RenderText_Solid(font,
		button.get_text(),
		text_color);

	if (buttonText == NULL)
	{
		std::cerr << "TTF_RenderText_Solid() Failed: " << TTF_GetError() << std::endl;
		TTF_Quit();
		return;
	}

	SDL_Rect textPosition;
	textPosition.x = button.getBounds().x + button.getBounds().w / 2 - buttonText->w / 2;
	textPosition.y = button.getBounds().y + button.getBounds().h / 2 - buttonText->h / 2;

	SDL_BlitSurface(buttonText, &button.getModel()->clip_rect, surface, &textPosition);
}