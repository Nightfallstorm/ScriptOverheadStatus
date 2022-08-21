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
	static void SetMainText(std::string newText);
	static void SetWarningText(std::string newText);



	static RE::stl::owner<RE::IMenu*> Creator() { return new WidgetMenu(); }

	void AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;

private:
	class Logger : public RE::GFxLog
	{
	public:
		void LogMessageVarg(LogMessageType, const char* a_fmt, std::va_list a_argList) override
		{
			std::string fmt(a_fmt ? a_fmt : "");
			while (!fmt.empty() && fmt.back() == '\n') {
				fmt.pop_back();
			}

			std::va_list args;
			va_copy(args, a_argList);
			std::vector<char> buf(static_cast<std::size_t>(std::vsnprintf(0, 0, fmt.c_str(), a_argList) + 1));
			std::vsnprintf(buf.data(), buf.size(), fmt.c_str(), args);
			va_end(args);

			logger::info("{}"sv, buf.data());
		}
	};
};
