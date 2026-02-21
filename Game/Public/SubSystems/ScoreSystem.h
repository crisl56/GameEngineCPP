#pragma once
#include <functional>
#include <list>
#include <memory>

#define SCORE_SYSTEM ScoreSystem::GetInstance()

// Fires when a score changes — passes (player1Score, player2Score)
using ScoreEventSignature = std::function<void(int, int)>;

class ScoreSystem
{
public:

	static ScoreSystem& GetInstance()
	{
		static ScoreSystem sInstance;
		return sInstance;
	}

	void SetP1Score(int newScore);
	void SetP2Score(int newScore);

	int GetP1Score() const;
	int GetP2Score() const;

	void ListenForScoreChange(ScoreEventSignature& delegateToAdd);
	void StopListeningForScoreChange(ScoreEventSignature& delegateToRemove);

private:

	ScoreSystem() = default;
	ScoreSystem(const ScoreSystem&) = delete;
	ScoreSystem& operator=(const ScoreSystem&) = delete;

	void BroadcastScoreChange();

	int mPlayer1Score = 0;
	int mPlayer2Score = 0;

	std::list<ScoreEventSignature> mScoreEvents;
};