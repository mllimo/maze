#pragma once

#include <string_view>

#include <gui/Component.hpp>
#include <gui/TextBox.hpp>

namespace maze {
class Button : public Component {
  public:
   Button(Vector2 pos = {0, 0}, Vector2 size = {50, 25},
          std::string_view text = "button");

   void SetText(std::string_view text);

   const std::string_view GetText() const;

   void OnClick(std::function<void(void)> callback) override;

   void Draw() const override;

  protected:
   void UpdateImp() override;
   void SetPositionImp(const Vector2& pos) override;

  private:
   TextBox _text;
};
}  // namespace maze
