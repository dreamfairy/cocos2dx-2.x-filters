#ifndef __GOD_RAY_FILTER_H__
#define __GOD_RAY_FILTER_H__

#include "CCFilter.h"

class CCGodRayFilter : public CCFilter
{
public:
	static CCGodRayFilter* create();

	CCGodRayFilter();

	void setLightPos(float x, float y);
	void initSprite(CCSpriteWidthFilter* sprite);
	void draw();
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* program);
	virtual void setUniforms(CCGLProgram* program);
private:
	CCPoint m_lightPos;
	float m_deltaTime;
	bool m_useUserPos;
};
#endif