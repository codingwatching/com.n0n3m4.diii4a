package com.karin.idTech4Amm.sys;

import android.support.annotation.NonNull;

import com.karin.idTech4Amm.R;
import com.n0n3m4.q3e.Q3EGlobals;
import com.n0n3m4.q3e.Q3EUtils;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

// game mod manager
public final class GameManager
{
    private final Map<String, List<GameProp>> GameProps = new LinkedHashMap<>();

    public final static String[] Games = {
            Q3EGlobals.GAME_DOOM3,
            Q3EGlobals.GAME_QUAKE4,
            Q3EGlobals.GAME_PREY,
            Q3EGlobals.GAME_RTCW,
            Q3EGlobals.GAME_QUAKE3,
            Q3EGlobals.GAME_QUAKE2,
            Q3EGlobals.GAME_QUAKE1,
            Q3EGlobals.GAME_DOOM3BFG,
            Q3EGlobals.GAME_TDM,
            Q3EGlobals.GAME_GZDOOM,
            Q3EGlobals.GAME_ETW,
            Q3EGlobals.GAME_REALRTCW,
            Q3EGlobals.GAME_FTEQW,
    };

    public GameManager()
    {
        InitGameProps();
    }

    public static class GameProp
    {
        public final int     index;
        public final String  game;
        public final String  fs_game;
        public final String  fs_game_base;
        public final boolean is_user;
        public final String  lib;
        public final String  file;

        public GameProp(int index, String game, String fs_game, String fs_game_base, boolean is_user, String lib, String file)
        {
            this.index = index;
            this.game = game;
            this.fs_game = fs_game;
            this.fs_game_base = fs_game_base;
            this.is_user = is_user;
            this.lib = lib;
            if(null == file)
                this.file = fs_game;
            else
                this.file = file;
        }

        public boolean IsGame(String game)
        {
            if (null == game)
                game = "";
            if(game.equals(this.game))
                return true;
            if(index == 0 && game.isEmpty())
                return true;
            return false;
        }

        public boolean IsValid()
        {
            return index >= 0 && !game.isEmpty();
        }
    }

    private void InitGameProps()
    {
        List<GameProp> props;
        GameProp prop;

        for(String game : Games)
            GameProps.put(game, new ArrayList<>());
        Game[] values = Game.values();

        for (Game value : values)
        {
            props = GameProps.get(value.type);
            prop = new GameProp(props.size(), value.game, value.fs_game, value.fs_game_base, false, value.lib, value.file);
            props.add(prop);
        }
    }

    public GameProp ChangeGameMod(String game, boolean userMod)
    {
        if (null == game)
            game = "";

        List<GameProp> list;
        if (Q3EUtils.q3ei.isQ4)
        {
            list = GameProps.get(Q3EGlobals.GAME_QUAKE4);
        }
        else if (Q3EUtils.q3ei.isPrey)
        {
            list = GameProps.get(Q3EGlobals.GAME_PREY);
        }
        else if (Q3EUtils.q3ei.isQ1)
        {
            list = GameProps.get(Q3EGlobals.GAME_QUAKE1);
        }
        else if (Q3EUtils.q3ei.isQ2)
        {
            list = GameProps.get(Q3EGlobals.GAME_QUAKE2);
        }
        else if (Q3EUtils.q3ei.isQ3)
        {
            list = GameProps.get(Q3EGlobals.GAME_QUAKE3);
        }
        else if (Q3EUtils.q3ei.isRTCW)
        {
            list = GameProps.get(Q3EGlobals.GAME_RTCW);
        }
        else if (Q3EUtils.q3ei.isTDM)
        {
            list = GameProps.get(Q3EGlobals.GAME_TDM);
        }
        else if (Q3EUtils.q3ei.isD3BFG)
        {
            list = GameProps.get(Q3EGlobals.GAME_DOOM3BFG);
        }
        else if (Q3EUtils.q3ei.isDOOM)
        {
            list = GameProps.get(Q3EGlobals.GAME_GZDOOM);
        }
        else if (Q3EUtils.q3ei.isETW)
        {
            list = GameProps.get(Q3EGlobals.GAME_ETW);
        }
        else if (Q3EUtils.q3ei.isRealRTCW)
        {
            list = GameProps.get(Q3EGlobals.GAME_REALRTCW);
        }
        else if (Q3EUtils.q3ei.isFTEQW)
        {
            list = GameProps.get(Q3EGlobals.GAME_FTEQW);
        }
        else
        {
            list = GameProps.get(Q3EGlobals.GAME_DOOM3);
        }

        GameProp res = null;
        for (GameProp prop : list)
        {
            if(prop.IsGame(game))
            {
                res = prop;
                break;
            }
        }
        if(null == res)
            res = new GameProp(0, "", game, "", userMod, "", null);
        return res;
    }

    public String GetGameOfMod(String game)
    {
        for (String key : GameProps.keySet())
        {
            List<GameProp> props = GameProps.get(key);
            for (GameProp prop : props)
            {
                if(prop.game.equals(game))
                    return key;
            }
        }
        return null;
    }

