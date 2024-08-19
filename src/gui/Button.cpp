#include <iostream>

#include <gui/Button.hpp>

namespace maze {
Button::Button(Vector2 pos, Vector2 size, std::string_view text)
    : Component(pos, size), _text(pos, size, text) {
   SetPosition(pos);
}

void Button::SetText(std::string_view text) {
   _text.SetText(text);
}

const std::string_view Button::GetText() const {
   return _text.GetText();
}

void Button::UpdateImp() {
   if (not GetCurrentEventState().is_active)
      return;
}

void Button::SetPositionImp(const Vector2& pos) {
   _text.SetPosition(pos);
}

void Button::OnClick(std::function<void(void)> callback) {
   auto wrapper = [callback, this]() {
      if (GetCurrentEventState().is_active)
         callback();
   };

   _on_click = wrapper;
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
   _text.Draw();
}

}  // namespace maze
