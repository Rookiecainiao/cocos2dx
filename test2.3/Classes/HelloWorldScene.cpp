#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "iostream"
#include "ui/UIButton.h"
using namespace std;
USING_NS_CC;
using namespace ui;

int percent = 0;

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
    
    this->setCascadeOpacityEnabled(true);
    initUI();
    
    return true;
}
void HelloWorld::update(float time){
    if (percent>=200) {
        percent = 0;
    }
    percent+=5;
    progress->setPercentage(percent);
    progress1->setPercentage(percent);
    shadow1->setPosition(Vec2(football->getPosition().x, football->getPosition().y));
    shadow2->setPosition(Vec2(football->getPosition().x, football->getPosition().y));
}
//UI布局初始化
void HelloWorld::initUI(){
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    cout<<"hello"<<visibleSize.width<<"  "<<visibleSize.height<<endl;
    
    auto titlesp = Sprite::create("res/titlesp.png");
    titlesp->setPosition(Vec2(visibleSize.width/2, visibleSize.height));
    titlesp->setAnchorPoint(Vec2(0.5, 1));
    auto titlesize = titlesp->getContentSize();
    titlesp->setScale(visibleSize.width/titlesize.width+1, 50/titlesize.height);
    addChild(titlesp,2);
    
    auto labtitle = Label::createWithSystemFont("竞猜", "fonts/arial.ttf", 32);
    labtitle->setPosition(Vec2(visibleSize.width/2, visibleSize.height-25));
    labtitle->setAnchorPoint(Vec2(0.5, 0.5));
    addChild(labtitle,3);
    
    auto bg = Sprite::create("res/baiju.png");
    //    bg->setOpacity(0.5);
    bg->setPosition(Vec2(visibleSize.width/2, visibleSize.height));
    bg->setAnchorPoint(Vec2(0.5, 1));
    bg->setColor(Color3B::BLACK);
    auto y = bg->getContentSize().height;
    bg->setScale(400, visibleSize.height/2/y);
    addChild(bg,1);
    
    
    cout<<y<<endl;
    
    sprbg = Sprite::create("res/donghuabg.png");
    sprbg->setPosition(Vec2(visibleSize.width/2, visibleSize.height-100));
    sprbg->setAnchorPoint(Vec2(0.5, 1));
    sprbg->setScale(visibleSize.width/sprbg->getContentSize().width);
    //    sprbg->setContentSize(Size(640,217.6));
    addChild(sprbg,2);
    auto sprsize = sprbg->getContentSize();
    cout<<sprsize.width<<"    "<<sprsize.height<<endl;
    
    auto btn = Button::create("res/u759.png");
    btn->setPosition(Vec2(20, visibleSize.height));
    btn->setAnchorPoint(Vec2(0.5,1));
    btn->setScale(4);
    btn->addClickEventListener(CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    addChild(btn,2);
    
    
    
    football = Sprite::create("res/football.png");
    football->setPosition(Vec2(visibleSize.width/2, visibleSize.height-200));
    addChild(football,4);
    auto ballaction = RotateBy::create(2, 180);
    auto ballaction2 = MoveBy::create(4, Vec2(100, 100));
    //    football->runAction(Spawn::create(ballaction, NULL));
    auto action1=Spawn::create(ballaction,ballaction2, NULL);
    auto action2=Spawn::create(ballaction,ballaction2->reverse(), NULL);
    football->runAction(RepeatForever::create(Sequence::create(action1,action2, NULL)));
    
    auto ballposition = football->getPosition();
    shadow1 = Sprite::create("res/baiyuan.png");
    shadow1->setPosition(Vec2(football->getPosition().x, football->getPosition().y));
    //    shadow1->setScale(5);
    addChild(shadow1,3);
    shadow1->setOpacity(100);
    auto shaction = ScaleBy::create(0.5, 5);
    auto shaction11 = ScaleBy::create(0.5, 1);
    shadow1->runAction(RepeatForever::create(Sequence::create(shaction,shaction11,shaction11->reverse(),shaction->reverse(), NULL)));
    
    shadow2 = Sprite::create("res/baiyuan.png");
    shadow2->setPosition(Vec2(football->getPosition().x, football->getPosition().y));
    
    //    shadow2->setScale(10);
    addChild(shadow2,3);
    shadow2->setOpacity(80);
    auto shaction1 = ScaleBy::create(1, 10);
    shadow2->runAction(RepeatForever::create(Sequence::create(shaction1,shaction1->reverse(), NULL)));
    
    auto lab1 = Label::createWithSystemFont("0", "fonts/arial.ttf", 24 );
    lab1->setPosition(Vec2(visibleSize.width/2-15, sprbg->getPosition().y+25));
    lab1->setColor(Color3B::RED);
    addChild(lab1,4);
    auto lab2 = Label::createWithSystemFont("-", "fonts/arial.ttf", 24 );
    lab2->setPosition(Vec2(visibleSize.width/2, sprbg->getPosition().y+25));
    lab2->setColor(Color3B::RED);
    addChild(lab2,4);
    auto lab3 = Label::createWithSystemFont("0", "fonts/arial.ttf", 24 );
    lab3->setPosition(Vec2(visibleSize.width/2+15, sprbg->getPosition().y+25));
    lab3->setColor(Color3B::RED);
    addChild(lab3,4);
    
    auto lab4 = Label::createWithSystemFont("阿尔巴尼克里克", "fonts/arial.ttf", 24 );
    lab4->setPosition(Vec2(visibleSize.width/4, sprbg->getPosition().y+25));
    lab4->setColor(Color3B::WHITE);
    addChild(lab4,4);
    auto lab5 = Label::createWithSystemFont("洛根利泰柠", "fonts/arial.ttf", 24 );
    lab5->setPosition(Vec2(visibleSize.width/4*3, sprbg->getPosition().y+25));
    lab5->setColor(Color3B::WHITE);
    addChild(lab5,4);
    
    auto lab6 = Label::createWithSystemFont("进攻", "fonts/arial.ttf", 24 );
    lab6->setPosition(Vec2(visibleSize.width/5, sprbg->getPosition().y-25-sprbg->getContentSize().height*2.75));
    lab6->setColor(Color3B::WHITE);
    addChild(lab6,4);
    auto lab7 = Label::createWithSystemFont("危险进攻", "fonts/arial.ttf", 24 );
    lab7->setPosition(Vec2(visibleSize.width/2, sprbg->getPosition().y-25-sprbg->getContentSize().height*2.75));
    lab7->setColor(Color3B::WHITE);
    addChild(lab7,4);
    auto lab8 = Label::createWithSystemFont("球权%", "fonts/arial.ttf", 24 );
    lab8->setPosition(Vec2(visibleSize.width/5*4, sprbg->getPosition().y-25-sprbg->getContentSize().height*2.75));
    lab8->setColor(Color3B::WHITE);
    addChild(lab8,4);
    
    
//    auto sprbgvisible = sprbg->getContentSize();
//    auto sprbgorigin = sprbg->getPosition();
//    
//    auto qmleft = Sprite::create("res/qiumen.png");
//    qmleft->setPosition(Vec2(0, sprbgorigin.y-sprbgvisible.height/2*(visibleSize.width/sprbg->getContentSize().width)));
//    qmleft->setAnchorPoint(Vec2(1, 0.5));
//    qmleft->setScale(visibleSize.width/sprbg->getContentSize().width);
//    qmleft->setRotation(180);
//    qmleft->setColor(Color3B::WHITE);
//    addChild(qmleft,5);
    
//    auto qmleft1 = Sprite::create("res/qiumen.png");
//    qmleft1->setPosition(Vec2(480, sprbgorigin.y-sprbgvisible.height/2*(visibleSize.width/sprbg->getContentSize().width)));
//    qmleft1->setAnchorPoint(Vec2(1, 0.5));
//    qmleft1->setScale(visibleSize.width/sprbg->getContentSize().width);
//    addChild(qmleft1,5);
    
    Jqshadow = Sprite::create("res/1.png");
    progress1 = ProgressTimer::create(Jqshadow);
    progress1->setPosition(Vec2(0, 700));
    progress1->setAnchorPoint(Vec2(0.5, 0));
    progress1->setScale(2.75);
    progress1->setOpacity(200);
    progress1->setMidpoint(Vec2(1, 0));//水平方向（1，y）表示从右向左，（0.y）表示从左向右
    progress1->setBarChangeRate(Vec2(0, 1));//纵向 (0,1)表示从下向上， （1，0）表示从上向下
    progress1->setType(kCCProgressTimerTypeBar);
    progress1->setPercentage(0);
    progress1->setRotation(150);
    
    sp = Sprite::create("res/jingong.png");
    sp->setOpacity(100);
    sp_wxjg = Sprite::create("res/weixianjingong.png");
    sp_kq = Sprite::create("res/kqyinying.png");
    progress = ProgressTimer::create(sp_kq);
    progress->setScale(2.75);
    progress->setPercentage(0);
    progress->setType(kCCProgressTimerTypeBar);
    progress->setOpacity(150);
    progress->setPosition(Vec2(0, sprbg->getPosition().y));
    progress->setAnchorPoint(Vec2(0, 1));
    progress->setMidpoint(Vec2(0, 0));//水平方向（1，y）表示从右向左，（0.y）表示从左向右
    progress->setBarChangeRate(Vec2(1, 0));//纵向
    
    addChild(progress1,3);
    addChild(progress,3);
    scheduleUpdate();
    
    progress->retain();
    progress1->retain();
    sp->retain();
    sp_wxjg->retain();
    sp_kq->retain();
    
    i = 0;
    state = 0;
}
//角球阴影三段技
void HelloWorld::jiaoqiu(int _state){
    auto sprbgvisible = sprbg->getContentSize();
    auto sprbgorigin = sprbg->getPosition();
    
    switch (state) {
        case 1:
            progress1->setPosition(Vec2(0, sprbgorigin.y));
            progress1->setRotation(150);
            cout<<"左上"<<endl;
            break;
            
        case 2:
            progress1->setPosition(Vec2(0, sprbgorigin.y-sprbgvisible.height*2.75));
            progress1->setRotation(30);
            cout<<"左下"<<endl;
            break;
        case 3:
            progress1->setPosition(Vec2(480, sprbgorigin.y));
            progress1->setRotation(-150);
            cout<<"右上"<<endl;
            break;
        case 4:
            progress1->setPosition(Vec2(480, sprbgorigin.y-sprbgvisible.height*2.75));
            progress1->setRotation(-30);
            cout<<"右下"<<endl;
            break;
        case 5:
            cout<<"中上"<<endl;
            break;
        case 6:
            cout<<"中下"<<endl;
            break;
            
        default:
            break;
    }
    
}
//控球状态
void HelloWorld::kongqiu(int _i){
    switch (i) {
        case 1:
            progress->setSprite(sp_kq);
            percent = 0;
            progress->setRotation(0);
            progress->setPosition(Vec2(0, sprbg->getPosition().y));
            progress->setAnchorPoint(Vec2(0, 1));
            progress->setMidpoint(Vec2(0, 0));//水平方向（1，y）表示从右向左，（0.y）表示从左向右
            progress->setBarChangeRate(Vec2(1, 0));//纵向
            cout<<"主控球"<<endl;
            break;
        case 2:
            progress->setSprite(sp);
            percent = 0;
            progress->setRotation(0);
            progress->setPosition(Vec2(0, sprbg->getPosition().y));
            progress->setAnchorPoint(Vec2(0, 1));
            progress->setMidpoint(Vec2(0, 0));//水平方向（1，y）表示从右向左，（0.y）表示从左向右
            progress->setBarChangeRate(Vec2(1, 0));//纵向
            cout<<"主进攻"<<endl;
            break;
        case 3:
            progress->setSprite(sp_wxjg);
            percent = 0;
            progress->setRotation(0);
            progress->setPosition(Vec2(0, sprbg->getPosition().y));
            progress->setAnchorPoint(Vec2(0, 1));
            progress->setMidpoint(Vec2(0, 0));//水平方向（1，y）表示从右向左，（0.y）表示从左向右
            progress->setBarChangeRate(Vec2(1, 0));//纵向
            cout<<"主危险进攻"<<endl;
            break;
        case 4:
            percent = 0;
            progress->setSprite(sp_kq);
            progress->setPosition(Vec2(480, sprbg->getPosition().y));
            progress->setAnchorPoint(Vec2(0, 0));
            progress->setRotation(180);
            cout<<"客控球"<<endl;
            break;
        case 5:
            percent = 0;
            progress->setSprite(sp);
            progress->setPosition(Vec2(480, sprbg->getPosition().y));
            progress->setAnchorPoint(Vec2(0, 0));
            progress->setRotation(180);
            cout<<"客进攻"<<endl;
            break;
        case 6:
            percent = 0;
            progress->setSprite(sp_wxjg);
            progress->setPosition(Vec2(480, sprbg->getPosition().y));
            progress->setAnchorPoint(Vec2(0, 0));
            progress->setRotation(180);
            cout<<"客危险进攻"<<endl;
            break;
        case 7:
            cout<<"主进球"<<endl;
            break;
        case 8:
            cout<<"客进球"<<endl;
            break;
            
        default:
            break;
    }
    
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    
    cout<<"hehahhahahahahah"<<endl;
    if (state>4) {
        state = 1;
    }
    if (i>5) {
        i=0;
    }
    kongqiu(++i);
    jiaoqiu(++state);
    //Close the cocos2d-x game scene and quit the application
//    Director::getInstance()->end();

//    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
