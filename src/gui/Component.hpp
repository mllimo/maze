#pragma once

#include <raylib.h>
#include <functional>

namespace maze {
class Component {
  public:
   struct EventData {
      bool is_pressed = false;
      bool is_released = false;
      bool is_active = true;
   };

   Component() = default;
   Component(Vector2 pos, Vector2 collider_size);

   virtual ~Component() = default;

   void SetPosition(const Vector2& pos);
   void SetCollider(const Vector2& collider);
   void SetActivation(bool is_active);

   virtual void OnClick(std::function<void(void)> callback);

   Vector2 GetPosition() const;
   Rectangle GetCollider() const;
   const EventData& GetCurrentEventState() const;

   bool CollideWith(const Component& component);
   bool CollideWith(Rectangle rec);
   bool CollideWith(Vector2 point);

   void Update();
   virtual void Draw() const = 0;

  protected:
   std::function<void(void)> _on_click;

   virtual void UpdateImp();
   virtual void SetPositionImp(const Vector2& pos);

  private:
   Vector2 _position = {0.f, 0.f};
   Vector2 _collide_box = {0.f, 0.f};
   EventData _current_state;

   void CheckEvents();
};
}  // namespace maze
