#include "Game/Public/Managers/ScoreManager.h"
#include "Game/Public/SubSystems/ScoreSystem.h"
#include <algorithm>

ScoreManager& ScoreManager::GetInstance()
{
	static ScoreManager sInstance;
	return sInstance;
}

void ScoreManager::IncrementP1()
{
	mPlayer1Score = std::max(0, mPlayer1Score + 1);

	// Update global ScoreSystem so ScoreKeeper UI updates
	SCORE_SYSTEM.SetP1Score(mPlayer1Score);

	// Check win
	if (mPlayer1Score >= mWinScore)
	{
		BroadcastWin(1);
	}
}

void ScoreManager::IncrementP2()
{

	mPlayer2Score = std::max(0, mPlayer2Score + 1);
	// Update global ScoreSystem so ScoreKeeper UI updates
	SCORE_SYSTEM.SetP2Score(mPlayer2Score);

	// Check win
	if (mPlayer2Score >= mWinScore)
	{
		BroadcastWin(2);
	}
}

void ScoreManager::ResetScores()
{
	mPlayer1Score = 0;
	mPlayer2Score = 0;

	// Reset scores
	SCORE_SYSTEM.SetP1Score(mPlayer1Score);
	SCORE_SYSTEM.SetP2Score(mPlayer2Score);
}

int ScoreManager::GetP1Score() const
{
	return mPlayer1Score;
}

int ScoreManager::GetP2Score() const
{
	return mPlayer2Score;
}

void ScoreManager::ListenForWin(WinEventSignature& delegateToAdd)
{
	mWinEvents.emplace_back(delegateToAdd);
}

void ScoreManager::StopListeningForWin(WinEventSignature& delegateToRemove)
{
	mWinEvents.remove_if(
		[&delegateToRemove](const WinEventSignature& Event) {
			return &Event == &delegateToRemove;
		});
}

void ScoreManager::BroadcastWin(int player)
{
	for (WinEventSignature& Event : mWinEvents)
	{
		Event(player);
	}
}
