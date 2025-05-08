idCVar botAi::harm_si_autoFillBots( "harm_si_autoFillBots", "0", CVAR_INTEGER | CVAR_GAME | CVAR_NOCHEAT | CVAR_ARCHIVE, "Automatic fill bots after map loaded in multiplayer game(0 = disable; -1 = max; > 0 = bot num).", -1, botAi::BOT_MAX_BOTS );
//karin: auto gen aas file for mp game map with bot
idCVar botAi::harm_g_autoGenAASFileInMPGame( "harm_g_autoGenAASFileInMPGame", "1", CVAR_BOOL | CVAR_GAME | CVAR_ARCHIVE, "For bot in Multiplayer-Game, if AAS file load fail and not exists, server can generate AAS file for Multiplayer-Game map automatic.");

#include "BotAI_cfg.cpp"

/*
===================
botAi::Addbot_f
TinMan: Console command. Bring in teh b0tz!
*todo* set default def to something sensible
*todo* random name if default bot
*todo* get passed in args working for no added classname
===================
*/
void botAi::Addbot_f( const idCmdArgs &args )
{
	if(!AllowBotOperation())
        return;

	if (args.Argc() < 2)
	{
		common->Printf("USAGE: %s <botdef> ...key/value pair. e.g. addBot bot_sabot_tinman - see def/bot_sabot_characters.def for more details\n", args.Argv(0));
		return;
	}

    const char *key, *value;
    int			i;
    idDict		dict;

    value = args.Argv( 1 );

    // TinMan: Add rest of key/values passed in
    for( i = 2; i < args.Argc() - 1; i += 2 )
    {
        key = args.Argv( i );
        value = args.Argv( i + 1 );

        dict.Set( key, value );
    }

    i = AddBot(value, dict);
    if (i < 0)
    {
        common->Warning("AddBot fail -> %d\n", i);
        return;
    }
}

/*
===================
botAi::Removebot_f
TinMan: Console command. Bye bye botty.
===================
*/
void botAi::Removebot_f( const idCmdArgs &args )
{
    if(!AllowBotOperation())
        return;

    if(args.Argc() < 2)
    {
        gameLocal.Printf("Usage: %s <botID>\n", args.Argv(0));
        return;
    }

    const char *value;
    int killBotID;

    value = args.Argv( 1 );

    killBotID = atoi( value );

    //gameLocal.Printf( "[botAi::Removebot][Bot #%d]\n", killBotID ); // TinMan: *debug*

    if ( !botAi::RemoveBot(killBotID) )
    {
        gameLocal.Warning( "There is no spoon, I mean, bot #%d", killBotID );
    }
}

bool botAi::IsAvailable(void)
{
    return botInitialized && botAvailable;
}

