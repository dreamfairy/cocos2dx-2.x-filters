#include "CCFlashFilter.h"

CCFlashFilter* CCFlashFilter::create()
{
	CCFlashFilter* filter = new CCFlashFilter();
	return filter;
}

CCFlashFilter* CCFlashFilter::create( int intervalFrame )
{
	CCFlashFilter* filter = CCFlashFilter::create();
	filter->setIntervalFrame(intervalFrame);
	return filter;
}

CCFlashFilter::CCFlashFilter()
{
	m_frameInterval = 5;
	m_currentFrameCount = 0;
	m_alpha = 0;

	this->shaderName = "Filter_Flash";
}

void CCFlashFilter::setIntervalFrame( int intervalFrame )
{
	m_frameInterval = intervalFrame;
	m_currentFrameCount = 0;
}

void CCFlashFilter::initSprite( CCSpriteWidthFilter* sprite )
{
	m_sprite = sprite;
	initProgram();

	m_sprite->setShaderProgram(m_program);
	CHECK_GL_ERROR_DEBUG();  
}

void CCFlashFilter::draw()
{
	setUniforms(m_sprite->getShaderProgram());
}

CCGLProgram* CCFlashFilter::loadShader()
{
	CCGLProgram* program = new CCGLProgram();
	program->initWithVertexShaderFilename("flash.vsh","flash.fsh");

	return program;
}

void CCFlashFilter::setAttributes( CCGLProgram* program )
{
	program->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);  
	program->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);  
}

void CCFlashFilter::setUniforms( CCGLProgram* program )
{
	int location = program->getUniformLocationForName("u_alpha");

	if(m_currentFrameCount >= m_frameInterval)
	{
		m_alpha = m_alpha >= 1 ? 0 : m_alpha + 0.1;
		m_currentFrameCount = 0;
	}

	m_currentFrameCount++;

	program->setUniformLocationWith1f(location,m_alpha);
}

