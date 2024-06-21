
#include "Geode/binding_intel/GJGameLevel.hpp"
#include "Geode/binding_intel/PlayLayer.hpp"
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJGameLevel.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>

#include <iomanip>
#include <ios>
#include <sstream>

using namespace geode::prelude;


class $modify(GJGameLevel) {
   bool init(){
    bool result = GJGameLevel::init();
    GJGameLevel::m_levelLength = 0;
    std::cout << "test" << std::endl;
    return result;
   }
};