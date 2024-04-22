
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>

#include <iomanip>
#include <ios>
#include <sstream>

using namespace geode::prelude;

class $modify(PlayLayer) {
    CCLabelBMFont* percentLabel;
    CCSprite* progressSprite;
    CCLabelBMFont* fromRunLabel;
    bool useOldLogic = false;
    bool useDecimals = GameManager::get()->getGameVariable("0126");
    void updateProgressbar() {
        PlayLayer::updateProgressbar();
        if (!m_level->isPlatformer()){
            if (m_fields->percentLabel == nullptr) {
                m_fields->percentLabel = static_cast<CCLabelBMFont*>(this->getChildByID("percentage-label"));
            } else if (m_fields->progressSprite == nullptr){
                CCSprite* progressSprite = static_cast<CCSprite*>(static_cast<CCSprite*>(this->getChildByID("progress-bar")->getChildren()->objectAtIndex(0)));
                m_fields->progressSprite = progressSprite;
                static_cast<CCNode*>(progressSprite)->setID("progress-bar-indicator");
            } else if (fromRunLabel == nullptr) {
                for (int i = 0; i < this->getChildrenCount(); i++) {
                        if (CCLabelBMFont* object = typeinfo_cast<CCLabelBMFont*>(this->getChildren()->objectAtIndex(i))) {
                            if (strcmp(&object->getString()[(strlen(object->getString()) - 1)], "%") == 0 && object != percentLabel) {
                                m_fields->fromRunLabel = object;
                                static_cast<CCNode*>(object)->setID("run-info-percent-label");
                                break;
                            }
                        }
                    }
            } else {
                if (!Mod::get()->getSettingValue<bool>("force-enable") && m_player1->getPositionX() > 0 && getCurrentPercent() == 0 && m_fields->useOldLogic == false){
                    m_fields->useOldLogic = true;
                }
                if (Mod::get()->getSettingValue<bool>("force-enable") || (m_fields->useOldLogic)){
                    float percent = (m_player1->getPositionX() / m_endPortal->getPositionX()) * 100.0;
                    std::ostringstream s;
                    s << std::fixed;
                    s << std::setprecision(m_fields->useDecimals ? 2 : 0);
                    s << percent;	
                    const char* percentStr = s.str().append("%").c_str();	
                    m_fields->percentLabel->setString(percentStr);
                    m_fields->progressSprite->setTextureRect(CCRect(0,0,(m_progressBar->getTextureRect().getMaxX() - 5) * (percent / 100), m_progressBar->getTextureRect().getMaxY() / 2));

                    //support for Run Info
                    if(fromRunLabel != nullptr){
                        std::string fromStr = "From ";
                        fromRunLabel->setString(fromStr.append(percentStr).c_str());
                    }
                }
            }
        }
    }
};