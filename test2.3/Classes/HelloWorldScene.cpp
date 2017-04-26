#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "iostream"
#include "ui/UIButton.h"
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/Document.h"
#include <stdlib.h>

using namespace std;
USING_NS_CC;
using namespace ui;
using namespace network;
using namespace rapidjson;


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    name_match = "非洲世界杯";
    name_teamA = "厄尔多瓜";
    teamA_yc = 0;
    teamA_rc = 0;
    teamA_yw = 0;
    teamA_jg = 0;
    teamA_wxjg = 0;
    teamA_qq = 0;
    teamA_sz = 0;
    teamA_sw = 0;
    teamA_jq = 0;
    name_teamB = "广州恒大";
    teamB_yc = 0;
    teamB_rc = 0;
    teamB_yw = 0;
    teamB_jg = 0;
    teamB_wxjg = 0;
    teamB_qq =0;
    teamB_sz = 0;
    teamB_sw = 0;
    teamB_jq = 0;
    
    
    match_timer_s = 0;
    match_timer_m = 0;
    schedule(schedule_selector(HelloWorld::update_timer),1);
    
    
    name_teamA = "厄尔多瓜 20岁以下";
    this->setCascadeOpacityEnabled(true);
    initUI();
   
    cc_state=0;
//    schedule(schedule_selector(HelloWorld::update_q), 0.5);
    return true;
}
void HelloWorld::update_timer(float dt){
//    cout<<"update_cc"<<endl;
    match_timer_s++;
    if (match_timer_s==60) {
        match_timer_m++;
        match_timer_s = 0;
    }
    string timer = String::createWithFormat("%02d:%02d",match_timer_m,match_timer_s)->getCString();
    match_timer->setString(timer);
}
//开局信息UI及出现特效
void HelloWorld::startUI(){
    startUInode = Node::create();
    startUInode->setPosition(Vec2::ZERO);
    auto lab_name = Label::createWithSystemFont("皇家马德里", "fonts/arial.ttf", 30);
    startUInode->addChild(lab_name,5);
    lab_name->setOpacity(0);
    lab_name->setPosition(Vec2(sprbg->getPosition().x,sprbg->getPosition().y));
    lab_name->setAnchorPoint(Vec2(0.5, 1));
//    lab1->runAction(Spawn::create(act1,act2, NULL));
    auto lab_time = Label::createWithSystemFont("开球", "fonts/arial.ttf", 26);
    lab_time->setPosition(Vec2(sprbg->getPosition().x-10, lab_name->getPosition().y-lab_name->getContentSize().height-50));
    lab_time->setAnchorPoint(Vec2(1, 1));
    lab_time->setColor(Color3B(204, 204, 204));
    
    addChild(lab_time,5);
    auto lab_timedate = Label::createWithSystemFont("18:30", "fonts/arial.ttf", 26);
    lab_timedate->setPosition(Vec2(sprbg->getPosition().x+10, lab_name->getPosition().y-lab_name->getContentSize().height-50));
    lab_timedate->setAnchorPoint(Vec2(0, 1));
    startUInode->addChild(lab_timedate,5);
    lab_timedate->setColor(Color3B(204, 204, 204));
    
    auto lab_teamA = Label::createWithSystemFont("皇家马德里A", "fonts/arial.ttf", 30);
    lab_teamA->setOpacity(0);
    startUInode->addChild(lab_teamA,5);
    lab_teamA->setPosition(Vec2(sprbg->getPosition().x-sprbg->getContentSize().width/2, sprbg->getPosition().y-sprbg->getContentSize().height/2));
    auto lab_teamB = Label::createWithSystemFont("皇家马德里B", "fonts/arial.ttf", 30);
    lab_teamB->setOpacity(0);
    startUInode->addChild(lab_teamB,5);
    lab_teamB->setPosition(Vec2(sprbg->getPosition().x+sprbg->getContentSize().width/2, sprbg->getPosition().y-sprbg->getContentSize().height/2));
    
    auto lab_weather = Label::createWithSystemFont("天气:良好", "fonts/arial.ttf", 26);
    lab_weather->setPosition(Vec2(sprbg->getPosition().x-20, sprbg->getPosition().y-sprbg->getContentSize().height+20));
    lab_weather->setAnchorPoint(Vec2(1, 0));
    startUInode->addChild(lab_weather,5);
    lab_weather->setColor(Color3B(204, 204, 204));
    
    auto lab_add = Label::createWithSystemFont("场地:良好", "fonts/arial.ttf", 26);
    lab_add->setPosition(Vec2(sprbg->getPosition().x+20, sprbg->getPosition().y-sprbg->getContentSize().height+20));
    lab_add->setAnchorPoint(Vec2(0, 0));
    lab_add->setColor(Color3B(204, 204, 204));
    startUInode->addChild(lab_add,5);
    
    auto act_fade = FadeTo::create(2, 255);
    auto act_fade1 = FadeTo::create(2, 255);
    auto act_move = MoveBy::create(2, Vec2(0, -20));
    auto act_moveA = MoveBy::create(2, Vec2(200, 0));
    auto act_moveB = MoveBy::create(2, Vec2(-200, 0));
    auto act1 = Spawn::create(act_fade,act_move, NULL);
    auto act2 = Spawn::create(act_fade1,act_moveA, NULL);
    auto act3 = Spawn::create(act_fade,act_moveB, NULL);
    auto act4 = TargetedAction::create(lab_name, act1);
    auto act5 = TargetedAction::create(lab_teamA, act2);
    auto act6 = TargetedAction::create(lab_teamB, act3);
    auto act7 = Spawn::create(act5,act6, NULL);
    //动作机制调用函数！！
    CallFuncN * callfunc = CallFuncN::create(CC_CALLBACK_1(HelloWorld::callback1, this));
    
    lab_teamB->runAction(Sequence::create(act4,act7,DelayTime::create(2),callfunc, NULL));
//同一个动作，两个node同时执行时，最后一个node执行，前面的node都不执行，即spawn方法如果有多个node执行，只显示最后执行的node的效果。
    
    addChild(startUInode,5);
}
//主状态实时监测
void HelloWorld::callback1(Node* sender){
    cout<<"this is callback2"<<endl;
//lambada公式
//    auto pri = [](){cout<<"lambada"<<endl;};
    startUInode->removeFromParent();
}
void HelloWorld::update(float time){
    if (vec.size()) {
        vec.pop_back();
        footballCaseType(vec.end()->caseStats);
    }else{
        unschedule(schedule_selector(HelloWorld::update));
    }
    
}
//UI布局初始化
void HelloWorld::initUI(){
    
    lab9_pro_percent = (float)teamB_qq/((float)teamA_qq+(float)teamB_qq)*100;
    lab8_pro_percent = (float)teamB_jg/((float)teamA_jg+(float)teamB_jg)*100;
    lab7_pro_percent = (float)teamB_wxjg/((float)teamA_wxjg+(float)teamB_wxjg)*100;
    lab_sz_pro_percent =(float)teamB_sz/((float)teamA_sz+(float)teamB_sz)*100;
    lab_sw_pro_percent = (float)teamB_sw/((float)teamA_sw+(float)teamB_sw)*100;
    if (teamB_jg == teamA_jg) {
        lab8_pro_percent = 50;
    }
    if (teamB_wxjg == teamA_wxjg) {
        lab7_pro_percent = 50;
    }
    if (teamB_qq == teamA_qq) {
        lab9_pro_percent = 50;
    }
    if (teamB_sz == teamA_sz) {
        lab_sz_pro_percent = 50;
    }
    if (teamB_sw == teamA_sw) {
        lab_sw_pro_percent = 50;
    }
    cout<<"比例"<<lab9_pro_percent<<"  "<<teamB_jg<<teamA_jg<<lab8_pro_percent<<"  "<<lab7_pro_percent<<"  "<<lab_sz_pro_percent<<"  "<<lab_sw_pro_percent<<endl;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    android_height = visibleSize.height;
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    visibleSize.height -= 100;
    auto titlesp = Sprite::create("res/titlesp.png");
    titlesp->setPosition(Vec2(visibleSize.width/2, android_height));
    titlesp->setAnchorPoint(Vec2(0.5, 1));
    auto titlesize = titlesp->getContentSize();
    titlesp->setScale(visibleSize.width/titlesize.width+1, 50/titlesize.height);
    addChild(titlesp,2);
    
    auto labtitle = Label::createWithSystemFont("竞猜", "fonts/arial.ttf", 32);
    labtitle->setPosition(Vec2(visibleSize.width/2, android_height-25));
    labtitle->setAnchorPoint(Vec2(0.5, 0.5));
    addChild(labtitle,3);
    auto btn = Button::create("res/u759.png");
    btn->setPosition(Vec2(20, android_height));
    btn->setAnchorPoint(Vec2(0.5,1));
    //    btn->setScale(4);
    btn->addClickEventListener(CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    addChild(btn,2);
//#endif
//    auto button_callback = Button::create("res/u759.png");
//    button_callback->setPosition(Vec2(380, 400));
//    addChild(button_callback,2);
//    button_callback->addClickEventListener(CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    auto bg = Sprite::create("res/baiju.png");
    bg->setPosition(Vec2(visibleSize.width/2, visibleSize.height));
    bg->setAnchorPoint(Vec2(0.5, 1));
    bg->setColor(Color3B::BLACK);
    auto y = bg->getContentSize().height;
    bg->setScale(400, visibleSize.height/2/y);
    addChild(bg,1);
    
    
    sprbg = Sprite::create("res/donghuabg.png");
    sprbg->setPosition(Vec2(visibleSize.width/2, visibleSize.height-80));
    sprbg->setAnchorPoint(Vec2(0.5, 1));
    addChild(sprbg,2);
    
    string timer = String::createWithFormat("%02d:%02d",match_timer_m,match_timer_s)->getCString();
    match_timer = Label::createWithSystemFont(timer, "fonts/arial.ttf", 24);
    match_timer->setPosition(sprbg->getPosition());
    addChild(match_timer,5);
    
    football = Sprite::create("res/football.png");
    football->setPosition(Vec2(visibleSize.width/2, visibleSize.height-200));
    football->setVisible(false);
    addChild(football,4);
    auto ballaction = RotateBy::create(2, 180);
    auto ballaction2 = MoveBy::create(4, Vec2(100, 100));
    //    football->runAction(Spawn::create(ballaction, NULL));
    auto action1=Spawn::create(ballaction,ballaction2, NULL);
    auto action2=Spawn::create(ballaction,ballaction2->reverse(), NULL);
//    football->runAction(RepeatForever::create(Sequence::create(action1,action2, NULL)));
    
    auto ballposition = football->getPosition();
   
    
    Jqshadow = Sprite::create("res/1.png");
    progress1 = ProgressTimer::create(Jqshadow);
    progress1->setPosition(Vec2(0, 700));
    progress1->setAnchorPoint(Vec2(0.5, 0));
    progress1->setOpacity(200);
    progress1->setMidpoint(Vec2(1, 0));//水平方向（1，y）表示从右向左，（0.y）表示从左向右
    progress1->setBarChangeRate(Vec2(0, 1));//纵向 (0,1)表示从下向上， （1，0）表示从上向下
    progress1->setType(kCCProgressTimerTypeBar);
    progress1->setPercentage(0);
    progress1->setRotation(150);
    
    sp = Sprite::create("res/jingong.png");
    sp->setOpacity(100);
    sp_wxjg = Sprite::create("res/weixianjingong.png");
    sp_wxjg->setOpacity(100);
    sp_kq = Sprite::create("res/kqyinying.png");
    progress = ProgressTimer::create(sp_kq);
//    progress->setScale(2.75);
    progress->setPercentage(0);
    progress->setType(kCCProgressTimerTypeBar);
    progress->setOpacity(100);
    progress->setPosition(Vec2(0, sprbg->getPosition().y));
    progress->setAnchorPoint(Vec2(0, 1));
    progress->setMidpoint(Vec2(0, 0));//水平方向（1，y）表示从右向左，（0.y）表示从左向右
    progress->setBarChangeRate(Vec2(1, 0));//纵向
    progress->setVisible(false);
    progress1->setVisible(false);
    addChild(progress1,3);
    addChild(progress,3);
//    scheduleUpdate();
    
    labUI();
}
//角球阴影三段技
void HelloWorld::update_dianqiu(float dt){
    if (percent_jiaoqiu>=300) {
        percent_jiaoqiu = 0;
    }
    percent_jiaoqiu+=5;
    progress1->setPercentage(percent_jiaoqiu);
}
//角球方法，点球，角球，球门球，掷界外球
void HelloWorld::jiaoqiu(int _state){
    this->removeAllChildren();
    this->unschedule(schedule_selector(HelloWorld::update_q));
    this->unschedule(schedule_selector(HelloWorld::update_dianqiu));
    initUI();
    schedule(schedule_selector(HelloWorld::update_dianqiu));
    progress1->setVisible(true);
    football->setVisible(true);
    auto sprbgvisible = sprbg->getContentSize();
    auto sprbgorigin = sprbg->getPosition();
    percent_jiaoqiu=100;
    switch (_state) {
        case 1:
            progress1->setPosition(Vec2(sprbgvisible.width, sprbgorigin.y));
            progress1->setRotation(-150);
            cout<<"左上"<<endl;
            lab_state(1, "角球");
            lab_move(Vec2(sprbgorigin.x+sprbgvisible.width/4, sprbgorigin.y-sprbgvisible.height/4));
            break;
        case 2:
            progress1->setPosition(Vec2(sprbgorigin.x-sprbgvisible.width/2, sprbgorigin.y-sprbgvisible.height));
            progress1->setRotation(30);
            cout<<"左下"<<endl;
            lab_state(1, "角球");
            lab_move(Vec2(sprbgorigin.x-sprbgvisible.width/4, sprbgorigin.y-sprbgvisible.height/4*3));
            break;
        case 3:
            progress1->setPosition(Vec2(sprbgorigin.x+sprbgvisible.width/2, sprbgorigin.y));
            progress1->setRotation(-150);
            cout<<"右上"<<endl;
            lab_state(2, "角球");
            lab_move(Vec2(sprbgorigin.x+sprbgvisible.width/4, sprbgorigin.y-sprbgvisible.height/4));
            break;
        case 4:
            progress1->setPosition(Vec2(sprbgorigin.x+sprbgvisible.width/2, sprbgorigin.y-sprbgvisible.height));
            progress1->setRotation(-30);
            cout<<"右下"<<endl;
            lab_state(2, "角球");
            lab_move(Vec2(sprbgorigin.x+sprbgvisible.width/4, sprbgorigin.y-sprbgvisible.height/4*3));
            break;
        case 5:
            progress1->setPosition(Vec2(sprbgorigin.x-sprbgvisible.width/2+50, sprbgorigin.y-sprbgvisible.height/2));
            progress1->setRotation(90);
            cout<<"主球门球"<<endl;
            lab_state(1, "球门球");
            lab_move(Vec2(sprbgorigin.x-sprbgvisible.width/4, sprbgorigin.y-sprbgvisible.height/4));
            break;
        case 6:
            progress1->setPosition(Vec2(sprbgorigin.x+sprbgvisible.width/2-50, sprbgorigin.y-sprbgvisible.height/2));
            progress1->setRotation(-90);
            cout<<"客球门球"<<endl;
            lab_state(2, "球门球");
            lab_move(Vec2(sprbgorigin.x+sprbgvisible.width/4, sprbgorigin.y-sprbgvisible.height/4));
            break;
        case 7:
            progress1->setPosition(Vec2(sprbgorigin.x, sprbgorigin.y-sprbgvisible.height/2));
            progress1->setRotation(90);
            cout<<"主任意球"<<endl;
            lab_state(1,"任意球");
            lab_move(Vec2(sprbgorigin.x-20, sprbgorigin.y-sprbgvisible.height/2));
            break;
        case 8:
            progress1->setPosition(Vec2(sprbgorigin.x, sprbgorigin.y-sprbgvisible.height/2));
            progress1->setRotation(-90);
            cout<<"客任意球"<<endl;
            lab_state(2,"任意球");
            lab_move(Vec2(sprbgorigin.x+20, sprbgorigin.y-sprbgvisible.height/2));
            break;
        case 9:
            progress1->setPosition(Vec2(sprbgorigin.x+140, sprbgorigin.y-sprbgvisible.height/2));
            progress1->setRotation(90);
            lab_state(1,"危险任意球");
            lab_move(Vec2(sprbgorigin.x+100, sprbgorigin.y-sprbgvisible.height/2));
            cout<<"主危险任意球"<<endl;
            break;
        case 10:
            progress1->setPosition(Vec2(sprbgorigin.x-140, sprbgorigin.y-sprbgvisible.height/2));
            progress1->setRotation(-90);
            cout<<"客危险任意球"<<endl;
            lab_state(2,"危险任意球");
            lab_move(Vec2(sprbgorigin.x-100, sprbgorigin.y-sprbgvisible.height/2));
            break;
        case 11:
            cout<<"主掷界外球"<<endl;
            break;
        case 12:
            cout<<"客掷界外球"<<endl;
            break;
        default:
            break;
    }
    football->stopAllActions();
    football->setPosition(progress1->getPosition());
}
//控球状态的阴影特效变换
void HelloWorld::kongqiu(int _i){
    percent_kongqiu=100;
    this->removeAllChildren();
    this->unschedule(schedule_selector(HelloWorld::update_q));
    this->unschedule(schedule_selector(HelloWorld::update_dianqiu));
    initUI();
    schedule(schedule_selector(HelloWorld::update_q));
    progress->setVisible(true);
    switch (_i) {
        case 1:
            progress->setSprite(sp_kq);
//            percent = 100;
            progress->setRotation(0);
            progress->setPosition(Vec2(sprbg->getPosition().x-sprbg->getContentSize().width/2, sprbg->getPosition().y));
            progress->setAnchorPoint(Vec2(0, 1));
            progress->setMidpoint(Vec2(0, 0));//水平方向（1，y）表示从右向左，（0.y）表示从左向右
            progress->setBarChangeRate(Vec2(1, 0));//纵向
            cout<<"主控球"<<endl;
            lab_move(Vec2(sprbg->getPosition().x-50, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            lab_state(1,"控球");
            break;
        case 2:
            progress->setSprite(sp);
//            percent = 100;
            progress->setRotation(0);
            progress->setPosition(Vec2(sprbg->getPosition().x-sprbg->getContentSize().width/2, sprbg->getPosition().y));
            progress->setAnchorPoint(Vec2(0, 1));
            progress->setMidpoint(Vec2(0, 0));//水平方向（1，y）表示从右向左，（0.y）表示从左向右
            progress->setBarChangeRate(Vec2(1, 0));//纵向
            cout<<"主进攻"<<endl;
            lab_move(Vec2(sprbg->getPosition().x+sprbg->getContentSize().width/8, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            lab_state(1,"进攻");
            break;
        case 3:
            progress->setSprite(sp_wxjg);
//            percent = 100;
            progress->setRotation(0);
            progress->setPosition(Vec2(sprbg->getPosition().x-sprbg->getContentSize().width/2, sprbg->getPosition().y));
            progress->setAnchorPoint(Vec2(0, 1));
            progress->setMidpoint(Vec2(0, 0));//水平方向（1，y）表示从右向左，（0.y）表示从左向右
            progress->setBarChangeRate(Vec2(1, 0));//纵向
            cout<<"主危险进攻"<<endl;
            lab_move(Vec2(sprbg->getPosition().x+sprbg->getContentSize().width/4, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            lab_state(1,"危险进攻");
            break;
        case 4:
//            percent = 100;
            progress->setSprite(sp_kq);
            progress->setPosition(Vec2(sprbg->getPosition().x+sprbg->getContentSize().width/2, sprbg->getPosition().y));
            progress->setAnchorPoint(Vec2(0, 0));
            progress->setRotation(180);
            cout<<"客控球"<<endl;
            lab_move(Vec2(sprbg->getPosition().x+50, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            lab_state(2,"控球");
            break;
        case 5:
//            percent = 100;
            progress->setSprite(sp);
            progress->setPosition(Vec2(sprbg->getPosition().x+sprbg->getContentSize().width/2, sprbg->getPosition().y));
            progress->setAnchorPoint(Vec2(0, 0));
            progress->setRotation(180);
            lab_move(Vec2(sprbg->getPosition().x-sprbg->getContentSize().width/8, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            lab_state(2,"进攻");
            cout<<"客进攻"<<endl;
            break;
        case 6:
//            percent = 100;
            progress->setSprite(sp_wxjg);
            progress->setPosition(Vec2(sprbg->getPosition().x+sprbg->getContentSize().width/2, sprbg->getPosition().y));
            progress->setAnchorPoint(Vec2(0, 0));
            progress->setRotation(180);
            lab_move(Vec2(sprbg->getPosition().x-sprbg->getContentSize().width/4, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            cout<<"客危险进攻"<<endl;
            lab_state(2,"危险进攻");
            break;
            
        default:
            break;
    }
    schedule(schedule_selector(HelloWorld::update_dianqiu));
}
//labUI的显示
void HelloWorld::labUI()
{
    //主队名前的红矩形
    auto lab_team_zc_bj = Sprite::create("res/hongT.png");
    lab_team_zc_bj->setPosition(Vec2(origin.x+70+lab_team_zc_bj->getContentSize().width/2, visibleSize.height-40));
    addChild(lab_team_zc_bj,4);
    //客队名前的白矩形
    auto lab_team_kc_hj = Sprite::create("res/baiT.png");
    lab_team_kc_hj->setPosition(Vec2(visibleSize.width-70-lab_team_kc_hj->getContentSize().width/2, lab_team_zc_bj->getPosition().y));
    addChild(lab_team_kc_hj,4);
    //主场进球
    auto lab1_sp = Sprite::create("res/huiju.png");
    lab1_sp->setPosition(Vec2(visibleSize.width/2-5-lab1_sp->getContentSize().width/2, lab_team_kc_hj->getPosition().y));
    addChild(lab1_sp,4);
//    string lab1_jq = to_string(teamA_jq);
    string lab1_jq = String::createWithFormat("%d",teamA_jq)->getCString();
    
//    char* lab1_jq;
//    sprintf(lab1_jq, "%d",teamA_jq);
    auto lab1 = Label::createWithSystemFont(lab1_jq, "fonts/arial.ttf", 36 );
    lab1->setPosition(lab1_sp->getPosition());
    lab1->setColor(Color3B(250, 206, 0));
    addChild(lab1,4);
    //客场进球
    auto lab2_sp = Sprite::create("res/huiju.png");
    lab2_sp->setPosition(Vec2(visibleSize.width/2+5+lab2_sp->getContentSize().width/2, lab_team_kc_hj->getPosition().y));
    addChild(lab2_sp,4);
//    string lab2_jq = to_string(teamB_jq);
    string lab2_jq = String::createWithFormat("%d",teamB_jq)->getCString();
//    char* lab2_jq;
//    sprintf(lab2_jq, "%d",teamB_jq);
    auto lab2 = Label::createWithSystemFont(lab2_jq, "fonts/arial.ttf", 36 );
    lab2->setPosition(lab2_sp->getPosition());
    lab2->setColor(Color3B(250, 206, 0));
    addChild(lab2,4);
    
    auto lab4 = Label::createWithSystemFont(name_teamA, "fonts/arial.ttf", 30 );
    lab4->setPosition(Vec2(lab_team_zc_bj->getPosition().x+lab_team_zc_bj->getContentSize().width/2+16+lab4->getContentSize().width/2, lab_team_zc_bj->getPosition().y));
    addChild(lab4,4);
    auto lab5 = Label::createWithSystemFont(name_teamB, "fonts/arial.ttf", 30 );
    lab5->setPosition(Vec2(lab_team_kc_hj->getPosition().x-lab_team_kc_hj->getContentSize().width/2-16-lab5->getContentSize().width/2, lab_team_kc_hj->getPosition().y));
    addChild(lab5,4);
    
//***************************圈显百分比*************************
    auto lab7 = Label::createWithSystemFont("危险进攻", "fonts/arial.ttf", 28 );
    lab7->setPosition(Vec2(visibleSize.width/2, sprbg->getPosition().y-30-sprbg->getContentSize().height));
    lab7->setAnchorPoint(Vec2(0.5, 1));
    lab7->setColor(Color3B::WHITE);
    addChild(lab7,4);
    auto lab7_sp1 = Sprite::create("res/quan.png");
    lab7_sp1->setPosition(Vec2(visibleSize.width/2, lab7->getPosition().y-lab7->getContentSize().height-20-lab7_sp1->getContentSize().height/2));
    auto lab7_sp2 = Sprite::create("res/quan2.png");
    auto lab7_pro = ProgressTimer::create(lab7_sp2);
    lab7_pro->setPosition(Vec2(visibleSize.width/2, lab7->getPosition().y-lab7->getContentSize().height-20-lab7_sp1->getContentSize().height/2));
//****比例****
    lab7_pro->setPercentage(lab7_pro_percent);
//*****类型转换****
//    string lab7_score1_teamA = to_string(teamA_wxjg);
//    string lab7_score2_teamB = to_string(teamB_wxjg);
    string lab7_score1_teamA = String::createWithFormat("%d",teamA_wxjg)->getCString();
    string lab7_score2_teamB = String::createWithFormat("%d",teamB_wxjg)->getCString();
//    char* lab7_score1_teamA;
//    sprintf(lab7_score1_teamA, "%d",teamA_wxjg);
//    char* lab7_score2_teamB;
//    sprintf(lab7_score2_teamB, "%d",teamB_wxjg);
//*****类型转换****
    auto lab7_score1 = Label::createWithSystemFont(lab7_score1_teamA, "fonts/arial.ttf", 28);
    auto lab7_score2 = Label::createWithSystemFont(lab7_score2_teamB, "fonts/arial.ttf", 28);
    lab7_score1->setPosition(Vec2(visibleSize.width/2-10-lab7_sp1->getContentSize().width/2-lab7_score1->getContentSize().width/2, lab7->getPosition().y-lab7->getContentSize().height-20-lab7_sp1->getContentSize().height/2));
    lab7_score2->setPosition(Vec2(visibleSize.width/2+10+lab7_sp1->getContentSize().width/2+lab7_score2->getContentSize().width/2, lab7->getPosition().y-lab7->getContentSize().height-20-lab7_sp1->getContentSize().height/2));
    addChild(lab7_score2,5);
    addChild(lab7_score1,5);
    addChild(lab7_sp1,5);
    addChild(lab7_pro,5);
    
//*****类型转换****
//    String* s = String::createWithFormat("%d",teamA_jq);
    cout<<"lab8_score1_teamA的值为"<<teamA_jg<<endl;
    string lab8_score1_teamA = String::createWithFormat("%d",teamA_jg)->getCString();
    string lab8_score2_teamB = String::createWithFormat("%d",teamB_jg)->getCString();
//    char* lab8_score1_teamA;
//    sprintf(lab8_score1_teamA, "%d",teamA_jg);
//    char* lab8_score2_teamB;
//    sprintf(lab8_score2_teamB, "%d",teamB_jg);
//*****类型转换****
    cout<<"lab8_score1_teamA的值为"<<lab8_score1_teamA<<" "<<lab8_score2_teamB<<endl;
    auto lab8_score1 = Label::createWithSystemFont(lab8_score1_teamA, "fonts/arial.ttf", 28);
    lab8_score1->setPosition(Vec2(origin.x+30+lab8_score1->getContentSize().width/2, lab7_score1->getPosition().y));
    auto lab8_sp1 = Sprite::create("res/quan.png");
    lab8_sp1->setPosition(Vec2(lab8_score1->getPosition().x+lab8_score1->getContentSize().width/2+10+lab8_sp1->getContentSize().width/2, lab8_score1->getPosition().y));
    auto lab8_sp2 = Sprite::create("res/quan2.png");
    auto lab8_pro = ProgressTimer::create(lab7_sp2);
    lab8_pro->setPosition(Vec2(lab8_score1->getPosition().x+lab8_score1->getContentSize().width/2+10+lab8_sp1->getContentSize().width/2, lab8_score1->getPosition().y));
//****比例****
    lab8_pro->setPercentage(lab8_pro_percent);
    auto lab8_score2 = Label::createWithSystemFont(lab8_score2_teamB, "fonts/arial.ttf", 28);
    lab8_score2->setPosition(Vec2(lab8_sp1->getPosition().x+lab8_sp1->getContentSize().width/2+10+lab8_score2->getContentSize().width/2, lab8_sp1->getPosition().y));
    auto lab8 = Label::createWithSystemFont("进攻", "fonts/arial.ttf", 28 );
    lab8->setPosition(Vec2(lab8_sp1->getPosition().x, lab7->getPosition().y));
    lab8->setAnchorPoint(Vec2(0.5, 1));
    lab8->setColor(Color3B::WHITE);
    addChild(lab8,4);
    addChild(lab8_score2,5);
    addChild(lab8_score1,5);
    addChild(lab8_sp1,5);
    addChild(lab8_pro,5);
    
//*****类型转换****
//    string lab9_score1_teamA = to_string(teamA_qq);
//    string lab9_score2_teamB = to_string(teamB_qq);
    string lab9_score1_teamA = String::createWithFormat("%d",teamA_qq)->getCString();
    string lab9_score2_teamB = String::createWithFormat("%d",teamB_qq)->getCString();
//    char* lab9_score1_teamA;
//    sprintf(lab9_score1_teamA, "%d",teamA_qq);
//    char* lab9_score2_teamB;
//    sprintf(lab9_score2_teamB, "%d",teamB_qq);
//*****类型转换****
    auto lab9_score2 = Label::createWithSystemFont(lab9_score2_teamB, "fonts/arial.ttf", 28);
    lab9_score2->setPosition(Vec2(visibleSize.width-30-lab9_score2->getContentSize().width/2, lab7_score1->getPosition().y));
    auto lab9_sp1 = Sprite::create("res/quan.png");
    lab9_sp1->setPosition(Vec2(lab9_score2->getPosition().x-lab9_score2->getContentSize().width/2-10-lab9_sp1->getContentSize().width/2, lab9_score2->getPosition().y));
    auto lab9_sp2 = Sprite::create("res/quan2.png");
    auto lab9_pro = ProgressTimer::create(lab7_sp2);
    lab9_pro->setPosition(Vec2(lab9_score2->getPosition().x-lab9_score2->getContentSize().width/2-10-lab9_sp1->getContentSize().width/2, lab9_score2->getPosition().y));
//****比例****
    lab9_pro->setPercentage(lab9_pro_percent);
    
    auto lab9_score1 = Label::createWithSystemFont(lab9_score1_teamA, "fonts/arial.ttf", 28);
    lab9_score1->setPosition(Vec2(lab9_sp1->getPosition().x-lab9_sp1->getContentSize().width/2-10-lab9_score2->getContentSize().width/2, lab9_sp1->getPosition().y));
    auto lab9 = Label::createWithSystemFont("球权%", "fonts/arial.ttf", 28 );
    lab9->setPosition(Vec2(lab9_sp1->getPosition().x, lab7->getPosition().y));
    lab9->setAnchorPoint(Vec2(0.5, 1));
    lab9->setColor(Color3B::WHITE);
    addChild(lab9,4);
    addChild(lab9_score2,5);
    addChild(lab9_score1,5);
    addChild(lab9_sp1,5);
    addChild(lab9_pro,5);
    
//***************************圈显百分比*************************
//***************************场上数据显示*************************
    //*****类型转换****
//    string lab_sz_score1_teamA = to_string(teamA_sz);
//    string lab_sz_score2_teamB = to_string(teamB_sz);
    string lab_sz_score1_teamA = String::createWithFormat("%d",teamA_sz)->getCString();
    string lab_sz_score2_teamB = String::createWithFormat("%d",teamB_sz)->getCString();
    
//    char* lab_sz_score1_teamA;
//    sprintf(lab_sz_score1_teamA, "%d",teamA_sz);
//    char* lab_sz_score2_teamB;
//    sprintf(lab_sz_score2_teamB, "%d",teamB_sz);
    //*****类型转换****
    auto lab_sz = Label::createWithSystemFont("射正球门", "fonts/arial.ttf", 22);
    lab_sz->setPosition(Vec2(lab7_sp1->getPosition().x, lab7_sp1->getPosition().y-lab7_sp1->getContentSize().height/2-30-lab_sz->getContentSize().height/2));
    addChild(lab_sz,5);
    auto lab_sz_sp1 = Sprite::create("res/hongju.png");
    lab_sz_sp1->setPosition(Vec2(lab_sz->getPosition().x, lab_sz->getPosition().y-lab_sz->getContentSize().height/2-14-lab_sz_sp1->getContentSize().height/2));
    addChild(lab_sz_sp1,4);
    auto lab_sz_sp2 = Sprite::create("res/baitiao.png");
    auto lab_sz_pro = ProgressTimer::create(lab_sz_sp2);
    lab_sz_pro->setType(kCCProgressTimerTypeBar);
    lab_sz_pro->setPosition(lab_sz_sp1->getPosition());
    lab_sz_pro->setMidpoint(Vec2(1, 0));//水平方向（1，y）表示从右向左，（0.y）表示从左向右
    lab_sz_pro->setBarChangeRate(Vec2(1, 0));//纵向
//***比例****
    
    lab_sz_pro->setPercentage(lab_sz_pro_percent);
    addChild(lab_sz_pro,5);
    auto lab_sz_score1 = Label::createWithSystemFont(lab_sz_score1_teamA, "fonts/arial.ttf", 28);
    lab_sz_score1->setPosition(Vec2(lab_sz_sp1->getPosition().x-lab_sz_sp1->getContentSize().width/2-10-lab_sz_score1->getContentSize().width/2, lab_sz_sp1->getPosition().y));
    addChild(lab_sz_score1,5);
    auto lab_sz_score2 = Label::createWithSystemFont(lab_sz_score2_teamB, "fonts/arial.ttf", 28);
    lab_sz_score2->setPosition(Vec2(lab_sz_sp1->getPosition().x+lab_sz_sp1->getContentSize().width/2+10+lab_sz_score2->getContentSize().width/2, lab_sz_sp1->getPosition().y));
    addChild(lab_sz_score2,5);
    //主客场红牌、黄牌、越位标示显示
    auto lab_zc_yc = Sprite::create("res/yc.png");
    lab_zc_yc->setPosition(Vec2(lab_sz_score1->getPosition().x-lab_sz_score1->getContentSize().width/2-70-lab_zc_yc->getContentSize().width/2, lab_sz_score1->getPosition().y));
    addChild(lab_zc_yc,5);
    auto lab_zc_rc = Sprite::create("res/rc.png");
    lab_zc_rc->setPosition(Vec2(lab_zc_yc->getPosition().x-lab_zc_yc->getContentSize().width/2-40-lab_zc_rc->getContentSize().width/2, lab_sz_score1->getPosition().y));
    addChild(lab_zc_rc,5);
    auto lab_zc_q1 = Sprite::create("res/baiqi.png");
    lab_zc_q1->setPosition(Vec2(lab_zc_rc->getPosition().x-lab_zc_rc->getContentSize().width/2-40-lab_zc_q1->getContentSize().width/2, lab_sz_score1->getPosition().y));
    addChild(lab_zc_q1,5);
    cout<<"旗子与旗子之间的距离为："<<lab8->getPosition().x-(lab_sz_score1->getPosition().x-lab_sz_score1->getContentSize().width/2-70-lab_zc_yc->getContentSize().width/2)<<endl;
    
    auto lab_kc_yc = Sprite::create("res/yc.png");
    lab_kc_yc->setPosition(Vec2(lab_sz_score2->getPosition().x+lab_sz_score2->getContentSize().width/2+70+lab_kc_yc->getContentSize().width/2, lab_sz_score1->getPosition().y));
    addChild(lab_kc_yc,5);
    auto lab_kc_rc = Sprite::create("res/rc.png");
    lab_kc_rc->setPosition(Vec2(lab_kc_yc->getPosition().x+lab_kc_yc->getContentSize().width/2+40+lab_kc_rc->getContentSize().width/2, lab_sz_score1->getPosition().y));
    addChild(lab_kc_rc,5);
    auto lab_kc_q1 = Sprite::create("res/baiqi.png");
    lab_kc_q1->setPosition(Vec2(lab_kc_rc->getPosition().x+lab_kc_rc->getContentSize().width/2+40+lab_kc_q1->getContentSize().width/2, lab_sz_score1->getPosition().y));
    addChild(lab_kc_q1,5);
    
    //射偏球门--
    auto lab_sw = Label::createWithSystemFont("射偏球门", "fonts/arial.ttf", 22);
    lab_sw->setPosition(Vec2(lab7_sp1->getPosition().x, lab_sz_sp1->getPosition().y-lab_sz_sp1->getContentSize().height/2-24-lab_sw->getContentSize().height/2));
    addChild(lab_sw,5);
    auto lab_sw_sp1 = Sprite::create("res/hongju.png");
    lab_sw_sp1->setPosition(Vec2(lab_sw->getPosition().x, lab_sw->getPosition().y-lab_sw->getContentSize().height/2-14-lab_sw_sp1->getContentSize().height/2));
    addChild(lab_sw_sp1,4);
    auto lab_sw_sp2 = Sprite::create("res/baitiao.png");
    auto lab_sw_pro = ProgressTimer::create(lab_sw_sp2);
    lab_sw_pro->setType(kCCProgressTimerTypeBar);
    lab_sw_pro->setPosition(lab_sw_sp1->getPosition());
    lab_sw_pro->setMidpoint(Vec2(1, 0));//水平方向（1，y）表示从右向左，（0.y）表示从左向右
    lab_sw_pro->setBarChangeRate(Vec2(1, 0));//纵向
//***比例****
    
    lab_sw_pro->setPercentage(lab_sw_pro_percent);
    addChild(lab_sw_pro,5);
    //*****类型转换****
//    string lab_sw_score1_teamA = to_string(teamA_sw);
//    string lab_sw_score2_teamB = to_string(teamB_sw);
    string lab_sw_score1_teamA = String::createWithFormat("%d",teamA_sw)->getCString();
    string lab_sw_score2_teamB = String::createWithFormat("%d",teamB_sw)->getCString();
//    char* lab_sw_score1_teamA;
//    sprintf(lab_sw_score1_teamA, "%d",teamA_sw);
//    char* lab_sw_score2_teamB;
//    sprintf(lab_sw_score2_teamB, "%d",teamB_sw);
//    sprintf(lab_sw_score1_teamA, "%d",teamA_sw);
//    sprintf(lab_sw_score2_teamB, "%d",teamB_sw);
    //*****类型转换****
    auto lab_sw_score1 = Label::createWithSystemFont(lab_sw_score1_teamA, "fonts/arial.ttf", 28);
    lab_sw_score1->setPosition(Vec2(lab_sw_sp1->getPosition().x-lab_sw_sp1->getContentSize().width/2-10-lab_sw_score1->getContentSize().width/2, lab_sw_sp1->getPosition().y));
    addChild(lab_sw_score1,5);
    auto lab_sw_score2 = Label::createWithSystemFont(lab_sw_score2_teamB, "fonts/arial.ttf", 28);
    lab_sw_score2->setPosition(Vec2(lab_sw_sp1->getPosition().x+lab_sw_sp1->getContentSize().width/2+10+lab_sw_score2->getContentSize().width/2, lab_sw_sp1->getPosition().y));
    addChild(lab_sw_score2,5);
    //主客场红牌、黄牌、越位次数显示
    //*****类型转换****
//    string lab_zc_r_c_teamA = to_string(teamA_rc);
//    string lab_zc_y_c_teamA = to_string(teamA_yc);
//    string lab_zc_q_c_teamA = to_string(teamA_yw);
//    string lab_kc_r_c_teamB = to_string(teamB_rc);
//    string lab_kc_y_c_teamB = to_string(teamB_yc);
//    string lab_kc_q_c_teamB = to_string(teamB_yw);
    string lab_zc_r_c_teamA = String::createWithFormat("%d",teamA_rc)->getCString();
    string lab_zc_y_c_teamA = String::createWithFormat("%d",teamA_yc)->getCString();
    string lab_zc_q_c_teamA = String::createWithFormat("%d",teamA_yw)->getCString();
    string lab_kc_r_c_teamB = String::createWithFormat("%d",teamB_rc)->getCString();
    string lab_kc_y_c_teamB = String::createWithFormat("%d",teamB_yc)->getCString();
    string lab_kc_q_c_teamB = String::createWithFormat("%d",teamB_yw)->getCString();
//    char* lab_zc_r_c_teamA;
//    sprintf(lab_zc_r_c_teamA, "%d",teamA_rc);
//    char* lab_zc_y_c_teamA;
//    sprintf(lab_zc_y_c_teamA, "%d",teamA_yc);
//    char* lab_zc_q_c_teamA;
//    sprintf(lab_zc_q_c_teamA, "%d",teamA_yw);
//    char* lab_kc_r_c_teamB;
//    sprintf(lab_kc_r_c_teamB, "%d",teamB_rc);
//    char* lab_kc_y_c_teamB;
//    sprintf(lab_kc_y_c_teamB, "%d",teamB_yc);
//    char* lab_kc_q_c_teamB;
//    sprintf(lab_kc_q_c_teamB, "%d",teamB_yw);
    //*****类型转换****
    //主场红牌次数
    auto lab_zc_r_c = Label::createWithSystemFont(lab_zc_r_c_teamA, "fonts/arial.ttf", 28);
    lab_zc_r_c->setPosition(Vec2(lab_zc_rc->getPosition().x, lab_sw_sp1->getPosition().y));
    addChild(lab_zc_r_c,5);
    //主场黄牌次数
    auto lab_zc_y_c = Label::createWithSystemFont(lab_zc_y_c_teamA, "fonts/arial.ttf", 28);
    lab_zc_y_c->setPosition(Vec2(lab_zc_yc->getPosition().x, lab_sw_sp1->getPosition().y));
    addChild(lab_zc_y_c,5);
    //主场越位次数
    auto lab_zc_q_c = Label::createWithSystemFont(lab_zc_q_c_teamA, "fonts/arial.ttf", 28);
    lab_zc_q_c->setPosition(Vec2(lab_zc_q1->getPosition().x, lab_sw_sp1->getPosition().y));
    addChild(lab_zc_q_c,5);
    
    //客场红牌次数
    auto lab_kc_r_c = Label::createWithSystemFont(lab_kc_r_c_teamB, "fonts/arial.ttf", 28);
    lab_kc_r_c->setPosition(Vec2(lab_kc_rc->getPosition().x, lab_sw_sp1->getPosition().y));
    addChild(lab_kc_r_c,5);
    //客场黄牌次数
    auto lab_kc_y_c = Label::createWithSystemFont(lab_kc_y_c_teamB, "fonts/arial.ttf", 28);
    lab_kc_y_c->setPosition(Vec2(lab_kc_yc->getPosition().x, lab_sw_sp1->getPosition().y));
    addChild(lab_kc_y_c,5);
    //客场越位次数
    auto lab_kc_q_c = Label::createWithSystemFont(lab_kc_q_c_teamB, "fonts/arial.ttf", 28);
    lab_kc_q_c->setPosition(Vec2(lab_kc_q1->getPosition().x, lab_sw_sp1->getPosition().y));
    addChild(lab_kc_q_c,5);
//***************************场上数据显示*************************
    

    lab_sp = Sprite::create("res/baiju.png");
    lab_sp->setPosition(Vec2(0, 0));
    lab = Label::createWithSystemFont("皇家马德里", "fonts/arial.ttf", 24);
    lab->setPosition(Vec2(-20, 30));
    lab->setAnchorPoint(Vec2(1, 1));
    lab_st = Label::createWithSystemFont("进攻", "fonts/arial.ttf", 24);
    lab_st->setPosition(Vec2(-20, 0));
    lab_st->setAnchorPoint(Vec2(1, 1));
    
    node_lab = Node::create();
    node_lab->addChild(lab_sp);
    node_lab->addChild(lab);
    node_lab->addChild(lab_st);
    addChild(node_lab,5);
    node_lab->setPosition(Vec2(sprbg->getPosition().x, sprbg->getPosition().y));
    node_lab->setVisible(false);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    netClick();
//    alternate(2);
//    pai_RY(5);
//    pai_RY(6);
    
    
//    cc_state++;
//    switch (cc_state) {
//        case 1:
//            jinqiu(1);
//            break;
//        case 2:
//            jinqiu(2);
//            break;
//        case 3:
//            jinqiu(3);
//            break;
//        case 4:
//            jinqiu(4);
//            break;
//        case 5:
//            jinqiu(5);
//            break;
//        case 6:
//            jinqiu(6);
//            cc_state=0;
//            break;
//        default:
//            break;
//    }
////    this->removeAllChildren();
//    cout<<"finish"<<endl;
//    if (UserDefault::getInstance()->getBoolForKey("isExisted")) {
//        cout<<"this had userdefault"<<endl;
//        cout<<UserDefault::getInstance()->getStringForKey("string")<<endl;
//        UserDefault::getInstance()->setBoolForKey("isExisted", false);
//    }else{
//        cout<<"this had no userdefault"<<endl;
//        UserDefault::getInstance()->setStringForKey("string", "helloworld");
//        UserDefault::getInstance()->setBoolForKey("isExisted", true);
//        UserDefault::getInstance()->flush();
//    }
//    cout<<cc_state<<endl;
//    if (cc_state>21) {
//        cc_state=0;
//    }
//    switch (cc_state) {
//        case 1:
//            footballCaseType(CASE_Start_RT1);
//            break;
//        case 2:
//            footballCaseType(CASE_AT1);
//            break;
//        case 3:
//            footballCaseType(CASE_DAT1);
//            break;
//        case 4:
//            footballCaseType(CASE_SAFE1);
//            break;
//        case 5:
//            footballCaseType(CASE_AT2);
//            break;
//        case 6:
//            footballCaseType(CASE_DAT2);
//            break;
//        case 7:
//            footballCaseType(CASE_SAFE2);
//            break;
//        case 8:
//            footballCaseType(CASE_CR2);
//            break;
//        case 9:
//            footballCaseType(CASE_GK2);
//            break;
//        case 10:
//            footballCaseType(CASE_GK1);
//            break;
//        case 11:
//            footballCaseType(CASE_RC1);
//            break;
//        case 12:
//            footballCaseType(CASE_CR1);
//            break;
//        case 13:
//            footballCaseType(CASE_YC1);
//            break;
//        case 14:
//            footballCaseType(CASE_DFK2);
//            break;
//        case 15:
//            footballCaseType(CASE_GOAL2);
//            break;
//        case 16:
//            footballCaseType(CASE_GOAL1);
//            break;
//        case 17:
//            footballCaseType(CASE_DFK1);
//            break;
//        case 18:
//            footballCaseType(CASE_FK1);
//            break;
//        case 19:
//            footballCaseType(CASE_RC2);
//            break;
//        case 20:
//            footballCaseType(CASE_YC2);
//            break;
//        case 21:
//            footballCaseType(CASE_GK2);
//            break;
//            
//        default:
//            break;
//    }
//    this->removeAllChildren();
//    kongqiu(cc_state);
//    jinqiu();
//    jiaoqiu(4);
//    netClick();
//    JX_json();
//    footballCaseType(CASE_Start_RT1);
    
}
//球移动到指定的位置
void HelloWorld::move(Point _point){
    football->stopAllActions();
    auto pp = football->getPosition();
    float tt = sqrt((_point.x-pp.x)*(_point.x-pp.x)+(_point.y-pp.y)*(_point.y-pp.y));
    cout<< tt<<endl;
    float tsp = tt/400;
    auto act = MoveTo::create(tsp, _point);
    football->runAction(act);
}
//球影效果，即球在没有移动时，缩放的阴影效果
void HelloWorld::qshadow(Point _point){
//    cout<<"ashadow"<<endl;
    if (_point == football->getPosition()) {
        unschedule(schedule_selector(HelloWorld::update_q));
        auto shadow1 = Sprite::create("res/baiyuan.png");
        shadow1->setPosition(Vec2(football->getPosition().x, football->getPosition().y));
        addChild(shadow1,3);
        shadow1->setOpacity(100);
        auto shadow2 = Sprite::create("res/baiyuan.png");
        shadow2->setPosition(Vec2(football->getPosition().x, football->getPosition().y));
        addChild(shadow2,3);
        shadow2->setOpacity(80);
        auto act1 = ScaleBy::create(0.5, 7);
        auto act2 = ScaleBy::create(1, 14);
        shadow1->runAction(RepeatForever::create(Sequence::create(act1,DelayTime::create(1),act1->reverse(),DelayTime::create(1), NULL)));
        shadow2->runAction(RepeatForever::create(Sequence::create(act2,DelayTime::create(1),act2->reverse(), NULL)));
    }
    
    
}
//监测球的位置，当球到达指定位置后，执行球没有移动的时候的阴影动作
void HelloWorld::update_q(float dt){
//    qshadow(Vec2(460, 700));
    if (percent_kongqiu>=300) {
        percent_kongqiu = 0;
    }
    percent_kongqiu+=5;
    progress->setPercentage(percent_kongqiu);
     
}
//进球时的动画展示
void HelloWorld::jinqiu(int _i){
    this->removeAllChildren();
    this->unschedule(schedule_selector(HelloWorld::update_q));
    this->unschedule(schedule_selector(HelloWorld::update_dianqiu));
    initUI();
    auto jinqiu = Sprite::create("res/jinqiu.png");
    addChild(jinqiu,5);
    auto men = Sprite::create("res/men.png");
    addChild(men,5);
    auto zhunxing = Sprite::create("res/zhunxing.png");
    addChild(zhunxing,5);
    //两个状态，1、主场进球  2、客场进球
    switch (_i) {
        case 1:
            jinqiu->setPosition(Vec2(sprbg->getPosition().x+sprbg->getContentSize().width/2-50, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            jinqiu->setRotation(0);
            lab_state(1, "进球");
            lab_move(Vec2(sprbg->getPosition().x+sprbg->getContentSize().width/2-100, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            break;
        case 2:
            jinqiu->setPosition(Vec2(sprbg->getPosition().x-sprbg->getContentSize().width/2+50, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            jinqiu->setRotation(180);
            lab_state(2, "进球");
            lab_move(Vec2(sprbg->getPosition().x-sprbg->getContentSize().width/2+100, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            break;
        case 3:
            men->setPosition(Vec2(sprbg->getPosition().x+50, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            zhunxing->setPosition(Vec2(sprbg->getPosition().x+50, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            lab_state(1, "射正球门");
            lab_move(Vec2(sprbg->getPosition().x, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            break;
        case 4:
            men->setPosition(Vec2(sprbg->getPosition().x+50, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            zhunxing->setPosition(Vec2(sprbg->getPosition().x+30, sprbg->getPosition().y-sprbg->getContentSize().height/2+15));
            lab_state(1, "射偏球门");
            lab_move(Vec2(sprbg->getPosition().x, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            break;
        case 5:
            men->setPosition(Vec2(sprbg->getPosition().x-50, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            zhunxing->setPosition(Vec2(sprbg->getPosition().x-50, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            lab_state(2, "射正球门");
            lab_move(Vec2(sprbg->getPosition().x, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            break;
        case 6:
            men->setPosition(Vec2(sprbg->getPosition().x-50, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            zhunxing->setPosition(Vec2(sprbg->getPosition().x-30, sprbg->getPosition().y-sprbg->getContentSize().height/2+15));
            lab_state(2, "射偏球门");
            lab_move(Vec2(sprbg->getPosition().x, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            break;
        default:
            break;
    }
    if (_i==5||_i ==6) {
        men->runAction(FlipX::create(true));
        zhunxing->runAction(FlipX::create(true));
    }
    jinqiu->setCascadeOpacityEnabled(true);
    jinqiu->setOpacity(0);
    auto act_node = FadeTo::create(1,255);
    auto act = FadeTo::create(1, 0);
    jinqiu->runAction(RepeatForever::create(Sequence::create(act_node,act, NULL)));
}
//进攻时的文字lab的动态展示
void HelloWorld::lab_state(int _state,char* _word){
    node_lab->setVisible(true);
    //1、主队文字  2、客队文字
    switch (_state) {
        case 1:
            lab_sp->setColor(Color3B::BLACK);
            lab_st->setString(_word);
            lab->setString(name_teamA);
            lab_st->setPosition(Vec2(lab_sp->getPosition().x-20, lab_sp->getPosition().y));
            lab_st->setAnchorPoint(Vec2(1, 1));
            lab->setPosition(Vec2(lab_sp->getPosition().x-20, lab_sp->getPosition().y));
            lab->setAnchorPoint(Vec2(1, 0));
            break;
        case 2:
            lab_sp->setColor(Color3B::WHITE);
            lab_st->setString(_word);
            lab_st->setPosition(Vec2(lab_sp->getPosition().x+20, lab_sp->getPosition().y));
            lab_st->setAnchorPoint(Vec2(0, 1));
            lab->setString(name_teamB);
            lab->setPosition(Vec2(lab_sp->getPosition().x+20, lab_sp->getPosition().y));
            lab->setAnchorPoint(Vec2(0, 0));
            break;
            
        default:
            break;
    }
}
//进攻时的文字lab的位置变化
void HelloWorld::lab_move(Point _point){
//    node_lab->stopAllActions();
//    auto point1 = node_lab->getPosition();
//    auto dst = sqrt((point1.x-_point.x)*(point1.x-_point.x)+(point1.y-_point.y)*(point1.y-_point.y));
//    auto time = dst/800;
//    auto act = MoveTo::create(time, _point);
//    node_lab->runAction(act);
    node_lab->setPosition(Vec2(_point.x, _point.y));
}
void HelloWorld::pai_RY(int _pai){
    this->removeAllChildren();
    this->unschedule(schedule_selector(HelloWorld::update_q));
    this->unschedule(schedule_selector(HelloWorld::update_dianqiu));
    initUI();
//    auto yuewei =
    //1、主队红牌 2、主队黄牌 3、客队红牌 4、客队黄牌 5、主队越位 6、客队越位
    switch (_pai) {
        case 1:
            pai_spr = Sprite::create("res/hongpai.png");
            pai_spr->setPosition(Vec2(sprbg->getPosition().x+20, sprbg->getPosition().y-sprbg->getContentSize().height/2-40));
            lab_state(1, "红牌");
            lab_move(Vec2(sprbg->getPosition().x, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            break;
        case 2:
            pai_spr = Sprite::create("res/huangpai.png");
            pai_spr->setPosition(Vec2(sprbg->getPosition().x+20, sprbg->getPosition().y-sprbg->getContentSize().height/2-40));
            lab_state(1, "黄牌");
            lab_move(Vec2(sprbg->getPosition().x, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            break;
        case 3:
            pai_spr = Sprite::create("res/hongpai.png");
            pai_spr->setPosition(Vec2(sprbg->getPosition().x-20, sprbg->getPosition().y-sprbg->getContentSize().height/2-40));
            lab_state(2, "红牌");
            lab_move(Vec2(sprbg->getPosition().x, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            break;
        case 4:
            pai_spr = Sprite::create("res/huangpai.png");
            pai_spr->setPosition(Vec2(sprbg->getPosition().x-20, sprbg->getPosition().y-sprbg->getContentSize().height/2-40));
            lab_state(2, "黄牌");
            lab_move(Vec2(sprbg->getPosition().x, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            break;
        case 5:
            pai_spr = Sprite::create("res/yuewei.png");
//            pai_spr->stopAllActions();
            pai_spr->runAction(FlipX::create(true));
            pai_spr->setPosition(Vec2(sprbg->getContentSize().width/8*7+pai_spr->getContentSize().width/2, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            lab_state(1, "越位");
            lab_move(Vec2(sprbg->getContentSize().width/8*7, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            break;
        case 6:
            pai_spr = Sprite::create("res/yuewei.png");
//            pai_spr->stopAllActions();
            pai_spr->setPosition(Vec2(sprbg->getContentSize().width/8-pai_spr->getContentSize().width/2, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            lab_state(2, "越位");
            lab_move(Vec2(sprbg->getContentSize().width/8, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            break;
        default:
            break;
    }
    
    pai_spr->setOpacity(0);
    auto act_pai = FadeTo::create(0.5, 255);
    auto act2_pai = MoveBy::create(0.5, Vec2(0, 40));
    if (_pai==1||_pai==2||_pai==3||_pai==4) {
    pai_spr->runAction(Spawn::create(act_pai,act2_pai, NULL));
    }else
    {
        pai_spr->setOpacity(255);
    }
    addChild(pai_spr,5);
    pai_spr->setCascadeOpacityEnabled(true);
}
//受伤
void HelloWorld::injured(){
    initUI();
    auto lab_injured = Label::createWithSystemFont("受伤", "fonts/arial.ttf", 35);
    addChild(lab_injured,5);
    lab_injured->setPosition(Vec2(sprbg->getPosition().x, sprbg->getPosition().y-sprbg->getContentSize().height/2));
}
//替补
void HelloWorld::alternate(int _i){
    this->removeAllChildren();
    this->unschedule(schedule_selector(HelloWorld::update_q));
    this->unschedule(schedule_selector(HelloWorld::update_dianqiu));
    initUI();
    auto tibu = Sprite::create("res/tibu.png");
    switch (_i) {
        case 1:
            lab_state(1, "替补");
            lab_move(Vec2(sprbg->getPosition().x+50, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            tibu->setPosition(Vec2(sprbg->getPosition().x+85, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            break;
        case 2:
            lab_state(2, "替补");
            lab_move(Vec2(sprbg->getPosition().x-50, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            tibu->setPosition(Vec2(sprbg->getPosition().x-85, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            break;
        default:
            break;
    }
    addChild(tibu,5);
}
//加时与半场
void HelloWorld::overtime(int _i){
    this->removeAllChildren();
    this->unschedule(schedule_selector(HelloWorld::update_q));
    this->unschedule(schedule_selector(HelloWorld::update_dianqiu));
    initUI();
    auto lab_injured = Label::createWithSystemFont("半场", "fonts/arial.ttf", 35);
    addChild(lab_injured,5);
    //1、加时  2、半场
    switch (_i) {
        case 1:
            lab_injured->setString("上半场开始");
            cout<<"上半场开始"<<endl;
            break;
        case 2:
            lab_injured->setString("上半场结束");
            cout<<"上半场结束"<<endl;
            break;
        case 3:
            lab_injured->setString("下半场开始");
            cout<<"下半场开始"<<endl;
            break;
        case 4:
            lab_injured->setString("下半场结束");
            cout<<"下半场结束"<<endl;
            break;
        default:
            break;
    }
    lab_injured->setPosition(Vec2(sprbg->getPosition().x, sprbg->getPosition().y-sprbg->getContentSize().height/2));
}
//network 异步请求与处理
void HelloWorld::netClick(){
    HttpRequest * request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::GET);
    request->setUrl("http://192.168.10.201:8080/api/mobileClientApi.action?function=tcmFindEventCaseStats&eventId=733215&timeMillis=14929815387500000");
    char* ss = "eventId";
    request->setResponseCallback(this, httpresponse_selector(HelloWorld::onHttpRequestCompleted));
    request->setRequestData(ss, strlen(ss));
    
    HttpClient* client = HttpClient::getInstance();
    client->setTimeoutForConnect(2);
    client->setTimeoutForRead(2);
    client->send(request);
    request->release();
    
}
void HelloWorld::onHttpRequestCompleted(Node *sender ,void *data){
    HttpResponse* response=(HttpResponse*)data;
    if (!response->isSucceed()) {
        String strError;
        strError.initWithFormat("Receive Error!\n %s \n",response->getErrorBuffer());
        cout<<strError.getCString()<<endl;
        return;
    }
    vector<char>* buffer = response->getResponseData();
    string recieveData;
    for (int i = 0; i<buffer->size(); i++) {
        recieveData+=(*buffer)[i];
    }
    string result(recieveData.begin(),recieveData.end());
    //将std::vector(char)* 转换成 std::string的两种方法
    string backStr = std::string(&(*buffer->begin()), buffer->size());
//    string anotherStr;
//    anotherStr.insert(anotherStr.begin(), buffer->begin(), buffer->end());
    printf("%s\n", backStr.c_str());
//    printf("%s\n", anotherStr.c_str());

    
        //json解析方法
    rapidjson::Document doc;
    doc.Parse<0>(backStr.c_str());
//*************state******************
    for (int i=0; i<doc["data"]["stats"].Size(); i++) {
        if (strcmp(doc["data"]["stats"][i]["statsId"].GetString(),"90012") == 0) {
            log("sehpianqiumen");
            string A_sw = doc["data"]["stats"][i]["homeTeamValue"].GetString();
            string B_sw = doc["data"]["stats"][i]["awayTeamValue"].GetString();
            teamA_sw = atoi(A_sw.c_str());
            teamB_sw = atoi(B_sw.c_str());
        }
        if (strcmp(doc["data"]["stats"][i]["statsId"].GetString(),"90013") == 0) {
            log("shezhong");
            string A_sw = doc["data"]["stats"][i]["homeTeamValue"].GetString();
            string B_sw = doc["data"]["stats"][i]["awayTeamValue"].GetString();
            teamA_sz = atoi(A_sw.c_str());
            teamB_sz = atoi(B_sw.c_str());
        }
        if (strcmp(doc["data"]["stats"][i]["statsId"].GetString(),"90011") == 0) {
            log("越位");
            string A_sw = doc["data"]["stats"][i]["homeTeamValue"].GetString();
            string B_sw = doc["data"]["stats"][i]["awayTeamValue"].GetString();
            teamA_yw = atoi(A_sw.c_str());
            teamB_yw = atoi(B_sw.c_str());
        }
        if (strcmp(doc["data"]["stats"][i]["statsId"].GetString(),"90009") == 0) {
            log("危险进攻");
            string A_sw = doc["data"]["stats"][i]["homeTeamValue"].GetString();
            string B_sw = doc["data"]["stats"][i]["awayTeamValue"].GetString();
            teamA_wxjg = atoi(A_sw.c_str());
            teamB_wxjg = atoi(B_sw.c_str());
        }
        if (strcmp(doc["data"]["stats"][i]["statsId"].GetString(),"90008") == 0) {
            log("进攻");
            string A_sw = doc["data"]["stats"][i]["homeTeamValue"].GetString();
            string B_sw = doc["data"]["stats"][i]["awayTeamValue"].GetString();
            teamA_jg = atoi(A_sw.c_str());
            teamB_jg = atoi(B_sw.c_str());
        }
        if (strcmp(doc["data"]["stats"][i]["statsId"].GetString(),"90002") == 0) {
            log("黄牌");
            string A_sw = doc["data"]["stats"][i]["homeTeamValue"].GetString();
            string B_sw = doc["data"]["stats"][i]["awayTeamValue"].GetString();
            teamA_yc = atoi(A_sw.c_str());
            teamB_yc = atoi(B_sw.c_str());
        }
        if (strcmp(doc["data"]["stats"][i]["statsId"].GetString(),"90003") == 0) {
            log("红牌");
            string A_sw = doc["data"]["stats"][i]["homeTeamValue"].GetString();
            string B_sw = doc["data"]["stats"][i]["awayTeamValue"].GetString();
            teamA_rc = atoi(A_sw.c_str());
            teamB_rc = atoi(B_sw.c_str());
        }
        if (strcmp(doc["data"]["stats"][i]["statsId"].GetString(),"90000") == 0) {
            log("进球");
            string A_sw = doc["data"]["stats"][i]["homeTeamValue"].GetString();
            string B_sw = doc["data"]["stats"][i]["awayTeamValue"].GetString();
            teamA_jq = atoi(A_sw.c_str());
            teamB_jq = atoi(B_sw.c_str());
        }
    }
    
//*************case******************
//    log("%s",doc["data"]["case"][0]["caseType"].GetString());
//    string s = doc["data"]["case"][0]["caseType"].GetString();
//    footballCaseType(atoi(s.c_str()));
//    vector<char>* vec;
    caseState csb;
    vector<caseState> vec2;
    
    for (int i = 0; i<doc["data"]["case"].Size(); i++) {
        cout<<"size is *********"<<doc["data"]["case"].Size()<<endl;
        log("%s\n",doc["data"]["case"][i]["caseTime"].GetString());
        string ssm = doc["data"]["case"][i]["caseTime"].GetString();
        long long sm = atoi(ssm.c_str());
        string ssw = doc["data"]["case"][i]["caseType"].GetString();
        int sw = atoi(ssw.c_str());
        csb.caseTimes = sm;
        csb.caseStats = sw;
        vec2.push_back(csb);
//        vec.push_back(csb);
//        vec->push_back(*doc["data"]["case"][i]["caseTime"].GetString());
    }
    vector<caseState>::reverse_iterator it = vec2.rbegin();
    while (it!=vec2.rend()) {
        vec.push_back(*it);
        it++;
    }
    for (int i = 0; i<vec.size(); i++) {
        cout<<vec[i].caseStats<<"  "<<vec[i].caseTimes<<endl;
    }
    cout<<vec.end()->caseStats<<endl;
    
    cout<<"size is *********"<<endl;
    cout<<vec.size()<<endl;
//    while(vec.size()) {
//        vec.pop_back();
//        cout<<vec.begin()->caseStats<<"   "<<vec.end()->caseStats<<endl;
//        cout<<"size is *********"<<endl;
//        for (int j=0; j<vec.size(); j++) {
//            cout<<vec[j].caseStats<<"  "<<vec[j].caseTimes<<endl;
//        }
//        cout<<vec.size()<<endl;
//    }
    schedule(schedule_selector(HelloWorld::update), 1);
}

//json文件解析
void HelloWorld::JX_json(){
    rapidjson::Document readdoc;
    bool bRet = false;
    ssize_t size = 0;
    //从文件中获取字符串
    string loadstr = FileUtils::getInstance()->getStringFromFile("res/File.txt");
    cout<<loadstr.c_str()<<endl;
    //将字符串转换成c格式的字符
    readdoc.Parse<0>(loadstr.c_str());
    if (readdoc.HasParseError()) {
        log("GetParseError%u\n",readdoc.GetParseError());
    }
    
    if (readdoc.HasMember("hello")) {
        cout<<readdoc["hello"].GetString()<<endl;
    }
    if (readdoc.HasMember("province")) {
        cout<<"object"<<endl;
        for (int i =0 ; i<readdoc["province"].Size();i++ ) {
            if (readdoc["province"][i].IsObject()) {
                cout<<"object"<<i<<endl;
                cout<<readdoc["province"][i]["name"].GetString()<<endl;
            }
        }
    }

        cout<<"this is guangdong"<<endl;
        cout<<readdoc["province"][1]["cities"]["city"][1].GetString()<<endl;
    
    
}
//球场状态转换选择
void HelloWorld::footballCaseType(int _FootballCaseType){
    switch (_FootballCaseType) {
        case CASE_Start_RT1:
            overtime(1);
            cout<<"上半场开始"<<endl;
            break;
        case CASE_Stop_RT1:
            overtime(2);
            cout<<"上半场结束"<<endl;
            break;
        case CASE_Start_RT2:
            overtime(3);
            cout<<"下半场开始"<<endl;
            break;
        case CASE_Stop_RT2:
            overtime(4);
            cout<<"下半场结束"<<endl;
            break;
        case CASE_Start_OT1:
            cout<<"加时赛上半场开始"<<endl;
            break;
        case CASE_Stop_OT1:
            cout<<"加时赛上半场结束"<<endl;
            break;
        case CASE_Start_OT2:
            cout<<"加时赛下半场开始"<<endl;
            break;
        case CASE_Stop_OT2:
            cout<<"加时赛下半场结束"<<endl;
            break;
        case CASE_Start_PEN:
            cout<<"点球大战开始"<<endl;
            break;
        case CASE_Stop_PEN:
            cout<<"点球大战结束"<<endl;
            break;
        case CASE_Start_RT1_Team_1:
            cout<<"上半场开始,主队发球"<<endl;
            break;
        case CASE_Start_RT1_Team_2:
            cout<<"上半场开始,客队发球"<<endl;
            break;
        case CASE_Start_RT2_Team_1:
            cout<<"下半场开始,主队发球"<<endl;
            break;
        case CASE_Start_RT2_Team_2:
            cout<<"下半场开始,客队发球"<<endl;
            break;
        case CASE_Start_OT1_Team_1:
            cout<<"加时赛上半场开始,主队发球"<<endl;
            break;
        case CASE_Start_OT1_Team_2:
            cout<<"加时赛上半场开始,客队发球"<<endl;
            break;
        case CASE_Start_OT2_Team_1:
            cout<<"加时赛下半场开始,主队发球"<<endl;
            break;
        case CASE_Start_OT2_Team_2:
            cout<<"加时赛下半场开始,客队发球"<<endl;
            break;
        case CASE_Start_PEN_Team_1:
            cout<<"点球大战开始,主队发球"<<endl;
            break;
        case CASE_Start_PEN_Team_2:
            cout<<"点球大战开始,客队发球"<<endl;
            break;
        case CASE_StopGame:
            cout<<"比赛结束"<<endl;
            break;
        case CASE_StartOT:
            cout<<"/加时赛开始"<<endl;
            break;
        case CASE_StopOvertime:
            cout<<"加时赛结束"<<endl;
            break;
        case CASE_Missed:
            cout<<"点球不中"<<endl;
            break;
        case CASE_PRC:
            cout<<"可能红牌"<<endl;
            break;
        case CASE_PPEN:
            cout<<"可能点球"<<endl;
            break;
        case CASE_NoRC:
            cout<<"无红牌"<<endl;
            break;
        case CASE_NoPEN:
            cout<<"无点球"<<endl;
            break;
        case CASE_RetakePEN:
            cout<<"点球重罚"<<endl;
            break;
        case CASE_Restart:
            cout<<"比赛继续,如伤停之后"<<endl;
            break;
        case CASE_GameSuspended:
            cout<<"比赛因未知原因暂停"<<endl;
            break;
        case CASE_AT1:
            kongqiu(2);
            cout<<"主队进攻"<<endl;
            break;
        case CASE_CR1:
            jiaoqiu(1);
            cout<<"主队角球"<<endl;
            break;
        case CASE_DAT1:
            kongqiu(3);
            cout<<"主队危险进攻"<<endl;
            break;
        case CASE_DFK1:
            jiaoqiu(9);
            cout<<"主队危险任意球"<<endl;
            break;
        case CASE_FK1:
            jiaoqiu(7);
            cout<<"主队任意球"<<endl;
            break;
        case CASE_GOAL1:
            jinqiu(1);
            cout<<"主队进球"<<endl;
            break;
        case CASE_CGOAL1:
            cout<<"主队进球取消"<<endl;
            break;
        case CASE_PEN1:
            cout<<"主队点球"<<endl;
            break;
        case CASE_RC1:
            pai_RY(1);
            cout<<"主队红牌"<<endl;
            break;
        case CASE_SH1:
            cout<<"主队射门"<<endl;
            break;
        case CASE_YC1:
            pai_RY(2);
            cout<<"主队黄牌"<<endl;
            break;
        case CASE_SHG1:
            cout<<"主队射正"<<endl;
            break;
        case CASE_SHB1:
            cout<<"主队射偏"<<endl;
            break;
        case CASE_SHW1:
            cout<<"主队射中门框"<<endl;
            break;
        case CASE_F1:
            cout<<"主队犯规"<<endl;
            break;
        case CASE_O1:
            pai_RY(5);
            cout<<"主队越位"<<endl;
            break;
        case CASE_KO1:
            cout<<"主队开球"<<endl;
            break;
        case CASE_YRC1:
            cout<<"主队两黄转一红"<<endl;
            break;
        case CASE_CYC_RC1:
            cout<<"主队两黄转一红取消"<<endl;
            break;
        case CASE_CRC1:
            cout<<"主队红牌取消"<<endl;
            break;
        case CASE_CYC1:
            cout<<"主队黄牌取消"<<endl;
            break;
        case CASE_CPEN1:
            cout<<"主队点球取消"<<endl;
            break;
        case CASE_CCR1:
            cout<<"主队角球取消"<<endl;
            break;
        case CASE_SAFE1:
            kongqiu(1);
            cout<<"主队控球"<<endl;
            break;
        case CASE_DANGER1:
            cout<<"主队威胁进攻"<<endl;
            break;
        case CASE_GK1:
            jiaoqiu(5);
            cout<<"主队球门球"<<endl;
            break;
        case CASE_TI1:
            cout<<"主队界外球"<<endl;
            break;
        case CASE_SUB1:
            cout<<"主队换人"<<endl;
            break;
        case CASE_DSH1:
            cout<<"主队威胁射门"<<endl;
            break;
        case CASE_SAVE1:
            cout<<"主队扑救"<<endl;
            break;
        case CASE_BLOCKED1:
            cout<<"主队封堵射门"<<endl;
            break;
        case CASE_RPEN1:
            cout<<"主队重罚点球"<<endl;
            break;
        case CASE_MPEN1:
            cout<<"主队点球射失"<<endl;
            break;
        case CASE_PPEN1:
            cout<<"主队可能点球"<<endl;
            break;
        case CASE_BREAKAWAY1:
            cout<<"主队突破"<<endl;
            break;
        case CASE_CONF_GOAL1:
            cout<<"主队进球确认"<<endl;
            break;
        case CASE_PCR1:
            cout<<"主队可能角球"<<endl;
            break;
        case CASE_NCR1:
            cout<<"主队无角球"<<endl;
            break;
        case CASE_AT2:
            kongqiu(5);
            cout<<"客队进攻"<<endl;
            break;
        case CASE_CR2:
            cout<<"客队角球"<<endl;
            break;
        case CASE_DAT2:
            kongqiu(6);
            cout<<"客队危险进攻"<<endl;
            break;
        case CASE_DFK2:
            jiaoqiu(10);
            cout<<"客队危险任意球"<<endl;
            break;
        case CASE_FK2:
            jiaoqiu(8);
            cout<<"客队任意球"<<endl;
            break;
        case CASE_GOAL2:
            jinqiu(2);
            cout<<"客队进球"<<endl;
            break;
        case CASE_CGOAL2:
            cout<<"客队进球取消"<<endl;
            break;
        case CASE_PEN2:
            cout<<"客队点球"<<endl;
            break;
        case CASE_RC2:
            pai_RY(3);
            cout<<"客队红牌"<<endl;
            break;
        case CASE_SH2:
            cout<<"客队射门"<<endl;
            break;
        case CASE_YC2:
            pai_RY(4);
            cout<<"客队黄牌"<<endl;
            break;
        case CASE_SHG2:
            cout<<"客队射正"<<endl;
            break;
        case CASE_SHB2:
            cout<<"客队射偏"<<endl;
            break;
        case CASE_SHW2:
            cout<<"客队射中门框"<<endl;
            break;
        case CASE_F2:
            cout<<"客队犯规"<<endl;
            break;
        case CASE_O2:
            pai_RY(6);
            cout<<"客队越位"<<endl;
            break;
        case CASE_KO2:
            cout<<"客队开球"<<endl;
            break;
        case CASE_YRC2:
            cout<<"客队两黄转一红"<<endl;
            break;
        case CASE_CYC_RC2:
            cout<<"客队两黄转一红取消"<<endl;
            break;
        case CASE_CRC2:
            cout<<"客队红牌取消"<<endl;
            break;
        case CASE_CYC2:
            cout<<"客队黄牌取消"<<endl;
            break;
        case CASE_CPEN2:
            cout<<"客队点球取消"<<endl;
            break;
        case CASE_CCR2:
            cout<<"客队角球取消"<<endl;
            break;
        case CASE_SAFE2:
            kongqiu(4);
            cout<<"客队控球"<<endl;
            break;
        case CASE_DANGER2:
            cout<<"客队威胁进攻"<<endl;
            break;
        case CASE_GK2:
            jiaoqiu(6);
            cout<<"客队球门球"<<endl;
            break;
        case CASE_TI2:
            cout<<"客队界外球"<<endl;
            break;
        case CASE_SUB2:
            cout<<"客队换人"<<endl;
            break;
        case CASE_DSH2:
            cout<<"客队威胁射门"<<endl;
            break;
        case CASE_SAVE2:
            cout<<"客队扑救"<<endl;
            break;
        case CASE_BLOCKED2:
            cout<<"客队封堵射门"<<endl;
            break;
        case CASE_RPEN2:
            cout<<"客队点球重罚"<<endl;
            break;
        case CASE_MPEN2:
            cout<<"客队点球射失"<<endl;
            break;
        case CASE_PPEN2:
            cout<<"客队可能点球"<<endl;
            break;
        case CASE_BREAKAWAY2:
            cout<<"客队突破"<<endl;
            break;
        case CASE_CONF_GOAL2:
            cout<<"客队进球确认"<<endl;
            break;
        case CASE_PCR2:
            cout<<"客队可能角球"<<endl;
            break;
        case CASE_NCR2:
            cout<<"客队无角球"<<endl;
            break;
        default:
            break;
    }
}

