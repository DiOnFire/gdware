#include "Utils.h"
#include "PauseLayer.h"

bool noclipEnabled = false;
bool everythingHurtsEnabled = false;

void PauseLayer::Callbacks::noclipButton(CCObject*) {
	noclipEnabled = !noclipEnabled;
	if (noclipEnabled) {
		write_bytes(gd::base + 0x20A23C, { 0xE9, 0x79, 0x06, 0x00, 0x00 });
	}
	else {
		write_bytes(gd::base + 0x20A23C, { 0x6A, 0x14, 0x8B, 0xCB, 0xFF });
	}
}

void PauseLayer::Callbacks::everythingHurtsButton(CCObject*) {
	everythingHurtsEnabled = !everythingHurtsEnabled;
	if (everythingHurtsEnabled) {
		write_bytes(gd::base + 0x20456D, { 0xB8, 0x02, 0x00, 0x00, 0x00, 0x90 });
	}																									 
	else {			
		write_bytes(gd::base + 0x20456D, { 0xB8, 0x83, 0x00, 0x03, 0x00, 0x00 });
	}
}

auto checkbox_callback(bool value, CCSprite* on, CCSprite* off) {
	return (value) ? on : off;
}

bool __fastcall PauseLayer::hook(CCLayer* self) {
	bool result = PauseLayer::init(self);
	auto director = CCDirector::sharedDirector();
	auto size = director->getWinSize();

	auto toggleOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
	auto toggleOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");

	auto noclipButton = gd::CCMenuItemToggler::create(checkbox_callback(noclipEnabled, toggleOn, toggleOff), checkbox_callback(noclipEnabled, toggleOff, toggleOn), self, menu_selector(PauseLayer::Callbacks::noclipButton));
	auto noclipLabel = CCLabelBMFont::create("NoClip", "bigFont.fnt");

	noclipButton->setScale(0.5F);
	noclipLabel->setScale(0.5F);

	noclipLabel->setPositionX(50);
	noclipLabel->setPositionY(5);
	noclipButton->setPositionX(5);
	noclipButton->setPositionY(5);

	auto menu = CCMenu::create();

	auto everythingHurtsButton = gd::CCMenuItemToggler::create(checkbox_callback(everythingHurtsEnabled, toggleOn, toggleOff), checkbox_callback(everythingHurtsEnabled, toggleOff, toggleOn), self, menu_selector(PauseLayer::Callbacks::everythingHurtsButton));
	auto everythingHurtsLabel = CCLabelBMFont::create("EverythingHurts", "bigFont.fnt");

	everythingHurtsButton->setScale(0.5F);
	everythingHurtsLabel->setScale(0.5F);

	everythingHurtsLabel->setPositionX(95);
	everythingHurtsLabel->setPositionY(30);
	everythingHurtsButton->setPositionX(5);
	everythingHurtsButton->setPositionY(30);

	menu->setPosition({ 10, 10 });
	menu->addChild(noclipLabel);
	menu->addChild(noclipButton);
	menu->addChild(everythingHurtsLabel);
	menu->addChild(everythingHurtsButton);

	self->addChild(menu);

	return result;
}