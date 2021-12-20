#include "Menu.h"
#include "Engine.h"
void Menu::play()
{
	engine->isPlaying = true;

}

void Menu::exit()
{

}

void Menu::update(sf::Time& dt)
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground;
	
	if (engine->isPlaying) {
		return;
	}
	bool open = true;
	
	ImGui::SFML::Update(*window, dt);
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(600, 480));
	
	ImGui::Begin("hello world", &open, window_flags);
	if (ImGui::Button("Play", ImVec2(130, 50))) { play(); }
	if (ImGui::Button("Exit", ImVec2(130, 50))) { exit(); }
	ImGui::Text("Im so good", 30);
	ImGui::End();
	ImGui::SFML::Render(*window);
}

Menu::Menu(sf::RenderWindow& window, Engine* engine)
{
	this->window = &window;
	this->engine = engine;
	ImGui::SFML::Init(window);
	//ImGuiIO& io = ImGui::GetIO();
	//font1 = io.Fonts->AddFontFromFileTTF("CyrilicOld.TTF", 60);
	//io.Fonts->Build();
}