int botAi::AddBot(const char *defName, const idDict &dict)
{
    int			i;
    idDict		userInfo;
    int newBotID;
    int newClientID;

    if ( !AllowBotOperation() )
    {
        return -1;
    }

    if (!defName || !defName[0])
    {
        gameLocal.Warning("Must set bot entity def name!");
        return -2;
    }

    // Try to find an ID in the bots list
    i = botAi::FindIdleBotSlot();

    if ( i >= BOT_MAX_NUM )
    {
        gameLocal.Warning("The maximum number of bots are already in the game.");
        return -3;
    }
    else
    {
        newBotID = i;
    }

    // TinMan: Check to see if valid def
    const idDeclEntityDef *botDef = gameLocal.FindEntityDef( defName );
    const char *spawnclass = botDef->dict.GetString( "spawnclass" );
    idTypeInfo *cls = idClass::GetClass( spawnclass );
    if ( !cls || !cls->IsType( botAi::Type ) )
    {
        gameLocal.Warning( "def not of type botAi or no def name given" );
        return -4;
    }

    newClientID = newBotID; // TinMan: client id, bots use >16

    //gameLocal.Printf("Spawning bot as client %d\n", newClientID);
    bots[newBotID].inUse = true; // must mark first
    bots[newBotID].entityNum = -1;
    // TinMan: Add client to bot list
    bots[newBotID].clientID = newClientID;
    // idStr::Copynz(bots[newBotID].defName, defName, sizeof(bots[newBotID].defName));

    // Start up client
    gameLocal.ServerClientConnect(newClientID, NULL);

    idDict clientArgs = dict;
    clientArgs.SetBool("isBot", true);
    clientArgs.SetInt("botID", newBotID);
    clientArgs.Set("botDefName", defName);
    int wp = MakeWeaponMask(harm_si_botWeapons.GetString());
    if(wp != 0)
    {
        idStr weapon = MakeWeaponString(InsertBasicWeaponMask(wp));
        gameLocal.Printf("Bot weapons: %s\n", weapon.c_str());
        clientArgs.Set("weapon", weapon.c_str());
    }
    if(harm_si_botAmmo.GetInteger() != 0)
    {
        idDict ammo = MakeAmmoDict(wp, harm_si_botAmmo.GetInteger());
        int numAmmo = ammo.GetNumKeyVals();
        if(numAmmo > 0)
        {
            if(numAmmo > 0)
            {
                for(int m = 0; m < numAmmo; m++)
                {
                    const idKeyValue *kv = ammo.GetKeyVal(m);
                    gameLocal.Printf("  %s = %s\n", kv->GetKey().c_str(), kv->GetValue().c_str());
                }
            }
            clientArgs.Copy(ammo);
        }
    }

    gameLocal.ServerBotClientBegin(newClientID, &clientArgs); // TinMan: spawn the fakeclient (and send message to do likewise on other machines)

    idPlayer * botClient = static_cast< idPlayer * >( gameLocal.entities[ newClientID ] ); // TinMan: Make a nice and pretty pointer to fakeclient
    // TinMan: Put our grubby fingerprints on fakeclient. *todo* may want to make these entity flags and make sure they go across to clients so we can rely on using them for clientside code
    botClient->spawnArgs.SetBool( "isBot", true );
    botClient->spawnArgs.SetInt( "botID", newBotID );

    gameLocal.Printf("Add bot: botID=%d\n", newBotID);

    return newClientID;
}

bool botAi::RemoveBot( int killBotID )
{
    if (killBotID < BOT_START_INDEX || killBotID >= BOT_MAX_NUM)
    {
        gameLocal.Warning( "Remove bot ID invalid: %d", killBotID );
        return false;
    }
    if( !gameLocal.entities[ killBotID ] )
    {
        gameLocal.Warning( "Remove bot is null entity: %d", killBotID );
        return false;
    }
    if( !gameLocal.entities[ killBotID ]->IsType(idPlayer::Type) )
    {
        gameLocal.Warning( "Remove bot is not player: %d", killBotID );
        return false;
    }
    idPlayer *client = static_cast<idPlayer *>(gameLocal.entities[ killBotID ]);
    if(!client->IsBot())
    {
        gameLocal.Warning( "Remove player is not bot: %d", killBotID );
        return false;
    }
    gameLocal.Printf( "Disconnect bot client: %d\n", killBotID );
    gameLocal.ServerClientDisconnect( killBotID ); // TinMan: KaWhoosh! Youuure outa there!
    return true;
}

void botAi::Cmd_AddBots_f(const idCmdArgs& args)
{
	if(!AllowBotOperation())
        return;

    if (args.Argc() < 2)
    {
        gameLocal.Printf("USAGE: %s <botdef>...... e.g. %s bot_sabot_tinman bot_sabot_fluffy bot_sabot_blackstar - see def/bot_sabot_characters.def for more details\n", args.Argv(0), args.Argv(0));
        return;
    }
    int num = args.Argc() - 1;
    if(num > botAi::BOT_MAX_BOTS)
    {
        gameLocal.Warning("Max bot num is %d", botAi::BOT_MAX_BOTS);
        return;
    }
    int rest = CheckRestClients(num);
    if(rest < 0)
    {
        gameLocal.Warning("Bots has not enough (%d/%d)", rest + num, botAi::BOT_MAX_BOTS);
        return;
    }
    for(int i = 0; i < num; i++)
    {
        const char *value = args.Argv(i + 1);
        int r = AddBot(value);
        if (r < 0)
        {
            gameLocal.Warning("AddBot fail -> %d", i);
            return;
        }
    }
}

