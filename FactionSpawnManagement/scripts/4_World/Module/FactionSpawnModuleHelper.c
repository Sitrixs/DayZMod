//this class contains all usefull methods that can be required for a project purpose.
class FactionSpawnModuleHelper {
    static void CreatePreviewObject(FactionItem item, inout EntityAI preview)
	{
		preview = EntityAI.Cast(GetGame().CreateObjectEx(item.className, vector.Zero, ECE_LOCAL|ECE_NOLIFETIME));
        if(!preview)
            return;

        if(item.attachments.Count() <= 0)
            return;
        
        foreach(FactionAttachment attachment: item.attachments)
        {
            Weapon_Base wpn = Weapon_Base.Cast(preview);
            EntityAI attach = EntityAI.Cast(GetGame().CreateObjectEx(attachment.className , vector.Zero, ECE_LOCAL|ECE_NOLIFETIME));

            EntityAI entAttachment;

            if(wpn && attach && attach.IsInherited(Magazine) && !attach.IsInherited(Ammunition_Base))
            {
                entAttachment = wpn.SpawnAttachedMagazine(attachment.className);
            }
            else
            {
                entAttachment = preview.GetInventory().CreateAttachment(attachment.className);
            }

            if(!entAttachment){
                entAttachment = preview.GetInventory().CreateInInventory(attachment.className);
            }

            GetGame().ObjectDelete(attach);
        }
	}

    static vector GetRandomPosition(vector position, float radius)
    {
        array<Object> excludedObjects = new array<Object>();
        array<Object> nearbyObjects = new array<Object>();

        int maxLoopCount = 20;
        for (int count = 0; count < maxLoopCount; count++)
        {
            string w_Surface = "";

            float angle = Math.RandomFloatInclusive(0.01, 6.28);

            int RandomX = position[0] + Math.RandomFloatInclusive(1, radius) * Math.Cos(angle);
            int RandomZ = position[2] + Math.RandomFloatInclusive(1, radius) * Math.Sin(angle);
            vector randomPosition = Vector(RandomX, GetGame().SurfaceY(position[0], position[2]), RandomZ);

            float surfaceY = GetGame().SurfaceY(randomPosition[0], randomPosition[2]);
            GetGame().SurfaceGetType3D(randomPosition[0], surfaceY, randomPosition[2], w_Surface);

            if (!GetGame().IsBoxColliding(Vector(randomPosition[0], surfaceY, randomPosition[2]), "0 0 0", "3 5 3", excludedObjects, nearbyObjects) && w_Surface != "FreshWater" && w_Surface != "sea" && !GetGame().SurfaceIsSea(randomPosition[0], randomPosition[2]))
            {
                return randomPosition;
            }
        }

        return position;
    }

    static void RemovePlayerClothes(PlayerBase player)
    {
        array<EntityAI> itemsArray = new array<EntityAI>();
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
        for (int i = itemsArray.Count() - 1; i >= 0; i--)
        {
            if(!itemsArray[i].IsInherited(PlayerBase))
                GetGame().ObjectDelete(itemsArray[i]);
        }
    }

    static void EquipPlayer(PlayerBase player, array<ref FactionItem> items)
    {
        RemovePlayerClothes(player);
        foreach(FactionItem item: items)
        {
            EntityAI entityToSpawn;
            if(item.slotName == "Hand")
            {
                entityToSpawn = player.GetHumanInventory().CreateInHands(item.className);
            }
            else if(item.slotName != string.Empty)
            {
                int slotId = InventorySlots.GetSlotIdFromString(item.slotName);
                entityToSpawn = player.GetInventory().CreateAttachmentEx(item.className, slotId);
            }
            else
            {
                entityToSpawn = player.GetHumanInventory().CreateInInventory(item.className);
            }

            if(!entityToSpawn)
                continue;

            if(item.quantity != -1)
                entityToSpawn = SetQuantity(entityToSpawn, item.quantity);

            if(item.attachments.Count() > 0)
                entityToSpawn = CreateAttachments(entityToSpawn, item.attachments)
        }
    }

    static EntityAI CreateAttachments(EntityAI entity, array<ref FactionAttachment> attachments)
    {
        foreach(FactionAttachment attachment: attachments)
        {
            Weapon_Base wpn = Weapon_Base.Cast(entity);
            EntityAI attach = EntityAI.Cast(GetGame().CreateObject(attachment.className , "0 0 0"));

            EntityAI entAttachment;

            if(wpn && attach && attach.IsInherited(Magazine) && !attach.IsInherited(Ammunition_Base))
            {
                entAttachment = wpn.SpawnAttachedMagazine(attachment.className);
            }
            else
            {
                entAttachment = entity.GetInventory().CreateAttachment(attachment.className);
            }

            if(!entAttachment){
                entAttachment = entity.GetInventory().CreateInInventory(attachment.className);
            }

            GetGame().ObjectDelete(attach);
                
            if(!entAttachment || attachment.quantity == -1)
                continue;

            SetQuantity(ItemBase.Cast(entAttachment), attachment.quantity);
        }

        return entity;
    }

    static ItemBase SetQuantity(ItemBase item, int quantity)
	{
		Magazine mag = Magazine.Cast(item);
		if (mag)
			mag.ServerSetAmmoCount(quantity);
		else
			item.SetQuantity(quantity);

		return item;
	}

    static string TrimUnt(string input)
    {
        input.Replace("$UNT$", "");
        return input;
    }

    static string GetDisplayName(string className)
    {
        string displayName = className;

        if (GetGame().ConfigGetText(CFG_VEHICLESPATH + " " + className + " displayName", displayName))
        {
            displayName = TrimUnt(displayName);
        }

        if (GetGame().ConfigGetText(CFG_WEAPONSPATH + " " + className + " displayName", displayName))
        {
        displayName = TrimUnt(displayName);
        }

        if (GetGame().ConfigGetText(CFG_MAGAZINESPATH + " " + className + " displayName", displayName))
        {
        displayName = TrimUnt(displayName);
        }

        return displayName;
    }

    static vector SnapToGround(vector pos)
    {
        float pos_x = pos[0];
        float pos_z = pos[2];
        float pos_y = GetGame().SurfaceY( pos_x, pos_z );
        return Vector( pos_x, pos_y, pos_z );
    }
}