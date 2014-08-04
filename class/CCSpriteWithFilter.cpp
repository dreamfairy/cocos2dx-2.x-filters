#include "CCSpriteWidthFilter.h"
#include "ccMacros.h"


void CCSpriteWidthFilter::draw()
{
	CCObject* obj;

	if(m_filters->count()){
		CCARRAY_FOREACH(m_filters,obj)
		{
			CCFilter* filter = static_cast<CCFilter*>(obj);

			CC_PROFILER_START_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");

			CCAssert(!m_pobBatchNode, "If CCSprite is being rendered by CCSpriteBatchNode,		CCSprite#draw SHOULD NOT be called");

			this->setShaderProgram(filter->getProgram());

			do 
			{
				ccGLEnable(m_eGLServerState);
				CCAssert(getShaderProgram(), "No shader program set for this node");
				{
					getShaderProgram()->use();
					getShaderProgram()->setUniformsForBuiltins();
				}
			} while (0);

			//useProgram后调用draw
			filter->draw();

			updateDefaultShader();
		}
	}else{

		CC_PROFILER_START_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");

		CCAssert(!m_pobBatchNode, "If CCSprite is being rendered by CCSpriteBatchNode, CCSprite#draw SHOULD NOT be called");

		ccGLEnable(m_eGLServerState); \
			CCAssert(getShaderProgram(), "No shader program set for this node"); \
		{ \
		getShaderProgram()->use(); \
		getShaderProgram()->setUniformsForBuiltins(); \
		} \

		updateDefaultShader();
	}
}

void CCSpriteWidthFilter::updateDefaultShader()
{
	ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );

	ccGLBindTexture2D( m_pobTexture->getName() );
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );

#define kQuadSize sizeof(m_sQuad.bl)
#ifdef EMSCRIPTEN
	long offset = 0;
	setGLBufferData(&m_sQuad, 4 * kQuadSize, 0);
#else
	long offset = (long)&m_sQuad;
#endif // EMSCRIPTEN

	// vertex
	int diff = offsetof( ccV3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

	// texCoods
	diff = offsetof( ccV3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// color
	diff = offsetof( ccV3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));


	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	CHECK_GL_ERROR_DEBUG();


#if CC_SPRITE_DEBUG_DRAW == 1
	// draw bounding box
	CCPoint vertices[4]={
		ccp(m_sQuad.tl.vertices.x,m_sQuad.tl.vertices.y),
		ccp(m_sQuad.bl.vertices.x,m_sQuad.bl.vertices.y),
		ccp(m_sQuad.br.vertices.x,m_sQuad.br.vertices.y),
		ccp(m_sQuad.tr.vertices.x,m_sQuad.tr.vertices.y),
	};
	ccDrawPoly(vertices, 4, true);
#elif CC_SPRITE_DEBUG_DRAW == 2
	// draw texture box
	CCSize s = this->getTextureRect().size;
	CCPoint offsetPix = this->getOffsetPosition();
	CCPoint vertices[4] = {
		ccp(offsetPix.x,offsetPix.y), ccp(offsetPix.x+s.width,offsetPix.y),
		ccp(offsetPix.x+s.width,offsetPix.y+s.height), ccp(offsetPix.x,offsetPix.y+s.height)
	};
	ccDrawPoly(vertices, 4, true);
#endif // CC_SPRITE_DEBUG_DRAW

	CC_INCREMENT_GL_DRAWS(1);

	CC_PROFILER_STOP_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
}

void CCSpriteWidthFilter::drawFilter()
{
	if(m_filters && m_filters->count() == 1)
	{
		static_cast<CCFilter*>(m_filters->objectAtIndex(0))->draw();
	}
}

//以push的方式增加filter
void CCSpriteWidthFilter::setFilter( CCFilter* filter )
{
	if(m_filters->indexOfObject(filter) == UINT_MAX)
	{
		m_filters->addObject(filter);
		filter->initSprite(this);
	}
}

void CCSpriteWidthFilter::clearFilter()
{
	//todo
}

