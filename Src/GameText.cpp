#include "GameText.h"
#include "Components/Components.h"
#include <string>

void setGameOverText(entt::registry& registry)
{
	auto mainTxtView = registry.view<GameOverMainText, Text>();
	for (auto e : mainTxtView)
	{
		auto& text = mainTxtView.get<Text>(e);
		text.setText("Game Over");
	}

	auto subTxtView = registry.view<GameOverSubText, Text>();
	for (auto e : subTxtView)
	{
		auto& text = subTxtView.get<Text>(e);
		text.setText("press enter to restart");
	}
}

void updateScoreText(entt::registry& registry)
{
	//score is equal to how many body parts the snake has gained (excludes head and tail)
	int score = registry.view<SnakeBody>().size();

	auto view = registry.view<ScoreText, Text>();
	for (auto e : view)
	{
		auto& text = view.get<Text>(e);
		text.setText(std::to_string(score));
	}
}
