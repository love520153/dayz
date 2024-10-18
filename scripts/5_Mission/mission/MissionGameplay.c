modded class MissionGameplay
{
    override void OnMissionStart()
    {
        super.OnMissionStart();
        SlowTemperatureChangeModConfig.LogInfo("任务开始，模组已加载");
    }
}