/******************************************************************
            Copyright (c) 2013, 天盟数码 研发中心
                   All rights reserved
         
    创建日期：  2014年7月1日   13时37分
    文件名称：  CCGrayFilter.h
    说    明：  灰度滤镜
    
    当前版本：  1.00
    作    者：  苍白的茧
    概    述：      

*******************************************************************/

#ifndef __CCFILTER_GRAY__H__
#define __CCFILTER_GRAY__H__

#include "CCFilter.h"

class CCSpriteWidthFilter;

class CCGrayFilter : public CCFilter
{
public:
	static CCGrayFilter* create();
	static CCGrayFilter* create(ccColor4F color);
	static CCGrayFilter* create(float r, float g, float b, float a = 1.0f);

	CCGrayFilter();

	void setColor(ccColor4F color);
	void setColor(float r, float g, float b, float a);
	void initSprite(CCSpriteWidthFilter* sprite);
	void draw();
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* program);
	virtual void setUniforms(CCGLProgram* program);

private:
	ccColor4F m_param;
};

#endif