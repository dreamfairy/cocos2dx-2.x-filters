#include "CCColorFlashFilter.h"

CCColorFlashFilter* CCColorFlashFilter::create()
{
	CCColorFlashFilter* filter = new CCColorFlashFilter();
	return filter;
}

CCColorFlashFilter* CCColorFlashFilter::create( float interval, float r, float g, float b )
{
	CCColorFlashFilter* filter = CCColorFlashFilter::create();
	filter->setColor(r,g,b);
	filter->setIntervalFrame(interval);
	return filter;
}

CCColorFlashFilter::CCColorFlashFilter()
{
	m_color.r = 1;
	m_color.g = 0;
	m_color.b = 0;

	m_count = 0;
	m_interval = 1;

	this->shaderName = "Filter_ColorFlash";
}

void CCColorFlashFilter::setColor( float r, float g, float b )
{
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
}

void CCColorFlashFilter::setIntervalFrame( float interval )
{
	m_interval = interval;
	m_count = 0;
}

void CCColorFlashFilter::initSprite( CCSpriteWidthFilter* sprite )
{
	m_sprite = sprite;
	initProgram();

	m_sprite->setShaderProgram(m_program);
	CHECK_GL_ERROR_DEBUG();  
}

void CCColorFlashFilter::draw()
{
	setUniforms(m_sprite->getShaderProgram());
}

CCGLProgram* CCColorFlashFilter::loadShader()
{
	CCGLProgram* program = new CCGLProgram();
	program->initWithVertexShaderFilename("colorFlash.vsh","colorFlash.fsh");

	return program;
}

void CCColorFlashFilter::setAttributes( CCGLProgram* program )
{
	program->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);  
	program->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);  
}

void CCColorFlashFilter::setUniforms( CCGLProgram* program )
{
	m_count += m_interval;
	m_percent = (sin(m_count) + 1.0f) * 0.25f;

	//CCLOG("count: %f, percent : %f", m_count, m_percent);

	ccColor4F c = ccc4f(m_color.r * m_percent, m_color.g * m_percent, m_color.b * m_percent, 1);

	int locaition = program->getUniformLocationForName("u_color");
	CHECK_GL_ERROR_DEBUG();

	m_program->setUniformLocationWith3f(locaition,c.r,c.g,c.b);
	CHECK_GL_ERROR_DEBUG();
}