    public String GetGameFileOfMod(String game)
    {
        if(null == game)
            game = "";
        for (String key : GameProps.keySet())
        {
            List<GameProp> props = GameProps.get(key);
            for (GameProp prop : props)
            {
                if(prop.fs_game.equals(game))
                    return prop.file;
            }
        }
        return null;
    }

    public List<GameProp> GetGame(String game)
    {
        return GameProps.get(game);
    }

    public static int GetGameIcon()
    {
        if (Q3EUtils.q3ei.isPrey)
            return R.drawable.prey_icon;
        else if (Q3EUtils.q3ei.isQ4)
            return R.drawable.q4_icon;
        else if (Q3EUtils.q3ei.isQ1)
            return R.drawable.q1_icon;
        else if (Q3EUtils.q3ei.isQ2)
            return R.drawable.q2_icon;
        else if (Q3EUtils.q3ei.isQ3)
            return R.drawable.q3_icon;
        else if (Q3EUtils.q3ei.isRTCW)
            return R.drawable.rtcw_icon;
        else if (Q3EUtils.q3ei.isTDM)
            return R.drawable.tdm_icon;
        else if (Q3EUtils.q3ei.isD3BFG)
            return R.drawable.d3bfg_icon;
        else if (Q3EUtils.q3ei.isDOOM)
            return R.drawable.gzdoom_icon;
        else if (Q3EUtils.q3ei.isETW)
            return R.drawable.etw_icon;
        else if (Q3EUtils.q3ei.isRealRTCW)
            return R.drawable.realrtcw_icon;
        else if (Q3EUtils.q3ei.isFTEQW)
            return R.drawable.fteqw_icon;
        else
            return R.drawable.d3_icon;
    }

    public static int GetGameIcon(String name)
    {
        if(Q3EGlobals.GAME_PREY.equalsIgnoreCase(name))
            return R.drawable.prey_icon;
        else if(Q3EGlobals.GAME_QUAKE4.equalsIgnoreCase(name))
            return R.drawable.q4_icon;
        else if(Q3EGlobals.GAME_QUAKE2.equalsIgnoreCase(name))
            return R.drawable.q2_icon;
        else if(Q3EGlobals.GAME_QUAKE3.equalsIgnoreCase(name))
            return R.drawable.q3_icon;
        else if(Q3EGlobals.GAME_RTCW.equalsIgnoreCase(name))
            return R.drawable.rtcw_icon;
        else if(Q3EGlobals.GAME_TDM.equalsIgnoreCase(name))
            return R.drawable.tdm_icon;
        else if(Q3EGlobals.GAME_QUAKE1.equalsIgnoreCase(name))
            return R.drawable.q1_icon;
        else if(Q3EGlobals.GAME_DOOM3BFG.equalsIgnoreCase(name))
            return R.drawable.d3bfg_icon;
        else if(Q3EGlobals.GAME_GZDOOM.equalsIgnoreCase(name))
            return R.drawable.gzdoom_icon;
        else if(Q3EGlobals.GAME_ETW.equalsIgnoreCase(name))
            return R.drawable.etw_icon;
        else if(Q3EGlobals.GAME_REALRTCW.equalsIgnoreCase(name))
            return R.drawable.realrtcw_icon;
        else if(Q3EGlobals.GAME_FTEQW.equalsIgnoreCase(name))
            return R.drawable.fteqw_icon;
        else
            return R.drawable.d3_icon;
    }

    public static int GetGameNameRS(String name)
    {
        if(Q3EGlobals.GAME_PREY.equalsIgnoreCase(name))
            return R.string.prey_preybase;
        else if(Q3EGlobals.GAME_QUAKE4.equalsIgnoreCase(name))
            return R.string.quake_iv_q4base;
        else if(Q3EGlobals.GAME_QUAKE2.equalsIgnoreCase(name))
            return R.string.quake_2_base;
        else if(Q3EGlobals.GAME_QUAKE3.equalsIgnoreCase(name))
            return R.string.quake_3_base;
        else if(Q3EGlobals.GAME_RTCW.equalsIgnoreCase(name))
            return R.string.rtcw_base;
        else if(Q3EGlobals.GAME_TDM.equalsIgnoreCase(name))
            return R.string.tdm_base;
        else if(Q3EGlobals.GAME_QUAKE1.equalsIgnoreCase(name))
            return R.string.quake_1_base;
        else if(Q3EGlobals.GAME_DOOM3BFG.equalsIgnoreCase(name))
            return R.string.d3bfg_base;
        else if(Q3EGlobals.GAME_GZDOOM.equalsIgnoreCase(name))
            return R.string.doom_base;
        else if(Q3EGlobals.GAME_ETW.equalsIgnoreCase(name))
            return R.string.etw_base;
        else if(Q3EGlobals.GAME_REALRTCW.equalsIgnoreCase(name))
            return R.string.realrtcw_base;
        else if(Q3EGlobals.GAME_FTEQW.equalsIgnoreCase(name))
            return R.string.fteqw_base;
        else
            return R.string.doom_iii;
    }

