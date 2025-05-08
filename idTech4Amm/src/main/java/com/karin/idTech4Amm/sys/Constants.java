package com.karin.idTech4Amm.sys;

import com.karin.idTech4Amm.BuildConfig;
import com.karin.idTech4Amm.lib.DateTimeUtility;
import com.karin.idTech4Amm.misc.TextHelper;

/**
 * Constants define
 */
public final class Constants
{
    public static final int    CONST_UPDATE_RELEASE = 65;
    public static final String CONST_RELEASE = "2025-05-05"; // 02-12
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
    public static final String CONST_CODE_ALIAS = "Lin Daiyu"; // Natasha; Verena; Caitlyn
	public static String[] CONST_CHANGES()
    {
        return new String[] {
            "Add cascaded shadow mapping with parallel lights(cvar `r_shadowMapSplits`) in OpenGL ES3 on DOOM 3/Quake 4/Prey(2006).",
            "Fix makron remote render at screen for texfure/cameraView1 in map game/core1 on Quake 4.",
            "Add spiritview and deathview GLSL shaders on Prey(2006).",
            "Update GZDOOM version to 4.14.1.",
            "Add multiplayer game bot support(need extract `d3_sabot_a7.pk4` patch resource first) on DOOM 3.",
            "Add player view flashlight with cvar `harm_ui_showViewLight`(include cvar: harm_ui_viewLightShader, harm_ui_viewLightRadius, harm_ui_viewLightOffset, harm_ui_viewLightType, harm_ui_viewLightOnWeapon), support bind to key for toggle(bind \"g\" \"_impulse52\") on DOOM 3.",
            "Support vsync setting on all OpenGL game.",
            "Improve multiplayer game bot system on Quake 4.",
            "Add skip player hit effect support with cvar `harm_g_skipHitEffect` and command `skipHitEffect` on DOOM 3/Quake 4/Prey(2006).",
            "Add enviroSuit player view vision GLSL shader on DOOM 3: RoE.",
            "Custom GLSL shaders using high precision(for fix blood pool in map game/waste) on Quake 4.",
            "Allow fire when focus NPC with cvar `harm_g_allowFireWhenFocusNPC` on Quake 4.",
            "Add custom GLSL shader program of new stage material support(keyword is `programGLSL`, e.g. programGLSL yourShaderInglProgs) on DOOM 3/Quake 4/Prey(2006).",
            "Fix save game path on FTEQW.",
            "On-screen buttons using OpenGL buffer.",
            "[Warning]: RealRTCW(ver 5.0) and The Dark Mod(2.12) have removed on this release!"
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
