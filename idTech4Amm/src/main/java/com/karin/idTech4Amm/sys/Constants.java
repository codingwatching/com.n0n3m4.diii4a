package com.karin.idTech4Amm.sys;

import com.karin.idTech4Amm.BuildConfig;
import com.karin.idTech4Amm.lib.DateTimeUtility;
import com.karin.idTech4Amm.misc.TextHelper;

import java.util.Arrays;
import java.util.Date;

/**
 * Constants define
 */
public final class Constants
{
    public static final int    CONST_UPDATE_RELEASE = 59;
    public static final String CONST_RELEASE = "2024-11-20";
    public static final String CONST_EMAIL = "beyondk2000@gmail.com";
    public static final String CONST_DEV = "Karin";
    public static final String CONST_CODE = "Harmattan";
    public static final String CONST_APP_NAME = "idTech4A++"; // "DIII4A++";
    public static final String CONST_NAME = "DOOM III/Quake 4/Prey(2006)/DOOM 3 BFG for Android(Harmattan Edition)";
	public static final String CONST_MAIN_PAGE = "https://github.com/glKarin/com.n0n3m4.diii4a";
    public static final String CONST_TIEBA = "https://tieba.baidu.com/p/6825594793";
	public static final String CONST_DEVELOPER = "https://github.com/glKarin";
    public static final String CONST_DEVELOPER_XDA = "https://forum.xda-developers.com/member.php?u=10584229";
    public static final String CONST_PACKAGE = "com.karin.idTech4Amm";
    public static final String CONST_FDROID = "https://f-droid.org/packages/com.karin.idTech4Amm/";
	public static final String CONST_CHECK_FOR_UPDATE_URL = "https://raw.githubusercontent.com/glKarin/com.n0n3m4.diii4a/master/CHECK_FOR_UPDATE.json";
    public static final String CONST_LICENSE_URL = "https://raw.githubusercontent.com/glKarin/com.n0n3m4.diii4a/master/LICENSE";
	public static String[] CONST_CHANGES()
    {
        return new String[] {
            "Support `Omni-Bot` in Wolfenstein: Enemy Territory.",
            "Fix rendering on Mali GPU in DOOM 3-BFG.",
            "Fix rendering on Mali GPU in The Dark Mod.",
            "Fix stencil shadow with `cg_shadows` = 2 in Wolfenstein: Enemy Territory.",
            "Support choose a mod directory in GZDOOM.",
            "Add some new features options on launcher in Wolfenstein: Enemy Territory, RealRTCW, DOOM3-BFG, Quake 2, GZDOOM, The Dark Mod.",
            "Add use high precision float on GLSL shaders(cvar `harm_r_useHighPrecision`) in DOOM 3/Quake 4/Prey.",
            "Add 5 onscreen buttons.",
            "Add `Phobos(for Dhewm3)` mod of DOOM3 support, game data directory named `tfphobos`(d3xp and dhewm3 compatibility patch required). More view in `" + TextHelper.GenLinkText("https://www.moddb.com/mods/phobos", "Doom 3: Phobos") + "` and .`" + TextHelper.GenLinkText("https://www.moddb.com/games/doom-iii/addons/doom-3-phobos-dhewm3-compatibility-patch", "Doom 3: Phobos - dhewm3 compatibility patch") + "`.",
        };
	};

    public static long GetBuildTimestamp()
    {
        return BuildConfig.BUILD_TIMESTAMP;
    }

    public static int GetBuildSDKVersion()
    {
        return BuildConfig.BUILD_SDK_VERSION;
    }

    public static boolean IsDebug()
    {
        return BuildConfig.DEBUG;
    }

    public static String GetBuildTime(String format)
    {
        return DateTimeUtility.Format(GetBuildTimestamp(), format);
    }
    
	private Constants() {}
}
