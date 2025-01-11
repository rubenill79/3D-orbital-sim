/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you
--  wrote the original software. If you use this software in a product, an acknowledgment
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#include "raylib.h"
#include "raymath.h"
#include "camera.h"

#pragma region imgui
//#include "imgui.h"
//#include "rlImGui.h"
//#include "imguiThemes.h"
#pragma endregion

#include "game.h"

//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
rlTPCamera orbitCam;
Vector3 cubePosition = { 0 };

Vector3 sunPosition = { 0.0f, 0.0f, 0.0f }; // Sun at the origin
float orbitRadius = 5.0f;                   // Radius of the planet's orbit
float orbitSpeed = 0.5f;                    // Speed of the planet in orbit
float orbitAngle = 0.0f;                    // Current angle of the planet in radians
Vector3 planetPosition = { 0.0f, 0.0f, 0.0f }; // Planet position

void GameInit()
{

    //SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(InitalWidth, InitalHeight, "Example");
    SetTargetFPS(165);

    // Initialization
    orbitCam.Setup(45, Vector3{ 0, 0 ,0 });
    orbitCam.ViewAngles.y = -15 * DEG2RAD;
}

void GameCleanup()
{
    // unload resources

    CloseWindow();
}

// Update
void GameUpdate()
{
    orbitCam.Update();

    orbitAngle += orbitSpeed * GetFrameTime(); // Increment the orbit angle
    if (orbitAngle > 2 * PI)
        orbitAngle -= 2 * PI; // Keep the angle within a full circle

    // Update the planet's position
    planetPosition.x = orbitRadius * cosf(orbitAngle);
    planetPosition.z = orbitRadius * sinf(orbitAngle);
}

// Draw
void GameDraw()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    orbitCam.BeginMode3D();

    //DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
    //DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
    //DrawGrid(10, 1.0f);

    // Draw the Sun
    DrawSphere(sunPosition, 1.0f, ORANGE);

    // Draw the Planet
    DrawSphere(planetPosition, 0.5f, BLUE);

    // Draw the Orbit (circle around the sun)
    for (int i = 0; i < 360; i += 5)
    {
        float angle1 = DEG2RAD * i;
        float angle2 = DEG2RAD * (i + 5);

        Vector3 point1 = { orbitRadius * cosf(angle1), 0.0f, orbitRadius * sinf(angle1) };
        Vector3 point2 = { orbitRadius * cosf(angle2), 0.0f, orbitRadius * sinf(angle2) };

        DrawLine3D(point1, point2, GRAY);
    }

    orbitCam.EndMode3D();

    DrawText("This is a raylib example", 10, 40, 20, RED);

    //if (GuiButton(Rectangle{20, 20, 20, 20}, GuiIconText(ICON_FILE_OPEN, "Open Image"))) { /* ACTION */ }


    DrawText("Right drag to rotate, Wheel to zoom, WASD to move", 100, 760, 20, GREEN);
    DrawFPS(10, 10);

    EndDrawing();
}

int main()
{
    GameInit();

    while (!WindowShouldClose())
    {
        GameUpdate();
        GameDraw();
    }
    GameCleanup();

    return 0;
}