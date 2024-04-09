class FactionCharacterViewController:ViewController
{
    static ref ScriptInvoker Event_OnComboBoxClickCallBack = new ScriptInvoker();
    ImageWidget factionImage;
    ButtonWidget selectFactionBtn;
    ref FactionSpawnModule moduleFaction;
    ref FactionInfoCardView selectedInfoCard;
    ref ObservableCollection<string> observable_combobox_teleportation = new ObservableCollection<string>(this);
    ref ObservableCollection<ref FactionInfoCardView> faction_item_labels = new ObservableCollection<ref FactionInfoCardView>(this); 
    string player_name;
    string player_money;
    string brief_history;
    string faction_name;
    int observable_combobox_teleportation_selection;
    ref FactionSelectView factionSelectView; 

    void FactionCharacterViewController()
    {
        FactionTeamCardView.Event_OnFactionTeamCardClickCallBack.Insert(OnFactionTeamCardBtnExecute);
        PlayerFactionModel.Event_OnChangePlayerFactionModelCallBack.Insert(OnChangePlayerFactionModel);
        FactionInfoCardView.Event_OnFactionInfoCardClickCallBack.Insert(OnFactionInfoCardExecute);
    }

    override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);

        moduleFaction = FactionSpawnModule.Cast(CF_ModuleCoreManager.Get(FactionSpawnModule));
        UpdateController();
	}

    void UpdateController()
    {
        if(moduleFaction.playerFactionModel.HasFaction())
            factionImage.LoadImageFile(0, GetFactionModule().GetFactionTeamFromName().imagePath);

        player_name = moduleFaction.playerFactionModel.name;
        faction_name = moduleFaction.playerFactionModel.factionName;
        NotifyPropertiesChanged({"player_name", "faction_name"});

        if(!moduleFaction.playerFactionModel.HasFaction()){
            selectFactionBtn.Show(true);
        }
        else{
            selectFactionBtn.Show(false);
        }

		FillComboBoxLocation();
        FillTeamInfoList();
    }

    void FillTeamInfoList()
    {
        array<ref FactionTeam> teams = moduleFaction.settings.factions;
        faction_item_labels.Clear();
        foreach(FactionTeam team: teams)
        {
            faction_item_labels.Insert(new FactionInfoCardView(team));
        }
    }

    void OnFactionInfoCardExecute(FactionInfoCardView factionInfoCard)
    {
        if(selectedInfoCard)
            selectedInfoCard.UnSelect();

        selectedInfoCard = factionInfoCard;
        selectedInfoCard.Select();
        brief_history = factionInfoCard.team.briefHistory;
        NotifyPropertyChanged("brief_history");
    }

    void OnChangePlayerFactionModel(PlayerFactionModel model)
	{
		UpdateController();
	}

    bool OnFactionSelectionPopUpExecute(ButtonCommandArgs args)
    {
        ShowSelectPopUp();
        return true;
    }

    void ShowSelectPopUp()
	{
		factionSelectView = new FactionSelectView();
		factionSelectView.Show(true);
	}

    bool OnLocationChangedExecute(ButtonCommandArgs args)
	{
        moduleFaction.playerFactionModel.locationNameSelected = observable_combobox_teleportation.Get(observable_combobox_teleportation_selection);
        return true;
    }

    void FillComboBoxLocation()
    {
        array<ref FactionLocation> locations = moduleFaction.GetFactionLocations();
        if(!locations)
            return;

        if(locations.Count() >= 1)
            moduleFaction.playerFactionModel.locationNameSelected = locations[0].name;
            
        observable_combobox_teleportation.Clear();
        foreach(FactionLocation location: locations)
        {
            observable_combobox_teleportation.Insert(location.name);
        }

        NotifyPropertyChanged("observable_combobox_teleportation");
    }

    void OnFactionTeamCardBtnExecute(FactionTeamCardView factionTeamCardView)
	{
		factionImage.LoadImageFile(0, factionTeamCardView.team.imagePath);
	}
}