////////////////////////////////////////////////////////////////////
//DeRap: config.bin
//Produced from mikero's Dos Tools Dll version 9.10
//https://mikero.bytex.digital/Downloads
//'now' is Wed Mar 20 23:28:58 2024 : 'file' last modified on Tue Mar 19 15:09:35 2024
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgMods
{
	class DmitriAssets
	{
		dir = "DmitriAssets";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "DmitriAssets";
		author = "Malinin";
		version = "Version 1.0";
		extra = 0;
		type = "mod";
		class defs
		{
			class widgetStyles
			{
				files[] = {"DmitriAssets/gui/Styles.styles"};
			};
			class imageSets
			{
				files[] = {"DmitriAssets/gui/Data/first.imageset"};
			};
		};
	};
};
class CfgPatches
{
	class DmitriAssets
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"RPC_Scripts"};
	};
};
