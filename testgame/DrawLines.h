//
//  DrawLines.h
//  Effect_Game_01
//
//  Created by Eddy on 12-3-28.
//  Copyright home 2012年. All rights reserved.
//

#import "cocos2d.h"
#define POINT_NUM 16
#define MIDDLE_POINT_R 255
#define MIDDLE_POINT_G 255
#define MIDDLE_POINT_B 255
#define MIDDLE_POINT_A 255
#define TOP_POINT_R	255
#define TOP_POINT_G	200
#define TOP_POINT_B	0
#define TOP_POINT_A	255
#define BOTTOM_POINT_R 255
#define BOTTOM_POINT_G 255
#define BOTTOM_POINT_B 0
#define BOTTOM_POINT_A 255
namespace cocos2d{
class DrawLines : public CCLayerColor {
protected:

	CCPoint                 m_pointPath[POINT_NUM] ;
	CCParticleSystem*       m_pParticle ;
	unsigned long			m_Index ;
	bool                    m_bTouched ;
    CCPoint                 m_touchBeganPoint ;
	CCPoint                 m_touchEndPoint ;
	long                   m_timer ;
public:
    CCPoint getTouchBeganPoint(){return m_touchBeganPoint ;}
    CCPoint getTouchEndPoint(){return m_touchEndPoint ;} ;
    bool getbTouched() {return m_bTouched ;}
    
    DrawLines() ;
    virtual ~DrawLines() ;
    bool init() ;
    void line();
    void erasureNail() ;
    void draw() ;
    void triangle(CCPoint* vertex, CCPoint p1, CCPoint p2, GLfloat w) ;
    void ccTouchesBegan(CCSet* touches, CCEvent* event) ;
    void ccTouchesMoved(CCSet* touches, CCEvent* event) ;
    void ccTouchesEnded(CCSet* touches, CCEvent* event) ;
} ;

}