class FactionTeamCardView: ScriptViewTemplate<FactionTeamCardViewController>
{
    static ref ScriptInvoker Event_OnFactionTeamCardClickCallBack = new ScriptInvoker();

    ImageWidget factionImage;

    ref FactionTeam team;

    override string GetLayoutFile() 
	{
		return "FactionSpawnManagement/datasets/gui/FactionTeamCard.layout";
	}

    void FactionTeamCardView(FactionTeam team)
    {
        this.team = team;
        factionImage.LoadImageFile(0, team.imagePath);
    }

    override bool OnMouseEnter(Widget w, int x, int y)
	{
        if(w && w.GetUserID() == 333)
            w.SetAlpha(1.0);

        return false;
	}

	
    override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
        if(w && w.GetUserID() == 333)
            w.SetAlpha(0.5);
        
        return false;
	}

    bool OnFactionTeamSelectExecute(ButtonCommandArgs args)
	{
        Event_OnFactionTeamCardClickCallBack.Invoke(this);
		return true;
	}
}