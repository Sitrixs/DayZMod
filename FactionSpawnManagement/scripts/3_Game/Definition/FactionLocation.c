class FactionLocation
{
    string name;
    vector position;
    int spawnRadius;

    void FactionLocation(string name, vector position, int spawnRadius)
    {
        this.name = name;
        this.position = position;
        this.spawnRadius = spawnRadius;
    }
}