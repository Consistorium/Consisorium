#include <iostream>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "MenuPage.h"
#include "GamePage.h"
#include "MouseButtonEnum.h"

bool userQuit = false;

void displayButtonOnScreen(Button &button, SDL_Surface* surface);
void* startButtonClickHandler(SDL_Window*  window);
void* exitButtonClickHandler();

MenuPage::MenuPage(SDL_Window * window)
	:Page(window)
{
}

void MenuPage::handleMouseClick(SDL_Event e)
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

void MenuPage::CreateButtons()
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

void MenuPage::Init()
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

void MenuPage::Run()
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

MenuPage::~MenuPage()
{
}

void* startButtonClickHandler(SDL_Window*  window)
{
	GamePage gamePage(window);
	gamePage.Run();
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