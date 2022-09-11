class CMCP23017Settings : public CWindow
{
private:
    int mRow; // Where the cursor is
    int mCol; // Where the cursor is
    const TSetting *mSettings;

public:
    CMCP23017Settings(){};

    void Init(const TSetting *appSettings)
    {
        mSettings = appSettings;
        mRow = 0;
        mCol = 0;
    }

    void _itoa(int n, char *p, int base)
    {
        if (base == 10)
            sprintf(p, "%d", n);
        else if (base == 16)
            sprintf(p, "%x", n);
        else
            _ASSERT(0);
    }

    virtual void OnPaint() override
    {
        CWindow::OnPaint();
        DrawSettings();
        // TODO: draw the settings
    }

    void DrawSettingItem(int id)
    {
        char scrollBuff[2];
        _itoa(mSettings[id].value, scrollBuff, 16);
        BIOS::LCD::Print(20, 40, RGB565(ffffff), gBackground, scrollBuff);
    }

    void DrawSettings()
    {
        for (int i = 0; i < 1; i++)
            DrawSettingItem(i);

    }

    virtual void OnKey(int nKey) override
    {
        if (nKey == BIOS::KEY::Left && mCol > 0)
        {
            mCol--;
            DrawSettings();
            return;
        }
        if (nKey == BIOS::KEY::Right && mCol < 10)
        {
            // mSettings[0].value++;
            // BIOS::DBG::Print("Value: %d", mSettings[0].value);
            mCol++;
            DrawSettings();
            return;
        }
        if (nKey == BIOS::KEY::Up && mRow > 0)
        {
            mRow--;
            return;
        }
        // if (nKey == BIOS::KEY::Down && mRow < COUNT(mSettings))
        if (nKey == BIOS::KEY::Down && mRow < 1)
        {
            mRow++;
            return;
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