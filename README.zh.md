## idTech4A++ (Harmattan Edition)
#### DOOM III/Quake 4/Prey(2006) for Android/Linux
#### 毁灭战士3/雷神之锤4/掠食(2006)安卓/Linux移植版. 
#### 原名DIII4A++, 基于n0n3m4的diii4a的OpenGLES版本.
**最新版本:**
1.1.0harmattan39(natasha)  
**最新更新日期:**
2024-04-10  
**架构支持:**
arm64 armv7-a  
**平台:**
Android 4.4+  
**许可证:**
GPLv3

----------------------------------------------------------------------------------
### 支持
* Linux/Windows(MinGW/MSVC(不支持编辑器))构建
* 多线程渲染
* png/dds纹理图片加载
* jpeg/png/bmp/dds格式截屏
* obj格式静态模型
* dae格式静态模型
* 纯阴影图映射软阴影
* OpenGLES2.0/OpenGLES3.0
* OpenAL(soft)和EFX混响
* 无光照渲染和无光照材质
* 半透明模板阴影
* 毁灭战士3 mods: 毁灭战士3(支持全身mod); The Lost Mission; Classic DOOM; Rivensin; Hardcorps; Overthinked; SABot-a7x; HexenEOC; Fragging-Free; LibreCoop
* 雷神之锤4(支持Bot mod; 全身mod)和Raven idTech4引擎
* 掠食(2006)(支持全身mod)和HumanHead idTech4引擎
* 雷神之锤2(Yamagi Quake II) 和mods: ctf; rogue; xatrix; zaero
* 雷神之锤3竞技场/雷神之锤3团队竞技场(ioquake3)
* 重返德军总部(iortcw)
* The Dark Mod

