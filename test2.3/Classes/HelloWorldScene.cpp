#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "iostream"
#include "ui/UIButton.h"
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
using namespace std;
USING_NS_CC;
using namespace ui;
using namespace network;

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
    
    
    
    startUI();
    cc_state=0;
//    schedule(schedule_selector(HelloWorld::update_q), 0.5);
    return true;
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
    CallFuncN * callfunc = CallFuncN::create(CC_CALLBACK_0(HelloWorld::callback1, this,node_RY));
    
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
//状态判定：1角球、球门球、点球、掷界外球状态 ； 2、控球状态 ； 3、球移动状态 ；
    
    //            state_dq;//点球状态判定
    //            state_kongqiu;//控球状态判定
    //            state_qmove;//球移动状态判定
    //           state_qjiewai;//角球状态判定
    
    switch (cc_state) {
            //状态1：角球
        case 1:
            if (state_dq) {
                jiaoqiu(1);
                progress->setVisible(false);
                progress1->setVisible(true);
            }
            state_dq = false;
            state_kongqiu = true;
            state_qmove = true;
            state_qjiewai = true;
            node_lab->setVisible(false);
            break;
            //状态2：控球
        case 2:
            //sta1=0;sta3=0;sta4=0;->true
            //if(sta2){fangf}
            //sta2->false
            progress->setVisible(true);
            progress1->setVisible(false);
            if (state_kongqiu) {
                kongqiu(1);
//                lab_state();
//                lab_move(Vec2(300, 700));
            }
//            unschedule(schedule_selector(HelloWorld::update_dianqiu));
            state_dq = true;
            state_kongqiu = false;
            state_qmove = true;
            state_qjiewai = true;
            node_lab->setVisible(true);
            break;
            //状态3：球移动
        case 3:
            unschedule(schedule_selector(HelloWorld::update_dianqiu));
            progress1->setVisible(false);
            progress->setVisible(false);
            move(Vec2(300, 400));
            state_dq = true;
            state_kongqiu = true;
            state_qjiewai = true;
            node_lab->setVisible(true);
            break;
        case 4:
            break;
        default:
            break;
    }
    
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
//    sprbg->setScale(visibleSize.width/sprbg->getContentSize().width);
    //    sprbg->setContentSize(Size(640,217.6));
    addChild(sprbg,2);
    auto sprsize = sprbg->getContentSize();
    cout<<sprsize.width<<"    "<<sprsize.height<<endl;
    
    auto btn = Button::create("res/u759.png");
    btn->setPosition(Vec2(20, visibleSize.height));
    btn->setAnchorPoint(Vec2(0.5,1));
