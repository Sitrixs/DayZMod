class FactionViewController:ViewController
{
	ref FactionSpawnModule moduleFaction;
	string point_left;
	string point_used;
    ref ObservableCollection<ref FactionItemCardView> inventory_item_list = new ObservableCollection<ref FactionItemCardView>(this);
    ref ObservableCollection<ref FactionItemCardView> loadout_item_list = new ObservableCollection<ref FactionItemCardView>(this);
 
	void FactionViewController()
	{
		FactionItemCardView.Event_OnItemCardClickCallBack.Insert(OnItemCardClick);
		PlayerFactionModel.Event_OnChangePlayerFactionModelCallBack.Insert(OnChangePlayerFactionModel);
	}
	
	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);

        moduleFaction = FactionSpawnModule.Cast(CF_ModuleCoreManager.Get(FactionSpawnModule));
		UpdateMenu();
	}

	void UpdateMenu()
	{
		FillInventoryItemList();
		FillLoadoutItemList();
		UpdatePoints();
	}

	void MoveSelectedItemCard(FactionItemCardView selectedItemCardView)
	{
		int pointUsed, pointLeft;
		GetPoints(pointUsed, pointLeft);
		
		int id = inventory_item_list.Find(selectedItemCardView);
		if(id != -1)
		{
			loadout_item_list.Insert(selectedItemCardView);
			inventory_item_list.Remove(id);
			return;
		}

		id = loadout_item_list.Find(selectedItemCardView);
		if(id != -1)
		{
			if(pointLeft < selectedItemCardView.factionItem.pointRequired)
				return;

			inventory_item_list.Insert(selectedItemCardView);
            loadout_item_list.Remove(id);
		}
	}

	int GetTotalInventoryPoint()
	{
		int totalPoint = 0;
		if(inventory_item_list.GetArray().Count() == 0)
			return totalPoint;

		foreach(FactionItemCardView itemCard : inventory_item_list.GetArray())
		{
			if(!itemCard)
				continue;

			totalPoint += itemCard.factionItem.pointRequired;
		}

		return totalPoint;
	}

	void FillLoadoutItemList()
    {
        array<ref FactionItem> items = moduleFaction.GetFactionLoadout();
		if(!items)
			return;

        foreach(FactionItem item : items)
        {
            loadout_item_list.Insert(new FactionItemCardView(item));
        }
    }

    void FillInventoryItemList()
    {
        array<ref FactionItem> items = moduleFaction.playerFactionModel.itemsPreset;
        foreach(FactionItem item : items)
        {
            inventory_item_list.Insert(new FactionItemCardView(item));
        }
    }

	array<ref FactionItem> GetItemsPresetFromInventoryList()
	{
		array<ref FactionItem> items = new array<ref FactionItem>();
		foreach(FactionItemCardView itemCard : inventory_item_list.GetArray())
		{
			if(!itemCard)
				continue;

			items.Insert(itemCard.factionItem);
		}

		return items;
	}

	bool StartExecute(ButtonCommandArgs args)
	{
		if(!moduleFaction.playerFactionModel.HasFaction()){
			return false;
        }

		moduleFaction.playerFactionModel.SetItemsPreset(GetItemsPresetFromInventoryList());
		GetRPCManager().SendRPC("FactionSpawnSystem", "GetFactionSpawnRequest", new Param1<PlayerFactionModel>(moduleFaction.playerFactionModel), true, null);
		GetFactionModule().CloseFactionMenu();
		return true;
	}

	void GetPoints(out int pointUsed, out int pointLeft)
	{
		pointUsed = GetTotalInventoryPoint();
		pointLeft = moduleFaction.playerFactionModel.totalPoint - pointUsed;
	}

	void UpdatePoints()
	{
		int pointUsed, pointLeft;
		GetPoints(pointUsed, pointLeft);
		point_left = pointLeft.ToString();
		point_used = pointUsed.ToString();
		NotifyPropertiesChanged({"point_left", "point_used"});
	}

	void OnChangePlayerFactionModel(PlayerFactionModel model)
	{
		UpdateMenu();
	}

	void OnItemCardClick(FactionItemCardView itemCardView)
	{
		MoveSelectedItemCard(itemCardView);
		UpdatePoints();
	}
}