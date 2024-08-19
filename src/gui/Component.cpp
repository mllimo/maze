#include <gui/Component.hpp>

namespace maze {
Component::Component(Vector2 pos, Vector2 collider_size)
    : _position(pos), _collide_box(collider_size) {}

void Component::SetPosition(const Vector2& pos) {
   _position = pos;
   SetPositionImp(pos);
}

void Component::SetCollider(const Vector2& collider) {
   _collide_box = collider;
}

void Component::SetActivation(bool is_active) {
   _current_state.is_active = is_active;
}

void Component::OnClick(std::function<void(void)> callback) {
   _on_click = callback;
}

Vector2 Component::GetPosition() const {
   return _position;
}

Rectangle Component::GetCollider() const {
   Rectangle rec = {.x = _position.x,
                    .y = _position.y,
                    .width = _collide_box.x,
                    .height = _collide_box.y};
   return rec;
}

const Component::EventData& Component::GetCurrentEventState() const {
   return _current_state;
}

bool Component::CollideWith(const Component& component) {
   return CollideWith(component.GetCollider());
}

bool Component::CollideWith(Rectangle rec) {
   return CheckCollisionRecs({.x = _position.x,
                              .y = _position.y,
                              .width = _collide_box.x,
                              .height = _collide_box.y},
                             rec);
}

bool Component::CollideWith(Vector2 point) {
   return CheckCollisionPointRec(point, {.x = _position.x,
                                         .y = _position.y,
                                         .width = _collide_box.x,
                                         .height = _collide_box.y});
}

void Component::Update() {
   CheckEvents();
   UpdateImp();
}

void Component::UpdateImp() {}

void Component::SetPositionImp(const Vector2& pos) {}

void Component::CheckEvents() {
   bool mouse_collide = CollideWith(GetMousePosition());

   if (mouse_collide && (IsMouseButtonDown(MOUSE_LEFT_BUTTON) ||
                         IsMouseButtonPressed(MOUSE_LEFT_BUTTON))) {
      _current_state.is_pressed = true;
   } else {
      _current_state.is_pressed = false;
   }

   if (mouse_collide && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
      _current_state.is_released = true;

      if (_on_click)
         _on_click();

   } else {
      _current_state.is_released = false;
   }
}

}  // namespace maze
