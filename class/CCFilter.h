#ifndef __CCFILTER__
#define __CCFILTER__

#include "cocos2d.h"
#include "CCGL.h"
#include "CCSpriteWidthFilter.h"

class CCSpriteWidthFilter;

USING_NS_CC;

class CCFilter : public CCObject
{
public:
	CCFilter();
	~CCFilter();

	virtual void initSprite(CCSpriteWidthFilter* sprite);
	virtual void draw();
	CCGLProgram* getProgram();

	const char* shaderName;
protected:
	CCGLProgram* m_program;
	void initProgram();
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* gl);
	virtual void setUniforms(CCGLProgram* gl);

	CCSpriteWidthFilter* m_sprite;
};
#endif