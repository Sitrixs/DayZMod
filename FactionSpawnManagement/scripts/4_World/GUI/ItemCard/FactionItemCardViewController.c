class FactionItemCardViewController:ViewController
{
    string item_name;
    string item_point;
    EntityAI preview;

    void Setup(FactionItem item)
    {
        item_name = FactionSpawnModuleHelper.GetDisplayName(item.className);
        item_point = item.pointRequired.ToString();

        EntityAI obj_preview;
        FactionSpawnModuleHelper.CreatePreviewObject(item, obj_preview)

        if(obj_preview)
            preview = obj_preview;

        NotifyPropertiesChanged({"item_name", "item_point", "preview"});
    }

    void ~FactionItemCardViewController()
    {
        if(preview)
            GetGame().ObjectDelete(preview);
    }
}