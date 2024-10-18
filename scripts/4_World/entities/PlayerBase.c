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
        this.timestamp = GetFormattedTimestamp();
    }

    string GetFormattedPosition()
    {
        return string.Format("X: %.2f, Y: %.2f, Z: %.2f", x, y, z);
    }

    private string GetFormattedTimestamp()
    {
        int year, month, day, hour, minute, second;
        GetGame().GetWorld().GetDate(year, month, day, hour, minute, second);
        return string.Format("%1-%2-%3 %4:%5:%6", year, month.ToStringLen(2), day.ToStringLen(2), hour.ToStringLen(2), minute.ToStringLen(2), second.ToStringLen(2));
    }
}

// ... PlayerBase 类的其余部分保持不变 ...