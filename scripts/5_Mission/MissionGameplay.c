modded class MissionGameplay
{
    protected ref DeathTeleportUI m_DeathTeleportUI;

    override void OnKeyPress(int key)
    {
        super.OnKeyPress(key);
        
        if (key == KeyCode.KC_T)
        {
            if (!m_DeathTeleportUI)
            {
                m_DeathTeleportUI = new DeathTeleportUI();
                m_DeathTeleportUI.Init();
            }
            m_DeathTeleportUI.ToggleVisibility();
        }
    }
}