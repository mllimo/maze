#include <raylib.h>
#include <iostream>

#include <gui/Button.hpp>
#include <gui/InputText.hpp>

#include <app/MazeController.hpp>

#include <algorithms/A.hpp>
#include <algorithms/Resolver.hpp>

void PrintSolution(app::MazeController& maze, const maze::Path& solution) {
   for (const auto& step : solution) {
      if (step == *maze.GetMaze().GetStartPoint() ||
          step == *maze.GetMaze().GetEndPoint()) {
         continue;
      }
      maze.AddElement(step, maze::Maze::ObjectType::ROAD);
   }
}

void HandleButtonEvents(maze::Button& solve_button, maze::Button& load_button,
                        maze::Button& reset_button, maze::InputText& input_text,
                        app::MazeController& maze_controller,
                        maze::Resolver& resolver, maze::AStar& a_star_algo) {
   solve_button.OnClick([&]() {
      std::cout << "button solve\n";
      auto solution = resolver.Resolve(maze_controller.GetMaze(), &a_star_algo);
      PrintSolution(maze_controller, solution);
   });

   load_button.OnClick([&]() {
      std::cout << "button load from file\n";
      maze_controller.LoadFromFile(input_text.GetText());
   });

   reset_button.OnClick([&]() {
      std::cout << "button reset\n";
      maze_controller.Reset();
   });
}

void HandleKeyboardInput(maze::Maze::ObjectType& selected_object) {
   if (IsKeyPressed(KEY_W))
      selected_object = maze::Maze::ObjectType::WALL;
   if (IsKeyPressed(KEY_S))
      selected_object = maze::Maze::ObjectType::START_POINT;
   if (IsKeyPressed(KEY_E))
      selected_object = maze::Maze::ObjectType::END_POINT;
   if (IsKeyPressed(KEY_R))
      selected_object = maze::Maze::ObjectType::UNDEFINED;
}

void HandleMouseInput(app::MazeController& maze_controller,
                      maze::Maze::ObjectType selected_object,
                      std::string& text) {
   if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      auto clicked_pos = maze_controller.CellClicked(GetMousePosition());
      if (clicked_pos.has_value()) {
         std::stringstream ss;
         ss << clicked_pos->x << " | " << clicked_pos->y;
         text = ss.str();
         maze_controller.AddElement(clicked_pos.value(), selected_object);
      }
   }
}

void UpdateGUI(maze::Button& solve_button, maze::Button& load_button,
               maze::Button& reset_button, maze::InputText& input_text) {
   solve_button.Update();
   load_button.Update();
   reset_button.Update();
   input_text.Update();
}

void DrawGUI(app::MazeController& maze_controller, const std::string& text,
             const maze::Button& solve_button, const maze::Button& load_button,
             const maze::Button& reset_button,
             const maze::InputText& input_text) {
   ClearBackground(WHITE);
   BeginDrawing();

   maze_controller.Display();
   DrawText(text.c_str(), 20, 20, 20, RED);
   solve_button.Draw();
   load_button.Draw();
   reset_button.Draw();
   input_text.Draw();

   EndDrawing();
}

int main() {
   const int screen_width = 800;
   const int screen_height = 450;

   InitWindow(screen_width, screen_height, "Maze resolver");

   maze::Resolver resolver;
   maze::AStar a_star_algo;

   app::MazeController maze_controller;
   maze_controller.Resize({28, 22});

   maze::InputText input_text({600, 275}, {150, 50});
   input_text.OnClick([&]() {
      std::cout << "input text clicked\n";
      input_text.SetActivation(!input_text.GetCurrentEventState().is_active);
   });

   maze::Button solve_button({600, 50}, {150, 50}, "Solve");
   maze::Button load_from_file_button({600, 125}, {150, 50}, "Load from file");
   maze::Button reset_button({600, 200}, {150, 50}, "Reset");

   HandleButtonEvents(solve_button, load_from_file_button, reset_button,
                      input_text, maze_controller, resolver, a_star_algo);

   std::string text;
   maze::Maze::ObjectType selected_object = maze::Maze::ObjectType::WALL;

   while (!WindowShouldClose()) {
      HandleKeyboardInput(selected_object);
      HandleMouseInput(maze_controller, selected_object, text);
      UpdateGUI(solve_button, load_from_file_button, reset_button, input_text);
      DrawGUI(maze_controller, text, solve_button, load_from_file_button,
              reset_button, input_text);
   }

   CloseWindow();
   return 0;
}
