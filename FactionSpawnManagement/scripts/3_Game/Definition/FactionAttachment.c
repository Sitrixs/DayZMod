class FactionAttachment
{
    string className;
    int quantity;

    void FactionAttachment(string className, int quantity = -1)
    {
        this.className = className;
        this.quantity = quantity;
    }
}