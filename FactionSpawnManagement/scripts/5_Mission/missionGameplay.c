modded class MissionGameplay extends MissionBase
{
	void MissionGameplay()
	{
		GetFactionSpawnManagementLogger().LogDebug("FactionSpawnManagement mod has started!");
	}

	override void Pause()
	{
		if(GetFactionModule().IsFactionViewOpen())
			return;

		super.Pause();
	}
};
