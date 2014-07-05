#include "CCGodRayFilter.h"

CCGodRayFilter* CCGodRayFilter::create()
{
	CCGodRayFilter* filter = new CCGodRayFilter();
	return filter;
}

CCGodRayFilter::CCGodRayFilter()
{
	m_deltaTime = 0;
	m_useUserPos = false;
	this->shaderName = "Filter_GodRay";
}

//uv×ø±êÇø¼ä (0~1);
//u = x / texture.width
//v = y / texture.height
void CCGodRayFilter::setLightPos( float x, float y )
{
	m_lightPos.setPoint(x,y);
	m_useUserPos = true;
}

void CCGodRayFilter::initSprite( CCSpriteWidthFilter* sprite )
{
	m_sprite = sprite;
	initProgram();

	m_sprite->setShaderProgram(m_program);
	CHECK_GL_ERROR_DEBUG(); 
}

void CCGodRayFilter::draw()
{
	setUniforms(m_sprite->getShaderProgram());
}

CCGLProgram* CCGodRayFilter::loadShader()
{
	CCGLProgram* program = new CCGLProgram();
	program->initWithVertexShaderFilename("godRay.vsh","godRay.fsh");

	return program;
}

void CCGodRayFilter::setAttributes( CCGLProgram* program )
{
	program->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);  
	program->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);  
}

void CCGodRayFilter::setUniforms( CCGLProgram* program )
{
	m_deltaTime += 0.0166;

	int locaition = program->getUniformLocationForName("u_time");
	CHECK_GL_ERROR_DEBUG();

	m_program->setUniformLocationWith1f(locaition,m_deltaTime);
	CHECK_GL_ERROR_DEBUG();

	locaition = program->getUniformLocationForName("u_useParamPos");
	CHECK_GL_ERROR_DEBUG();

	m_program->setUniformLocationWith1i(locaition,m_useUserPos);
	CHECK_GL_ERROR_DEBUG();

	locaition = program->getUniformLocationForName("u_localPos");
	CHECK_GL_ERROR_DEBUG();

	m_program->setUniformLocationWith2f(locaition,m_lightPos.x,m_lightPos.y);
	CHECK_GL_ERROR_DEBUG();

	m_useUserPos = false;
}