void botAi::Cmd_FillBots_f(const idCmdArgs& args)
{
	if(!AllowBotOperation())
        return;

    int num = CheckRestClients(0);
    if(args.Argc() > 1)
    {
        int n = atoi(args.Argv(1));
        if(n > 0)
            num = n;
    }

	gameLocal.Printf("Try to add %d bots\n", num);
	int max = botAi::BOT_MAX_BOTS;
    if(num > max)
    {
        gameLocal.Warning("Max bot num is %d", max);
        return;
    }

    int rest = CheckRestClients(num);
    if(rest < 0)
    {
        gameLocal.Warning("Bots has not enough (%d/%d)", rest + num, max);
        return;
    }

    idStrList botNames;
    int botNum = GetBotDefs(botNames);
    idStrList list;
    for(int i = 0; i < num; i++)
    {
        if(list.Num() == 0)
            list = botNames;
        int index = gameLocal.random.RandomInt(list.Num());
        idStr name = list[index];
        list.RemoveIndex(index);
        AddBot(name);
    }
#if 0
    AddBot("bot_sabot_tinman");
	AddBot("bot_sabot_fluffy");
	AddBot("bot_sabot_blackstar");
#endif
}

void botAi::Cmd_RemoveBots_f(const idCmdArgs& args)
{
    if(!AllowBotOperation())
        return;

    if (args.Argc() < 2)
    {
        gameLocal.Printf("USAGE: %s <botdef> <bot ID>......\n", args.Argv(0));
        return;
    }
    int num = args.Argc() - 1;
    for(int i = 0; i < num; i++)
    {
        int value = atoi(args.Argv(i + 1));
        int r = RemoveBot(value);
        if (r < 0)
        {
            gameLocal.Warning("RemoveBot %d fail -> %d", i, r);
        }
    }
}

void botAi::Cmd_AppendBots_f(const idCmdArgs& args)
{
    if(!AllowBotOperation())
        return;

	int max = botAi::BOT_MAX_BOTS;
    int numBots = GetNumConnectedClients(false); // GetNumCurrentActiveBots();
    int maxClients = MAX_CLIENTS;
    int idle = maxClients - numBots;
    int num = idle;
    if(args.Argc() > 1)
    {
        int n = atoi(args.Argv(1));
        if(n > 0)
            num = n;
    }

	gameLocal.Printf("Try to append %d bots\n", num);
    if(num > max)
    {
        gameLocal.Warning("Max bot num is %d", max);
        return;
    }

    int rest = idle - num;
    if(rest < 0)
    {
        gameLocal.Warning("Bots has not enough (%d/%d)", rest + num, max);
        return;
    }

    idStrList botNames;
    int botNum = GetBotDefs(botNames);
    idStrList list;
    for(int i = 0; i < num; i++)
    {
        if(list.Num() == 0)
            list = botNames;
        int index = gameLocal.random.RandomInt(list.Num());
        idStr name = list[index];
        list.RemoveIndex(index);
        AddBot(name);
    }
}

void botAi::ArgCompletion_addBot( const idCmdArgs &args, void(*callback)( const char *s ) )
{
    int i;
    int num;

    num = declManager->GetNumDecls(DECL_ENTITYDEF);

    for (i = 0; i < num; i++) {
        const idDeclEntityDef *decl = (const idDeclEntityDef *)declManager->DeclByIndex(DECL_ENTITYDEF, i , false);
        if(!decl)
            continue;
        if(!idStr(decl->GetName()).IcmpPrefix("bot_sabot"))
            callback(idStr(args.Argv(0)) + " " + decl->GetName());
    }
}

void botAi::ArgCompletion_botLevel( const idCmdArgs &args, void(*callback)( const char *s ) )
{
    int i;
    int num;

    num = declManager->GetNumDecls(DECL_ENTITYDEF);

    for (i = 0; i < num; i++) {
        const idDeclEntityDef *decl = (const idDeclEntityDef *)declManager->DeclByIndex(DECL_ENTITYDEF, i , false);
        if(!decl)
            continue;
        if(!idStr(decl->GetName()).IcmpPrefix("bot_level"))
            callback(idStr(args.Argv(0)) + " " + (decl->GetName() + strlen("bot_level")));
    }
}

void botAi::ArgCompletion_botSlots( const idCmdArgs &args, void(*callback)( const char *s ) )
{
    for ( int clientID = BOT_START_INDEX; clientID < MAX_CLIENTS; clientID++ ) {
        if ( gameLocal.entities[ clientID ] && gameLocal.entities[ clientID ]->IsType( idPlayer::Type ) ) {
            idPlayer *client = static_cast<idPlayer *>(gameLocal.entities[ clientID ]);
            if(client->IsBot())
                callback(va("%s %d", args.Argv(0), clientID));
        }
    }
}

