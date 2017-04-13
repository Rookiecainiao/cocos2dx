//
//  Qshadow.cpp
//  test2.3
//
//  Created by yaofuyu on 17/4/13.
//
//

#include "Qshadow.hpp"
#include <iostream>
using namespace std;
Scene* Qshadow::creatScene(){
    auto scene = Scene::create();
    auto layer = Qshadow::create();
    scene->addChild(layer);
    return scene;
}
bool Qshadow::init(){
    if (!Layer::init()) {
        return false;
    }
    
    schedule(schedule_selector(Qshadow::updateQshadow), 3.0);
    qshadow = Sprite::create("res/1.png");
    progress = ProgressTimer::create(qshadow);
    progress->setMidpoint(Vec2(1, 0));
    progress->setBarChangeRate(Vec2(0, 1));
    progress->setPosition(Vec2(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height/2));
    progress->setScale(3);
    progress->setType(kCCProgressTimerTypeBar);
    progress->setPercentage(0);
    percent=0;
    
    addChild(progress);
    
    
    return true;
}
void Qshadow::updateQshadow(float dt){
    
    log("QQQQQQQQ");
    progress->runAction(FadeIn::create(0.1));
    scheduleUpdate();
    
}
void Qshadow::update(float dt){
    percent++;
    if (percent>=100) {
        unscheduleUpdate();
        auto action = FadeOut::create(1);
        progress->runAction(action);
        percent=0;
    }else{
        progress->setPercentage(percent);
    }
    cout<<percent<<progress->getPosition().x<<endl;
}
