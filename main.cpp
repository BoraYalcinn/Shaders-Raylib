//
// Created by Bora on 18.01.2026.
//

#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <rcamera.h>

#define RLIGHTS_IMPLEMENTATION
#include <rlights.h>


#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION 330
#else
    #define GLSL_VERSION 100
#endif



int main() {

    const int screenWidth = 800;
    const int screenHeight = 600;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Basic Shaders Using Raylib");

    Camera camera = { 0 };
    camera.position = (Vector3){ 6.0f, 6.0f, 4.0f };
    camera.target = (Vector3){ 0.0f, 0.5f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Shader shader = LoadShader(TextFormat("./resources/shaders/lighting.vs", GLSL_VERSION),
                               TextFormat("./resources/shaders/lighting.fs", GLSL_VERSION));

    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

    int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, (float[4]){ 0.1f, 0.1f, 0.1f, 1.0f }, SHADER_UNIFORM_VEC4);

    Light lights[4] = {0};
    lights[0] = CreateLight(LIGHT_POINT,(Vector3){ 3, 1, 3 },Vector3Zero(),YELLOW,shader);
    lights[1] = CreateLight(LIGHT_POINT,(Vector3){ -3, 1, 3 },Vector3Zero(),RED,shader);
    lights[2] = CreateLight(LIGHT_POINT,(Vector3){ 3, 1, -3 },Vector3Zero(),GREEN,shader);
    lights[3] = CreateLight(LIGHT_POINT,(Vector3){ -3, 1, -3 },Vector3Zero(),BLUE,shader);

    Model car = LoadModel("C:/dev/RayLibProjects/BasicShaders/models/car.glb");

    // FOR DEBUGGING
    std::cout << "Meshes: " << car.meshCount << std::endl;
    std::cout << "Materials: " << car.materialCount << std::endl;

    for (int i = 0; i < car.materialCount; i++) {
        car.materials[i].shader = shader;
    }

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        UpdateCamera(&camera , CAMERA_ORBITAL);

        float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
        SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);


        if (IsKeyPressed(KEY_ONE)) { lights[0].enabled = !lights[0].enabled; }
        if (IsKeyPressed(KEY_TWO)) { lights[1].enabled = !lights[1].enabled; }
        if (IsKeyPressed(KEY_THREE)) { lights[2].enabled = !lights[2].enabled; }
        if (IsKeyPressed(KEY_FOUR)) { lights[3].enabled = !lights[3].enabled; }


        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);
        BeginShaderMode(shader);

        DrawModel(car, {0,0,0}, 1.0f, WHITE);


        for (int i = 0; i < 4; i++) {
            UpdateLightValues(shader, lights[i]);
            if (lights[i].enabled) {
                DrawSphereEx(lights[i].position, 0.2f, 8,8,lights[i].color);
            }else {
                DrawSphereWires(lights[i].position, 0.2f, 8,8,ColorAlpha(lights[i].color,0.3f));
            }
        }
        EndMode3D();
        DrawFPS(10,10);

        DrawText("Use keys [1][2][3][4] to toggle lights",10,40,20,DARKGRAY);
        EndDrawing();

    }

    UnloadShader(shader);

    CloseWindow();

    return 0;
}