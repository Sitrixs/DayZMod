static ref FactionSpawnModule GetFactionModule()
{
    return FactionSpawnModule.Cast(CF_ModuleCoreManager.Get(FactionSpawnModule));
}

[CF_RegisterModule(FactionSpawnModule)]
class FactionSpawnModule : CF_ModuleWorld
{
    ref FactionSpawnSettings settings;
    ref PlayerFactionModel playerFactionModel;
    ref FactionView factionViewMenu;

    override void OnInit()
    {
        super.OnInit();
        EnableMissionStart();
        EnableInvokeConnect();
        EnableUpdate();
    }

    void InitializeModule()
    {
        GetFactionSpawnManagementLogger().LogInfo("FactionSpawnModule has started");

        if(GetGame().IsServer())
        {
            settings = FactionSpawnSettings.Load();
        }
        else
        {
            settings = new FactionSpawnSettings();
            playerFactionModel = new PlayerFactionModel();
        }

        InitRPCs();
    }

    void InitRPCs()
    {
        //client
        if(GetGame().IsClient())
        {
            GetRPCManager().AddRPC("FactionSpawnSystem", "GetConfigResponse", this, SingeplayerExecutionType.Client);
            GetRPCManager().AddRPC("FactionSpawnSystem", "GetPlayerFactionModelResponse", this, SingeplayerExecutionType.Client);
            GetRPCManager().AddRPC("FactionSpawnSystem", "GetOpenMenuFactionRequest", this, SingeplayerExecutionType.Client);
        }
        else //server
        {
            GetRPCManager().AddRPC("FactionSpawnSystem", "GetFactionSpawnRequest", this, SingeplayerExecutionType.Server);
        }
    }

    FactionTeam GetFactionTeamFromName()
    {
        FactionTeam factionTeam = settings.GetFactionFromName(playerFactionModel.factionName);
        if(!factionTeam)
            return null;
        
        return factionTeam;
    }

    array<ref FactionLocation> GetFactionLocations()
    {
        FactionTeam factionTeam = GetFactionTeamFromName();
        if(!factionTeam)
            return null;
        
        return factionTeam.spawnLocations;
    }

    array<ref FactionItem> GetFactionLoadout()
    {
        FactionTeam factionTeam = GetFactionTeamFromName();
        if(!factionTeam)
            return null;
    
        array<ref FactionItem> playerItems = playerFactionModel.itemsPreset;
        array<ref FactionItem> filteredFactionItems = new array<ref FactionItem>(); // Copy of faction items
        FactionCopyClass<array<ref FactionItem>>.Copy(factionTeam.items, filteredFactionItems);

        // Iterate over the player’s items and remove matching items from the faction's loadout
        foreach (FactionItem playerItem : playerItems) {
            for (int i = filteredFactionItems.Count() - 1; i >= 0 ; i--) {
                if (filteredFactionItems[i].className == playerItem.className){
                    filteredFactionItems.Remove(i);
                    break;
                }
            }
        }

        return filteredFactionItems; // Return the filtered loadout
    }

    //RPC Method trigger when the method GetRPCmANA
    void GetConfigResponse(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if(type != CallType.Client)
            return;

        Param1<FactionSpawnSettings> data;
        if(!ctx.Read(data)){
            return;
        }

        settings = data.param1;
        JsonFileLoader<FactionSpawnSettings>.JsonSaveFile(FactionSpawnManagement_ROOT_FOLDER + "settings.json", settings);
    }

    //RPC Method trigger when the method GetRPCmANA
    void GetPlayerFactionModelResponse(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if(type != CallType.Client)
            return;

        Param1<PlayerFactionModel> data;
        if(!ctx.Read(data)){
            return;
        }

        playerFactionModel = data.param1;
    }

