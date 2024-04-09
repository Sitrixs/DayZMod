class FactionView: ScriptViewTemplate<FactionViewController>
{
	float deltaT = 0.0;
	float REFRESH_PERIOD = 1.0;

    void FactionView()
	{
		PPEffects.SetBlurMenu(0.5);
		if (GetGame()) {
			GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
			GetGame().GetInput().ChangeGameFocus(1, INPUT_DEVICE_MOUSE);
			GetGame().GetInput().ChangeGameFocus(1, INPUT_DEVICE_KEYBOARD);
			GetGame().GetUIManager().ShowUICursor(true);
			GetGame().GetMission().GetHud().Show(false);
		}
	}

	void ~FactionView()
	{
		PPEffects.SetBlurMenu(0.0);
				
		if (GetGame()) {
			GetGame().GetMission().PlayerControlEnable(false);
			GetGame().GetInput().ChangeGameFocus(-1, INPUT_DEVICE_MOUSE);
			GetGame().GetInput().ChangeGameFocus(-1, INPUT_DEVICE_KEYBOARD);
			GetGame().GetUIManager().ShowUICursor(false);
			GetGame().GetMission().GetHud().Show(true);		
		}
	}

    override string GetLayoutFile() 
	{
		return "FactionSpawnManagement/datasets/gui/FactionManagement.layout";
	}

	override protected void Update(float dt)
	{
		if(deltaT < REFRESH_PERIOD){
			deltaT+= dt;
			return;
		}

		deltaT = 0.0;
		GetGame().GetUIManager().ShowUICursor(true);
	}
}