//    btn->setScale(4);
    btn->addClickEventListener(CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    addChild(btn,2);
    
    
    
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
//    progress1->setScale(2.75);
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
//    progress->setVisible(false);
//    progress1->setVisible(false);
    addChild(progress1,3);
    addChild(progress,3);
//    scheduleUpdate();
    
    labUI();
}
//角球阴影三段技
void HelloWorld::update_dianqiu(float dt){
    if (percent>=200) {
        percent = 0;
    }
    percent+=5;
    progress->setPercentage(percent);
    progress1->setPercentage(percent);
    cout<<"update_dianqiu"<<endl;
}
//角球方法，点球，角球，球门球，掷界外球
void HelloWorld::jiaoqiu(int _state){
    initUI();
    progress->setVisible(false);
    football->setVisible(true);
    auto sprbgvisible = sprbg->getContentSize();
    auto sprbgorigin = sprbg->getPosition();
    
    switch (cc_state) {
        case 1:
            progress1->setPosition(Vec2(sprbgorigin.x-sprbgvisible.width/2, sprbgorigin.y));
            progress1->setRotation(150);
            cout<<"左上"<<endl;
            break;
        case 2:
            progress1->setPosition(Vec2(sprbgorigin.x-sprbgvisible.width/2, sprbgorigin.y-sprbgvisible.height));
            progress1->setRotation(30);
            cout<<"左下"<<endl;
            break;
        case 3:
            progress1->setPosition(Vec2(sprbgorigin.x+sprbgvisible.width/2, sprbgorigin.y));
            progress1->setRotation(-150);
            cout<<"右上"<<endl;
            break;
        case 4:
            progress1->setPosition(Vec2(sprbgorigin.x+sprbgvisible.width/2, sprbgorigin.y-sprbgvisible.height));
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
    football->stopAllActions();
    football->setPosition(progress1->getPosition());
    schedule(schedule_selector(HelloWorld::update_dianqiu), 0.05);
}
//控球状态的阴影特效变换
void HelloWorld::kongqiu(int _i){
//    cc_state = _i;
    initUI();
    progress1->setVisible(false);
    switch (cc_state) {
        case 1:
            progress->setSprite(sp_kq);
//            percent = 0;
            progress->setRotation(0);
            progress->setPosition(Vec2(sprbg->getPosition().x-sprbg->getContentSize().width/2, sprbg->getPosition().y));
            progress->setAnchorPoint(Vec2(0, 1));
            progress->setMidpoint(Vec2(0, 0));//水平方向（1，y）表示从右向左，（0.y）表示从左向右
            progress->setBarChangeRate(Vec2(1, 0));//纵向
            cout<<"主控球"<<endl;
            lab_move(Vec2(sprbg->getPosition().x-50, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            lab_state(cc_state);
            break;
        case 2:
            progress->setSprite(sp);
            percent = 0;
            progress->setRotation(0);
            progress->setPosition(Vec2(sprbg->getPosition().x-sprbg->getContentSize().width/2, sprbg->getPosition().y));
            progress->setAnchorPoint(Vec2(0, 1));
            progress->setMidpoint(Vec2(0, 0));//水平方向（1，y）表示从右向左，（0.y）表示从左向右
            progress->setBarChangeRate(Vec2(1, 0));//纵向
            cout<<"主进攻"<<endl;
            lab_move(Vec2(sprbg->getPosition().x+sprbg->getContentSize().width/8, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            lab_state(cc_state);
            break;
        case 3:
            progress->setSprite(sp_wxjg);
            percent = 0;
            progress->setRotation(0);
            progress->setPosition(Vec2(sprbg->getPosition().x-sprbg->getContentSize().width/2, sprbg->getPosition().y));
            progress->setAnchorPoint(Vec2(0, 1));
            progress->setMidpoint(Vec2(0, 0));//水平方向（1，y）表示从右向左，（0.y）表示从左向右
            progress->setBarChangeRate(Vec2(1, 0));//纵向
            cout<<"主危险进攻"<<endl;
            lab_move(Vec2(sprbg->getPosition().x+sprbg->getContentSize().width/4, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            lab_state(cc_state);
            break;
        case 4:
            percent = 0;
            progress->setSprite(sp_kq);
            progress->setPosition(Vec2(sprbg->getPosition().x+sprbg->getContentSize().width/2, sprbg->getPosition().y));
            progress->setAnchorPoint(Vec2(0, 0));
            progress->setRotation(180);
            cout<<"客控球"<<endl;
            lab_move(Vec2(sprbg->getPosition().x+50, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            lab_state(cc_state);
            break;
        case 5:
            percent = 0;
            progress->setSprite(sp);
            progress->setPosition(Vec2(sprbg->getPosition().x+sprbg->getContentSize().width/2, sprbg->getPosition().y));
            progress->setAnchorPoint(Vec2(0, 0));
            progress->setRotation(180);
            lab_move(Vec2(sprbg->getPosition().x-sprbg->getContentSize().width/8, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            lab_state(cc_state);
            cout<<"客进攻"<<endl;
            break;
        case 6:
            percent = 0;
            progress->setSprite(sp_wxjg);
            progress->setPosition(Vec2(sprbg->getPosition().x+sprbg->getContentSize().width/2, sprbg->getPosition().y));
            progress->setAnchorPoint(Vec2(0, 0));
            progress->setRotation(180);
            lab_move(Vec2(sprbg->getPosition().x-sprbg->getContentSize().width/4, sprbg->getPosition().y-sprbg->getContentSize().height/2));
            cout<<"客危险进攻"<<endl;
            lab_state(cc_state);
            break;
        case 7:
            progress->setSprite(sp_wxjg);
            percent = 0;
            progress->setRotation(0);
            progress->setPosition(Vec2(sprbg->getPosition().x-sprbg->getContentSize().width/2, sprbg->getPosition().y));
            progress->setAnchorPoint(Vec2(0, 1));
            progress->setMidpoint(Vec2(0, 0));//水平方向（1，y）表示从右向左，（0.y）表示从左向右
            progress->setBarChangeRate(Vec2(1, 0));//纵向
//            progress->setScaleX(1.2);
            cout<<"主危险进攻深入"<<endl;
            break;
        case 8:
            percent = 0;
            progress->setSprite(sp_wxjg);
            progress->setPosition(Vec2(sprbg->getPosition().x+sprbg->getContentSize().width/2, sprbg->getPosition().y));
            progress->setAnchorPoint(Vec2(0, 0));
            progress->setRotation(180);
//            progress->setScaleX(1.2);
            cout<<"客危险进攻深入"<<endl;
            break;
            
        default:
            break;
    }
    schedule(schedule_selector(HelloWorld::update_dianqiu));
}
//labUI的显示
void HelloWorld::labUI()
{
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
    lab6->setPosition(Vec2(visibleSize.width/5, sprbg->getPosition().y-25-sprbg->getContentSize().height));
    lab6->setColor(Color3B::WHITE);
    addChild(lab6,4);
    auto lab7 = Label::createWithSystemFont("危险进攻", "fonts/arial.ttf", 24 );
    lab7->setPosition(Vec2(visibleSize.width/2, sprbg->getPosition().y-25-sprbg->getContentSize().height));
    lab7->setColor(Color3B::WHITE);
    addChild(lab7,4);
    auto lab8 = Label::createWithSystemFont("球权%", "fonts/arial.ttf", 24 );
    lab8->setPosition(Vec2(visibleSize.width/5*4, sprbg->getPosition().y-25-sprbg->getContentSize().height));
    lab8->setColor(Color3B::WHITE);
    addChild(lab8,4);

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
    cc_state++;

    cout<<cc_state<<endl;
    if (cc_state>6) {
        cc_state=0;
    }
    this->removeAllChildren();
//    kongqiu(cc_state);
//    jinqiu();
    jiaoqiu(2);
    
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
    qshadow(Vec2(460, 700));
    
}
//进球时的动画展示
void HelloWorld::jinqiu(){
    initUI();
    auto jinqiu = Sprite::create("res/jinqiu.png");
    jinqiu->setPosition(Vec2::ZERO);
    auto lab_jinqiu = Label::createWithSystemFont("进球", "fonts/arial.ttf", 24);
    lab_jinqiu->setPosition(Vec2(-60, 0));
    node_jinqiu  = Node::create();
    node_jinqiu->addChild(jinqiu);
    node_jinqiu->addChild(lab_jinqiu);
    addChild(node_jinqiu,5);
    node_jinqiu->setPosition(Vec2(sprbg->getPosition().x, sprbg->getPosition().y-sprbg->getContentSize().height/2));
    node_jinqiu->setCascadeOpacityEnabled(true);
    node_jinqiu->setOpacity(0);
    auto act_node = FadeTo::create(1,255);
    auto act = FadeTo::create(1, 0);
    node_jinqiu->runAction(RepeatForever::create(Sequence::create(act_node,act, NULL)));
}
//进攻时的文字lab的动态展示
void HelloWorld::lab_state(int _state){
    node_lab->setVisible(true);
    switch (_state) {
        case 1:
            lab_sp->setColor(Color3B::BLACK);
            lab_st->setString("控球");
            lab->setString("黑影队");
            lab_st->setPosition(Vec2(lab_sp->getPosition().x-20, lab_sp->getPosition().y));
            lab_st->setAnchorPoint(Vec2(1, 1));
            lab->setPosition(Vec2(lab_sp->getPosition().x-20, lab_sp->getPosition().y));
            lab->setAnchorPoint(Vec2(1, 0));
            break;
        case 2:
            lab_sp->setColor(Color3B::BLACK);
            lab_st->setString("进攻");
            lab->setString("黑影队");
            lab_st->setPosition(Vec2(lab_sp->getPosition().x-20, lab_sp->getPosition().y));
            lab_st->setAnchorPoint(Vec2(1, 1));
            lab->setPosition(Vec2(lab_sp->getPosition().x-20, lab_sp->getPosition().y));
            lab->setAnchorPoint(Vec2(1, 0));
            break;
        case 3:
            lab_sp->setColor(Color3B::BLACK);
            lab_st->setString("危险进攻");
            lab->setString("黑影队");
            lab_st->setPosition(Vec2(lab_sp->getPosition().x-20, lab_sp->getPosition().y));
            lab_st->setAnchorPoint(Vec2(1, 1));
            lab->setPosition(Vec2(lab_sp->getPosition().x-20, lab_sp->getPosition().y));
            lab->setAnchorPoint(Vec2(1, 0));
            break;
        case 4:
            lab_sp->setColor(Color3B::WHITE);
            lab_st->setString("控球");
            lab_st->setPosition(Vec2(lab_sp->getPosition().x+20, lab_sp->getPosition().y));
            lab_st->setAnchorPoint(Vec2(0, 1));
            lab->setString("白影队");
            lab->setPosition(Vec2(lab_sp->getPosition().x+20, lab_sp->getPosition().y));
            lab->setAnchorPoint(Vec2(0, 0));
            break;
        case 5:
            lab_sp->setColor(Color3B::WHITE);
            lab_st->setString("进攻");
            lab_st->setPosition(Vec2(lab_sp->getPosition().x+20, lab_sp->getPosition().y));
            lab_st->setAnchorPoint(Vec2(0, 1));
            lab->setString("白影队");
            lab->setPosition(Vec2(lab_sp->getPosition().x+20, lab_sp->getPosition().y));
            lab->setAnchorPoint(Vec2(0, 0));
            break;
        case 6:
            lab_sp->setColor(Color3B::WHITE);
            lab_st->setString("危险进攻");
            lab_st->setPosition(Vec2(lab_sp->getPosition().x+20, lab_sp->getPosition().y));
            lab_st->setAnchorPoint(Vec2(0, 1));
            lab->setString("白影队");
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
void HelloWorld::pai_RY(){
    node_RY->setPosition(Vec2(sprbg->getPosition().x, sprbg->getPosition().y-sprbg->getContentSize().height/2-40));
    addChild(node_RY,5);
    auto pai_spr = Sprite::create();
    auto lab_pai = Label::createWithSystemFont("红牌", "fonts/arial.ttf", 24);
    node_RY->setCascadeOpacityEnabled(true);
    if (true) {
        pai_spr = Sprite::create("res/hongpai.png");
        lab_pai->setString("红牌");
    }else{
        pai_spr = Sprite::create("res/huangpai.png");
        lab_pai->setString("黄牌");
    }
    pai_spr->setPosition(Vec2::ZERO);
    lab_pai->setPosition(Vec2(-30, 0));
    node_RY->addChild(lab_pai);
    node_RY->addChild(pai_spr);
    node_RY->setOpacity(0);
    auto act_pai = FadeTo::create(0.5, 255);
    auto act2_pai = MoveBy::create(0.5, Vec2(0, 40));
    node_RY->runAction(Spawn::create(act_pai,act2_pai, NULL));
    
}
//受伤
void HelloWorld::injured(){
    initUI();
    auto lab_injured = Label::createWithSystemFont("受伤", "fonts/arial.ttf", 35);
    addChild(lab_injured,5);
    lab_injured->setPosition(Vec2(sprbg->getPosition().x, sprbg->getPosition().y-sprbg->getContentSize().height/2));
}
//替补
void HelloWorld::alternate(){
    
}
//加时与半场
void HelloWorld::overtime(){
    initUI();
    auto lab_injured = Label::createWithSystemFont("半场", "fonts/arial.ttf", 35);
    addChild(lab_injured,5);
    lab_injured->setPosition(Vec2(sprbg->getPosition().x, sprbg->getPosition().y-sprbg->getContentSize().height/2));
}
//network 异步请求与处理
void HelloWorld::netClick(){
    HttpRequest * request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::POST);
    request->setUrl("www.baidu.com");
    char* ss = "hello,world";
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
    size_t begin = recieveData.find("<body")+6;
    size_t end = recieveData.find("</body>");
    string result(recieveData.begin(),recieveData.end());
    
}
