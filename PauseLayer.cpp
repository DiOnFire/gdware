#include "pch.h"
#include "PauseLayer.h"

bool noclipEnabled = false;

void PauseLayer::Callbacks::noclipButton(CCObject*) {
	noclipEnabled = !noclipEnabled;
	if (noclipEnabled) {
		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20A23C), "\xe9\x79\x06\x00\x00", 5, NULL);
	}
	else {
		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20A23C), "\x6a\x14\x8b\xcb\xff", 5, NULL);
	}
}

auto noclipCallback(CCSprite* toggleOn, CCSprite* toggleOff) {
	return (noclipEnabled) ? toggleOn : toggleOff;
}

bool __fastcall PauseLayer::hook(CCLayer* self) {
	bool result = PauseLayer::init(self);
	auto director = CCDirector::sharedDirector();
	auto size = director->getWinSize();

	auto toggleOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
	auto toggleOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");

	auto noclipButton = gd::CCMenuItemToggler::create(noclipCallback(toggleOn, toggleOff), noclipCallback(toggleOff, toggleOn), self, menu_selector(PauseLayer::Callbacks::noclipButton));
	auto noclipLabel = CCLabelBMFont::create("NoClip", "bigFont.fnt");

	noclipButton->setScale(0.5F);
	noclipLabel->setScale(0.5F);

	noclipLabel->setPositionX(10);
	noclipLabel->setPositionY(50);
	noclipButton->setPositionX(5);
	noclipButton->setPositionY(5);

	auto menu = CCMenu::create();
	menu->setPosition({ 25, 25 });
	menu->addChild(noclipLabel);
	menu->addChild(noclipButton);

	self->addChild(menu);

	return result;
}