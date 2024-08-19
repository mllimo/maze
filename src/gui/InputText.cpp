#include <gui/InputText.hpp>

namespace maze {

InputText::InputText(Vector2 pos, Vector2 size)
    : Component(pos, size), _text(pos, size) {
   _text.SetPosition(pos);
}

void InputText::SetText(std::string_view text) {
   _text.SetText(text);
}

std::string_view InputText::GetText() const {
   return _text.GetText();
}

void InputText::Draw() const {
   DrawRectangleRec(GetCollider(), GRAY);

   auto fontPos = _text.GetFontPosition();
   auto selectorX = fontPos.x + _text.GetFontWidth() + _text.GetFontSpacing();
   DrawLine(selectorX, fontPos.y + _text.GetFontSize(), selectorX,
            fontPos.y - _text.GetFontSize() / 3, BLACK);

   _text.Draw();
}

void InputText::UpdateImp() {
   if (!GetCurrentEventState().is_active)
      return;

   if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_V)) {
      if (const char* clipboardText = GetClipboardText(); clipboardText) {
         _text.SetText(clipboardText);
      }
      return;
   }

   for (int key = GetCharPressed(); key > 0; key = GetCharPressed()) {
      if ((key >= 32 && key <= 125) &&
          (_text.GetText().length() < MAX_LENGTH)) {
         _text.AppendBack(static_cast<char>(key));
      }
   }

   if (!_text.GetText().empty() && IsKeyPressed(KEY_BACKSPACE)) {
      _text.PopBack();
   }
}

}  // namespace maze
