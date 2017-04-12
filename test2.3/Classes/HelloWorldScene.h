#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

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
    void jiaoqiu(int _state);//角球方法
    void kongqiu(int _i);//控球方法 状态：1、控球 2、进攻 3、危险进攻
    
    //成员变量
public:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    int state;
    int i;
    
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
};

#endif // __HELLOWORLD_SCENE_H__
