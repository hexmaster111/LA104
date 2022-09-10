class CMCP23017Settings : public CWindow
{
private:
    int mRow; // Where the cursor is
    int mCol; // Where the cursor is

public:
    CMCP23017Settings(){};

    void Init()
    {
        mRow = 0;
        mCol = 0;
    }

    virtual void OnPaint() override
    {
        CWindow::OnPaint();

        // TODO: draw the settings
    }

    virtual void OnKey(int nKey) override
    {
        if (nKey == BIOS::KEY::Left && mCol > 0)
        {
            mCol--;
            return;
        }
        if (nKey == BIOS::KEY::Right && mCol < 2)
        {
            // mSettings[0].value++;
            // BIOS::DBG::Print("Value: %d", mSettings[0].value);
            mCol++;
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