class FactionItemCardView: ScriptViewTemplate<FactionItemCardViewController>
{
    ButtonWidget itemCardBtn;
    Widget itemBackground;
    ref FactionItem factionItem;
    static ref ScriptInvoker Event_OnItemCardClickCallBack = new ScriptInvoker();
    
    void FactionItemCardView(FactionItem item)
    {
        factionItem = item;
        m_TemplateController.Setup(item);
    }

    override string GetLayoutFile() 
	{
		return "FactionSpawnManagement/datasets/gui/FactionItemCard.layout";
	}

    bool OnItemBtnExecute(ButtonCommandArgs args)
	{
        Event_OnItemCardClickCallBack.Invoke(this);
		return true;
	}

    override bool OnMouseEnter(Widget w, int x, int y)
	{
        if(w && w.GetUserID() == 444 && w == itemCardBtn)
            itemBackground.Enable(true);

        return false;
	}

	
    override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
        if(w && w.GetUserID() == 444 && w == itemCardBtn)
            itemBackground.Enable(false);
        
        return false;
	}
}