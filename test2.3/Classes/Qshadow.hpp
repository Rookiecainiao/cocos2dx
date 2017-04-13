//
//  Qshadow.hpp
//  test2.3
//
//  Created by yaofuyu on 17/4/13.
//
//

#ifndef Qshadow_hpp
#define Qshadow_hpp

#include <stdio.h>
#include <cocos2d.h>

USING_NS_CC;

class Qshadow:public Layer
{
public:
    static Scene* creatScene();
    virtual bool init();
    CREATE_FUNC(Qshadow);
    
public:
    ProgressTimer* progress;
    Sprite* qshadow;
    int percent;
    
public:
    void createQshadow();
    void updateQshadow(float dt);
    void update(float dt);
};

#endif /* Qshadow_hpp */
