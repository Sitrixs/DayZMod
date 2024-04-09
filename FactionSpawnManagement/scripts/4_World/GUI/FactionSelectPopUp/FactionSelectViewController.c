class FactionSelectViewController:ViewController
{
    FactionSpawnModule moduleFaction;
    ref ObservableCollection<ref FactionTeamCardView> faction_teams = new ObservableCollection<ref FactionTeamCardView>(this);
    
    void FactionSelectViewController()
    {
        FactionTeamCardView.Event_OnFactionTeamCardClickCallBack.Insert(OnFactionTeamCardBtnExecute);
    }

    void ~FactionSelectViewController()
    {
        faction_teams.Clear();
        delete faction_teams;
    }

    override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);

        moduleFaction = FactionSpawnModule.Cast(CF_ModuleCoreManager.Get(FactionSpawnModule));
        FillTeamFactionCardList();
	}

    void FillTeamFactionCardList()
    {
        array<ref FactionTeam> factions = moduleFaction.settings.factions;
        JsonFileLoader<array<ref FactionTeam>>.JsonSaveFile(FactionSpawnManagement_ROOT_FOLDER + "factions.json", factions);
        foreach(FactionTeam team : factions)
        {
            faction_teams.Insert(new FactionTeamCardView(team));
        }
    }

    void OnFactionTeamCardBtnExecute(FactionTeamCardView factionTeamCardView)
	{
        moduleFaction.playerFactionModel.SetFactionName(factionTeamCardView.team.name);
        moduleFaction.playerFactionModel.SetTotalPoint(GetFactionModule().GetFactionTeamFromName().totalPoints);
        Show(false);
		delete this;
	}
}