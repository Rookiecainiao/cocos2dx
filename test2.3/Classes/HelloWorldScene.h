#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void update(float time);
    
    //常用方法
public:
    void initUI();//UI布局初始化
    
    void startUI();//开赛前的信息
    
    void update_dianqiu(float dt);//点球，角球，球门球实时监测
    void jiaoqiu(int _state);//角球方法，点球，角球，球门球，掷界外球
    
    void kongqiu(int _i);//控球方法 状态：1、控球 2、进攻 3、危险进攻
    void move(Point _point);//球移动到指定的位置
    
    void labUI();//界面labUI的方法
    
    void update_q(float dt);//监测球的位置，当球到达指定位置后，执行球没有移动的时候的阴影动作
    void qshadow(Point _point);//球没有移动的时候的阴影动作
    
    void jinqiu();//进球的时的进球动画
    void lab_state(int _state);//遮罩层上的lab状态显示
    void lab_move(Point _point);
    
    void pai_RY();//红牌与黄牌
    
    void injured();//受伤
    
    void alternate();//替补
    
    void overtime();//加时与半场
    
    
public:
    void callback1(Node* sender);
    
    void netClick();
    void onHttpRequestCompleted(Node *sender ,void *data);
    //成员变量
public:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    int cc_state;
    
    cocos2d::ProgressTimer * progress;
    cocos2d::ProgressTimer * progress1;
    cocos2d::Sprite* football;
    cocos2d::Sprite* sprbg;
    cocos2d::Sprite* sp;
    cocos2d::Sprite* sp_wxjg;
    cocos2d::Sprite* sp_kq;
    cocos2d::Sprite*shadow1;
    cocos2d::Sprite*shadow2;
    cocos2d::Sprite*Jqshadow;
    cocos2d::Label*labstr1;
    
    Node*node_lab;//
    Node*node_jinqiu;//进球node
    Node*node_RY;//红黄牌node
    Node*startUInode;//显示比赛开始时的lab情况
    Sprite*lab_sp;//lab上的矩形
    Label* lab_st;//lab上的进攻状态
    Label* lab;//lab上的球队
    
private:
    bool state_dq = true;//点球状态判定
    bool state_kongqiu = true;//控球状态判定
    bool state_qmove = true;//球移动状态判定
    bool state_qjiewai = true;//角球状态判定
    
};

#endif // __HELLOWORLD_SCENE_H__