void botAi::Cmd_CleanBots_f(const idCmdArgs& args)
{
    if(!AllowBotOperation())
        return;

    for ( int clientID = BOT_START_INDEX; clientID < MAX_CLIENTS; clientID++ ) {
        if ( gameLocal.entities[ clientID ] && gameLocal.entities[ clientID ]->IsType( idPlayer::Type ) ) {
            idPlayer *client = static_cast<idPlayer *>(gameLocal.entities[ clientID ]);
			if(client->IsBot())
				RemoveBot(clientID);
        }
    }
}

void botAi::Cmd_TruncBots_f(const idCmdArgs& args)
{
    if(!AllowBotOperation())
        return;

	int num;
    if(args.Argc() > 1)
    {
        int n = atoi(args.Argv(1));
        if(n > 0)
            num = n;
		else if(n < 0)
			num = MAX_CLIENTS + n;
		else
			num = 1;
    }
    else
        num = BOT_MAX_NUM;

    for ( int clientID = MAX_CLIENTS - 1; num > 0 && clientID >= BOT_START_INDEX; clientID-- ) {
        if ( gameLocal.entities[ clientID ] && gameLocal.entities[ clientID ]->IsType( idPlayer::Type ) ) {
            idPlayer *client = static_cast<idPlayer *>(gameLocal.entities[ clientID ]);
			if(client->IsBot())
			{
				RemoveBot(clientID);
				num--;
			}
        }
    }
}

int botAi::GetNumCurrentActiveBots(void)
{
    int numBots = 0;
    for ( int i = BOT_START_INDEX; i < BOT_MAX_NUM; i++ )
    {
        if ( botAi::bots[i].inUse )
        {
            numBots++;
        }
    }
    return numBots;
}

int botAi::CheckRestClients(int num)
{
    int numBots = GetNumConnectedClients(true); // GetNumCurrentActiveBots();
    int maxClients = Min(gameLocal.serverInfo.GetInt("si_maxPlayers"), botAi::BOT_MAX_BOTS);
    return maxClients - num - numBots;
}

void botAi::Cmd_BotInfo_f(const idCmdArgs& args)
{
    gameLocal.Printf("SABot(a9)\n");
    gameLocal.Printf("gameLocal.isMultiplayer: %d\n", gameLocal.isMultiplayer);
    gameLocal.Printf("gameLocal.isServer: %d\n", gameLocal.isServer);
    gameLocal.Printf("gameLocal.isClient: %d\n", gameLocal.isClient);
    gameLocal.Printf("botAi::IsAvailable(): %d\n", botAi::IsAvailable());
    gameLocal.Printf("BOT_ENABLED(): %d\n", BOT_ENABLED());
    gameLocal.Printf("Bot slots: total(%d)\n", botAi::BOT_MAX_BOTS);

    int numAAS = gameLocal.GetNumAAS();
    bool botAasLoaded = false;
    gameLocal.Printf("Bot AAS: total(%d)\n", numAAS);
    for(int i = 0; i < numAAS; i++)
    {
        idAAS *aas = gameLocal.GetAAS(i);
        if(!aas)
            continue;
        const idAASFile *aasFile = aas->GetFile();
        if(!aasFile)
            continue;
        gameLocal.Printf("\t%d: %s\n", i, aasFile->GetName());
        if (idStr(aasFile->GetName()).Find( BOT_AAS, false ) > 0)
        {
            botAasLoaded = true;
            break;
        }
    }
    gameLocal.Printf("Bot AAS loaded: %d\n", botAasLoaded);

    int numBots = 0;
    idList<int> botIds;
    for ( int i = BOT_START_INDEX; i < BOT_MAX_NUM; i++ )
    {
        gameLocal.Printf("\t[%d]: inUse(%d), clientID(%d), entityNum(%d), selected(%d)\n", i, botAi::bots[i].inUse, botAi::bots[i].clientID, botAi::bots[i].entityNum, botAi::bots[i].selected);
        if ( botAi::bots[i].inUse )
        {
            botIds.Append(botAi::bots[i].clientID);
            numBots++;
        }
    }
    gameLocal.Printf("Bot slots: used(%d)\n", numBots);

    idStrList botNames;
    int botNum = GetBotDefs(botNames);
    gameLocal.Printf("Bot defs: total(%d)\n", botNum);
    for(int i = 0; i < botNum; i++)
    {
        gameLocal.Printf("\t%d: %s\n", i, botNames[i].c_str());
    }

    int client = 0;
    gameLocal.Printf("gameLocal.numClients: total(%d)\n", gameLocal.numClients);
    for ( int i = 0; i < gameLocal.numClients ; i++ )
    {
        const idEntity *ent = gameLocal.entities[ i ];

        if(!ent)
            gameLocal.Printf("\t%d: <NULL>\n", i);
        else if ( ent->IsType( idPlayer::Type ) )
        {
            if(botIds.FindIndex(i) < 0)
                gameLocal.Printf("\t%d: Player(%s)\n", i, gameLocal.userInfo[ i ].GetString( "ui_name" ));
            else
                gameLocal.Printf("\t%d: Bot(%s)\n", i, gameLocal.userInfo[ i ].GetString( "ui_name" ));
            client++;
        }
        else
            gameLocal.Printf("\t%d: <NOT PLAYER>\n", i);
    }

    gameLocal.Printf("gameLocal.numClients: connected(%d)\n", client);

    for ( int i = 0; i < gameLocal.num_entities ; i++ )
    {
        const idEntity *ent = gameLocal.entities[ i ];

        if(!ent)
            continue;
        if ( ent->IsType( botAi::Type ) )
        {
            const botAi *bot = (const botAi *)ent;
            gameLocal.Printf("\t%d: Bot(%s) -> level=%d, fov=%f, aim rate=%f, find radius=%f\n", bot->botID, gameLocal.userInfo[ bot->clientID() ].GetString( "ui_name" ), bot->botLevel, bot->spawnArgs.GetFloat("fov", ""), bot->aimRate, bot->findRadius);
        }
    }
}

