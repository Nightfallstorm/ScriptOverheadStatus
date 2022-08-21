#pragma once
#include "widgetmenu.h"

WidgetMenu::WidgetMenu()
{
	auto scaleformManager = RE::BSScaleformManager::GetSingleton();
	inputContext = Context::kNone;
	depthPriority = 0;

	//menuFlags.set(RE::UI_MENU_FLAGS::kDontHideCursorWhenTopmost);
	//menuFlags.set(RE::UI_MENU_FLAGS::kAlwaysOpen);
	//menuFlags.set(RE::UI_MENU_FLAGS::kRequiresUpdate);
	//menuFlags.set(RE::UI_MENU_FLAGS::kAllowSaving);
	//menuFlags.set(RE::UI_MENU_FLAGS::kAdvancesUnderPauseMenu);

	scaleformManager->LoadMovieEx(this, MENU_PATH, [](RE::GFxMovieDef* a_def) -> void {
		a_def->SetState(RE::GFxState::StateType::kLog,
			RE::make_gptr<Logger>().get());
	});
}

void WidgetMenu::Register()
{
	auto ui = RE::UI::GetSingleton();
	if (ui) {
		ui->Register(MENU_NAME, Creator);
		WidgetMenu::Show();
	}
}

void WidgetMenu::Show()
{
	auto msgQ = RE::UIMessageQueue::GetSingleton();
	if (msgQ) {
		msgQ->AddMessage(WidgetMenu::MENU_NAME, RE::UI_MESSAGE_TYPE::kShow, nullptr);
	}
}

void WidgetMenu::Hide()
{
	auto msgQ = RE::UIMessageQueue::GetSingleton();
	if (msgQ) {
		msgQ->AddMessage(WidgetMenu::MENU_NAME, RE::UI_MESSAGE_TYPE::kHide, nullptr);
	}
}

void WidgetMenu::SetMainText(std::string newText) 
{
	if (auto ui = RE::UI::GetSingleton(); ui) {
		if (auto menu = ui->GetMenu(WidgetMenu::MENU_NAME); menu) {
			const RE::GFxValue newGfxText = newText.c_str();
			menu->uiMovie->Invoke("_root.main.SetTextMain", nullptr, &newGfxText, 1);
		}
	}
}

void WidgetMenu::SetWarningText(std::string newText)
{
	if (auto ui = RE::UI::GetSingleton(); ui) {
		if (auto menu = ui->GetMenu(WidgetMenu::MENU_NAME); menu) {
			const RE::GFxValue newGfxText = newText.c_str();
			menu->uiMovie->Invoke("_root.main.SetTextWarning", nullptr, &newGfxText, 1);
		}
	}
}

// Every time a new frame of the menu is rendered call the update function.
void WidgetMenu::AdvanceMovie(float a_interval, std::uint32_t a_currentTime)
{
	//put our code to update the thing here.
	auto main = "<h2><medium>allRunningStacks: size " + std::to_string(RE::BSScript::Internal::VirtualMachine::GetSingleton()->allRunningStacks.size()) + "</medium></h2>";
	auto player = RE::PlayerCharacter::GetSingleton();
	auto name = player->GetName();
	main = main + "\n<h2><good>Player Name: " + name +"</good></h2>"; 
	SetMainText(main);
	auto warning = "<h1><MajorWarning>WARNING TEXT</h1></MajorWarning>";
	SetWarningText(warning);
	RE::IMenu::AdvanceMovie(a_interval, a_currentTime);
}
