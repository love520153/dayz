class PlayerConfig
{
    string steamId;
    int reviveTokens;

    void PlayerConfig(string id, int tokens = 3)
    {
        steamId = id;
        reviveTokens = tokens;
    }
}

PlayerConfig GetPlayerConfig(string steamId)
{
    string filePath = "$profile:DeathTeleportMod/" + steamId + "_config.json";
    PlayerConfig config = new PlayerConfig(steamId);
    
    if (FileExist(filePath))
    {
        JsonFileLoader<PlayerConfig>.JsonLoadFile(filePath, config);
    }
    
    return config;
}

void SavePlayerConfig(PlayerConfig config)
{
    string filePath = "$profile:DeathTeleportMod/" + config.steamId + "_config.json";
    JsonFileLoader<PlayerConfig>.JsonSaveFile(filePath, config);
}