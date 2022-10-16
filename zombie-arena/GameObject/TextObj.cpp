#include "TextObj.h"

TextObj::TextObj()
{
}

TextObj::~TextObj()
{
}

void TextObj::Draw(RenderWindow& window)
{
	window.draw(text);
}

void TextObj::SetFont(Font& font)
{
	text.setFont(font);
}

void TextObj::SetText(string str)
{
	text.setString(str);
}

void TextObj::SetAll(Font& font, string str, int size, Color color, Vector2f pos)
{
	text.setFont(font);
	text.setString(str);
	text.setCharacterSize(size);
	text.setFillColor(color);
	text.setPosition(pos);
}

void TextObj::SetColor(Color color)
{
	text.setFillColor(color);
}

const string& TextObj::GetText() const
{
	return text.getString();
}
