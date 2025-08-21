#include "raylib.h"
#include "raymath.h"

int main()
{
    const int   windowDimensions[2]{ 512, 512 };
    const char* windowTitle{ "Gabe's Top Down RPG Game" };
    const Color mapTexture_color{ WHITE };
    const int   target_fps{ 60 };

    InitWindow(windowDimensions[0], windowDimensions[1], windowTitle);
    SetTargetFPS(target_fps);

    Texture2D mapTexture = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2   mapPos{ 0.0, 0.0 };
    float     speed{ 4.1 };

    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2   knightPos{ windowDimensions[0] / 2.0f - (0.5f * knight.width / 6.0f),
                       windowDimensions[1] / 2.0f - 4.0f * (0.5f * knight.height) };

    Rectangle sourceRec{ 0.0f, 0.0f, knight.width / 6.0f, (float)knight.height };

    Rectangle destRec{ knightPos.x,
                       knightPos.y,
                       (knight.width / 6.0f) * 4.0f,
                       (float)knight.height * 4.0f };

    Vector2 origin{ destRec.width / 2.0f, destRec.height / 2.0f };
    int     frame       = 0;
    float   runningTime = 0.0f;
    float   updateTime  = 1.0f / 12.0f;

    while (!WindowShouldClose())
    {
        const float dt{ GetFrameTime() };

        BeginDrawing();

        ClearBackground(mapTexture_color);

        Vector2 direction{};

        if (IsKeyDown(KEY_A))
        {
            direction.x -= 1.0;
        }

        if (IsKeyDown(KEY_D))
        {
            direction.x += 1.0;
        }

        if (IsKeyDown(KEY_W))
        {
            direction.y -= 1.0;
        }

        if (IsKeyDown(KEY_S))
        {
            direction.y += 1.0;
        }

        if (Vector2Length(direction) != 0.0)
        {
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));

            runningTime += dt;
            if (runningTime >= updateTime)
            {
                runningTime = 0.0f;

                frame++;
                if (frame > 5)
                {
                    frame = 0;
                }

                sourceRec.x = frame * (knight.width / 6.0f);
            }

            // Flip horizontally depending on x direction
            if (direction.x < 0)
            {
                sourceRec.width = -(knight.width / 6.0f);
            }
            else if (direction.x > 0)
            {
                sourceRec.width = (knight.width / 6.0f);
            }
        }
        else
        {
            frame       = 0;
            sourceRec.x = 0.0f;
        }

        DrawTextureEx(mapTexture, mapPos, 0.0, 4.0, WHITE);
        DrawTexturePro(knight, sourceRec, destRec, origin, 0.0, WHITE);
        EndDrawing();
    }
    UnloadTexture(knight);
    UnloadTexture(mapTexture);
    CloseWindow();
}
