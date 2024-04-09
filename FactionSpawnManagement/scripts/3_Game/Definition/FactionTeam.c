class FactionTeam
{
    string name;
    int totalPoints;
    string briefHistory;
    string imagePath;
    ref array<ref FactionLocation> spawnLocations;
    ref array<ref FactionItem> items;

    void FactionTeam(string name, int totalPoints)
    {
        this.name = name;
        this.totalPoints = totalPoints;
        this.items = new array<ref FactionItem>();
        this.spawnLocations = new array<ref FactionLocation>();
    }

    void GenerateDefaultSpawnLocations()
    {
        spawnLocations.Insert(new FactionLocation("spawn point 1", Vector(7500,0,7500), 100));
        spawnLocations.Insert(new FactionLocation("spawn point 2", Vector(7500,0,7500), 100));
        spawnLocations.Insert(new FactionLocation("spawn point 3", Vector(7500,0,7500), 100));
    }

    void GenerateDefaultItems()
    {
        items.Insert(new FactionItem("M4A1_Black",4,1, "Hand"));
        items[0].attachments.Insert(new FactionAttachment("Mag_STANAG_60Rnd"));
        items.Insert(new FactionItem("M65Jacket_Khaki",3));
        items.Insert(new FactionItem("Jeans_Black",2));
        items.Insert(new FactionItem("CombatBoots_Black",7));
        items.Insert(new FactionItem("ImprovisedExplosive",7));
        items.Insert(new FactionItem("BandageDressing",2));
        items.Insert(new FactionItem("BandageDressing",2));
        items.Insert(new FactionItem("BandageDressing",2));
        items.Insert(new FactionItem("SVD",4,1, "Hand"));
        items[8].attachments.Insert(new FactionAttachment("Mag_SVD_10Rnd"));
        items.Insert(new FactionItem("GhillieSuit",8));
        items.Insert(new FactionItem("HunterPants_Brown",3));
        items.Insert(new FactionItem("Binoculars",4));
        items.Insert(new FactionItem("USMCJacket_Woodland",8));
        items.Insert(new FactionItem("SKS",2,1, "Hand"));
        items[13].attachments.Insert(new FactionAttachment("PUScope"));
        items.Insert(new FactionItem("GhillieSuit",8));
        items.Insert(new FactionItem("FirstAidKit",3));
        items.Insert(new FactionItem("AmmoBox_762x39_20Rnd",4));
        items.Insert(new FactionItem("AmmoBox_762x39_20Rnd",8));
    }

    void SetBriefHistory(string history)
    {
        briefHistory = history;
    }

    void SetImagePath(string imgPath)
    {
        imagePath = imgPath;
    }



    FactionLocation GetSpawnLocation(string locationNameSelected)
    {
        foreach(FactionLocation location: spawnLocations)
        {
            if(location.name == locationNameSelected)
                return location;
        }

        return null;
    }
}