#include "Game/Public/Components/TextRenderComponent.h"
#include "Engine/Public/EngineInterface.h"


void TextRenderComponent::Render(exEngineInterface* EngineInterface)
{
	if (EngineInterface) {
		if (!mOwner.expired()) {
			EngineInterface->DrawText(mFontId, mLocation, mText.data(), mRenderColor, 5);
		}
	}
}

void TextRenderComponent::UpdateText(String newText) 
{
	mText = newText;
}

TextRenderComponent::TextRenderComponent(std::weak_ptr<Actor> owner, String text, float size, int fontId, exColor color, exVector2 location) :
	RenderComponent(owner, color), mText(text), mSize(size), mFontId(fontId), mLocation(location)
{
}
