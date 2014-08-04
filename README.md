cocos2dx-2.x-filters
====================
2014-08-04:
修复路径filter路径错误的问题
修复CCSpriteWithFilter 不设置滤镜情况下不显示的问题
修复CCGodRay在手机上导致崩溃的问题,并且在构造函数中增加采样次数和权重的设置，默认为50次采样，0.1权重

2014-07-27:

增加了CCWaveFilter
使用范例
<li>CCWaveFilter* waveFilter = CCWaveFilter::create(1,1);</li>

<li>sprite->setFilter(waveFilter);</li>

参数中的宽高为百分比，本质为扭曲的终点

once upon a time:

使用范例
<li>CCGodRayFilter* filter = CCGodRayFilter::create();</li>

<li>CCSpriteWidthFilter* sprite = CCSpriteWidthFilter::create("HelloWorld.png");</li>

<li>sprite->setFilter(filter);</li>


god ray 预览图:

<img src="http://www.dreamfairy.cn/blog/wp-content/uploads/2014/06/cocso2dxgodray.jpg" /img>
