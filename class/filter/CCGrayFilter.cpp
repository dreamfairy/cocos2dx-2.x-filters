#include "CCGrayFilter.h"


//================== CCGrayFilter

CCGrayFilter* CCGrayFilter::create()
{
	CCGrayFilter* filter = new CCGrayFilter();
	filter->autorelease();
	return filter;
}

CCGrayFilter* CCGrayFilter::create(ccColor4F color)
{
	CCGrayFilter* filter = CCGrayFilter::create();
	filter->setColor(color);
	return filter;
}

CCGrayFilter* CCGrayFilter::create(float r, float g, float b, float a)
{
	CCGrayFilter* filter = CCGrayFilter::create();
	filter->setColor(r,g,b,a);
	return filter;
}

CCGrayFilter::CCGrayFilter()
{
	m_param.r = 0.299f;
	m_param.g = 0.587f;
	m_param.b = 0.114f;
	m_param.a = 1.0f;

	this->shaderName = "Filter_Gray";
}

void CCGrayFilter::setColor( ccColor4F color )
{
	m_param = color;
}

void CCGrayFilter::setColor( float r, float g, float b, float a )
{
	this->setColor(ccc4f(r,g,b,a));
}

CCGLProgram* CCGrayFilter::loadShader()
{
	CCGLProgram* program = new CCGLProgram();
	program->initWithVertexShaderFilename("gray.vsh","gray.fsh");

	return program;
}

void CCGrayFilter::setAttributes( CCGLProgram* program )
{
	program->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);  
	program->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);  
	program->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);  
}

void CCGrayFilter::setUniforms( CCGLProgram* program )
{
	int locaition = program->getUniformLocationForName("u_paramColor");
	CHECK_GL_ERROR_DEBUG();

	m_program->setUniformLocationWith4f(locaition,m_param.r,m_param.g,m_param.b,0);
	CHECK_GL_ERROR_DEBUG();
}

void CCGrayFilter::initSprite( CCSpriteWidthFilter* sprite )
{
	m_sprite = sprite;
	initProgram();

	m_sprite->setShaderProgram(m_program);
	CHECK_GL_ERROR_DEBUG();  
}

void CCGrayFilter::draw()
{
	//CCLOG("Gray draw: %d", m_program->getProgram());
	setUniforms(m_sprite->getShaderProgram());
}
