#include "pch.h"
#include "PauseLayer.h"

bool noclipEnabled = false;
bool noAttemptsEnabled = false;

void PauseLayer::Callbacks::noclipButton(CCObject*) {
	noclipEnabled = !noclipEnabled;
	if (noclipEnabled) {
		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20A23C), "\xe9\x79\x06\x00\x00", 5, NULL);
	}
	else {
		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20A23C), "\x6a\x14\x8b\xcb\xff", 5, NULL);
	}
}

void PauseLayer::Callbacks::everythingHurtsButton(CCObject*) {
	noAttemptsEnabled = !noAttemptsEnabled;
	if (noAttemptsEnabled) {
		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20456D), "\xb8\x02\x00\x00\x00\x90", 6, NULL);
	}																									 
	else {																								 
		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20456D), "\xb8\x83\x00\x03\x00\x00", 6, NULL);
	}
}

auto noclipCallback(CCSprite* toggleOn, CCSprite* toggleOff) {
	return (noclipEnabled) ? toggleOn : toggleOff;
}

auto everythingHurtsCallback(CCSprite* toggleOn, CCSprite* toggleOff) {
	return (noAttemptsEnabled) ? toggleOn : toggleOff;
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

	noclipLabel->setPositionX(50);
	noclipLabel->setPositionY(5);
	noclipButton->setPositionX(5);
	noclipButton->setPositionY(5);

	auto menu = CCMenu::create();

	auto noAttemptsButton = gd::CCMenuItemToggler::create(everythingHurtsCallback(toggleOn, toggleOff), everythingHurtsCallback(toggleOff, toggleOn), self, menu_selector(PauseLayer::Callbacks::everythingHurtsButton));
	auto noAttemptsLabel = CCLabelBMFont::create("EverythingHurts", "bigFont.fnt");

	noAttemptsButton->setScale(0.5F);
	noAttemptsLabel->setScale(0.5F);

	noAttemptsLabel->setPositionX(95);
	noAttemptsLabel->setPositionY(30);
	noAttemptsButton->setPositionX(5);
	noAttemptsButton->setPositionY(30);

	menu->setPosition({ 10, 10 });
	menu->addChild(noclipLabel);
	menu->addChild(noclipButton);
	menu->addChild(noAttemptsLabel);
	menu->addChild(noAttemptsButton);

	self->addChild(menu);

	return result;
}