////////////////////////////////////////////////////////////////////
//DeRap: config.bin
//Produced from mikero's Dos Tools Dll version 9.10
//https://mikero.bytex.digital/Downloads
//'now' is Wed Mar 20 23:29:46 2024 : 'file' last modified on Tue Mar 19 15:09:22 2024
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class FactionSpawnManagement_Script
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {};
	};
};
class CfgMods
{
	class FactionSpawnManagement
	{
		dir = "FactionSpawnManagement";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "FactionSpawnManagement";
		credits = "TheDmitri";
		author = "TheDmitri";
		authorID = "0";
		version = "1.1";
		extra = 0;
		type = "mod";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"FactionSpawnManagement/scripts/Common","FactionSpawnManagement/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"FactionSpawnManagement/scripts/Common","FactionSpawnManagement/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"FactionSpawnManagement/scripts/Common","FactionSpawnManagement/scripts/5_Mission"};
			};
		};
	};
};
class CfgVehicles{};
