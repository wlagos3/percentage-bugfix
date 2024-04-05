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
            if (m_fields->percentLabel == nullptr) {
                for (size_t i = 0; i < this->getChildrenCount(); i++) {
                    auto obj = this->getChildren()->objectAtIndex(i);
                    if (typeinfo_cast<CCLabelBMFont*>(obj) && m_fields->percentLabel == nullptr) {
                        auto labelTest = static_cast<CCLabelBMFont*>(obj);
                        auto labelEnding = labelTest->getString() + (strlen(labelTest->getString()) - 1);
                        if (strcmp(labelEnding, "%") == 0) {
                            m_fields->percentLabel = labelTest;;
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