//
//  DrawLines.cpp
//  Effect_Game_01
//
//  Created by Eddy on 12-3-28.
//  Copyright home 2012年. All rights reserved.
//
#include <iostream>
#include "DrawLines.h"

using namespace cocos2d ;
using namespace std;

DrawLines::DrawLines() 
{
    
}
DrawLines::~DrawLines() 
{
    
}
bool DrawLines::init()
{
    bool bRet = false;
    do {
        CCGLProgram * glShaderProgram = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor);
        this->setShaderProgram(glShaderProgram);
        m_pParticle = CCParticleSystemQuad::particleWithFile("Particle.plist") ;
        this->addChild(m_pParticle, 10) ;
        m_pParticle->setVisible(false) ;
        memset(m_pointPath, 0, sizeof(m_pointPath)) ;
        m_timer = 0 ;
        m_touchBeganPoint = m_touchEndPoint = ccp(0, 0) ;
        bRet = true ;
    } while (0);
    return true ;
}
void DrawLines::line()
{
    if (m_Index<3 || m_Index > 1024) {
		return;
	}
	CCPoint *p = m_pointPath ;
	//CCPoint vertexMiddle[1024]={ccp(0.0, 0.0)};
    CCPoint*vertexMiddle = new CCPoint[m_Index] ;
	//memset(vertexMiddle, 0, sizeof(vertexMiddle)) ;
	memcpy(vertexMiddle, p, sizeof(CCPoint)*m_Index);
	
	CCPoint pt = ccpSub(p[m_Index-1], p[m_Index-2]);
	GLfloat angle = ccpToAngle(pt);
	vertexMiddle[m_Index-1].x += cosf(angle)*10*CC_CONTENT_SCALE_FACTOR();
	vertexMiddle[m_Index-1].y += sinf(angle)*10*CC_CONTENT_SCALE_FACTOR();
    
	CCPoint vertexTop[1024]={ccp(0.0, 0.0)};
	
	vertexTop[0].x = p[m_Index-1].x + cosf(angle)*10*CC_CONTENT_SCALE_FACTOR();
	vertexTop[0].y = p[m_Index-1].y + sinf(angle)*10*CC_CONTENT_SCALE_FACTOR();
	
	GLint count1 = 1;
	
	for (int i = (m_Index-2); i>0; --i) {
		float w = i*0.5f ;
		if (w < 3)w = 3 ;
		else if(w > 8)w = 8 ;
		triangle(&(vertexTop[count1]),p[i],p[i-1], w);
		count1++;
	}
	vertexTop[count1++] = p[0];
    
	CCPoint vertexBottom[1024]={ccp(0.0, 0.0)};
	
	vertexBottom[0].x = p[m_Index-1].x + cosf(angle)*10*CC_CONTENT_SCALE_FACTOR();
	vertexBottom[0].y = p[m_Index-1].y + sinf(angle)*10*CC_CONTENT_SCALE_FACTOR();
	
	GLint count2 = 1;
	
	for (int i = (m_Index-2); i>0; --i) {
		float w = i*0.5f ;
		if (w < 3)w = 3 ;
		else if(w > 8)w =8 ;
		triangle(&(vertexBottom[count2]),p[i],p[i-1], -w);
		count2++;
	}
	vertexBottom[count2++] = p[0];
	
	CCPoint vertexTriangle[512] ={ccp(0.0, 0.0)} ;
	CCPoint*vertexCpy = vertexTriangle;
	GLubyte lineColors[1024] = {0};
	GLubyte*lineCpy = lineColors ;
	//1
	*vertexCpy = vertexMiddle[m_Index-1] ;
	*lineCpy = MIDDLE_POINT_R; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_G; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_B; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_A; lineCpy++ ;
	vertexCpy++ ;
	
	*vertexCpy = vertexMiddle[m_Index-2] ;
	*lineCpy = MIDDLE_POINT_R; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_G; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_B; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_A; lineCpy++ ;
	vertexCpy++ ;
	
	*vertexCpy = vertexTop[1] ;
	*lineCpy = TOP_POINT_R; lineCpy++ ;
	*lineCpy = TOP_POINT_G; lineCpy++ ;
	*lineCpy = TOP_POINT_B; lineCpy++ ;
	*lineCpy = TOP_POINT_A; lineCpy++ ;
	vertexCpy++ ;
	
	*vertexCpy = vertexMiddle[m_Index-1] ;
	*lineCpy = MIDDLE_POINT_R; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_G; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_B; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_A; lineCpy++ ;
	vertexCpy++ ;
	*vertexCpy = vertexBottom[1] ;
	*lineCpy = BOTTOM_POINT_R; lineCpy++ ;
	*lineCpy = BOTTOM_POINT_G; lineCpy++ ;
	*lineCpy = BOTTOM_POINT_B; lineCpy++ ;
	*lineCpy = BOTTOM_POINT_A; lineCpy++ ;
	vertexCpy++ ;
	*vertexCpy = vertexMiddle[m_Index-2] ;
	*lineCpy = MIDDLE_POINT_R; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_G; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_B; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_A; lineCpy++ ;
	vertexCpy++ ;
	
	for (int i = 0; i < m_Index-2; i++) {
		//上半个四边形
		*vertexCpy = vertexMiddle[m_Index-(i+2)] ;
		*lineCpy = MIDDLE_POINT_R; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_G; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_B; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		*vertexCpy = vertexMiddle[m_Index-(i+3)] ;
		*lineCpy = MIDDLE_POINT_R; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_G; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_B; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		*vertexCpy = vertexTop[i+1] ;
		*lineCpy = TOP_POINT_R; lineCpy++ ;
		*lineCpy = TOP_POINT_G; lineCpy++ ;
		*lineCpy = TOP_POINT_B; lineCpy++ ;
		*lineCpy = TOP_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		
		*vertexCpy = vertexTop[i+1] ;
		*lineCpy = TOP_POINT_R; lineCpy++ ;
		*lineCpy = TOP_POINT_G; lineCpy++ ;
		*lineCpy = TOP_POINT_B; lineCpy++ ;
		*lineCpy = TOP_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		*vertexCpy = vertexMiddle[m_Index-(i+3)] ;
		*lineCpy = MIDDLE_POINT_R; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_G; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_B; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		*vertexCpy = vertexTop[i+2] ;
		*lineCpy = TOP_POINT_R; lineCpy++ ;
		*lineCpy = TOP_POINT_G; lineCpy++ ;
		*lineCpy = TOP_POINT_B; lineCpy++ ;
		*lineCpy = TOP_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		
		//下半个四边形
		*vertexCpy = vertexBottom[i+1] ;
		*lineCpy = BOTTOM_POINT_R; lineCpy++ ;
		*lineCpy = BOTTOM_POINT_G; lineCpy++ ;
		*lineCpy = BOTTOM_POINT_B; lineCpy++ ;
		*lineCpy = BOTTOM_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		*vertexCpy = vertexBottom[i+2] ;
		*lineCpy = BOTTOM_POINT_R; lineCpy++ ;
		*lineCpy = BOTTOM_POINT_G; lineCpy++ ;
		*lineCpy = BOTTOM_POINT_B; lineCpy++ ;
		*lineCpy = BOTTOM_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		*vertexCpy = vertexMiddle[m_Index-(i+2)] ;
		*lineCpy = MIDDLE_POINT_R; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_G; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_B; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		
		*vertexCpy = vertexMiddle[m_Index-(i+2)] ;
		*lineCpy = MIDDLE_POINT_R; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_G; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_B; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		*vertexCpy = vertexBottom[i+2] ;
		*lineCpy = BOTTOM_POINT_R; lineCpy++ ;
		*lineCpy = BOTTOM_POINT_G; lineCpy++ ;
		*lineCpy = BOTTOM_POINT_B; lineCpy++ ;
		*lineCpy = BOTTOM_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		*vertexCpy = vertexMiddle[m_Index-(i+3)] ;
		*lineCpy = MIDDLE_POINT_R; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_G; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_B; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_A; lineCpy++ ;
		vertexCpy++ ;
	}
    glDisable(GL_TEXTURE_2D);
//    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//	glDisable(GL_TEXTURE_2D);
//	
//	glVertexPointer(2, GL_FLOAT, 0, vertexTriangle);
//	glEnableClientState(GL_VERTEX_ARRAY);
//	glColorPointer(4, GL_UNSIGNED_BYTE, 0, lineColors);
//	glEnableClientState(GL_COLOR_ARRAY);
//	glDrawArrays(GL_TRIANGLES, 0, (GLint)((vertexCpy-vertexTriangle-1)));
//    
//	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//	glEnable(GL_TEXTURE_2D);
    


    //以下代码为上面代码的2.0版本
    // Enable the needed vertex attributes.
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color );
    // Tell OpenGL ES 2.0 to use the shader program assigned in the init of this node.
    this->getShaderProgram()->use();
    this->getShaderProgram()->setUniformForModelViewProjectionMatrix();
    
   
    ccVertex2F vetexes[512]={0};
    for (int i=0; i<512; i++) {
        vetexes[i].x=vertexTriangle[i].x;
        vetexes[i].y=vertexTriangle[i].y;
    }
    // Pass the verticies to draw to OpenGL
    glEnableVertexAttribArray(kCCVertexAttribFlag_Position);
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_TRUE, 0,vetexes);

    // Pass the colors of the vertices to draw to OpenGL
    glEnableVertexAttribArray(kCCVertexAttribFlag_Color);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, lineColors);

    GLint numberTo=(GLint)((vertexCpy-vertexTriangle-1));
    glDrawArrays(GL_TRIANGLES, 0,numberTo );

    glEnable(GL_TEXTURE_2D);
    delete [] vertexMiddle ;
}
void DrawLines::erasureNail() 
{
    if ( m_Index < 3 || m_Index > 1024)
        return ;
    
    CCPoint*p = m_pointPath ;
    m_Index-- ;
    memmove(p, &(p[1]), sizeof(CCPoint)*(m_Index)) ;
}
void DrawLines::draw() 
{
    long dt = time(NULL) ;
    
    if ( m_timer > 10 )
    {
        m_timer = 0 ;
        erasureNail() ;
    }
    else {
        m_timer += dt ;
    }
    line() ;
}
void DrawLines::triangle(CCPoint* vertex, CCPoint p1, CCPoint p2, GLfloat w)
{
    CCPoint pt = ccpSub(p1, p2);
	GLfloat angle = ccpToAngle(pt);
	
	GLfloat x = sinf(angle) * w;
	GLfloat y = cosf(angle) * w;
	vertex->x = p1.x+x;
	vertex->y = p1.y-y;
}
void DrawLines::ccTouchesBegan(CCSet* touches, CCEvent* event) 
{
    CCTouch*touch = (CCTouch*)touches->anyObject() ;
    CCPoint touchPoint = touch->getLocationInView() ;
    touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint) ;
    m_touchEndPoint = m_touchBeganPoint = touchPoint ;
	
	m_bTouched = true ;
	m_Index = 0 ;
	m_pointPath[m_Index++] = ccpMult(touchPoint, CC_CONTENT_SCALE_FACTOR())  ;
	m_pParticle->resetSystem() ;
	m_pParticle->setPosition(touchPoint) ;
}
void DrawLines::ccTouchesMoved(CCSet* touches, CCEvent* event) 
{
    CCTouch*touch = (CCTouch*)touches->anyObject() ;
    m_touchBeganPoint = touch->getLocationInView() ;
    m_touchBeganPoint = CCDirector::sharedDirector()->convertToGL(m_touchBeganPoint) ;
    
    m_touchEndPoint = touch->getPreviousLocationInView() ;
    m_touchEndPoint = CCDirector::sharedDirector()->convertToGL(m_touchEndPoint) ;
    
    m_bTouched = true ;
    m_pParticle->setVisible(true) ;
    m_pParticle->setPosition(m_touchBeganPoint) ;
    
    CCPoint pointTmp = ccpMult(m_touchBeganPoint, CC_CONTENT_SCALE_FACTOR());
	float distance = ccpDistance(pointTmp, m_pointPath[m_Index]) ;
	if ( distance < 5  )return ;
	if ( m_Index < POINT_NUM )
	{
		m_pointPath[m_Index++] = pointTmp ;
	}
	else {
		memmove(m_pointPath, &m_pointPath[1], sizeof(CCPoint)*(POINT_NUM-1)) ;
		m_pointPath[m_Index-1] = pointTmp ;
	}
}
void DrawLines::ccTouchesEnded(CCSet* touches, CCEvent* event) 
{
    CCTouch*touch = (CCTouch*)touches->anyObject() ;
    CCPoint touchPoint = touch->getLocationInView() ;
    touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint) ;
	m_bTouched = false ;
	m_touchEndPoint = touchPoint ;
	m_pParticle->stopSystem() ;
}
