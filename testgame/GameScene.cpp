//
//  GameScene.cpp
//  FruitGame
//
//  Created by 志华 温 on 12-12-10.
//  Copyright (c) 2012年 bh. All rights reserved.
//

#include <iostream>
#include "GameScene.h"
#include "DrawLines.h"

using namespace cocos2d;
using namespace std;

GameScene::GameScene(){
    
}

GameScene::~GameScene(){
    
}

CCScene * GameScene::scene()
{
    CCScene *scene = CCScene::create();
    GameScene* layer = new GameScene();
    scene->addChild(layer);
    layer->release();
    return scene;
}


void GameScene::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
    DrawLines * m_pLineLayer = new DrawLines() ; 
    m_pLineLayer->init() ;
    m_pLineLayer->setTouchEnabled(true) ;
	this->addChild(m_pLineLayer, 10) ;
}
