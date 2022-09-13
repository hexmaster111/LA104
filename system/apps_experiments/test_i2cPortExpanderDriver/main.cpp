#include <library.h>
#include "shapes.h"
#include "shapes2.h"
#include "Menu.h"
#include "appSettings.h"

// Test includes
#include "arduino.h"

using namespace BIOS;

class CMenuMain : public CTopMenu
{
public:
	virtual TItem GetItem(int i)
	{
		switch (i)
		{
		case 0:
			return TItem{"MCP23017", TItem::Static};
		case 1:
			return TItem{"PA", TItem::Default};
		case 2:
			return TItem{"PB", TItem::Default};
		case 3:
			return TItem{"Cfg", TItem::Default};
		default:
			return TItem{nullptr, TItem::None};
		}
	}
};

constexpr uint16_t gBackground(RGB565(404040));
constexpr uint16_t gControl(RGB565(909090));

class CWindow : public CWnd
{
public:
	void Window(const CRect &rcRect, uint16_t clr)
	{
		CRect rcClient = rcRect;
		BIOS::LCD::RoundRect(rcClient, RGB565(000000));
		rcClient.Deflate(2, 2, 2, 2);
		BIOS::LCD::RoundRect(rcClient, clr);
		rcClient.Deflate(2, 14, 2, 2);
		BIOS::LCD::RoundRect(rcClient, gBackground);
	}

	virtual void OnPaint() override
	{
		Window(m_rcClient, RGB565(d0d0d0));
		BIOS::LCD::Print((m_rcClient.right + m_rcClient.left - (int)strlen(m_pszId) * 8) / 2, m_rcClient.top + 2,
						 RGB565(000000), RGBTRANS, m_pszId);
	}
};

#include "PortView.h"
#include "settings.h"

class CApplication : public CWnd
{
	CMenuMain mMenu;

	CPortView mPortA;			 // Port viwer screen
	CPortView mPortB;			 // Port viwer screen
	CMCP23017Settings mSettings; // Settings Screen

public:
	TSetting mSessionSettings[2] = {
		{"Addr", 0x20, 0x20, 0x40, TSetting::TFormat::hex}, // I2C Target address
		{"test", 15, 0, 100, TSetting::TFormat::dec},	 // Just A test value
	};

	void Create()
	{

		Arduino::Wire.begin();

		mSettings.Init(mSessionSettings, 2);
		mPortA.Init();
		mPortB.Init();

		CWnd::Create("A", CWnd::WsVisible, CRect(0, 0, BIOS::LCD::Width, BIOS::LCD::Height), nullptr);
		mMenu.Create("M", CWnd::WsVisible, CRect(0, 0, BIOS::LCD::Width, 14), this);

		constexpr int padding = 0;
		mPortA.Create("PA", CWnd::WsHidden, CRect(padding, 14 + padding, BIOS::LCD::Width - padding, BIOS::LCD::Height - padding), this);
		mPortB.Create("PB", CWnd::WsHidden, CRect(padding, 14 + padding, BIOS::LCD::Width - padding, BIOS::LCD::Height - padding), this);
		mSettings.Create("CFG", CWnd::WsHidden, CRect(padding, 14 + padding, BIOS::LCD::Width - padding, BIOS::LCD::Height - padding), this);

		mPortA.ShowWindow(true);
		mPortA.SetFocus();
	}

	void Destroy()
	{
		// TODO: Cleanup the I2C Stuffs
	}
	virtual void OnMessage(CWnd *pSender, int code, uintptr_t data) override
	{
		if (code == ToWord('M', 'S'))
		{
			if (pSender == &mMenu && data == 1 && !mPortA.IsVisible())
			{
				mPortA.ShowWindow(true);
				mPortB.ShowWindow(false);
				mSettings.ShowWindow(false);

				Invalidate();
			}
			if (pSender == &mMenu && data == 2 && !mPortB.IsVisible())
			{
				mPortA.ShowWindow(false);
				mPortB.ShowWindow(true);
				mSettings.ShowWindow(false);

				Invalidate();
			}
			if (pSender == &mMenu && data == 3 && !mSettings.IsVisible())
			{
				mPortA.ShowWindow(false);
				mPortB.ShowWindow(false);
				mSettings.ShowWindow(true);

				Invalidate();
			}
		}
	}

private:
	virtual void OnPaint() override
	{
		GUI::Background(m_rcClient, RGB565(404040), RGB565(101010));
	}
};

CApplication app;

#ifdef _ARM
__attribute__((__section__(".entry")))
#endif
int
_main(void)
{
	app.Create();

	app.WindowMessage(CWnd::WmPaint);

	BIOS::KEY::EKey key;
	while ((key = BIOS::KEY::GetKey()) != BIOS::KEY::Escape)
	{
		if (key != BIOS::KEY::None)
			app.WindowMessage(CWnd::WmKey, key);
		app.WindowMessage(CWnd::WmTick);
	}

	app.Destroy();
	return 0;
}

void _HandleAssertion(const char *file, int line, const char *cond)
{
	BIOS::DBG::Print("Assertion failed in ");
	BIOS::DBG::Print(file);
	BIOS::DBG::Print(") [%d]: %s\n", line, cond);
#ifdef __APPLE__
	// kill(getpid(), SIGSTOP);
#endif
	while (1)
		;
}
