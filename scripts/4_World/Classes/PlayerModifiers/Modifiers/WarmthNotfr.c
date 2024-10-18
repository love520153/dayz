modded class WarmthNotfr: NotifierBase 
{
    const float TEMPERATURE_CHANGE_MULTIPLIER = 0.25; // 进一步减缓温度变化速度
    const float TENDENCY_THRESHOLD_MULTIPLIER = 2.0; // 增加趋势阈值，使显示更稳定

    void WarmthNotfr()
    {
        SlowTemperatureChangeModConfig.LogInfo("WarmthNotfr 类已初始化");
    }

    override void Update(float delta)
    {
        float original_delta = delta;
        delta *= TEMPERATURE_CHANGE_MULTIPLIER;
        SlowTemperatureChangeModConfig.LogInfo("更新: 原始 delta: " + original_delta + ", 修改后 delta: " + delta);
        super.Update(delta);
    }

    override float GetObservedValue()
    {
        float original_value = super.GetObservedValue();
        float modified_value = original_value * TEMPERATURE_CHANGE_MULTIPLIER;
        SlowTemperatureChangeModConfig.LogInfo("获取观察值: 原始值: " + original_value + ", 修改后值: " + modified_value);
        return modified_value;
    }

    override protected DSLevelsTemp DetermineLevel(float value, float m_warning_treshold, float m_critical_treshold, float m_empty_treshold, float p_warning_treshold, float p_critical_treshold, float p_empty_treshold)
    {
        // 调整阈值以适应减缓的温度变化
        m_warning_treshold *= TEMPERATURE_CHANGE_MULTIPLIER;
        m_critical_treshold *= TEMPERATURE_CHANGE_MULTIPLIER;
        m_empty_treshold *= TEMPERATURE_CHANGE_MULTIPLIER;
        p_warning_treshold *= TEMPERATURE_CHANGE_MULTIPLIER;
        p_critical_treshold *= TEMPERATURE_CHANGE_MULTIPLIER;
        p_empty_treshold *= TEMPERATURE_CHANGE_MULTIPLIER;

        DSLevelsTemp level = super.DetermineLevel(value, m_warning_treshold, m_critical_treshold, m_empty_treshold, p_warning_treshold, p_critical_treshold, p_empty_treshold);

        SlowTemperatureChangeModConfig.LogInfo("确定等级: 值: " + value + ", 等级: " + level);
        return level;
    }
    
    override void DisplayTendency(float delta)
    {
        float original_delta = delta;
        delta *= TEMPERATURE_CHANGE_MULTIPLIER;
        
        // 调整趋势阈值
        float adjusted_inc_low = INC_TRESHOLD_LOW * TENDENCY_THRESHOLD_MULTIPLIER;
        float adjusted_inc_med = INC_TRESHOLD_MED * TENDENCY_THRESHOLD_MULTIPLIER;
        float adjusted_inc_high = INC_TRESHOLD_HIGH * TENDENCY_THRESHOLD_MULTIPLIER;
        float adjusted_dec_low = DEC_TRESHOLD_LOW * TENDENCY_THRESHOLD_MULTIPLIER;
        float adjusted_dec_med = DEC_TRESHOLD_MED * TENDENCY_THRESHOLD_MULTIPLIER;
        float adjusted_dec_high = DEC_TRESHOLD_HIGH * TENDENCY_THRESHOLD_MULTIPLIER;

        int tendency = CalculateTendency(delta, adjusted_inc_low, adjusted_inc_med, adjusted_inc_high, adjusted_dec_low, adjusted_dec_med, adjusted_dec_high);
        
        DSLevelsTemp level = DetermineLevel(GetObservedValue(), PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_WARNING, PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_CRITICAL, PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_EMPTY, PlayerConstants.THRESHOLD_HEAT_COMFORT_PLUS_WARNING, PlayerConstants.THRESHOLD_HEAT_COMFORT_PLUS_CRITICAL, PlayerConstants.THRESHOLD_HEAT_COMFORT_PLUS_EMPTY);
        
        DisplayElementTendency dis_elm = DisplayElementTendency.Cast(GetVirtualHud().GetElement(eDisplayElements.DELM_TDCY_TEMPERATURE));
        
        if(dis_elm)
        {
            dis_elm.SetTendency(tendency);
            dis_elm.SetSeriousnessLevel(level);
        }

        SlowTemperatureChangeModConfig.LogInfo("显示趋势: 原始 delta: " + original_delta + ", 修改后 delta: " + delta + ", 趋势: " + tendency + ", 等级: " + level);
    }

    override protected int CalculateTendency(float delta, float inc_low, float inc_med, float inc_high, float dec_low, float dec_med, float dec_high)
    {
        int tendency = super.CalculateTendency(delta, inc_low * TENDENCY_THRESHOLD_MULTIPLIER, inc_med * TENDENCY_THRESHOLD_MULTIPLIER, inc_high * TENDENCY_THRESHOLD_MULTIPLIER, dec_low * TENDENCY_THRESHOLD_MULTIPLIER, dec_med * TENDENCY_THRESHOLD_MULTIPLIER, dec_high * TENDENCY_THRESHOLD_MULTIPLIER);
        SlowTemperatureChangeModConfig.LogInfo("计算趋势: Delta: " + delta + ", 趋势: " + tendency);
        return tendency;
    }
}