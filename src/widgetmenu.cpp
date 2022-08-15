#pragma once
#include "widgetmenu.h"

WidgetMenu::WidgetMenu()
{
	auto scaleformManager = RE::BSScaleformManager::GetSingleton();
	inputContext = Context::kNone;
	depthPriority = 0;

	menuFlags.set(RE::UI_MENU_FLAGS::kDontHideCursorWhenTopmost);
	menuFlags.set(RE::UI_MENU_FLAGS::kAlwaysOpen);
	menuFlags.set(RE::UI_MENU_FLAGS::kRequiresUpdate);
	menuFlags.set(RE::UI_MENU_FLAGS::kAllowSaving);
	menuFlags.set(RE::UI_MENU_FLAGS::kAdvancesUnderPauseMenu);

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

// Every time a new frame of the menu is rendered call the update function.
void WidgetMenu::AdvanceMovie(float a_interval, std::uint32_t a_currentTime)
{
	//put our code to update the thing here.
	RE::IMenu::AdvanceMovie(a_interval, a_currentTime);
}
