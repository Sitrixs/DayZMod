class FactionInfoCardView: ScriptViewTemplate<FactionInfoCardViewController>
{
    ref FactionTeam team;
    ButtonWidget factionInfoBtn;
    Widget selectedBackground;
    static ref ScriptInvoker Event_OnFactionInfoCardClickCallBack = new ScriptInvoker();  

    void FactionInfoCardView(FactionTeam team)
    {
        this.team = team;
        m_TemplateController.Setup(team.imagePath, team.name);
    }

    void Select()
    {
        selectedBackground.Enable(true);
    }

    void UnSelect()
    {
        selectedBackground.Enable(false);
    }

    bool OnFactionInfoCardExecute(ButtonCommandArgs args)
	{
        Event_OnFactionInfoCardClickCallBack.Invoke(this);
		return true;
	}

    override bool OnMouseEnter(Widget w, int x, int y)
	{
        if(w && factionInfoBtn == w)
            factionInfoBtn.SetAlpha(1.0);

        if(w && w.GetUserID() == 555)
            w.SetAlpha(1.0);

        return false;
	}

	
    override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
        if(w && factionInfoBtn == w)
            factionInfoBtn.SetAlpha(0.5);

        if(w && w.GetUserID() == 555)
            w.SetAlpha(0.5);
        
        return false;
	}

    override string GetLayoutFile() 
	{
		return "FactionSpawnManagement/datasets/gui/FactionInfoCard.layout";
	}
}