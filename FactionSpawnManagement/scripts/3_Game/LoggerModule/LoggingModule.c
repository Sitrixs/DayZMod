
static ref FactionSpawnManagementLoggingModule GetFactionSpawnManagementLogger()
{
    return FactionSpawnManagementLoggingModule.Cast(CF_ModuleCoreManager.Get(FactionSpawnManagementLoggingModule));
}

[CF_RegisterModule(FactionSpawnManagementLoggingModule)]
class FactionSpawnManagementLoggingModule : CF_ModuleGame
{
    private int networkSync_LogLevel;

    ref FactionSpawnManagementLoggingSettings settings;

    FileHandle fileHandle;

    float dtime = 0;


    override void OnInit()
    {
        super.OnInit();
        
        EnableUpdate();
        EnableMissionStart();
    }

    override void OnMissionStart(Class sender, CF_EventArgs args)
    {
        super.OnMissionStart(sender, args);

        fileHandle = CreateNewLogFile();

        if(GetGame().IsServer())
        {
            settings = FactionSpawnManagementLoggingSettings.Load();

            networkSync_LogLevel = settings.logLevel;
            SynchLogLevel();       
        }
        else
        {
            AddLegacyRPC("GetLogLevelResponse", SingleplayerExecutionType.Client);
        }
    }

    void GetLogLevelResponse(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		 if (type != CallType.Client)
			 return;

		 Param1<int> data;
		 if (!ctx.Read(data))
            return;

		 networkSync_LogLevel = data.param1;
	}

    void SynchLogLevel()
    {
        GetRPCManager().SendRPC(ClassName(), "GetLogLevelResponse",  new Param1<int>(networkSync_LogLevel), true, NULL);
    }

    override void OnUpdate(Class sender, CF_EventArgs args)
    {
        auto update = CF_EventUpdateArgs.Cast(args);

        if(!GetGame().IsServer())
            return;

        if(!settings)
            return;

        dtime += update.DeltaTime;
        if(dtime >= settings.refreshRateInSeconds)
        {
            dtime = 0;

            settings = FactionSpawnManagementLoggingSettings.Load();

            networkSync_LogLevel = settings.logLevel;
            SynchLogLevel();
        }
    }


    void MakeDirectoryIfNotExists()
    {
        if(!FileExist(FactionSpawnManagement_ROOT_FOLDER))
            MakeDirectory(FactionSpawnManagement_ROOT_FOLDER);

        if(!FileExist(FactionSpawnManagement_LOG_FOLDER))
            MakeDirectory(FactionSpawnManagement_LOG_FOLDER);

        if(!FileExist(FactionSpawnManagement_LOGGER_CONFIG_DIR))
            MakeDirectory(FactionSpawnManagement_LOGGER_CONFIG_DIR);
        
        if(!FileExist(FactionSpawnManagement_LOGGER_LOG_DIR))
            MakeDirectory(FactionSpawnManagement_LOGGER_LOG_DIR);
    }
    
    string GenerateShortDateString()
    {
        int year, month, day;
        GetYearMonthDay(year, month, day);
        return "" + year + "_" + month + "_" + day;
    }

    string GenerateShortTimeString()
    {
        int hour, minute, second;
        GetHourMinuteSecond(hour, minute, second);
        return "" + hour + "_" + minute + "_" + second;
    }

    string GenerateFullTimestamp()
    {
        string dateStr = GenerateShortDateString();
        string timeStr = GenerateShortTimeString();

        return dateStr + "-" + timeStr;
    }

    FileHandle CreateNewLogFile()
    {
        MakeDirectoryIfNotExists();

        string filePath = string.Format(FactionSpawnManagement_LOGGER_LOG_FILE, GenerateFullTimestamp());

        fileHandle = OpenFile(filePath, FileMode.WRITE);

        if(fileHandle != 0)
        {
            FPrintln(fileHandle, "Creation Time: " + GenerateFullTimestamp());
            return fileHandle;
        }

        return null;
    }

    void Log(string content, FactionSpawnManagementLogLevel logLevel)
    {
        if(logLevel < networkSync_LogLevel)
            return;
        
        string timestamp = GenerateShortTimeString();
        FPrintln(fileHandle, timestamp + " | " + GetLogLevelString(logLevel) + " | " + content);
    }

    void LogInfo(string content)
    {
        Log(content, FactionSpawnManagementLogLevel.Info);
    }

    void LogWarning(string content)
    {
        Log(content, FactionSpawnManagementLogLevel.Warn);
    }

    void LogError(string content)
    {
        Log(content, FactionSpawnManagementLogLevel.Error);
    }

    void LogDebug(string content)
    {
        Log(content, FactionSpawnManagementLogLevel.Debug);
    }

    string GetLogLevelString(FactionSpawnManagementLogLevel logLevel)
    {
        switch(logLevel)
        {
             case FactionSpawnManagementLogLevel.Debug:
                return "DEBUG";
            case FactionSpawnManagementLogLevel.Info:
                return "INFO";
            case FactionSpawnManagementLogLevel.Warn:
                return "WARNING";
            case FactionSpawnManagementLogLevel.Error:
                return "ERROR";
            default:
                return "";
        }

        return "";
    }

}