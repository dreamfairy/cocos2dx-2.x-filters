#include "CCWaveFilter.h"


CCWaveFilter* CCWaveFilter::create()
{
	CCWaveFilter* filter = new CCWaveFilter();
	return filter;
}

CCWaveFilter* CCWaveFilter::create( float pWidth, float pHeight )
{
	CCWaveFilter* filter = new CCWaveFilter(pWidth,pHeight);
	return filter;
}

CCWaveFilter::CCWaveFilter()
{
	m_time = 0;
	m_resolution.setPoint(100,100);
	this->shaderName = "Filter_Wave";
}

CCWaveFilter::CCWaveFilter( float pWidth, float pHeight )
{
	m_time = 0;
	m_resolution.setPoint(pWidth,pHeight);
	this->shaderName = "Filter_Wave";
}

void CCWaveFilter::initSprite( CCSpriteWidthFilter* sprite )
{
	m_sprite = sprite;
	initProgram();

	m_sprite->setShaderProgram(m_program);
	CHECK_GL_ERROR_DEBUG();  
}

void CCWaveFilter::draw()
{
	setUniforms(m_sprite->getShaderProgram());
}

CCGLProgram* CCWaveFilter::loadShader()
{
	CCGLProgram* program = new CCGLProgram();
	program->initWithVertexShaderFilename("wave.vsh","wave.fsh");

	return program;
}

void CCWaveFilter::setAttributes( CCGLProgram* program )
{
	program->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);  
	program->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);  
}

void CCWaveFilter::setUniforms( CCGLProgram* program )
{
	int location = program->getUniformLocationForName("time");
	m_time += 1.0f/60.0f;
	program->setUniformLocationWith1f(location,m_time);

	location = program->getUniformLocationForName("resolution");
	program->setUniformLocationWith2f(location,m_resolution.x,m_resolution.y);
}
