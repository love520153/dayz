modded class MissionServer
{
    override void OnInit()
    {
        super.OnInit();
        
        CreateDeathTeleportModFolder();
    }
    
    void CreateDeathTeleportModFolder()
    {
        string folderPath = "$profile:DeathTeleportMod";
        if (!FileExist(folderPath))
        {
            Print("[DeathTeleportMod] Creating mod folder: " + folderPath);
            MakeDirectory(folderPath);
        }
        else
        {
            Print("[DeathTeleportMod] Mod folder already exists: " + folderPath);
        }
    }
}