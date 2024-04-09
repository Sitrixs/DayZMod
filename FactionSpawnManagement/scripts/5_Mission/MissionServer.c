modded class MissionServer extends MissionBase
{
	void ~MissionServer() {
	}

	void MissionServer()
	{
		GetFactionSpawnManagementLogger().LogDebug("FactionSpawnManagement mod has started!");
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		GetFactionModule().OnPlayerRespawn(player, player.GetIdentity());
	}
};
