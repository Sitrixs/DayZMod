const string FactionSpawnManagement_ROOT_FOLDER = "$profile:FactionSpawnManagement\\";

const string FactionSpawnManagement_CONFIG_FOLDER = FactionSpawnManagement_ROOT_FOLDER + "Config\\";
const string FactionSpawnManagement_CONFIG_FILE = FactionSpawnManagement_CONFIG_FOLDER + "FactionSpawnManagementSettings.json";

const string FactionSpawnManagement_DB_FOLDER = FactionSpawnManagement_ROOT_FOLDER + "Database\\";
const string FactionSpawnManagement_DB_FILE = FactionSpawnManagement_DB_FOLDER + "playerFaction_%1.json";

const string FactionSpawnManagement_LOG_FOLDER = FactionSpawnManagement_ROOT_FOLDER + "Logging\\";
const string FactionSpawnManagement_LOGGER_CONFIG_DIR = FactionSpawnManagement_LOG_FOLDER + "Config\\";
const string FactionSpawnManagement_LOGGER_CONFIG_FILE = FactionSpawnManagement_LOGGER_CONFIG_DIR + "LoggingSettings.json";
const string FactionSpawnManagement_LOGGER_LOG_DIR = FactionSpawnManagement_LOG_FOLDER + "Logs\\";
const string FactionSpawnManagement_LOGGER_LOG_FILE = FactionSpawnManagement_LOGGER_LOG_DIR + "FactionSpawnManagement_%1.log";

const string FactionSpawnManagement_VERSION = "1.0.0";

enum EFACTION_UI_LIST
{
    INVENTORY = 0,
    LOADOUT
}
