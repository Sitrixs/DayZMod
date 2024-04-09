class FactionSpawnManagementLoggingSettings 
{
    int logLevel = 0;
    int refreshRateInSeconds = 60;

    void MakeDirectoryIfNotExists()
    {
        if(!FileExist( FactionSpawnManagement_ROOT_FOLDER))
            MakeDirectory( FactionSpawnManagement_ROOT_FOLDER);

        if(!FileExist( FactionSpawnManagement_LOG_FOLDER))
            MakeDirectory( FactionSpawnManagement_LOG_FOLDER);

        if(!FileExist( FactionSpawnManagement_LOGGER_CONFIG_DIR))
            MakeDirectory( FactionSpawnManagement_LOGGER_CONFIG_DIR);
        
        if(!FileExist( FactionSpawnManagement_LOGGER_LOG_DIR))
            MakeDirectory( FactionSpawnManagement_LOGGER_LOG_DIR);
    }

    void Save()
    {
        JsonFileLoader<FactionSpawnManagementLoggingSettings>.JsonSaveFile( FactionSpawnManagement_LOGGER_CONFIG_FILE, this);
    }

    static ref FactionSpawnManagementLoggingSettings Load()
    {
        FactionSpawnManagementLoggingSettings settings = new FactionSpawnManagementLoggingSettings();

        settings.MakeDirectoryIfNotExists();

        if(FileExist( FactionSpawnManagement_LOGGER_CONFIG_FILE))
        {
            JsonFileLoader<FactionSpawnManagementLoggingSettings>.JsonLoadFile( FactionSpawnManagement_LOGGER_CONFIG_FILE, settings);
            return settings;
        }

        settings.Save();
        return settings;
    }

}