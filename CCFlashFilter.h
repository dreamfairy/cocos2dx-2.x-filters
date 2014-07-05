/******************************************************************
            Copyright (c) 2013, 天盟数码 研发中心
                   All rights reserved
         
    创建日期：  2014年7月1日   13时37分
    文件名称：  CCFlashFilter.h
    说    明：  闪烁滤镜
    
    当前版本：  1.00
    作    者：  苍白的茧
    概    述：      

*******************************************************************/

#ifndef __FLASHFILETE_H__
#define __FLASHFILETE_H__

#include "CCFilter.h"

class CCSpriteWidthFilter;

class CCFlashFilter : public CCFilter
{
public:
	static CCFlashFilter* create();
	static CCFlashFilter* create(int intervalFrame);

	CCFlashFilter();

	void setIntervalFrame(int intervalFrame);
	void initSprite(CCSpriteWidthFilter* sprite);
	void draw();
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* program);
	virtual void setUniforms(CCGLProgram* program);

private:
	int m_currentFrameCount;
	int m_frameInterval;
	float m_alpha;
};

#endif