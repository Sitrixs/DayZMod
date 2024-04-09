class FactionSpawnSettings
{
    string version = FactionSpawnManagement_VERSION;

    ref array<ref FactionTeam> factions;

    void FactionSpawnSettings()
    {
        factions = new array<ref FactionTeam>();
    }

    FactionTeam GetFactionFromName(string factionName)
    {
        foreach(FactionTeam faction: factions)
        {
            if(faction.name == factionName)
                return faction;
        }

        return null;
    }


    void FactionSpawnDefaultSettings()
    {
        factions.Insert(new FactionTeam("Bandits", 20));
        factions[0].SetBriefHistory("Bandit brief history");
        factions[0].SetImagePath("FactionSpawnManagement/datasets/images/stalker/Bandits.edds");
        factions[0].GenerateDefaultSpawnLocations();
        factions[0].GenerateDefaultItems();
        factions.Insert(new FactionTeam("ClearSky", 20));
        factions[1].SetBriefHistory("ClearSky brief history");
        factions[1].SetImagePath("FactionSpawnManagement/datasets/images/stalker/ClearSky.edds");
        factions[1].GenerateDefaultSpawnLocations();
        factions[1].GenerateDefaultItems();
        factions.Insert(new FactionTeam("Duty", 20));
        factions[2].SetBriefHistory("Duty brief history");
        factions[2].SetImagePath("FactionSpawnManagement/datasets/images/stalker/Duty.edds");
        factions[2].GenerateDefaultSpawnLocations();
        factions[2].GenerateDefaultItems();
        factions.Insert(new FactionTeam("Ecologists", 20));
        factions[3].SetBriefHistory("Ecologists brief history");
        factions[3].SetImagePath("FactionSpawnManagement/datasets/images/stalker/Ecologists.edds");
        factions[3].GenerateDefaultSpawnLocations();
        factions[3].GenerateDefaultItems();
        factions.Insert(new FactionTeam("Freedom", 20));
        factions[4].SetBriefHistory("Freedom brief history");
        factions[4].SetImagePath("FactionSpawnManagement/datasets/images/stalker/Freedom.edds");
        factions[4].GenerateDefaultSpawnLocations();
        factions[4].GenerateDefaultItems();
        factions.Insert(new FactionTeam("FreeStalker", 20));
        factions[5].SetBriefHistory("FreeStalker brief history");
        factions[5].SetImagePath("FactionSpawnManagement/datasets/images/stalker/FreeStalker.edds");
        factions[5].GenerateDefaultSpawnLocations();
        factions[5].GenerateDefaultItems();
        factions.Insert(new FactionTeam("ISG", 20));
        factions[6].SetBriefHistory("ISG brief history");
        factions[6].SetImagePath("FactionSpawnManagement/datasets/images/stalker/ISG.edds");
        factions[6].GenerateDefaultSpawnLocations();
        factions[6].GenerateDefaultItems();
        factions.Insert(new FactionTeam("Mercinaries", 20));
        factions[7].SetBriefHistory("Mercinaries brief history");
        factions[7].SetImagePath("FactionSpawnManagement/datasets/images/stalker/Mercinaries.edds");
        factions[7].GenerateDefaultSpawnLocations();
        factions[7].GenerateDefaultItems();
        factions.Insert(new FactionTeam("Military", 20));
        factions[8].SetBriefHistory("Military brief history");
        factions[8].SetImagePath("FactionSpawnManagement/datasets/images/stalker/Military.edds");
        factions[8].GenerateDefaultSpawnLocations();
        factions[8].GenerateDefaultItems();
        factions.Insert(new FactionTeam("Monolith", 20));
        factions[9].SetBriefHistory("Monolith brief history");
        factions[9].SetImagePath("FactionSpawnManagement/datasets/images/stalker/Monolith.edds");
        factions[9].GenerateDefaultSpawnLocations();
        factions[9].GenerateDefaultItems();
        factions.Insert(new FactionTeam("Renegade", 20));
        factions[10].SetBriefHistory("Renegade brief history");
        factions[10].SetImagePath("FactionSpawnManagement/datasets/images/stalker/Renegade.edds");
        factions[10].GenerateDefaultSpawnLocations();
        factions[10].GenerateDefaultItems();
        factions.Insert(new FactionTeam("Sin", 20));
        factions[11].SetBriefHistory("Sin brief history");
        factions[11].SetImagePath("FactionSpawnManagement/datasets/images/stalker/Sin.edds");
        factions[11].GenerateDefaultSpawnLocations();
        factions[11].GenerateDefaultItems();
        Save();
    }

    void Save()
    {
        //save json file
        JsonFileLoader<FactionSpawnSettings>.JsonSaveFile(FactionSpawnManagement_CONFIG_FILE, this);
    }

    static void MakeDirectoryIfNotExist()
    {
        if(!FileExist(FactionSpawnManagement_ROOT_FOLDER)){
            MakeDirectory(FactionSpawnManagement_ROOT_FOLDER);
        }

        if(!FileExist(FactionSpawnManagement_CONFIG_FOLDER)){
            MakeDirectory(FactionSpawnManagement_CONFIG_FOLDER);
        }

        if(!FileExist(FactionSpawnManagement_DB_FOLDER)){
            MakeDirectory(FactionSpawnManagement_DB_FOLDER);
        }

        if(!FileExist(FactionSpawnManagement_LOG_FOLDER)){
            MakeDirectory(FactionSpawnManagement_LOG_FOLDER);
        }
    }

    static FactionSpawnSettings Load()
    {
        FactionSpawnSettings settings = new FactionSpawnSettings();

        MakeDirectoryIfNotExist();

        if(FileExist(FactionSpawnManagement_CONFIG_FILE))
        {
            JsonFileLoader<FactionSpawnSettings>.JsonLoadFile(FactionSpawnManagement_CONFIG_FILE, settings);
            return settings;
        }

        settings.FactionSpawnDefaultSettings();
        return settings;
    }
}