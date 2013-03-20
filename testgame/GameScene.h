//
//  GameScene.h
//  FruitGame
//
//  Created by 志华 温 on 12-12-10.
//  Copyright (c) 2012年 bh. All rights reserved.
//

#ifndef FruitGame_GameScene_h
#define FruitGame_GameScene_h

#include "cocos2d.h"

class GameScene : public cocos2d::CCLayer{
    
public:
    ~GameScene();
    GameScene();
    static cocos2d::CCScene* scene();
    
public:
    virtual void onEnterTransitionDidFinish();
};


#endif
