class PlayerFactionModel
{
    string name;
    string steamId64;
    string factionName;
    int totalPoint;
    string locationNameSelected;
    ref array<ref FactionItem> itemsPreset;
    static ref ScriptInvoker Event_OnChangePlayerFactionModelCallBack = new ScriptInvoker();

    void PlayerFactionModel()
    {
        this.itemsPreset = new array<ref FactionItem>();
    }

    void SetItemsPreset(array<ref FactionItem> presets)
    {
        itemsPreset = presets;
        OnChange();
    }

    void SetFactionName(string name)
    {
        factionName = name;
        OnChange();
    }

    void SetTotalPoint(int point)
    {
        this.totalPoint = point;
        OnChange();
    }

    void OnChange()
    {
        Event_OnChangePlayerFactionModelCallBack.Invoke(this);
    }

    void Initiate(string name, string steamId)
    {
        this.name = name;
        this.steamId64 = steamId;
        Save();
    }

    bool HasFaction()
    {
        return factionName != string.Empty;
    }

    void Save()
    {
        JsonFileLoader<PlayerFactionModel>.JsonSaveFile(string.Format(FactionSpawnManagement_DB_FILE, steamId64), this);
    }

    static PlayerFactionModel Load(PlayerBase player)
    {
        PlayerFactionModel model = new PlayerFactionModel();

        string steamId = player.GetIdentity().GetPlainId();
        string filePath = string.Format(FactionSpawnManagement_DB_FILE, steamId);
        if(FileExist(filePath))
        {
            JsonFileLoader<PlayerFactionModel>.JsonLoadFile(filePath, model);
            return model;        
        }

        model.Initiate(player.GetIdentity().GetName(), steamId);
        return model;
    }
}
