#include <gui/Button.hpp>

namespace maze {
Button::Button(Vector2 pos, Vector2 size, std::string_view text)
    : Component(pos, size), _text(text) {}

void Button::SetText(std::string_view text) {
   _text = text;
}

const std::string_view Button::GetText() const {
   return _text;
}

void Button::UpdateImp() {
   if (GetCurrentEventState().is_released) {
      if (_on_click) {
         _on_click();
      }
   }
}

void Button::Draw() const {
   Rectangle rec = GetCollider();
   Color color = GRAY;

   if (GetCurrentEventState().is_pressed) {
      color.r -= 10;
      color.g -= 10;
      color.b -= 10;
   }
   
   DrawRectangleRec(GetCollider(), color);

   // Calcular el ancho y alto del texto
   int text_height = 20;
   int text_width = MeasureText(_text.c_str(), text_height);

   int text_x = rec.x + (rec.width - text_width) / 2;
   int text_y = rec.y + (rec.height - text_height) / 2;

   DrawText(_text.c_str(), text_x, text_y, text_height, BLACK);
}

}  // namespace maze
