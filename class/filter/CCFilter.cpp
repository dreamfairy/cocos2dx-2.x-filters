#include "CCFilter.h"

CCFilter::CCFilter()
: shaderName(NULL),
m_program(NULL)
{

}

CCFilter::~CCFilter()
{

}

void CCFilter::initSprite(CCSpriteWidthFilter* sprite)
{

}

void CCFilter::draw()
{

}

CCGLProgram* CCFilter::getProgram()
{
	return m_program;
}

void CCFilter::initProgram()
{
	CCGLProgram* program = CCShaderCache::sharedShaderCache()->programForKey(this->shaderName);
	if(!program)
	{
		program = loadShader();

		this->setAttributes(program);
		CHECK_GL_ERROR_DEBUG();
		program->link();
		CHECK_GL_ERROR_DEBUG();
		program->updateUniforms();
		CHECK_GL_ERROR_DEBUG();
		CCShaderCache::sharedShaderCache()->addProgram(program, this->shaderName);
		program->release();
	}

	if(!m_program)
	{
		m_program = program;
		m_program->retain();
	}
}

CCGLProgram* CCFilter::loadShader()
{
	return NULL;
}

void CCFilter::setAttributes(CCGLProgram* gl)
{

}

void CCFilter::setUniforms(CCGLProgram* gl)
{

}