bool botAi::AllowBotOperation(void)
{
    if ( !gameLocal.isMultiplayer )
    {
        gameLocal.Warning( "You may only operate bot to a multiplayer game" );
        return false;
    }

    if ( !gameLocal.isServer )
    {
        gameLocal.Warning( "Bots may only be operated on server, only it has the powah!" );
        return false;
    }

    if ( !IsAvailable() )
    {
        gameLocal.Warning( "SABot(a7) mod file missing!" );
        return false;
    }

    int numAAS = gameLocal.GetNumAAS();
    bool botAasLoaded = false;
    for(int i = 0; i < numAAS; i++)
    {
        idAAS *aas = gameLocal.GetAAS(i);
        if(!aas)
            continue;
        const idAASFile *aasFile = aas->GetFile();
        if(!aasFile)
            continue;
        if (idStr(aasFile->GetName()).Find( BOT_AAS, false ) > 0)
        {
            botAasLoaded = true;
            break;
        }
    }
    if ( !botAasLoaded )
    {
        gameLocal.Warning( "bot aas file not loaded!" );
        return false;
    }
	return true;
}

void botAi::Cmd_SetupBotLevel_f(const idCmdArgs& args)
{
    if(!AllowBotOperation())
        return;

    if (args.Argc() < 2)
    {
        gameLocal.Printf("USAGE: %s <bot level>\n", args.Argv(0));
        return;
    }

    int level = atoi(args.Argv(1));
    for ( int i = 0; i < gameLocal.num_entities ; i++ )
    {
        idEntity *ent = gameLocal.entities[ i ];

        if(!ent)
            continue;
        if ( ent->IsType( botAi::Type ) )
        {
            botAi *bot = (botAi *)ent;
            bot->SetBotLevel(level);
        }
    }
}

