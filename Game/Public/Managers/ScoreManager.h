#pragma once
#include <functional>
#include <list>

class ScoreManager
{
public:

	// Singleton accessor
	static ScoreManager& GetInstance();

	// Score operations
	void IncrementP1();
	void IncrementP2();
	void ResetScores();

	int GetP1Score() const;
	int GetP2Score() const;

	// Win event (notifies who reached win score first). Argument: winner player index (1 or 2)
	using WinEventSignature = std::function<void(int)>;
	void ListenForWin(WinEventSignature& delegateToAdd);
	void StopListeningForWin(WinEventSignature& delegateToRemove);

private:

	ScoreManager() = default;
	ScoreManager(const ScoreManager&) = delete;
	ScoreManager& operator=(const ScoreManager&) = delete;

	void BroadcastWin(int player);

	int mPlayer1Score{ 0 };
	int mPlayer2Score{ 0 };
	const int mWinScore{ 5 };

	std::list<WinEventSignature> mWinEvents;
};

