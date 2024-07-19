#pragma once
#include<vector>

class RulePage 
{
public:
	RulePage();

	void draw(int _page) const;
	int getPageNum() const;

private:
	typedef void(RulePage::* FUNC)() const;
	std::vector<FUNC> m_draw_page;

	void m_draw_BaseRule00() const;
	void m_draw_BaseRule01() const;
	void m_draw_Saihai() const;
	void m_draw_Self() const;
	void m_draw_Mod5() const;
	void m_draw_Senryaku00() const;
	void m_draw_Senryaku01() const;
	void m_draw_Other00() const;
	void m_draw_Other01() const;
	void m_draw_Other02() const;

	void m_setFunc();

	int m_font_24, m_font_32;
};
