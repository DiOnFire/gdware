#include "MenuLayer.h"

bool __fastcall MenuLayer::hook(CCLayer* self) {
	bool result = MenuLayer::init(self);
	auto director = CCDirector::sharedDirector();
	auto size = director->getWinSize();

	auto watermark = CCLabelBMFont::create("GDWare made by DiOnFire", "bigFont.fnt");
	watermark->setScale(0.5F);

	watermark->setPositionX(5);
	watermark->setPositionY(5);

	auto menu = CCMenu::create();
	menu->setPosition({ size.width / 2, 10 });
	menu->addChild(watermark);

	self->addChild(menu);

	return result;
}