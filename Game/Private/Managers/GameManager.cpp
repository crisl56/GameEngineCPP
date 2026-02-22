#include "Game/Public/Managers/GameManager.h"
#include "Game/Public/Managers/ScoreManager.h"
#include <algorithm>

GameManager& GameManager::GetInstance()
{
	static GameManager sInstance;
	return sInstance;
}

GameManager::GameManager()
{
	// Subscribe to score manager win events to transition to GameOver state
	ScoreManager::WinEventSignature winDel = [this](int winner) 
	{
		// When someone wins, move to GameOver and notify listeners
		mState = EState::GameOver;
		BroadcastGameOver(winner);

		// After game over, we want to reset round (ball/players) but keep scores so
		// players can see result. For a simple flow, move to Resetting and call ResetRound.
		mState = EState::Resetting;
		BroadcastReset();
		// leave state as GameOver until ResetGame or StartGame called
	};
	ScoreManager::GetInstance().ListenForWin(winDel);
}

GameManager::EState GameManager::GetState() const
{
	return mState;
}

void GameManager::StartGame()
{
	// Start playing: clear any Reset state
	mState = EState::Playing;
	// Ensure a fresh round start (reset ball & players positions)
	BroadcastReset();
}

void GameManager::ResetRound()
{
	// Reset ball & player positions / small state transition
	mState = EState::Resetting;
	BroadcastReset();
	// After reset, go back to playing
	mState = EState::Playing;
}

void GameManager::ResetGame()
{
	// Full reset: scores and round
	mState = EState::Resetting;
	// Reset scores first
	ScoreManager::GetInstance().ResetScores();
	// Reset positions
	BroadcastReset();
	mState = EState::Idle;
}

void GameManager::ListenForReset(ResetEventSignature& delegateToAdd)
{
	mResetEvents.emplace_back(delegateToAdd);
}

void GameManager::StopListeningForReset(ResetEventSignature& delegateToRemove)
{
	mResetEvents.remove_if(
		[&delegateToRemove](const ResetEventSignature& Event) {
			return &Event == &delegateToRemove;
		});
}

void GameManager::ListenForGameOver(GameOverSignature& delegateToAdd)
{
	mGameOverEvents.emplace_back(delegateToAdd);
}

void GameManager::StopListeningForGameOver(GameOverSignature& delegateToRemove)
{
	mGameOverEvents.remove_if(
		[&delegateToRemove](const GameOverSignature& Event) {
			return &Event == &delegateToRemove;
		});
}

void GameManager::BroadcastReset()
{
	for (ResetEventSignature& Event : mResetEvents)
	{
		Event();
	}
}

void GameManager::BroadcastGameOver(int winner)
{
	for (GameOverSignature& Event : mGameOverEvents)
	{
		Event(winner);
	}
}
