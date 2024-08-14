#pragma once

#include <string>
#include <string_view>

#include <gui/Component.hpp>

namespace maze {
class InputText : public Component {
  public:
   InputText(Vector2 pos = {0, 0}, Vector2 size = {50, 25});

   void SetText(std::string_view text);

   std::string_view GetText() const;

   void Draw() const override;

protected:
   void UpdateImp() override;

  private:
   std::string _text;
   const unsigned MAX_LENGHT = 256;
};
}  // namespace maze