[<img src="https://fdroid.gitlab.io/artwork/badge/get-it-on.png"
alt="Get it on F-Droid"
height="80">](https://f-droid.org/packages/com.karin.idTech4Amm/)

或者在[Releases Section](https://github.com/glKarin/com.n0n3m4.diii4a/releases/latest)下载最新的APK.
标签以`-free`结尾的仅为了F-Droid更新.

| 功能支持 | Github | F-Droid |
|:-|:-:|:-:|
| Ouya TV | 是 | 否 |

----------------------------------------------------------------------------------
### 更新

* 阴影映射支持镂空图层阴影.
* 新增毁灭战士3 mod `LibreCoop`支持, 游戏数据文件夹命名为`librecoop`. 详情[LibreCoop](https://www.moddb.com/mods/librecoop-dhewm3-coop).
* 新增`雷神之锤2`支持, 游戏数据文件夹命名为`baseq2`. 详情[Quake II](https://store.steampowered.com/app/2320/Quake_II/).
* 新增`雷神之锤3竞技场`支持, 游戏数据文件夹命名为`baseq3`; 新增`雷神之锤3团队竞技场`支持, 游戏数据文件夹命名为`missionpack`. 详情[Quake III Arena](https://store.steampowered.com/app/2200/Quake_III_Arena/).
* 新增`重返德军总部`支持, 游戏数据文件夹命名为`main`. 详情[Return to Castle Wolfenstein](https://www.moddb.com/games/return-to-castle-wolfenstein).
* 新增`The Dark Mod`v2.11支持, 游戏数据文件夹命名为`darkmod`. 详情[The Dark Mod](https://www.thedarkmod.com).
* 新增一个虚拟按键主题.

----------------------------------------------------------------------------------

#### 关于掠食(2006)
###### 运行掠食(2006)([jmarshall](https://github.com/jmarshall23) 's [PreyDoom](https://github.com/jmarshall23/PreyDoom)). 目前可以运行全部关卡, 部分关卡存在bug.
> 1. 将PC端掠食(2006)游戏文件放到`preybase`文件夹, 然后直接启动游戏.
> 2. 已知问题的解决方案: 例如. 使用cvar `harm_ui_translateAlienFont`自动翻译GUI中的外星人文字.
> 3. 已知bugs: 例如一些错误的碰撞检测(使用`noclip`), 部分GUI不工作(RoadHouse的CD播放器).
> 4. 如果设置页面不工作, 可以通过编辑`preyconfig.cfg`来绑定额外按键.
> > * bind "幽灵行走按键" "_impulse54"
> > * bind "武器第2攻击键" "_attackAlt"
> > * bind "打火机开关键" "_impulse16"
> > * bind "扔物体键" "_impulse25"

----------------------------------------------------------------------------------

#### 关于雷神之锤4
###### 运行雷神之锤4([jmarshall](https://github.com/jmarshall23) 's [Quake4Doom](https://github.com/jmarshall23/Quake4Doom)). 目前可以运行全部关卡, 部分关卡存在bug.  
> 1. 将PC端雷神之锤4游戏文件放到`q4base`文件夹, 然后直接启动游戏.
> 2. 建议先解压雷神之锤4补丁资源到`q4base`资源目录(在菜单`Other` -> `Extract resource`).
> - 雷神之锤3bot文件(在多人游戏中, 进入游戏后在控制台使用命令`addbots <bot_file>`或`fillbots`添加bot, 或者设置`harm_si_autoFillBots`为1自动添加bot).
> - `SABot a9 mod`多人游戏地图的aas文件和脚本文件(多人游戏的bot支持).

###### 问题和解决方案:
> 1. *粒子系统*: 目前工作的不完整(雷神之锤4使用了新的更高级的粒子系统`BSE`, 非开源, `jmarshall`通过反编译`深入敌后: 雷神战争`的BSE二进制实现了, 更多详情 [jmarshall23/Quake4BSE](https://github.com/jmarshall23/Quake4BSE)), 但是至今不工作. 现在实现了一个基于毁灭战士3的粒子特效系统的开源BSE, 可以渲染一些, 但是效果不是很理想.
> 2. *物体渲染*: 存在一些物体错误的渲染结果.

###### Bot mod:
> 1. 添加SABot a7 mod支持. 
> 2. 解压apk中的`q4base/sabot_a9.pk4`文件到雷神之锤4游戏文件目录, 其中包含一些配置文件, 脚本文件和多人游戏地图的AAS文件.
> 3. 设置`harm_g_autoGenAASFileInMPGame`为1自动在多人游戏地图载入(如果没有一个有效的该地图的AAS文件)后生成一个不怎么好的AAS文件, 也可以把你自己用其他方式生成的AAS文件放到游戏数据目录的`maps/mp`文件夹(botaas32)).
> 4. 设置`harm_si_autoFillBots`自动添加bot当开始多人游戏.
> 5. 执行`addbots`添加bot.
> 6. 执行`fillbots`自动填满bot.

----------------------------------------------------------------------------------
### 截图
> 游戏

<img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_doom3_bathroom.png" alt="Classic bathroom">
<img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_bathroom_jill_stars.png" alt="Classic bathroom in Rivensin mod">
<img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_quake4_game_2.png" alt="Quake IV on DOOM3">
<img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_prey_girlfriend.png" alt="Prey(2006) on DOOM3">

> Mod

<img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_doom3_roe.png" width="50%" alt="Resurrection of Evil"><img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_doom3_the_lost_mission.png" width="50%" alt="The lost mission">
<img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_classic_doom3.png" width="50%" alt="Classic DOOM"><img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_doom3_hardcorps.png" width="50%" alt="Hardcorps">
<img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_doom3_rivensin.png" width="50%" alt="Rivensin"><img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_quake4.png" width="50%" alt="Quake IV">
<img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_prey.png" width="50%" alt="Prey(2006)">

----------------------------------------------------------------------------------

### 更新:

[更新日志](CHANGES.zh.md ':include')

----------------------------------------------------------------------------------

### 编译构建:

#### 引擎
> 1. _MULTITHREAD: 多线程支持.
> 2. _USING_STB: 使用stb加载jpeg/png/dds纹理图片支持和jpeg/png/bmp/dds格式截图支持.
> 3. _K_CLANG: 如果使用clang编译而不是GCC.
> 4. _MODEL_OBJ: 添加obj静态模型支持.
> 5. _MODEL_DAE: 添加dae静态模型支持.
> 6. _SHADOW_MAPPING: 增加Shadow mapping软阴影支持.
> 7. _OPENGLES3: 增加OpenGL ES3.0支持.
> 8. _OPENAL _OPENAL_EFX _OPENAL_SOFT: 增加OpenAL(soft)和EFX混响支持.
> 9. _NO_LIGHT: 添加无光照渲染支持.
> 10. _TRANSLUCENT_STENCIL_SHADOW: 添加半透明模板阴影支持.

#### 如果想要移植`雷神之锤4`和`掠食(2006)`到同基于开源版本的`毁灭战士3`源码的PC端或其他平台, 由于DIII4A基于安卓平台和OpenGLES, 所以和原始的代码有些区别. 但是我把所有修改都用宏在源码上做了标记作为补丁, 但即使这样也要搜索这些宏和手动应用这些补丁.
#### 为了保持原毁灭战士3的源码结构, 对于全部新增加的源码文件, 我放在了外面的新文件夹中, 并且在这些新文件夹内保持和毁灭战士3一样的目录结构(例如. framework, renderer, idlib...).

#### 雷神之锤4
##### `_RAVEN`, `_QUAKE4`是补丁宏, 在`DIII4A`源码中查找.
##### 所有新源码放置在`raven`文件夹.
> 1. _RAVEN: 编译`core引擎 (毁灭战士3的源码)`和`idlib (毁灭战士3的源码)`.
> 2. _QUAKE4: 编译`游戏 (雷神之锤4的SDK源码)`库.
> 3. 构建core引擎: 声明宏`_RAVEN`, `_RAVEN_FX(如果需要OpenBSE, 非必须)`
> 4. 构建游戏库: 声明宏`_RAVEN`, `_QUAKE4`
##### 关于`BSE`
由于`BSE`没开源, 所以我默认使用了一个什么都不做的空实现和一个不完整的但可以工作的基于毁灭战士3原来的Particle/Fx粒子特效系统的实现(使用宏`_RAVEN_FX`标记).
##### 关于`BOT`
声明宏`MOD_BOTS`将编译SABot a7(来自毁灭战士3) mod源码的多人游戏的bot支持.

#### 掠食(2006)
##### `_HUMANHEAD`, `_PREY`是补丁宏, 在`DIII4A`源码中查找.
##### 所有新源码放置在`humanhead`文件夹.
> 1. _HUMANHEAD: 编译`core引擎(毁灭战士3的源码)`和`idlib (毁灭战士3的源码)`.
> 2. _PREY: 编译`游戏 (掠食(2006)的SDK源码)`库.
> 3. 构建core引擎: 声明宏`_HUMANHEAD`
> 4. 构建游戏库: 声明宏`_HUMANHEAD`, `_PREY`, 和原来SDK的宏`HUMANHEAD`

#### 安卓
##### 声明宏`__ANDROID__`.
> 1. _OPENSLES: OpenSLES声音支持.

#### Linux
> 1. 需要 ALSA, zlib, X11, EGL

#### Windows(MinGW/MSVC)
> 1. 需要 SDL2, zlib, cURL

----------------------------------------------------------------------------------

### 关于:

* 源码在apk里的`assets/source`目录下.
	
----------------------------------------------------------------------------------

### 分支:

> `master`:
> * /idTech4Amm: 前端启动器源码
> * /Q3E /Q3E/src/main/jni/doom3: 游戏源码
> * /CHECK_FOR_UPDATE.json: 检查更新的配置JSON

> `free`:
> * F-Droid自由版本.

> `package`:
> * /screenshot: 截图
> * /source: 引用的源码
> * /pak: 游戏资源

> `n0n3m4_original_old_version`:
> * 原来旧的`n0n3m4`的版本.

----------------------------------------------------------------------------------
### 其他下载方式:

* [Baidu网盘: https://pan.baidu.com/s/1hXvKmrajAACfcCj9_ThZ_w](https://pan.baidu.com/s/1hXvKmrajAACfcCj9_ThZ_w) 提取码: `pyyj`
* [Baidu贴吧: BEYONDK2000](https://tieba.baidu.com/p/6825594793)
* [F-Droid(不同的签名)](https://f-droid.org/packages/com.karin.idTech4Amm/)
----------------------------------------------------------------------------------
