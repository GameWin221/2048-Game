#include "Menu/Menu.hpp"

namespace Menu
{
	Window* menuWindow;

	Texture* vignetteTexture;
	Sprite* vignette;

	Text* titleText;
	Text* chooseText;

	Texture* topPanelTexture;
	Sprite* topPanel;
	
	GridSizeButton* button2 ;
	GridSizeButton* button3 ;
	GridSizeButton* button4 ;
	GridSizeButton* button6 ;
	GridSizeButton* button8;
	GridSizeButton* button14;
	GridSizeButton* button20;
	GridSizeButton* button24;
	GridSizeButton* button32;

	int* sizeIntPtr;
	int chosenSize = 0;
	
	void Start(int* sizeInt, Window* window)
	{
		sizeIntPtr = sizeInt;
		menuWindow = window;

		//menuWindow = new Window(glm::uvec2(900, 1024), "2048");
		glfwSetWindowCloseCallback(menuWindow->glfwWindow, Exit);

		vignetteTexture = new Texture("Resources/Textures/Vignette.png");

		vignette = new Sprite(vignetteTexture);
		vignette->position = glm::vec2(450, 512);
		vignette->size = vignette->position;
		vignette->opacity = 0.5f;

		topPanelTexture = new Texture("Resources/Textures/BGWide.png");
		topPanel = new Sprite(topPanelTexture);
		topPanel->position = glm::vec2(450, 884);
		topPanel->color = glm::vec3(0.4f);
		topPanel->size = glm::vec2(440, 140);

		titleText  = new Text(Font::DefaultFont(), "2048");
		titleText->position = glm::vec2(450, 940);
		titleText->color = glm::vec3(0.2f);
		titleText->scale = 1.2f;
		titleText->centered = true;

		chooseText = new Text(Font::DefaultFont(), "Choose the grid's size:");
		chooseText->position = glm::vec2(450, 820);
		chooseText->color = glm::vec3(0.2f);
		chooseText->scale = 0.65f;
		chooseText->centered = true;

		button2  = new GridSizeButton(glm::vec2(150, 610), 2 );
		button3  = new GridSizeButton(glm::vec2(450, 610), 3 );
		button4  = new GridSizeButton(glm::vec2(750, 610), 4 );
		button6  = new GridSizeButton(glm::vec2(150, 380), 6 );
		button8  = new GridSizeButton(glm::vec2(450, 380), 8 );
		button14 = new GridSizeButton(glm::vec2(750, 380), 14);
		button20 = new GridSizeButton(glm::vec2(150, 150), 20);
		button24 = new GridSizeButton(glm::vec2(450, 150), 24);
		button32 = new GridSizeButton(glm::vec2(750, 150), 32);
	}
	void Update()
	{
		menuWindow->PollEvents();

		button2 ->CheckPress();
		button3 ->CheckPress();
		button4 ->CheckPress();
		button6 ->CheckPress();
		button8 ->CheckPress();
		button14->CheckPress();
		button20->CheckPress();
		button24->CheckPress();
		button32->CheckPress();
	}
	void Render()
	{
		menuWindow->Clear(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

		Sprite::InitInstancing();
		topPanel->Render();

		Text::InitInstancing();
		titleText ->Render();
		chooseText->Render();

		Sprite::InitInstancing();
		button2 ->Render();
		button3 ->Render();
		button4 ->Render();
		button6 ->Render();
		button8 ->Render();
		button14->Render();
		button20->Render();
		button24->Render();
		button32->Render();

		Text::InitInstancing();
		button2 ->RenderText();
		button3 ->RenderText();
		button4 ->RenderText();
		button6 ->RenderText();
		button8 ->RenderText();
		button14->RenderText();
		button20->RenderText();
		button24->RenderText();
		button32->RenderText();

		Sprite::InitInstancing();
		vignette->Render();

		menuWindow->Display();
	}

	void CloseMenu()
	{
		delete vignetteTexture;
		delete vignette;
		delete titleText;
		delete chooseText;
		delete topPanelTexture;
		delete topPanel;
		delete button2 ;
		delete button3 ;
		delete button4 ;
		delete button6 ;
		delete button8 ;
		delete button14;
		delete button20;
		delete button24;
		delete button32;
	}

	const int& GetChosenSize()
	{
		return chosenSize;
	}

	void SetChosenSize(const int size)
	{
		chosenSize = size;
		*sizeIntPtr = chosenSize;
	}

	void Exit(GLFWwindow* window)
	{
		menuWindow->Close();
		exit(0);
	}
	bool IsRunning()
	{
		return menuWindow->IsOpen();
	}
}