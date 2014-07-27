#include "CCFilter.h"
//²Ô°×µÄ¼ë

class CCSpriteWidthFilter;

class CCWaveFilter : public CCFilter
{
public:
	static CCWaveFilter* create();
	static CCWaveFilter* create(float pWidth, float pHeight);
	CCWaveFilter();
	CCWaveFilter(float pWidth, float pHeight);

	void initSprite(CCSpriteWidthFilter* sprite);
	void draw();
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* program);
	virtual void setUniforms(CCGLProgram* program);
private:
	float m_time;
	CCPoint m_resolution;
};