botAi * botAi::SpawnBot(idPlayer *botClient)
{
    int			i;
    const char* name;
    idDict		userInfo;
    idEntity *	ent;
    idDict		dict;

    int newClientID = botClient->entityNumber;

    if(newClientID < botAi::BOT_START_INDEX || newClientID >= BOT_MAX_NUM)
    {
        gameLocal.Warning("Client ID(%d) not allow spawn bot!", newClientID);
        return NULL;
    }
    if(!botClient->spawnArgs.GetBool("isBot"))
    {
        gameLocal.Warning("Client ID(%d) not a bot!", newClientID);
        return NULL;
    }
    if(!botAi::bots[newClientID].inUse) // so must mark first
    {
        gameLocal.Warning("Client ID(%d) spawn slot not a bot!", newClientID);
        return NULL;
    }

    const char *defName = botClient->spawnArgs.GetString("botDefName"); // botAi::bots[newBotID].defName;
    if(!defName[0])
    {
        gameLocal.Warning("Client ID(%d) missing spawn bot defName!", newClientID);
        return NULL;
    }

    int newBotID = newClientID;
    gameLocal.Printf("Spawn bot: botID=%d\n", newBotID);

    idDict botLevelDict;
    int botLevel = GetBotLevelData(harm_si_botLevel.GetInteger(), botLevelDict);
    if(botLevel > 0)
    {
        const char *Bot_Level_Keys[] = {
                "fov",
                "aim_rate",
                "find_radius",
        };
        int keysLength = sizeof(Bot_Level_Keys) / sizeof(Bot_Level_Keys[0]);
        for(i = 0; i < keysLength; i++)
        {
            const char *v = botLevelDict.GetString(Bot_Level_Keys[i], "");
            if(v && v[0])
                dict.Set(Bot_Level_Keys[i], v);
        }
    }
    dict.SetInt("botLevel", botLevel);
    idStr uiName = GetBotName(-1);
    if(uiName && uiName[0])
        dict.Set("ui_name", uiName.c_str());

    dict.Set( "classname", defName );

    dict.Set( "name", va( "bot_%d", newBotID ) ); // TinMan: Set entity name for easier debugging
    dict.SetInt( "botID", newBotID ); // TinMan: Bot needs to know this before it's spawned so it can sync up with the client

    //gameLocal.Printf("Spawning bot as client %d\n", newClientID);

    // Start up client
    // TinMan: Put our grubby fingerprints on fakeclient. *todo* may want to make these entity flags and make sure they go across to clients so we can rely on using them for clientside code

    // TinMan: Add client to bot list
    bots[newBotID].clientID = newClientID;

    // TinMan: Spawn bot with our dict
    gameLocal.SpawnEntityDef( dict, &ent, false );
    botAi * newBot = static_cast< botAi * >( ent ); // TinMan: Make a nice and pretty pointer to bot

    // TinMan: Add bot to bot list
    bots[newBotID].entityNum = newBot->entityNumber;
    botClient->spawnArgs.SetInt("botEntityNumber", newBot->entityNumber);
    botClient->spawnArgs.SetInt("botLevel", botLevel);

    // TinMan: Give me your name, licence and occupation.
    name = newBot->spawnArgs.GetString( "ui_name" );
    idStr botName(va( "[BOT%d] %s", newBotID, name));
    if(botLevel > 0)
        botName.Append(va(" (%d)", botLevel));
    userInfo.Set( "ui_name", botName ); // TinMan: *debug* Prefix [BOTn]

    // TinMan: I love the skin you're in.
    int skinNum = newBot->spawnArgs.GetInt( "mp_skin" );
    //k userInfo.Set( "ui_skin", ui_skinArgs[ skinNum ] );

    // TinMan: Set team
    if ( IsGametypeTeamBased() )
    {
        userInfo.Set( "ui_team", newBot->spawnArgs.GetInt( "team" ) ? "Marine" : "Strogg" );
    }
    else if ( gameLocal.gameType == GAME_SP )
    {
        botClient->team = newBot->spawnArgs.GetInt( "team" );
    }

    // TinMan: Finish up connecting - Called in SetUserInfo
    //gameLocal.mpGame.EnterGame(newClientID);
    //gameLocal.Printf("Bot has been connected, and client has begun.\n");

    userInfo.Set( "ui_ready", "Ready" );

    idStrList playerModelNames;
    int numMarinePlayerModel = GetPlayerModelNames(playerModelNames, TEAM_MARINE);
    if(numMarinePlayerModel > 0)
    {
        int index = gameLocal.random.RandomInt(numMarinePlayerModel);
        const char *modelName = playerModelNames[index];
        userInfo.Set("model", modelName);
        userInfo.Set("model_marine", modelName);
        userInfo.Set("ui_model", modelName);
        userInfo.Set("ui_model_marine", modelName);
        userInfo.Set("def_default_model", modelName);
        userInfo.Set("def_default_model_marine", modelName);
        botClient->spawnArgs.Set("model", modelName);
        botClient->spawnArgs.Set("model_marine", modelName);
        botClient->spawnArgs.Set("ui_model", modelName);
        botClient->spawnArgs.Set("ui_model_marine", modelName);
        botClient->spawnArgs.Set("def_default_model", modelName);
        botClient->spawnArgs.Set("def_default_model_marine", modelName);
    }
    int numStroggPlayerModel = GetPlayerModelNames(playerModelNames, TEAM_STROGG);
    if(numStroggPlayerModel > 0)
    {
        int index = gameLocal.random.RandomInt(numStroggPlayerModel) + numMarinePlayerModel;
        const char *modelName = playerModelNames[index];
        userInfo.Set("model_strogg", modelName);
        userInfo.Set("ui_model_strogg", modelName);
        userInfo.Set("def_default_model_strogg", modelName);
        botClient->spawnArgs.Set("model_strogg", modelName);
        botClient->spawnArgs.Set("ui_model_strogg", modelName);
        botClient->spawnArgs.Set("def_default_model_strogg", modelName);
    }
    int numPlayerModel = GetPlayerModelNames(playerModelNames, TEAM_NONE);
    if(playerModelNames.Num() > 0)
    {
        int index = gameLocal.random.RandomInt(playerModelNames.Num());
        const char *modelName = playerModelNames[index];
        userInfo.Set("model", modelName);
        userInfo.Set("ui_model", modelName);
        userInfo.Set("def_default_model", modelName);
        botClient->spawnArgs.Set("model", modelName);
        botClient->spawnArgs.Set("ui_model", modelName);
        botClient->spawnArgs.Set("def_default_model", modelName);
    }

    gameLocal.SetUserInfo( newClientID, userInfo, false ); // TinMan: apply the userinfo *note* func was changed slightly in 1.3
    botClient->Spectate( false ); // TinMan: Finally done, get outa spectate
    //botClient->UpdateModelSetup(true);

    if ( IsGametypeTeamBased() && !si_autobalance.GetBool() )
		botClient->BalanceTeam();

    cmdSystem->BufferCommandText( CMD_EXEC_NOW, va( "updateUI %d\n", newClientID ) );

    return newBot;
}