    void GetFactionSpawnRequest(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if(type != CallType.Server)
            return;

        Param1<PlayerFactionModel> data;
        if(!ctx.Read(data)){
            return;
        }

        PlayerFactionModel playerFactionModel = data.param1;
        playerFactionModel.Save();

        PlayerBase player = GetPlayerByIdentity(sender);
        if(!player)
            return;

        player.EquipLoadout(playerFactionModel);

        FactionTeam faction = settings.GetFactionFromName(playerFactionModel.factionName);
        if(!faction){
            return;
        }

        player.Teleport(faction.GetSpawnLocation(playerFactionModel.locationNameSelected));
    }

    void OnPlayerConnect(PlayerBase player, PlayerIdentity identity)
    {
        GetFactionSpawnManagementLogger().LogDebug(string.Format("OnPlayerConnect - %1 - %2", identity.GetName(), identity.GetPlainId()));
        GetRPCManager().SendRPC("FactionSpawnSystem", "GetConfigResponse", new Param1<FactionSpawnSettings>(settings), true, identity);
        JsonFileLoader<FactionSpawnSettings>.JsonSaveFile(FactionSpawnManagement_ROOT_FOLDER + "settings.json", settings);

        PlayerFactionModel factionModel = PlayerFactionModel.Load(player);
        GetRPCManager().SendRPC("FactionSpawnSystem", "GetPlayerFactionModelResponse", new Param1<PlayerFactionModel>(factionModel), true, identity);
    }

    void OnPlayerRespawn(PlayerBase player, PlayerIdentity identity)
    {
        GetFactionSpawnManagementLogger().LogDebug(string.Format("OnPlayerRespawn - %1 - %2", identity.GetName(), identity.GetPlainId()));
        GetRPCManager().SendRPC("FactionSpawnSystem", "GetOpenMenuFactionRequest", null, true, identity);
    }

    override void OnInvokeConnect(Class sender, CF_EventArgs args)
    {
        super.OnInvokeConnect(sender, args);

        auto cArgs = CF_EventPlayerArgs.Cast(args);

        if(!IsMissionHost()){
            return;
        }

        if(!cArgs.Player || !cArgs.Identity)
            return;

        OnPlayerConnect(cArgs.Player, cArgs.Identity);
    }

    void GetOpenMenuFactionRequest(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if(type != CallType.Client)
            return;

        GetFactionSpawnManagementLogger().LogDebug("GetOpenMenuFactionRequest");

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(OpenMenuFaction, 1000, true);
    }

    void OpenMenuFaction()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if(!player)
            return;
        
        if(!player.IsPlayerLoaded())
            return;

        Mission mission = GetGame().GetMission();
        if(mission.IsPlayerRespawning())
            return;

        GetFactionSpawnManagementLogger().LogDebug("OpenMenuFaction");

        OpenFactionMenu();
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(OpenMenuFaction);
    }

    FactionView GetFactionView()
    {
        return factionViewMenu;
    }

    void OpenFactionMenu()
    {
        if (!factionViewMenu) {
            factionViewMenu = new FactionView();
		}

        factionViewMenu.Show(true);
    }

    bool IsFactionViewOpen()
    {
        return factionViewMenu != null;
    }

    void CloseFactionMenu()
    {
        if (factionViewMenu){
            delete factionViewMenu;
        }
    }

    override void OnMissionStart(Class sender, CF_EventArgs args)
    {
        super.OnMissionStart(sender, args);
        if(GetGame().IsServer())
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(InitializeModule, 1000); 
            return;
        }

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(InitializeModule, 100); 
    }

    override void OnUpdate(Class sender, CF_EventArgs args)
    {
        super.OnUpdate(sender, args);
    }

    static PlayerBase GetPlayerByIdentity(PlayerIdentity identity)
    {
        int low = 0;
        int high = 0;
        GetGame().GetPlayerNetworkIDByIdentityID(identity.GetPlayerId(), low, high);
        return PlayerBase.Cast(GetGame().GetObjectByNetworkId(low, high));
    }
}