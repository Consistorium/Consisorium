#include <iostream>
#include <SDL_ttf.h>

#include "MenuPage.h"
#include "GamePage.h"

bool userQuit = false;

enum class MouseButton
{
	Left = 1,
	Right = 2
};

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

struct Point
{
	int x_;
	int y_;

	Point(int x, int y)
	{
		x_ = x;
		y_ = y;
	};
};

bool clickIsInsideBounds(Point click, SDL_Rect bounds)
{
	if ((click.x_ >= bounds.x && click.x_ <= bounds.x + bounds.w) &&
		(click.y_ >= bounds.y && click.y_ <= bounds.y + bounds.h))
	{
		return true;
	}

	return false;
}

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
			Point clickPosition(e.button.x, e.button.y);
			if (clickIsInsideBounds(clickPosition, buttons_[i]->getBounds()))
			{
				buttons_[i]->click(window_);
			}
		}
	}
}

void MenuPage::CreateButtons()
{
	auto startButton = new Button(50, 150, DEFAULT_BTN_MODEL_NAME, "Start Game");
	startButton->setOnClick(&startButtonClickHandler);
	auto tutorialButton = new Button(50, 250, DEFAULT_BTN_MODEL_NAME, "Tutorial");
	auto exitButton = new Button(50, 350, DEFAULT_BTN_MODEL_NAME, "Exit");
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
			SDL_BlitSurface(buttons_[i]->getModel(), &buttons_[i]->getModel()->clip_rect, windowSurface_, &buttons_[i]->getBounds());

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
				buttons_[i]->get_text(),
				text_color);

			if (buttonText == NULL)
			{
				std::cerr << "TTF_RenderText_Solid() Failed: " << TTF_GetError() << std::endl;
				TTF_Quit();
				return;
			}

			SDL_BlitSurface(buttonText, &buttons_[i]->getModel()->clip_rect, windowSurface_, &buttons_[i]->getBounds());
		}

		SDL_UpdateWindowSurface(window_);
	}
}

MenuPage::~MenuPage()
{
}