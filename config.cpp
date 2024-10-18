class CfgPatches
{
    class SlowTemperatureChangeMod
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DZ_Scripts"};
    };
};

class CfgMods
{
    class SlowTemperatureChangeMod
    {
        dir = "SlowTemperatureChangeMod";
        picture = "";
        action = "";
        hideName = 1;
        hidePicture = 1;
        name = "Slow Temperature Change Mod";
        credits = "Your Name";
        author = "Your Name";
        authorID = "0";
        version = "1.0";
        extra = 0;
        type = "mod";
        
        dependencies[] = {"Game", "World", "Mission"};
        
        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"SlowTemperatureChangeMod/scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"SlowTemperatureChangeMod/scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"SlowTemperatureChangeMod/scripts/5_Mission"};
            };
        };
    };
};