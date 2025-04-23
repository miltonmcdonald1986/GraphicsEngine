#pragma once

#include "App.h"

using Result_AppWasSelected = bool;
using Result_SelectedItem = int;

class MainMenuApp : public App
{
public:
	explicit MainMenuApp(GLFWwindow* pWindow);
	virtual ~MainMenuApp() override;
	auto GetResults() -> std::pair<Result_AppWasSelected, Result_SelectedItem>;
	virtual auto Run() -> void override;

private:
	bool m_AppSelected = false;
	int m_SelectedItem = 0;

	GLFWkeyfun m_MainMenuPrevKeyCallback;
	void* m_MainMenuPrevUserPointer = nullptr;
};