bool CCSpriteWidthFilter::updateFilters()
{
	return true;
}


CCFilter* CCSpriteWidthFilter::getFilter( unsigned int index /*= 0*/ )
{
	return static_cast<CCFilter*>(m_filters->objectAtIndex(index));
}


CCSpriteWidthFilter* CCSpriteWidthFilter::create()
{
	CCSpriteWidthFilter* sprite = new CCSpriteWidthFilter();
	if(sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

CCSpriteWidthFilter* CCSpriteWidthFilter::create(const char* $pszFileName)
{
	CCSpriteWidthFilter* sprite = new CCSpriteWidthFilter();
	if (sprite && sprite->initWithFile($pszFileName))
	{
		sprite->autorelease();
		return sprite;
	}else{
		CC_SAFE_DELETE(sprite);
		return NULL;
	}
}

CCSpriteWidthFilter* CCSpriteWidthFilter::create(const char* $pszFileName, const CCRect& $rect)
{
	CCSpriteWidthFilter *sprite = new CCSpriteWidthFilter();
	if (sprite && sprite->initWithFile($pszFileName, $rect))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

CCSpriteWidthFilter* CCSpriteWidthFilter::createWithTexture(CCTexture2D* $pTexture)
{
	CCSpriteWidthFilter *sprite = new CCSpriteWidthFilter();
	if (sprite && sprite->initWithTexture($pTexture))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

CCSpriteWidthFilter* CCSpriteWidthFilter::createWithTexture(CCTexture2D* $pTexture, const CCRect& rect)
{
	CCSpriteWidthFilter *sprite = new CCSpriteWidthFilter();
	if (sprite && sprite->initWithTexture($pTexture, rect))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

CCSpriteWidthFilter* CCSpriteWidthFilter::createWithSpriteFrame(CCSpriteFrame* $pSpriteFrame)
{
	CCSpriteWidthFilter *sprite = new CCSpriteWidthFilter();
	if ($pSpriteFrame && sprite)
	{
		if ($pSpriteFrame->isRotated())
		{
			CCSprite* __sp = CCSprite::createWithSpriteFrame($pSpriteFrame);
			CCSize __size = __sp->getContentSize();
			__sp->setAnchorPoint(ccp(0,0));
			__sp->setPosition(ccp(0,0));
			CCRenderTexture* __rTex = CCRenderTexture::create(__size.width, __size.height);
			__rTex->begin();
			__sp->visit();
			__rTex->end();
			CCTexture2D* __newTex = new CCTexture2D();
			__newTex->initWithImage(__rTex->newCCImage(true));
			__newTex->autorelease();
			sprite->initWithTexture(__newTex);
			//CCLOG("==== CCFilteredSprite::initWithTexture, rotated true texture wh(%f,%f)", __newTex->getContentSize().width, __newTex->getContentSize().height);
		}
		else
		{
			sprite->initWithSpriteFrame($pSpriteFrame);
		}
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

CCSpriteWidthFilter* CCSpriteWidthFilter::createWithSpriteFrameName(const char* $pszSpriteFrameName)
{
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName($pszSpriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = { 0 };
	sprintf(msg, "Invalid spriteFrameName: %s", $pszSpriteFrameName);
	CCAssert(pFrame != NULL, msg);
#endif

	return createWithSpriteFrame(pFrame);
}

CCSpriteWidthFilter::CCSpriteWidthFilter()
{
	m_filters = CCArray::create();
	m_filters->retain();
}

CCSpriteWidthFilter::~CCSpriteWidthFilter()
{
	m_filters->release();

	//CC_SAFE_DELETE(m_filters);
}

void CCSpriteWidthFilter::setFilters( CCArray* filters )
{
	CCObject* obj;
	CCARRAY_FOREACH(filters, obj)
	{
		CCFilter* addFilter = static_cast<CCFilter*>(obj);
		addFilter->initSprite(this);
	}
	m_filters->addObjectsFromArray(filters);
}

CCArray* CCSpriteWidthFilter::getFilters()
{
	return m_filters;
}