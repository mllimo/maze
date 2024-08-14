#include <gui/InputText.hpp>

namespace maze {
InputText::InputText(Vector2 pos, Vector2 size) : Component(pos, size) {}

void InputText::SetText(std::string_view text) {
   _text = text;
}

std::string_view InputText::GetText() const {
   return _text;
}

void InputText::Draw() const {
   Rectangle rec = GetCollider();
   Color color = GRAY;

   DrawRectangleRec(GetCollider(), color);

   int text_height = 20;
   int text_width = MeasureText(_text.c_str(), text_height);

   int text_x = rec.x + (rec.width - text_width) / 2;
   int text_y = rec.y + (rec.height - text_height) / 2;

   {
      int selector_pos_x = text_x + text_width + 5;
      DrawLine(selector_pos_x, text_y + text_height, selector_pos_x,
               text_y - text_height / 3,
               BLACK);
   }

   DrawText(_text.c_str(), text_x, text_y, text_height, BLACK);
}

void InputText::UpdateImp() {
   int key = GetCharPressed();

   if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_V)) {
      const char* text = GetClipboardText();
      if (text != NULL) {
         _text = text;
      }
      return;
   }

   // Check if more characters have been pressed on the same frame
   while (key > 0) {
      if ((key >= 32) && (key <= 125) && (_text.size() < MAX_LENGHT)) {
         _text += (char)key;
      }
      key = GetCharPressed();  // Check next character in the queue
   }

   if (_text.size() > 0 && IsKeyPressed(KEY_BACKSPACE)) {
      _text.pop_back();
   }
}

}  // namespace maze
