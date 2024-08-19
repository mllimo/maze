#pragma once

#include <string>
#include <string_view>

#include <gui/Component.hpp>

namespace maze {

/**
 * TextBox with text centered.
 */
class TextBox : public Component {
  public:
   TextBox(const Vector2& pos, const Vector2& size, std::string_view text = "");

   void AppendBack(char c);
   void PopBack();

   void SetText(std::string_view text);
   void SetBoxSize(const Vector2& size);
   void SetFontSize(unsigned size);
   void SetColor(Color color);

   std::string_view GetText() const;
   const Vector2& GetBoxSize() const;
   const Vector2& GetFontPosition() const;
   unsigned GetFontWidth() const;
   unsigned GetFontSize() const;
   unsigned GetFontSpacing() const;
   Color GetColor() const;

   void Draw() const override;

protected:
   void SetPositionImp(const Vector2& pos);

  private:
   std::string _text;
   Color _color = BLACK;
   Vector2 _font_position;
   unsigned _font_size = 20;
   unsigned _spacing = 2;
};
}  // namespace maze