void botAi::ReleaseBotSlot(int clientNum)
{
    int botID = clientNum;
    gameLocal.Printf("Release bot slot: botID=%d\n", botID);
    if(botID < botAi::BOT_START_INDEX || botID >= BOT_MAX_NUM)
        return;
    botAi::bots[botID].inUse = false;
    botAi::bots[botID].clientID = -1;
    botAi::bots[botID].entityNum = -1;
    // botAi::bots[botID].defName[0] = '\0';
}

bool botAi::PlayerHasBotSlot(int clientNum)
{
    int botID = clientNum;
    if(botID < botAi::BOT_START_INDEX || botID >= BOT_MAX_NUM)
        return false;
    // gameLocal.Printf("Player has bot slot: botID=%d\n", botID);
    return botAi::bots[botID].inUse;
}

int botAi::GetNumConnectedClients(bool ava)
{
    int num = 0;
    bool useReady = gameLocal.serverInfo.GetBool( "si_useReady" );
    for ( int clientID = 0; clientID < MAX_CLIENTS; clientID++ ) {
        if ( gameLocal.entities[ clientID ] && gameLocal.entities[ clientID ]->IsType( idPlayer::Type ) ) {
            idPlayer *client = static_cast<idPlayer *>(gameLocal.entities[ clientID ]);
            if(!ava || ((!useReady || client->ready) && !client->spectating))
                num++;
        }
    }
    return num;
}

