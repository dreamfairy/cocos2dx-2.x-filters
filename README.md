cocos2dx-2.x-filters
====================

2014-07-27
增加了CCWaveFilter
使用范例
<li>CCWaveFilter* waveFilter = CCWaveFilter::create(1,1);</li>
<li>sprite->setFilter(waveFilter);</li>

参数中的宽高为百分比，本质为扭曲的终点

使用范例
<li>CCGodRayFilter* filter = CCGodRayFilter::create();</li>

<li>CCSpriteWidthFilter* sprite = CCSpriteWidthFilter::create("HelloWorld.png");</li>

<li>sprite->setFilter(filter);</li>


god ray 预览图:

<img src="http://www.dreamfairy.cn/blog/wp-content/uploads/2014/06/cocso2dxgodray.jpg" /img>
