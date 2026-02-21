#include "Game/Public/Actors/ScoreKeeper.h"
#include "Game/Public/Components/TextRenderComponent.h"

ScoreKeeper::ScoreKeeper(int fontId) : mFontId(fontId)
{
}

void ScoreKeeper::BeginPlay()
{
	// Register with tick/render systems via Actor::BeginPlay()
	Actor::BeginPlay();

	exColor White;
	White.mColor[0] = 255;
	White.mColor[1] = 255;
	White.mColor[2] = 255;
	White.mColor[3] = 255;

	// Top-center of an 800x600 window — adjust to your resolution
	exVector2 ScoreLocation;
	ScoreLocation.x = 370.0f;
	ScoreLocation.y = 20.0f;

	AddComponentOfType<TextRenderComponent>("0 - 0", 32.0f, mFontId, White, ScoreLocation);

	// Build the delegate and register it with ScoreSystem
	mScoreDelegate = [this](int p1Score, int p2Score)
		{
			OnScoreChanged(p1Score, p2Score);
		};

	SCORE_SYSTEM.ListenForScoreChange(mScoreDelegate);
}

void ScoreKeeper::Tick(const float DeltaSeconds)
{
	// Nothing to do — display updates are event-driven via OnScoreChanged
}

void ScoreKeeper::OnScoreChanged(int p1Score, int p2Score)
{
	if (std::shared_ptr<TextRenderComponent> TextComp = GetComponentOfType<TextRenderComponent>())
	{
		String ScoreText = std::to_string(p1Score) + " - " + std::to_string(p2Score);
		TextComp->UpdateText(ScoreText);
	}
}