    public static int GetGameName()
    {
        if (Q3EUtils.q3ei.isPrey)
            return R.string.prey_preybase;
        else if (Q3EUtils.q3ei.isQ4)
            return R.string.quake_iv_q4base;
        else if (Q3EUtils.q3ei.isQ2)
            return R.string.quake_2_base;
        else if (Q3EUtils.q3ei.isQ3)
            return R.string.quake_3_base;
        else if (Q3EUtils.q3ei.isRTCW)
            return R.string.rtcw_base;
        else if (Q3EUtils.q3ei.isTDM)
            return R.string.tdm_base;
        else if (Q3EUtils.q3ei.isQ1)
            return R.string.quake_1_base;
        else if (Q3EUtils.q3ei.isD3BFG)
            return R.string.d3bfg_base;
        else if (Q3EUtils.q3ei.isDOOM)
            return R.string.doom_base;
        else if (Q3EUtils.q3ei.isETW)
            return R.string.etw_base;
        else if (Q3EUtils.q3ei.isRealRTCW)
            return R.string.realrtcw_base;
        else if (Q3EUtils.q3ei.isFTEQW)
            return R.string.fteqw_base;
        else
            return R.string.doom_iii;
    }

    public static int GetGameThemeColor()
    {
        if (Q3EUtils.q3ei.isPrey)
            return R.color.theme_prey_main_color;
        else if (Q3EUtils.q3ei.isQ4)
            return R.color.theme_quake4_main_color;
        else if (Q3EUtils.q3ei.isQ1)
            return R.color.theme_quake1_main_color;
        else if (Q3EUtils.q3ei.isQ2)
            return R.color.theme_quake2_main_color;
        else if (Q3EUtils.q3ei.isQ3)
            return R.color.theme_quake3_main_color;
        else if (Q3EUtils.q3ei.isRTCW)
            return R.color.theme_rtcw_main_color;
        else if (Q3EUtils.q3ei.isTDM)
            return R.color.theme_tdm_main_color;
        else if (Q3EUtils.q3ei.isD3BFG)
            return R.color.theme_d3bfg_main_color;
        else if (Q3EUtils.q3ei.isDOOM)
            return R.color.theme_gzdoom_main_color;
        else if (Q3EUtils.q3ei.isETW)
            return R.color.theme_etw_main_color;
        else if (Q3EUtils.q3ei.isRealRTCW)
            return R.color.theme_realrtcw_main_color;
        else if (Q3EUtils.q3ei.isFTEQW)
            return R.color.theme_fteqw_main_color;
        else
            return R.color.theme_doom3_main_color;
    }

    public static int GetGameNameTs(String name)
    {
        if(Q3EGlobals.GAME_PREY.equalsIgnoreCase(name))
            return R.string.prey_2006;
        else if(Q3EGlobals.GAME_QUAKE4.equalsIgnoreCase(name))
            return R.string.quake_4;
        else if(Q3EGlobals.GAME_QUAKE2.equalsIgnoreCase(name))
            return R.string.quake_2;
        else if(Q3EGlobals.GAME_QUAKE3.equalsIgnoreCase(name))
            return R.string.quake_3;
        else if(Q3EGlobals.GAME_RTCW.equalsIgnoreCase(name))
            return R.string.rtcw;
        else if(Q3EGlobals.GAME_TDM.equalsIgnoreCase(name))
            return R.string.tdm;
        else if(Q3EGlobals.GAME_QUAKE1.equalsIgnoreCase(name))
            return R.string.quake_1;
        else if(Q3EGlobals.GAME_DOOM3BFG.equalsIgnoreCase(name))
            return R.string.doom_3_bfg;
        else if(Q3EGlobals.GAME_GZDOOM.equalsIgnoreCase(name))
            return R.string.doom;
        else if(Q3EGlobals.GAME_ETW.equalsIgnoreCase(name))
            return R.string.etw;
        else if(Q3EGlobals.GAME_REALRTCW.equalsIgnoreCase(name))
            return R.string.realrtcw;
        else if(Q3EGlobals.GAME_FTEQW.equalsIgnoreCase(name))
            return R.string.fteqw;
        else
            return R.string.doom_3;
    }

    public String[] GetGameLibs(String name, boolean makePlatform)
    {
        List<GameProp> gameProps = GameProps.get(name);
        List<String> list = new ArrayList<>();
        for (GameProp gameProp : gameProps)
        {
            if(!list.contains(gameProp.lib))
                list.add(gameProp.lib);
        }
        if(!makePlatform)
            return list.toArray(new String[0]);
        else
        {
            String[] res = new String[list.size()];
            for (int i = 0; i < list.size(); i++)
            {
                res[i] = "lib" + list.get(i) + ".so";
            }
            return res;
        }
    }
}
