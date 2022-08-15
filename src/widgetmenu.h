#include "PCH.h"

class WidgetMenu : RE::IMenu
{
public:
	static constexpr const char* MENU_PATH = "SeeOperatingStateWidget";
	static constexpr const char* MENU_NAME = "SeeOperatingStateWidget";

	WidgetMenu();

	static void Register();
	static void Show();
	static void Hide();

	static RE::stl::owner<RE::IMenu*> Creator() { return new WidgetMenu(); }

	void AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;
};
