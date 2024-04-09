class FactionItem
{
    string className;
    int pointRequired;
    int quantity;
    string slotName;
    ref array<ref FactionAttachment> attachments;

    void FactionItem(string className,int pointRequired, int quantity = -1, string slotName = string.Empty)
    {
        this.className = className;
        this.pointRequired = pointRequired;
        this.quantity = quantity;
        this.slotName = slotName;
        this.attachments = new array<ref FactionAttachment>();
    }
}