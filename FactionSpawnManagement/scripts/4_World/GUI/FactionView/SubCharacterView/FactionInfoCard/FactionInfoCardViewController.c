class FactionInfoCardViewController:ViewController
{
    ImageWidget factionImage;
    string faction_name;

    void Setup(string imagePath, string factionName)
    {
        factionImage.LoadImageFile(0, imagePath);
        faction_name = factionName;

        NotifyPropertyChanged("faction_name");
    }
}