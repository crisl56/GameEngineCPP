#pragma once
#include <functional>
#include <list>

class GameManager
{
public:
	// Singleton accessor
	static GameManager& GetInstance();

	// Simple state machine
	enum class EState
	{
		Idle,
		Playing,
		Resetting,
		GameOver
	};

	EState GetState() const;

	// Start / reset controls
	void StartGame();
	void ResetRound();
	void ResetGame();

	// Reset event delegates: systems/components register callbacks to be reset
	using ResetEventSignature = std::function<void()>;
	void ListenForReset(ResetEventSignature& delegateToAdd);
	void StopListeningForReset(ResetEventSignature& delegateToRemove);

	// Optionally listen for game over events (who won)
	using GameOverSignature = std::function<void(int /*winner*/ )>;
	void ListenForGameOver(GameOverSignature& delegateToAdd);
	void StopListeningForGameOver(GameOverSignature& delegateToRemove);

private:

	GameManager();
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	void BroadcastReset();
	void BroadcastGameOver(int winner);

	EState mState{ EState::Idle };
	std::list<ResetEventSignature> mResetEvents;
	std::list<GameOverSignature> mGameOverEvents;
};

