#pragma once
#include "gui.h"


class GuiProject :public Gui
{
	
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	std::string GetName()override { return "Project"; }
};
