#pragma once

class GameManager;
class Renderer;

class Application
{
public:
	Application();
	~Application();

	void go();
private:
	GameManager* gManager;
	Renderer* pRenderer;
};

