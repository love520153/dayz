class DeathTeleportUI extends UIScriptedMenu
{
    // ... 保持其他代码不变 ...

    void UpdateList()
    {
        m_DeathPositionList.ClearItems();
        for (int i = 0; i < m_DeathPositions.Count(); i++)
        {
            DeathPosition deathPos = m_DeathPositions[i];
            string entry = string.Format("%1 - X: %.2f, Y: %.2f, Z: %.2f", deathPos.timestamp, deathPos.x, deathPos.y, deathPos.z);
            m_DeathPositionList.AddItem(entry, NULL, 0);
            Print("[DeathTeleportMod] 添加死亡位置到列表: " + entry);
        }
    }

    // ... 保持其他代码不变 ...
}