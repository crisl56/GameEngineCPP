#pragma once
#include "Game/Public/Components/RenderComponent.h"
#include "Engine/Public/EngineTypes.h"

class exEngineInterface;

class TextRenderComponent : public RenderComponent
{
	friend class Actor;

public:

	TextRenderComponent() = delete;

	virtual void Render(exEngineInterface* EngineInterface) override;

	void UpdateText(String newText);

protected:

	TextRenderComponent(std::weak_ptr<Actor> owner, String text, float size, int fontId, exColor color, exVector2 location);

private:
	String mText;
	float mSize;
	int mFontId;
	exVector2 mLocation;
};