void botAi::Cmd_SetupBotWeapons_f(const idCmdArgs& args)
{
    if(!AllowBotOperation())
        return;

    int w = 0;
    if (args.Argc() >= 2)
    {
        int num = args.Argc();
        idStrList list;
        for(int i = 1; i < num; i++)
        {
            const char *value = args.Argv(i);
            if(!idStr::Cmp("*", value))
            {
                w = BOT_ALL_MP_WEAPON;
                break;
            }
            list.AddUnique(value);
        }
        if(w == 0)
            w = MakeWeaponMask(list);

    }
    if(w == 0)
        w = InsertBasicWeaponMask();

    idStr weapon = MakeWeaponString(w);
    gameLocal.Printf("Setup bot weapons: %s\n", weapon.c_str());
    int a = harm_si_botAmmo.GetInteger();
    if(a == 0)
        a = 1;
    idDict ammo = MakeAmmoDict(w, a);
    int numAmmo = ammo.GetNumKeyVals();
    if(numAmmo > 0)
    {
        for(int i = 0; i < numAmmo; i++)
        {
            const idKeyValue *kv = ammo.GetKeyVal(i);
            gameLocal.Printf("  %s = %s\n", kv->GetKey().c_str(), kv->GetValue().c_str());
        }
    }
    InsertEmptyAmmo(ammo);

    for ( int clientID = BOT_START_INDEX; clientID < MAX_CLIENTS ; clientID++ )
    {
        if ( gameLocal.entities[ clientID ] && gameLocal.entities[ clientID ]->IsType( idPlayer::Type ) ) {
            idPlayer *client = static_cast<idPlayer *>(gameLocal.entities[ clientID ]);
            if(!client->IsBot())
                continue;
            client->spawnArgs.Set("weapon", weapon.c_str());
            if(numAmmo > 0)
            {
                client->spawnArgs.Copy(ammo);
            }
        }
    }
    gameLocal.Printf("Setup bot weapons will be available after the bot next spawn.\n");
}

void botAi::Cmd_SetupBotAmmo_f(const idCmdArgs& args)
{
    if(!AllowBotOperation())
        return;

    int a = 0;
    if (args.Argc() >= 2)
    {
        a = atoi(args.Argv(1));
    }

    gameLocal.Printf("Setup bot weapons ammo: %d\n", a);

    for ( int clientID = BOT_START_INDEX; clientID < MAX_CLIENTS ; clientID++ )
    {
        if ( gameLocal.entities[ clientID ] && gameLocal.entities[ clientID ]->IsType( idPlayer::Type ) ) {
            idPlayer *client = static_cast<idPlayer *>(gameLocal.entities[ clientID ]);
            if(!client->IsBot())
                continue;
            const char *wp = client->spawnArgs.GetString("weapon", "");
            int w = MakeWeaponMask(wp);
            idDict ammo = MakeAmmoDict(w, a);
            InsertEmptyAmmo(ammo);
            int numAmmo = ammo.GetNumKeyVals();
            if(numAmmo > 0)
            {
                gameLocal.Printf("Bot %d weapons: %s -> %x\n", clientID, wp, w);
                for(int i = 0; i < numAmmo; i++)
                {
                    const idKeyValue *kv = ammo.GetKeyVal(i);
                    gameLocal.Printf("  %s = %s\n", kv->GetKey().c_str(), kv->GetValue().c_str());
                }
                client->spawnArgs.Copy(ammo);
            }
        }
    }
    gameLocal.Printf("Setup bot weapons ammo will be available after the bot next spawn.\n");
}

void botAi::ArgCompletion_botWeapons( const idCmdArgs &args, void(*callback)( const char *s ) )
{
#define BOT_MW(I, N, A, U, M) \
	callback(va("%s %d", args.Argv(0), I)); \
	callback(va("%s %s", args.Argv(0), N)); \
	callback(va("%s weapon_%s", args.Argv(0), N));

    //BOT_MW(0, "blaster", "", -1, -1);
    BOT_MW(0, "gauntlet", "", 0, 0);
    BOT_MW(1, "machinegun", "machinegun", 40, 300);
    BOT_MW(2, "shotgun", "shotgun", 8, 50);
    BOT_MW(3, "hyperblaster", "hyperblaster", 60, 400);
    BOT_MW(4, "grenadelauncher", "grenadelauncher", 8, 50);
    BOT_MW(5, "nailgun", "nailgun", 50, 300);
    BOT_MW(6, "rocketlauncher", "rocketlauncher", 1, 40);
    BOT_MW(7, "railgun", "railgun", 3, 50);
    BOT_MW(8, "lightninggun", "lightninggun", 100, 400);
    BOT_MW(9, "dmg", "dmg", 1, 25);
    BOT_MW(10, "napalmgun", "napalmgun", 20, 40);

#undef BOT_MW
}
