/******************************************************************
            Copyright (c) 2013, dreamfairy
                   All rights reserved
         
    创建日期：  2014年7月1日   15时44分
    文件名称：  CCColorFlashFilter.h
    说    明：  颜色闪烁
    
    当前版本：  1.00
    作    者：  苍白的茧
    概    述：      

*******************************************************************/

#ifndef __COLORFLASHFILTER_H__
#define __COLORFLASHFILTER_H__

#include "CCFilter.h"

class CCSpriteWidthFilter;

class CCColorFlashFilter : public CCFilter
{
public:
	static CCColorFlashFilter* create();
	static CCColorFlashFilter* create(float interval, float r, float g, float b);

	CCColorFlashFilter();

	void setColor(float r, float g, float b);
	void setIntervalFrame(float interval);
	void initSprite(CCSpriteWidthFilter* sprite);
	void draw();
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* program);
	virtual void setUniforms(CCGLProgram* program);
private:
	float m_count;
	float m_interval;
	ccColor4F m_color; 
	float m_percent;
};

#endif // !__COLORFLASHFILTER_H__
