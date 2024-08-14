#include <iostream>

#include <raylib.h>

#include <gui/Button.hpp>
#include <gui/InputText.hpp>

#include <app/MazeController.hpp>

int main() {
   app::MazeController maze_controller;
   maze_controller.Resize({20, 20});

   maze::InputText input_text_load_file({600, 200}, {150, 50});

   maze::Button load_from_file_button({600, 50}, {150, 50}, "Load from file");
   load_from_file_button.OnClick([&]() { 
      std::cout << "button load from file\n";
      maze_controller.LoadFromFile(input_text_load_file.GetText());
   });

   maze::Button reset_button({600, 125}, {150, 50}, "Reset");
   reset_button.OnClick([&]() {
      std::cout << "button reset\n";
      maze_controller.Reset();
   });


   const int screenWidth = 800;
   const int screenHeight = 450;

   const int virtualScreenWidth = 160;
   const int virtualScreenHeight = 90;

   InitWindow(screenWidth, screenHeight, "Maze resolver");
   std::string txt;
   maze::Maze::ObjectType selected = maze::Maze::ObjectType::WALL;

   while (!WindowShouldClose()) {
      // Update
      //----------------------------------------------------------------------------------
      if (IsKeyPressed(KEY_W))
         selected = maze::Maze::ObjectType::WALL;
      if (IsKeyPressed(KEY_S))
         selected = maze::Maze::ObjectType::START_POINT;
      if (IsKeyPressed(KEY_E))
         selected = maze::Maze::ObjectType::END_POINT;
      if (IsKeyPressed(KEY_R))
         selected = maze::Maze::ObjectType::ROAD;

      if (false || IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
         auto clicked_pos = maze_controller.CellClicked(GetMousePosition());
         if (clicked_pos.has_value()) {
            std::stringstream ss;
            ss << clicked_pos->x << " | " << clicked_pos->y;
            txt = ss.str();
            maze_controller.AddElement(clicked_pos.value(), selected);
         }
      }

      load_from_file_button.Update();
      reset_button.Update();
      input_text_load_file.Update();

      //----------------------------------------------------------------------------------
      // Draw
      //----------------------------------------------------------------------------------

      ClearBackground(WHITE);
      BeginDrawing();

      maze_controller.Display();
      DrawText(txt.c_str(), 20, 20, 20, RED);
      load_from_file_button.Draw();
      reset_button.Draw();
      input_text_load_file.Draw();

      EndDrawing();

      //----------------------------------------------------------------------------------
   }
}
