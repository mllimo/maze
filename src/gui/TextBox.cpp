#include <stdexcept>

#include <gui/TextBox.hpp>

namespace maze {
TextBox::TextBox(const Vector2& pos, const Vector2& size, std::string_view text)
    : Component(pos, size), _text(text), _color(BLACK), _font_position({0, 0}) {}

void TextBox::AppendBack(char c) {
   _text.push_back(c);
   SetPositionImp(GetPosition());
}

void TextBox::PopBack() {
   _text.pop_back();
   SetPositionImp(GetPosition());
}

void TextBox::SetText(std::string_view text) {
   _text = text;
}

void TextBox::SetBoxSize(const Vector2& size) {
   SetCollider(size);
}

void TextBox::SetFontSize(unsigned size) {
   _font_size = size;
}

void TextBox::SetColor(Color color) {
   _color = color;
}

std::string_view TextBox::GetText() const {
   return _text;
}

const Vector2& TextBox::GetBoxSize() const {
   Rectangle rec = GetCollider();
   return {rec.x, rec.y};
}

const Vector2& TextBox::GetFontPosition() const {
   return _font_position;
}

unsigned TextBox::GetFontWidth() const {
   Font font = GetFontDefault();

   if (font.texture.id == 0) {
      throw std::runtime_error("Error getting the default font");
   }

   return MeasureTextEx(font, GetText().data(), GetFontSize(), _spacing).x;
}

unsigned TextBox::GetFontSpacing() const {
   return _spacing;
}

unsigned TextBox::GetFontSize() const {
   return _font_size;
}

Color TextBox::GetColor() const {
   return _color;
}

void TextBox::Draw() const {
   Vector2 pos = GetPosition();
   DrawText(_text.c_str(), _font_position.x, _font_position.y, _font_size,
            _color);
}

void TextBox::SetPositionImp(const Vector2& pos) {
   Rectangle rec = GetCollider();

   int text_width = GetFontWidth();

   Vector2 text_position;
   _font_position.x = rec.x + (rec.width - text_width) / 2;
   _font_position.y = rec.y + (rec.height - GetFontSize()) / 2;
}
}  // namespace maze
