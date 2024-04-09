modded class PlayerBase 
{
    void EquipLoadout(PlayerFactionModel factionModel)
    {
        FactionSpawnModuleHelper.EquipPlayer(this, factionModel.itemsPreset);
    }

    void Teleport(FactionLocation spawnLocation)
    {
        vector position = FactionSpawnModuleHelper.GetRandomPosition(spawnLocation.position, spawnLocation.spawnRadius);
        SetPosition(FactionSpawnModuleHelper.SnapToGround(position));
    }
}