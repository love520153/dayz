modded class PlayerBase
{
    protected vector m_LastDeathPosition;
    protected ref array<ref DeathPosition> m_DeathPositions;
    
    override void EEKilled(Object killer)
    {
        super.EEKilled(killer);
        
        // 记录死亡位置
        m_LastDeathPosition = GetPosition();
        
        // 保存死亡位置到文件
        SaveDeathPosition();
    }
    
    void SaveDeathPosition()
    {
        string steamId = GetIdentity().GetPlainId();
        string filePath = "$profile:playdead/" + steamId + "_deaths.json";
        
        if (!m_DeathPositions)
        {
            m_DeathPositions = new array<ref DeathPosition>;
        }
        
        // 如果文件存在，先读取现有数据
        if (FileExist(filePath))
        {
            JsonFileLoader<array<ref DeathPosition>>.JsonLoadFile(filePath, m_DeathPositions);
        }
        
        // 添加新的死亡位置
        m_DeathPositions.Insert(new DeathPosition(m_LastDeathPosition[0], m_LastDeathPosition[1], m_LastDeathPosition[2]));
        
        // 保存到文件
        JsonFileLoader<array<ref DeathPosition>>.JsonSaveFile(filePath, m_DeathPositions);
    }
    
    bool TeleportToDeathPosition(int index)
    {
        string steamId = GetIdentity().GetPlainId();
        ref PlayerConfig playerConfig = GetPlayerConfig(steamId);
        
        if (playerConfig && playerConfig.reviveTokens > 0 && m_DeathPositions && index < m_DeathPositions.Count())
        {
            DeathPosition deathPos = m_DeathPositions.Get(index);
            vector position = Vector(deathPos.x, deathPos.y, deathPos.z);
            SetPosition(position);
            playerConfig.reviveTokens--;
            SavePlayerConfig(playerConfig);
            Print("[DeathTeleportMod] Player teleported to death position: " + position.ToString());
            Print("[DeathTeleportMod] Remaining revive tokens: " + playerConfig.reviveTokens);
            return true;
        }
        else if (playerConfig && playerConfig.reviveTokens <= 0)
        {
            Print("[DeathTeleportMod] No revive tokens left.");
        }
        else
        {
            Print("[DeathTeleportMod] Invalid death position index or player config not found.");
        }
        return false;
    }

    array<ref DeathPosition> GetDeathPositions()
    {
        if (!m_DeathPositions)
        {
            string steamId = GetIdentity().GetPlainId();
            string filePath = "$profile:playdead/" + steamId + "_deaths.json";
            m_DeathPositions = new array<ref DeathPosition>;
            if (FileExist(filePath))
            {
                JsonFileLoader<array<ref DeathPosition>>.JsonLoadFile(filePath, m_DeathPositions);
            }
        }
        return m_DeathPositions;
    }
}

class DeathPosition
{
    float x;
    float y;
    float z;
    string timestamp;
    
    void DeathPosition(float x, float y, float z)
    {
        this.x = x;
        this.y = y;
        this.z = z;
        this.timestamp = GetGame().GetTime().ToString();
    }

    string GetFormattedPosition()
    {
        return "X: " + x.ToString() + ", Y: " + y.ToString() + ", Z: " + z.ToString();
    }
}

// ... (保留 PlayerConfig, GetPlayerConfig, 和 SavePlayerConfig 的现有代码)

modded class MissionGameplay
{
    protected ref DeathTeleportUI m_DeathTeleportUI;

    override void OnKeyPress(int key)
    {
        super.OnKeyPress(key);
        
        // 使用 'T' 键打开死亡传送 UI
        if (key == KeyCode.KC_T)
        {
            if (!m_DeathTeleportUI)
            {
                m_DeathTeleportUI = new DeathTeleportUI();
            }
            m_DeathTeleportUI.Toggle();
        }
    }
}

class DeathTeleportUI extends UIScriptedMenu
{
    protected Widget m_LayoutRoot;
    protected TextListboxWidget m_DeathPositionList;
    protected ButtonWidget m_TeleportButton;
    protected TextWidget m_TokensText;

    protected PlayerBase m_Player;
    protected ref array<ref DeathPosition> m_DeathPositions;

    void DeathTeleportUI()
    {
        m_Player = PlayerBase.Cast(GetGame().GetPlayer());
        m_DeathPositions = m_Player.GetDeathPositions();
    }

    override Widget Init()
    {
        layoutRoot = GetGame().GetWorkspace().CreateWidgets("DeathTeleportMod/Layouts/DeathTeleportUI.layout");
        m_DeathPositionList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("DeathPositionList"));
        m_TeleportButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("TeleportButton"));
        m_TokensText = TextWidget.Cast(layoutRoot.FindAnyWidget("TokensText"));

        UpdateList();
        UpdateTokens();

        return layoutRoot;
    }

    void Toggle()
    {
        if (layoutRoot.IsVisible())
        {
            Close();
        }
        else
        {
            Open();
        }
    }

    void Open()
    {
        UpdateList();
        UpdateTokens();
        layoutRoot.Show(true);
        GetGame().GetInput().ChangeGameFocus(1);
        GetGame().GetUIManager().ShowCursor(true);
    }

    void Close()
    {
        layoutRoot.Show(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowCursor(false);
    }

    void UpdateList()
    {
        m_DeathPositionList.ClearItems();
        for (int i = 0; i < m_DeathPositions.Count(); i++)
        {
            string entry = m_DeathPositions[i].timestamp + " - " + m_DeathPositions[i].GetFormattedPosition();
            m_DeathPositionList.AddItem(entry, NULL, 0);
        }
    }

    void UpdateTokens()
    {
        PlayerConfig config = GetPlayerConfig(m_Player.GetIdentity().GetPlainId());
        if (config)
        {
            m_TokensText.SetText("Revive Tokens: " + config.reviveTokens.ToString());
        }
    }

    bool OnClick(Widget w, int x, int y, int button)
    {
        if (w == m_TeleportButton)
        {
            int selectedRow = m_DeathPositionList.GetSelectedRow();
            if (selectedRow != -1)
            {
                if (m_Player.TeleportToDeathPosition(selectedRow))
                {
                    UpdateTokens();
                    Close();
                }
            }
        }
        return super.OnClick(w, x, y, button);
    }
}