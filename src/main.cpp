#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <fmt/format.h>
using namespace geode::prelude;

class $modify(PlayLayer) {
    CCLabelBMFont* percentLabel;
	CCSprite* progressSprite;
	bool useOldLogic = false;
    void updateProgressbar() {
        PlayLayer::updateProgressbar();
        if (!m_level->isPlatformer()){
		//Credit to FireMario211
		//https://github.com/FireMario211/Golden-Best/blob/fae9033b781e00ecb86557426fad8e68d19b4ba5/src/main.cpp#L10-L24
            if (m_fields->percentLabel == nullptr) {
                for (int i = 0; i < this->getChildrenCount(); i++) {
                    if (CCLabelBMFont* object = typeinfo_cast<CCLabelBMFont*>(this->getChildren()->objectAtIndex(i))) {
                        if (strcmp(&object->getString()[(strlen(object->getString()) - 1)], "%") == 0) {
                            m_fields->percentLabel = object;;
                            break;
                        }
                    }
                }
            } else if (m_fields->progressSprite == nullptr){
                m_fields->progressSprite = typeinfo_cast<CCSprite*>(m_progressBar->getChildren()->objectAtIndex(0));
        } else {
            float percent;			
            if (m_player1->getPositionX() > 0 && getCurrentPercent() == 0 && m_fields->useOldLogic == false){
                m_fields->useOldLogic = true;
            }
            if(m_fields->useOldLogic){
                percent = (m_player1->getPositionX() / m_endPortal->getPositionX()) * 100.0;
                m_fields->percentLabel->setString(fmt::to_string((int) percent).append("%").c_str());
                m_fields->progressSprite->setTextureRect(CCRect(0,0,(m_progressBar->getTextureRect().getMaxX() - 5) * (percent / 100), m_progressBar->getTextureRect().getMaxY() / 2));
                }
            }
        }
    }
};