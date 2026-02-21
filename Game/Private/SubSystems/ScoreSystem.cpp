#include "Game/Public/SubSystems/ScoreSystem.h"

void ScoreSystem::SetP1Score(int newScore)
{
	mPlayer1Score = newScore;
	BroadcastScoreChange();
}

void ScoreSystem::SetP2Score(int newScore)
{
	mPlayer2Score = newScore;
	BroadcastScoreChange();
}

int ScoreSystem::GetP1Score() const
{
	return mPlayer1Score;
}

int ScoreSystem::GetP2Score() const
{
	return mPlayer2Score;
}

void ScoreSystem::ListenForScoreChange(ScoreEventSignature& delegateToAdd)
{
	mScoreEvents.emplace_back(delegateToAdd);
}

void ScoreSystem::StopListeningForScoreChange(ScoreEventSignature& delegateToRemove)
{
	mScoreEvents.remove_if(
		[&delegateToRemove](const ScoreEventSignature& Event) {
			return &Event == &delegateToRemove;
		});
}

void ScoreSystem::BroadcastScoreChange()
{
	for (ScoreEventSignature& Event : mScoreEvents) {
		Event(mPlayer1Score, mPlayer2Score);
	}
}
