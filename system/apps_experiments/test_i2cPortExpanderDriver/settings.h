
class CMCP23017Settings : public CWindow
{
private:
    int mRow; // Where the cursor is
    TSetting *mSettings;
    int mSettingsCount;

public:
    CMCP23017Settings(){};

    void Init(TSetting *appSettings, int settingsCount)
    {
        mSettings = appSettings;
        mRow = 0;
        mSettingsCount = settingsCount;
    }

    virtual void OnPaint() override
    {
        CWindow::OnPaint();
        DrawSettings();
        // TODO: draw the settings
    }

    void DrawSettingItem(int id)
    {
        int y = 16 + 16 + id * 16;

        unsigned short color;

        if (id == mRow)
        {
            color = RGB565(ffffff);
        }
        else
        {
            color = RGB565(808080);
        }

        if (mSettings[id].format == TSetting::hex)
            LCD::Printf(20, y, color, gBackground, "%s: 0x%02x", mSettings[id].name, mSettings[id].value);
        else
            LCD::Printf(20, y, color, gBackground, "%s: %d", mSettings[id].name, mSettings[id].value);

        // BIOS::LCD::Printf(20, y, RGB565(ffffff), gBackground, "%s:%d", mSettings[id].name, mSettings[id].value);
    }

    void DrawApplyButton()
    {
        int y = 16 + 16 + mSettingsCount * 16 + 16;

        unsigned short color;

        if (mRow == mSettingsCount)
        {
            color = RGB565(ffffff);
        }
        else
        {
            color = RGB565(808080);
        }

        LCD::Printf(20, y, color, gBackground, "Apply");
    }

    void DrawSettings()
    {
        for (int i = 0; i < mSettingsCount; i++)
            DrawSettingItem(i);

        DrawApplyButton();

        BIOS::LCD::Printf(20, 200, RGB565(ffffff), gBackground, "Row:%d Val:%x", mRow, mSettings[mRow].value);
    }

    virtual void OnKey(int nKey) override
    {
        if (nKey == BIOS::KEY::Left && mSettings[mRow].value > mSettings[mRow].min)
        {
            mSettings[mRow].value--;
            DrawSettingItem(mRow);
            return;
        }
        if (nKey == BIOS::KEY::Right && mSettings[mRow].value < mSettings[mRow].max)
        {
            mSettings[mRow].value++;
            DrawSettingItem(mRow);
            return;
        }
        if (nKey == BIOS::KEY::Up && mRow > 0)
        {
            mRow--;
            DrawSettings();
            return;
        }
        if (nKey == BIOS::KEY::Down && mRow < mSettingsCount) // Not - 1 because of Apply button
        {
            mRow++;
            DrawSettings();
            return;
        }

        if (nKey == BIOS::KEY::Enter)
        {
            if (mRow == mSettingsCount)
            {
                // Apply
                BIOS::SYS::Beep(100);
            }
        }

        CWnd::OnKey(nKey);
    }

    virtual void OnTimer() override
    {
    }

    virtual void WindowMessage(int nMsg, int nParam) override
    {
        if (nMsg == CWnd::WmWillShow)
        {
        }

        if (nMsg == CWnd::WmWillHide)
        {
        }

        CWnd::WindowMessage(nMsg, nParam);
    }
};