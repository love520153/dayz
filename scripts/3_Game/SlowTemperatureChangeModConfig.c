class SlowTemperatureChangeModConfig
{
    static const string MOD_PREFIX = "[缓慢温度变化模组]";

    static void LogInfo(string message)
    {
        Print(MOD_PREFIX + " INFO: " + message);
    }

    static void LogError(string message)
    {
        Error(MOD_PREFIX + " ERROR: " + message);
    }
}