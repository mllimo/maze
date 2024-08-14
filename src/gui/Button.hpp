#pragma once

#include <string_view>

#include <gui/Component.hpp>

namespace maze {
class Button : public Component {
  public:
   Button(Vector2 pos = {0, 0}, Vector2 size = {50, 25},
          std::string_view text = "button");

   void SetText(std::string_view text);

   const std::string_view GetText() const;

   void Draw() const override;

  protected:
   void UpdateImp() override;

  private:
   std::string _text;
};
}  // namespace maze
