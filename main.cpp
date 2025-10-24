#define _USE_MATH_DEFINES // For M_PI
#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib") // Link the Windows sound library

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// --- Master Control Variables ---
int currentScene = 0;
const int NUM_SCENES = 4;
// Scene Order: 0:Rural(N), 1:Turbine(S), 2:Ocean(A), 3:City(Z)
void masterUpdate(int value); // Forward declaration for timer functions

// =================================================================
// --- SCENE A (FROM main_a.cpp) --- This is now Scene 2
// =================================================================
namespace SceneA {
    // Global Variables for Scene A
    float carX = -300.0f;
    float ballY = 0.0f;
    bool ballUp = true;

    // Utility: Draw filled circle for Scene A
    void drawCircle(float cx, float cy, float radius, float r, float g, float b) {
        glColor3f(r, g, b);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= 100; ++i) {
            float angle = 2 * 3.1416f * i / 100;
            glVertex2f(cx + cos(angle) * radius, cy + sin(angle) * radius);
        }
        glEnd();
    }

    // Cartoon Car for Scene A
    void drawRedCartoonCarA(float x, float y) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex2f(x + 120, y); glVertex2f(x, y);
        glVertex2f(x, y + 20); glVertex2f(x + 20, y + 40);
        glVertex2f(x + 80, y + 40); glVertex2f(x + 100, y + 20);
        glVertex2f(x + 120, y + 20);
        glEnd();

        glColor3f(0.6f, 0.8f, 1.0f);
        glBegin(GL_POLYGON);
        glVertex2f(x + 12, y + 22); glVertex2f(x + 25, y + 38);
        glVertex2f(x + 55, y + 38); glVertex2f(x + 55, y + 22);
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(x + 60, y + 22); glVertex2f(x + 60, y + 38);
        glVertex2f(x + 82, y + 38); glVertex2f(x + 98, y + 22);
        glEnd();

        for (int i = 0; i < 2; i++) {
            float cx = x + 25 + i * 70;
            float cy = y - 2;
            drawCircle(cx, cy, 12, 0, 0, 0);
            drawCircle(cx, cy, 6, 1, 1, 1);
        }
    }

    // Small Tree for Scene A
    void drawSmallMountainTree(float x, float y) {
        glColor3f(0.4f, 0.2f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex2f(x - 1, y); glVertex2f(x + 1, y);
        glVertex2f(x + 1, y + 5); glVertex2f(x - 1, y + 5);
        glEnd();
        drawCircle(x, y + 8, 4, 0.0f, 0.4f, 0.0f);
    }

    // Fruit Tree for Scene A
    void drawFruitTree(float x, float y) {
        glColor3f(0.55f, 0.27f, 0.07f);
        glBegin(GL_POLYGON);
        glVertex2f(x - 5, y); glVertex2f(x + 5, y);
        glVertex2f(x + 5, y + 50); glVertex2f(x - 5, y + 50);
        glEnd();

        float cx = x, cy = y + 60;
        drawCircle(cx, cy + 10, 20, 0.0f, 0.6f, 0.0f);
        drawCircle(cx - 15, cy, 18, 0.0f, 0.5f, 0.0f);
        drawCircle(cx + 15, cy, 18, 0.0f, 0.5f, 0.0f);

        drawCircle(cx - 5, cy + 5, 3, 1, 0, 0);
        drawCircle(cx + 8, cy + 12, 3, 1, 0, 0);
        drawCircle(cx - 12, cy - 4, 3, 1, 0, 0);
        drawCircle(cx + 15, cy - 2, 3, 1, 0, 0);
        drawCircle(cx + 2, cy - 8, 3, 1, 0, 0);
    }

    // Boat for Scene A
    void drawBoat(float x, float y) {
        glColor3f(0.4f, 0.2f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex2f(x - 20, y); glVertex2f(x + 20, y);
        glVertex2f(x + 15, y - 10); glVertex2f(x - 15, y - 10);
        glEnd();

        glColor3f(0.2f, 0.2f, 0.2f);
        glBegin(GL_LINES);
        glVertex2f(x, y); glVertex2f(x, y + 20);
        glEnd();

        glColor3f(1, 1, 1);
        glBegin(GL_TRIANGLES);
        glVertex2f(x, y + 20); glVertex2f(x, y);
        glVertex2f(x + 15, y + 10);
        glEnd();
    }

    // Mountains for Scene A
    void drawDistantMountains() {
        glColor3f(0.7f, 0.9f, 0.7f);
        glBegin(GL_TRIANGLES);
        glVertex2f(50, 300); glVertex2f(200, 400); glVertex2f(350, 300);
        glVertex2f(300, 300); glVertex2f(450, 420); glVertex2f(600, 300);
        glVertex2f(550, 300); glVertex2f(620, 370); glVertex2f(700, 300);
        glEnd();

        float treeX[] = {120, 160, 200, 280, 320, 360, 400, 460, 520, 580, 600, 650};
        float treeY[] = {310, 315, 320, 310, 305, 300, 310, 305, 310, 300, 310, 305};
        for (int i = 0; i < 12; ++i)
            drawSmallMountainTree(treeX[i], treeY[i]);
    }

    // Ocean for Scene A
    void drawOcean() {
        glColor3f(0.2f, 0.6f, 1.0f);
        glBegin(GL_POLYGON);
        glVertex2f(0, 150); glVertex2f(800, 150);
        glVertex2f(800, 300); glVertex2f(0, 300);
        glEnd();

        drawBoat(200, 250);
        drawBoat(700, 270);
        drawBoat(500, 210);
    }

    // Beach for Scene A
    void drawBeach() {
        glColor3f(0.96f, 0.76f, 0.26f);
        glBegin(GL_POLYGON);
        glVertex2f(0, 100); glVertex2f(800, 100);
        glVertex2f(800, 200); glVertex2f(0, 200);
        glEnd();
    }

    // Road for Scene A
    void drawRoad() {
        glColor3f(0.1f, 0.1f, 0.1f);
        glBegin(GL_POLYGON);
        glVertex2f(0, 0); glVertex2f(800, 0);
        glVertex2f(800, 100); glVertex2f(0, 100);
        glEnd();

        glColor3f(1, 1, 1);
        for (float i = 0; i < 800; i += 40) {
            glBegin(GL_LINES);
            glVertex2f(i, 50); glVertex2f(i + 20, 50);
            glEnd();
        }
    }

    // Beach Ball for Scene A
    void drawBeachBallOnSand() {
        float cx = 650, cy = 130 + ballY, radius = 12;
        float colors[6][3] = {
            {1, 0, 0}, {1, 1, 0}, {0, 1, 0},
            {0, 1, 1}, {0, 0, 1}, {1, 0, 1}
        };

        for (int i = 0; i < 100; ++i) {
            int colorIndex = (i * 6) / 100;
            glColor3f(colors[colorIndex][0], colors[colorIndex][1], colors[colorIndex][2]);
            float a1 = i * 2 * 3.1416f / 100;
            float a2 = (i + 1) * 2 * 3.1416f / 100;
            glBegin(GL_TRIANGLES);
            glVertex2f(cx, cy);
            glVertex2f(cx + cos(a1) * radius, cy + sin(a1) * radius);
            glVertex2f(cx + cos(a2) * radius, cy + sin(a2) * radius);
            glEnd();
        }
        drawCircle(cx, cy, 3, 1, 1, 1);
    }

    // Sun for Scene A
    void drawSunA() {
        drawCircle(100, 450, 30, 1, 0.85f, 0);
    }

    // Cloud for Scene A
    void drawCloudA(float x, float y) {
        drawCircle(x, y, 15, 1, 1, 1);
        drawCircle(x + 20, y, 15, 1, 1, 1);
        drawCircle(x + 10, y + 10, 15, 1, 1, 1);
    }

    // Bird for Scene A
    void drawBirdA(float x, float y) {
        glColor3f(0.2f, 0.2f, 0.2f);
        glBegin(GL_LINES);
        glVertex2f(x - 5, y); glVertex2f(x, y + 5);
        glVertex2f(x, y + 5); glVertex2f(x + 5, y);
        glEnd();
    }

    // Roadside Trees for Scene A
    void drawRoadsideTrees() {
        float positions[10] = {50, 130, 210, 290, 370, 450, 530, 610, 690, 770};
        for (int i = 0; i < 10; i++) {
            drawFruitTree(positions[i], 100);
        }
    }

    // Main Display Function for Scene A
    void displayA() {
        glClear(GL_COLOR_BUFFER_BIT);
        drawSunA();
        drawDistantMountains();
        drawOcean();
        drawBeach();
        drawRoad();
        drawRoadsideTrees();
        drawBeachBallOnSand();
        drawRedCartoonCarA(carX, 90);
        drawCloudA(500, 430); drawCloudA(600, 390); drawCloudA(700, 410);
        drawBirdA(200, 420); drawBirdA(250, 410);
        glutSwapBuffers();
    }

    // Animation Update Function for Scene A
    void updateA(int value) {
        if (currentScene != 2) { // Only update if this is the current scene
            glutTimerFunc(16, masterUpdate, 0);
            return;
        }

        carX += 2.0f;
        if (carX > 800) carX = -150;

        ballY += ballUp ? 0.8f : -0.8f;
        if (ballY > 15) ballUp = false;
        if (ballY < 0) ballUp = true;

        glutPostRedisplay();
        glutTimerFunc(16, masterUpdate, 0);
    }

    // Initialization for Scene A
    void initA() {
        glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, 800, 0, 500);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
}

// =================================================================
// --- SCENE N (FROM main_n.cpp) --- This is now Scene 0
// =================================================================
namespace SceneN {
    // Constants and Global Variables for Scene N
    #define N_PI 3.14159265358979323846f
    #define N_WIDTH 800
    #define N_HEIGHT 600

    float N_cloudPosition1 = 0.0f;
    float N_cloudPosition2 = 300.0f;
    float N_cloudPosition3 = 600.0f;
    float N_birdX = 0.0f;
    float N_birdY = 400.0f;
    bool N_birdDirection = true;
    float N_birdWingAngle = 0.0f;
    bool N_birdWingUp = true;
    float N_birdFlapSpeed = 0.2f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(0.3f)));
    float N_sunX = N_WIDTH * 0.7f;
    float N_sunY = -200.0f;
    bool N_sunRising = true;
    bool N_sunHasRisen = false;
    const float N_peakSunY = N_HEIGHT * 0.7f;
    float N_carX = -120.0f;
    float N_carSpeed = 3.0f;
    bool N_carMoving = false;
    float N_riverWaveOffset = 0.0f;

    // Color constants for day/night cycle
    const float N_FOG_R = 0.85f;
    const float N_FOG_G = 0.9f;
    const float N_FOG_B = 0.95f;
    float N_dawn_horizon_R = 0.9f, N_dawn_horizon_G = 0.5f, N_dawn_horizon_B = 0.2f;
    float N_dawn_top_R = 0.1f, N_dawn_top_G = 0.2f, N_dawn_top_B = 0.4f;
    float N_day_horizon_R = 0.7f, N_day_horizon_G = 0.9f, N_day_horizon_B = 1.0f;
    float N_day_top_R = 0.2f, N_day_top_G = 0.5f, N_day_top_B = 0.8f;


    // Helper Drawing Functions for Scene N
    void drawFilledEllipseN(float cx, float cy, float rx, float ry, float alpha, float r, float g, float b, int segments =36) {
        glColor4f(r, g, b, alpha);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= segments; i++) {
            float angle = i * 2 * N_PI / segments;
            glVertex2f(cx + rx * cos(angle), cy + ry * sin(angle));
        }
        glEnd();
    }

    void drawSkyN() {
        float normalized_sun_y = (N_sunY - (-200.0f)) / (N_peakSunY - (-200.0f));
        if (normalized_sun_y < 0.0f) normalized_sun_y = 0.0f;
        if (normalized_sun_y > 1.0f) normalized_sun_y = 1.0f;

        float current_horizon_R = N_dawn_horizon_R + (N_day_horizon_R - N_dawn_horizon_R) * normalized_sun_y;
        float current_horizon_G = N_dawn_horizon_G + (N_day_horizon_G - N_dawn_horizon_G) * normalized_sun_y;
        float current_horizon_B = N_dawn_horizon_B + (N_day_horizon_B - N_dawn_horizon_B) * normalized_sun_y;
        float current_top_R = N_dawn_top_R + (N_day_top_R - N_dawn_top_R) * normalized_sun_y;
        float current_top_G = N_dawn_top_G + (N_day_top_G - N_dawn_top_G) * normalized_sun_y;
        float current_top_B = N_dawn_top_B + (N_day_top_B - N_dawn_top_B) * normalized_sun_y;

        glBegin(GL_QUAD_STRIP);
            glColor3f(current_top_R, current_top_G, current_top_B);
            glVertex2f(0, N_HEIGHT);
            glVertex2f(N_WIDTH, N_HEIGHT);
            glColor3f(current_top_R * 0.7f + current_horizon_R * 0.3f,
                      current_top_G * 0.7f + current_horizon_G * 0.3f,
                      current_top_B * 0.7f + current_horizon_B * 0.3f);
            glVertex2f(0, N_HEIGHT * 0.6f);
            glVertex2f(N_WIDTH, N_HEIGHT * 0.6f);
            glColor3f(current_horizon_R, current_horizon_G, current_horizon_B);
            glVertex2f(0, N_HEIGHT * 0.4f);
            glVertex2f(N_WIDTH, N_HEIGHT * 0.4f);
        glEnd();
    }

    void drawHorizonHazeN() {
        float normalized_sun_y = (N_sunY - (-200.0f)) / (N_peakSunY - (-200.0f));
        if (normalized_sun_y < 0.0f) normalized_sun_y = 0.0f;
        if (normalized_sun_y > 1.0f) normalized_sun_y = 1.0f;
        float haze_alpha = 0.6f - (0.3f * normalized_sun_y);
        if (haze_alpha < 0.1f) haze_alpha = 0.1f;
        float current_fog_R = N_FOG_R + (0.95f - N_FOG_R) * normalized_sun_y;
        float current_fog_G = N_FOG_G + (0.98f - N_FOG_G) * normalized_sun_y;
        float current_fog_B = N_FOG_B + (1.0f - N_FOG_B) * normalized_sun_y;

        glBegin(GL_QUAD_STRIP);
            glColor4f(current_fog_R, current_fog_G, current_fog_B, 0.0f);
            glVertex2f(0, N_HEIGHT * 0.45f);
            glVertex2f(N_WIDTH, N_HEIGHT * 0.45f);
            glColor4f(current_fog_R, current_fog_G, current_fog_B, haze_alpha);
            glVertex2f(0, N_HEIGHT * 0.35f);
            glVertex2f(N_WIDTH, N_HEIGHT * 0.35f);
        glEnd();
    }

    void drawHillsN() {
        float hill_visibility_factor = (N_sunY - (-200.0f)) / (N_peakSunY - (-200.0f));
        if (hill_visibility_factor < 0.0f) hill_visibility_factor = 0.0f;
        if (hill_visibility_factor > 1.0f) hill_visibility_factor = 1.0f;
        float far_hill_r = 0.10f + (0.20f - 0.10f) * hill_visibility_factor;
        float far_hill_g = 0.30f + (0.50f - 0.30f) * hill_visibility_factor;
        float far_hill_b = 0.05f + (0.15f - 0.05f) * hill_visibility_factor;

        glBegin(GL_POLYGON);
            glColor3f(far_hill_r, far_hill_g, far_hill_b);
            glVertex2f(0, N_HEIGHT * 0.4f);
            glVertex2f(N_WIDTH * 0.15f, N_HEIGHT * 0.50f);
            glVertex2f(N_WIDTH * 0.35f, N_HEIGHT * 0.46f);
            glVertex2f(N_WIDTH * 0.55f, N_HEIGHT * 0.53f);
            glVertex2f(N_WIDTH * 0.75f, N_HEIGHT * 0.48f);
            glVertex2f(N_WIDTH, N_HEIGHT * 0.51f);
            glVertex2f(N_WIDTH, N_HEIGHT * 0.35f);
            glVertex2f(0, N_HEIGHT * 0.35f);
        glEnd();

        float mid_hill_r = 0.15f + (0.28f - 0.15f) * hill_visibility_factor;
        float mid_hill_g = 0.40f + (0.60f - 0.40f) * hill_visibility_factor;
        float mid_hill_b = 0.07f + (0.10f - 0.07f) * hill_visibility_factor;
        glBegin(GL_POLYGON);
            glColor3f(mid_hill_r, mid_hill_g, mid_hill_b);
            glVertex2f(0, N_HEIGHT * 0.3f);
            glVertex2f(N_WIDTH * 0.1f, N_HEIGHT * 0.36f);
            glVertex2f(N_WIDTH * 0.25f, N_HEIGHT * 0.33f);
            glVertex2f(N_WIDTH * 0.4f, N_HEIGHT * 0.41f);
            glVertex2f(N_WIDTH * 0.55f, N_HEIGHT * 0.39f);
            glVertex2f(N_WIDTH * 0.7f, N_HEIGHT * 0.35f);
            glVertex2f(N_WIDTH * 0.85f, N_HEIGHT * 0.30f);
            glVertex2f(N_WIDTH, N_HEIGHT * 0.32f);
            glVertex2f(N_WIDTH, N_HEIGHT * 0.25f);
            glVertex2f(0, N_HEIGHT * 0.25f);
        glEnd();
    }

    void drawGroundN() {
        glBegin(GL_POLYGON);
            glColor3f(0.15f, 0.45f, 0.08f);
            glVertex2f(0, 0);
            glVertex2f(N_WIDTH, 0);
            glColor3f(0.25f, 0.55f, 0.12f);
            glVertex2f(N_WIDTH, N_HEIGHT * 0.25f);
            glVertex2f(0, N_HEIGHT * 0.25f);
        glEnd();

        glColor4f(0.1f, 0.3f, 0.05f, 0.2f);
        glBegin(GL_POINTS);
        for(int i = 0; i < N_WIDTH; i += 5) {
            for(int j = 0; j < N_HEIGHT * 0.25f; j += 5) {
                if (rand() % 10 == 0)
                    glVertex2f(i + (rand() % 5), j + (rand() % 5));
            }
        }
        glEnd();
    }

    void drawHouseN(float x, float y, float scale, float sun_brightness_factor) {
		float base_width = 50.0f * scale;
		float base_height = 50.0f * scale;
		float roof_height = 30.0f * scale;
		float foundation_height = 5.0f * scale;
		float door_width = 15.0f * scale;
		float door_height = 35.0f * scale;
		float window_size = 12.0f * scale;

		float dawn_foundation_r = 0.35f, dawn_foundation_g = 0.25f, dawn_foundation_b = 0.15f;
		float day_foundation_r = 0.45f, day_foundation_g = 0.35f, day_foundation_b = 0.25f;

		float dawn_body_top_r = 0.65f, dawn_body_top_g = 0.55f, dawn_body_top_b = 0.4f;
		float day_body_top_r = 0.85f, day_body_top_g = 0.75f, day_body_top_b = 0.6f;

		float dawn_body_bottom_r = 0.55f, dawn_body_bottom_g = 0.45f, dawn_body_bottom_b = 0.3f;
		float day_body_bottom_r = 0.75f, day_body_bottom_g = 0.65f, day_body_bottom_b = 0.5f;

		float dawn_texture_r = 0.4f, dawn_texture_g = 0.3f, dawn_texture_b = 0.2f;
		float day_texture_r = 0.6f, day_texture_g = 0.5f, day_texture_b = 0.4f;

		float dawn_thatch_base_r = 0.5f, dawn_thatch_base_g = 0.35f, dawn_thatch_base_b = 0.15f;
		float day_thatch_base_r = 0.7f, day_thatch_base_g = 0.55f, day_thatch_base_b = 0.35f;

		float dawn_thatch_main_r = 0.6f, dawn_thatch_main_g = 0.45f, dawn_thatch_main_b = 0.25f;
		float day_thatch_main_r = 0.8f, day_thatch_main_g = 0.65f, day_thatch_main_b = 0.45f;

		float dawn_thatch_ridge_r = 0.4f, dawn_thatch_ridge_g = 0.25f, dawn_thatch_ridge_b = 0.05f;
		float day_thatch_ridge_r = 0.6f, day_thatch_ridge_g = 0.4f, day_thatch_ridge_b = 0.2f;


		float current_foundation_r = dawn_foundation_r + (day_foundation_r - dawn_foundation_r) * sun_brightness_factor;
		float current_foundation_g = dawn_foundation_g + (day_foundation_g - dawn_foundation_g) * sun_brightness_factor;
		float current_foundation_b = dawn_foundation_b + (day_foundation_b - dawn_foundation_b) * sun_brightness_factor;

		float current_body_top_r = dawn_body_top_r + (day_body_top_r - dawn_body_top_r) * sun_brightness_factor;
		float current_body_top_g = dawn_body_top_g + (day_body_top_g - dawn_body_top_g) * sun_brightness_factor;
		float current_body_top_b = dawn_body_top_b + (day_body_top_b - dawn_body_top_b) * sun_brightness_factor;

		float current_body_bottom_r = dawn_body_bottom_r + (day_body_bottom_r - dawn_body_bottom_r) * sun_brightness_factor;
		float current_body_bottom_g = dawn_body_bottom_g + (day_body_bottom_g - dawn_body_bottom_g) * sun_brightness_factor;
		float current_body_bottom_b = dawn_body_bottom_b + (day_body_bottom_b - dawn_body_bottom_b) * sun_brightness_factor;

		float current_texture_r = dawn_texture_r + (day_texture_r - dawn_texture_r) * sun_brightness_factor;
		float current_texture_g = dawn_texture_g + (day_texture_g - dawn_texture_g) * sun_brightness_factor;
		float current_texture_b = dawn_texture_b + (day_texture_b - dawn_texture_b) * sun_brightness_factor;

		float current_thatch_base_r = dawn_thatch_base_r + (day_thatch_base_r - dawn_thatch_base_r) * sun_brightness_factor;
		float current_thatch_base_g = dawn_thatch_base_g + (day_thatch_base_g - dawn_thatch_base_g) * sun_brightness_factor;
		float current_thatch_base_b = dawn_thatch_base_b + (day_thatch_base_b - dawn_thatch_base_b) * sun_brightness_factor;

		float current_thatch_main_r = dawn_thatch_main_r + (day_thatch_main_r - dawn_thatch_main_r) * sun_brightness_factor;
		float current_thatch_main_g = dawn_thatch_main_g + (day_thatch_main_g - dawn_thatch_main_g) * sun_brightness_factor;
		float current_thatch_main_b = dawn_thatch_main_b + (day_thatch_main_b - dawn_thatch_main_b) * sun_brightness_factor;

		float current_thatch_ridge_r = dawn_thatch_ridge_r + (day_thatch_ridge_r - dawn_thatch_ridge_r) * sun_brightness_factor;
		float current_thatch_ridge_g = dawn_thatch_ridge_g + (day_thatch_ridge_g - dawn_thatch_ridge_g) * sun_brightness_factor;
		float current_thatch_ridge_b = dawn_thatch_ridge_b + (day_thatch_ridge_b - dawn_thatch_ridge_b) * sun_brightness_factor;


		glColor3f(current_foundation_r, current_foundation_g, current_foundation_b);
		glBegin(GL_POLYGON);
			glVertex2f(x - 2 * scale, y - foundation_height);
			glVertex2f(x + base_width + 2 * scale, y - foundation_height);
			glVertex2f(x + base_width, y);
			glVertex2f(x, y);
		glEnd();

		glBegin(GL_POLYGON);
			glColor3f(current_body_top_r, current_body_top_g, current_body_top_b);
			glVertex2f(x, y + base_height);
			glVertex2f(x + base_width, y + base_height);
			glColor3f(current_body_bottom_r, current_body_bottom_g, current_body_bottom_b);
			glVertex2f(x + base_width, y);
			glVertex2f(x, y);
		glEnd();

		glColor4f(current_texture_r, current_texture_g, current_texture_b, 0.2f);
		glBegin(GL_LINES);
		for (int i = 0; i < base_width; i += 7 * scale) {
			glVertex2f(x + i, y);
			glVertex2f(x + i, y + base_height);
		}
		glEnd();


		glColor3f(current_thatch_base_r, current_thatch_base_g, current_thatch_base_b);
		glBegin(GL_POLYGON);
			glVertex2f(x - 5 * scale, y + base_height - 3 * scale);
			glVertex2f(x + base_width + 5 * scale, y + base_height - 3 * scale);
			glVertex2f(x + base_width + 2 * scale, y + base_height + roof_height * 0.2f);
			glVertex2f(x - 2 * scale, y + base_height + roof_height * 0.2f);
		glEnd();

		glColor3f(current_thatch_main_r, current_thatch_main_g, current_thatch_main_b);
		glBegin(GL_TRIANGLES);
			glVertex2f(x - 5 * scale, y + base_height);
			glVertex2f(x + base_width + 5 * scale, y + base_height);
			glVertex2f(x + base_width / 2, y + base_height + roof_height);
		glEnd();

		glColor3f(current_thatch_ridge_r, current_thatch_ridge_g, current_thatch_ridge_b);
		glLineWidth(2.0 * scale);
		glBegin(GL_LINES);
			glVertex2f(x + base_width / 2, y + base_height + roof_height);
			glVertex2f(x + base_width / 2, y + base_height + roof_height - 5 * scale);
		glEnd();
		glLineWidth(1.0);


		glColor3f(0.3f, 0.15f, 0.05f);
		glBegin(GL_POLYGON);
			glVertex2f(x + (base_width - door_width) / 2, y);
			glVertex2f(x + (base_width + door_width) / 2, y);
			glVertex2f(x + (base_width + door_width) / 2, y + door_height);
			glVertex2f(x + (base_width - door_width) / 2, y + door_height);
		glEnd();
		glColor3f(0.1f, 0.05f, 0.0f);
		drawFilledEllipseN(x + (base_width + door_width) / 2 - 3 * scale, y + door_height / 2, 1.5 * scale, 1.5 * scale, 1.0f, 0.1f, 0.05f, 0.0f);


		glColor3f(0.2f, 0.2f, 0.2f);
		glBegin(GL_POLYGON);
			glVertex2f(x + 10 * scale, y + base_height - 25 * scale);
			glVertex2f(x + 10 * scale + window_size, y + base_height - 25 * scale);
			glVertex2f(x + 10 * scale + window_size, y + base_height - 25 * scale + window_size);
			glVertex2f(x + 10 * scale, y + base_height - 25 * scale + window_size);
		glEnd();
		if (base_width > 40 * scale) {
			glBegin(GL_POLYGON);
				glVertex2f(x + base_width - 10 * scale - window_size, y + base_height - 25 * scale);
				glVertex2f(x + base_width - 10 * scale, y + base_height - 25 * scale);
				glVertex2f(x + base_width - 10 * scale, y + base_height - 25 * scale + window_size);
				glVertex2f(x + base_width - 10 * scale - window_size, y + base_height - 25 * scale + window_size);
			glEnd();
		}
    }

    void drawRealisticTreeN(float x, float y, float scale) {
        float trunk_base_w = 15 * scale;
        float trunk_top_w = 8 * scale;
        float trunk_h = 80 * scale;
        float canopy_r_max = 60 * scale;

        glColor3f(0.45f, 0.22f, 0.05f);
        glBegin(GL_POLYGON);
            glVertex2f(x - trunk_base_w / 2, y);
            glVertex2f(x + trunk_base_w / 2, y);
            glVertex2f(x + trunk_top_w / 2 + 2 * scale, y + trunk_h * 0.4f);
            glVertex2f(x - trunk_top_w / 2 - 2 * scale, y + trunk_h * 0.4f);
        glEnd();

        glColor3f(0.55f, 0.27f, 0.07f);
        glBegin(GL_POLYGON);
            glVertex2f(x - trunk_top_w / 2 * 0.8f, y + trunk_h * 0.4f);
            glVertex2f(x + trunk_top_w / 2 * 0.8f, y + trunk_h * 0.4f);
            glVertex2f(x + trunk_top_w / 2 * 0.8f, y + trunk_h);
            glVertex2f(x - trunk_top_w / 2 * 0.8f, y + trunk_h);
        glEnd();

        glColor3f(0.4f, 0.2f, 0.05f);
        glLineWidth(2.0);
        glBegin(GL_POLYGON);
            glVertex2f(x + (rand() % 5), y + trunk_h + (rand() % 10));
            glVertex2f(x - trunk_top_w / 2 * 0.8f, y + trunk_h * 0.7f);
            glVertex2f(x - trunk_top_w / 1.5f, y + trunk_h * 0.8f);
            glVertex2f(x - trunk_top_w * 2.5f, y + trunk_h * 1.1f);
            glVertex2f(x - trunk_top_w * 2, y + trunk_h * 1.0f);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2f(x + trunk_top_w / 2 * 0.8f, y + trunk_h * 0.6f);
            glVertex2f(x + trunk_top_w * 1.2f, y + trunk_h * 0.7f);
            glVertex2f(x + trunk_top_w * 2.0f, y + trunk_h * 0.9f);
            glVertex2f(x + trunk_top_w * 1.5f, y + trunk_h * 0.8f);
        glEnd();
        glLineWidth(1.0);

        drawFilledEllipseN(x + 5 * scale, y + trunk_h + 30 * scale, canopy_r_max * 0.8f, canopy_r_max * 0.7f, 0.8f, 0.05f, 0.45f, 0.05f, 24);
        drawFilledEllipseN(x + 10 * scale, y + trunk_h + 45 * scale, canopy_r_max, canopy_r_max * 0.9f, 0.85f, 0.1f, 0.6f, 0.1f, 28);
        drawFilledEllipseN(x - 15 * scale, y + trunk_h + 35 * scale, canopy_r_max * 0.7f, canopy_r_max * 0.8f, 0.88f, 0.15f, 0.65f, 0.15f, 26);
        drawFilledEllipseN(x + 25 * scale, y + trunk_h + 30 * scale, canopy_r_max * 0.6f, canopy_r_max * 0.65f, 0.87f, 0.12f, 0.62f, 0.12f, 25);
        drawFilledEllipseN(x + 20 * scale, y + trunk_h + 55 * scale, canopy_r_max * 0.7f, canopy_r_max * 0.65f, 0.9f, 0.2f, 0.7f, 0.2f, 24);
        drawFilledEllipseN(x - 5 * scale, y + trunk_h + 60 * scale, canopy_r_max * 0.5f, canopy_r_max * 0.55f, 0.9f, 0.25f, 0.75f, 0.25f, 22);
        drawFilledEllipseN(x + 30 * scale, y + trunk_h + 70 * scale, canopy_r_max * 0.3f, canopy_r_max * 0.28f, 0.95f, 0.4f, 0.85f, 0.4f, 18);

        drawFilledEllipseN(x + 8 * scale, y + trunk_h + 20 * scale, canopy_r_max * 0.6f, canopy_r_max * 0.5f, 0.6f, 0.0f, 0.3f, 0.0f, 20);
        drawFilledEllipseN(x - 10 * scale, y + trunk_h + 25 * scale, canopy_r_max * 0.5f, canopy_r_max * 0.45f, 0.65f, 0.02f, 0.35f, 0.02f, 20);
    }

    void drawRoadN() {
        glBegin(GL_POLYGON);
            glColor3f(0.2f, 0.2f, 0.2f); glVertex2f(0, 0);
            glColor3f(0.2f, 0.2f, 0.2f); glVertex2f(N_WIDTH, 0);
            glColor3f(0.3f, 0.3f, 0.3f); glVertex2f(N_WIDTH, N_HEIGHT * 0.12f);
            glColor3f(0.3f, 0.3f, 0.3f); glVertex2f(0, N_HEIGHT * 0.12f);
        glEnd();

        glColor4f(0.1f, 0.1f, 0.1f, 0.3f);
        glBegin(GL_QUADS);
            glVertex2f(N_WIDTH * 0.2f, N_HEIGHT * 0.05f);
            glVertex2f(N_WIDTH * 0.25f, N_HEIGHT * 0.06f);
            glVertex2f(N_WIDTH * 0.23f, N_HEIGHT * 0.09f);
            glVertex2f(N_WIDTH * 0.18f, N_HEIGHT * 0.08f);

            glVertex2f(N_WIDTH * 0.6f, N_HEIGHT * 0.02f);
            glVertex2f(N_WIDTH * 0.63f, N_HEIGHT * 0.03f);
            glVertex2f(N_WIDTH * 0.62f, N_HEIGHT * 0.06f);
            glVertex2f(N_WIDTH * 0.59f, N_HEIGHT * 0.05f);
        glEnd();
    }

    void drawDashedRoadLineN() {
        glColor3f(0.9f, 0.9f, 0.0f);
        glLineWidth(4.0);

        float roadCenterY = (0 + N_HEIGHT * 0.12f) / 2.0f;
        float lineBottomY = roadCenterY - 3;
        float lineTopY = roadCenterY + 3;

        for (int i = 0; i < N_WIDTH; i += 80) {
            glBegin(GL_POLYGON);
                glVertex2f(i, lineBottomY);
                glVertex2f(i + 40, lineBottomY);
                glVertex2f(i + 40, lineTopY);
                glVertex2f(i, lineTopY);
            glEnd();
        }
        glLineWidth(1.0);
    }

    void drawCarN(float x, float y) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glVertex2f(x + 120, y);
            glVertex2f(x, y);
            glVertex2f(x, y + 20);
            glVertex2f(x + 20, y + 40);
            glVertex2f(x + 80, y + 40);
            glVertex2f(x + 100, y + 20);
            glVertex2f(x + 120, y + 20);
        glEnd();

        glColor3f(0.6f, 0.8f, 1.0f);
        glBegin(GL_POLYGON);
            glVertex2f(x + 12, y + 22);
            glVertex2f(x + 25, y + 38);
            glVertex2f(x + 55, y + 38);
            glVertex2f(x + 55, y + 22);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex2f(x + 60, y + 22);
            glVertex2f(x + 60, y + 38);
            glVertex2f(x + 82, y + 38);
            glVertex2f(x + 98, y + 22);
        glEnd();

        for (int i = 0; i < 2; i++) {
            float cx = x + 25 + i * 70;
            float cy = y - 2;
            float radiusOuter = 12;
            float radiusInner = 6;

            glColor3f(0.0f, 0.0f, 0.0f);
            glBegin(GL_TRIANGLE_FAN);
                glVertex2f(cx, cy);
                for (int j = 0; j <= 100; ++j) {
                    float angle = 2 * 3.1416f * j / 100;
                    glVertex2f(cx + cos(angle) * radiusOuter, cy + sin(angle) * radiusOuter);
                }
            glEnd();

            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_TRIANGLE_FAN);
                glVertex2f(cx, cy);
                for (int j = 0; j <= 100; ++j) {
                    float angle = 2 * 3.1416f * j / 100;
                    glVertex2f(cx + cos(angle) * radiusInner, cy + sin(angle) * radiusInner);
                }

            glEnd();
        }
    }

    void drawSunN(float x, float y, float baseRadius) {
        drawFilledEllipseN(x, y, baseRadius, baseRadius, 1.0f, 1.0f, 1.0f, 0.0f, 60);
        drawFilledEllipseN(x, y, baseRadius * 1.3, baseRadius * 1.3, 0.3f, 1.0f, 0.9f, 0.0f, 60);
        drawFilledEllipseN(x, y, baseRadius * 1.6, baseRadius * 1.6, 0.15f, 1.0f, 0.85f, 0.0f, 60);
        drawFilledEllipseN(x, y, baseRadius * 2.0, baseRadius * 2.0, 0.08f, 1.0f, 0.8f, 0.0f, 60);

        glColor4f(1.0f, 1.0f, 0.5f, 0.1f);
        for (int i = 0; i < 16; ++i) {
            float angle = i * (360.0f / 16) * N_PI / 180.0f;
            float start_x = x + baseRadius * cos(angle);
            float start_y = y + baseRadius * sin(angle);
            float end_x = x + baseRadius * 2.5 * cos(angle);
            float end_y = y + baseRadius * 2.5 * sin(angle);

            glBegin(GL_LINES);
                glVertex2f(start_x, start_y);
                glVertex2f(end_x, end_y);
            glEnd();
        }
    }

    void drawCloudN(float x, float y) {
        const float CLOUD_R = 0.95f;
        const float CLOUD_G = 0.97f;
        const float CLOUD_B = 1.0f;

        drawFilledEllipseN(x + 40, y + 12, 60, 25, 0.9f, CLOUD_R, CLOUD_G, CLOUD_B, 30);
        drawFilledEllipseN(x + 15, y + 16, 45, 20, 0.92f, CLOUD_R * 1.02f, CLOUD_G * 1.02f, CLOUD_B * 1.02f, 30);
        drawFilledEllipseN(x + 75, y + 16, 55, 22, 0.88f, CLOUD_R, CLOUD_G, CLOUD_B, 30);

        drawFilledEllipseN(x + 30, y + 22, 40, 20, 0.95f, CLOUD_R * 1.05f, CLOUD_G * 1.05f, CLOUD_B * 1.05f, 30);
        drawFilledEllipseN(x + 65, y + 25, 45, 22, 0.9f, CLOUD_R * 1.03f, CLOUD_G * 1.03f, CLOUD_B * 1.03f, 30);
        drawFilledEllipseN(x + 50, y + 30, 35, 18, 0.98f, 1.0f, 1.0f, 1.0f, 30);

        drawFilledEllipseN(x + 40, y + 2, 60, 20, 0.5f, CLOUD_R * 0.8f, CLOUD_G * 0.8f, CLOUD_B * 0.8f, 30);
        drawFilledEllipseN(x + 25, y + 6, 30, 15, 0.45f, CLOUD_R * 0.75f, CLOUD_G * 0.75f, CLOUD_B * 0.75f, 30);

        drawFilledEllipseN(x + 55, y + 33, 20, 12, 0.9f, 1.0f, 1.0f, 1.0f, 30);
        drawFilledEllipseN(x + 20, y + 27, 18, 10, 0.85f, 1.0f, 1.0f, 1.0f, 30);
    }

    void drawRiverN(float y_start, float y_end) {
        glColor3f(0.2f, 0.6f, 0.9f);

        glBegin(GL_POLYGON);
            glVertex2f(0, y_start);
            glVertex2f(N_WIDTH, y_start);
            glVertex2f(N_WIDTH, y_end);
            glVertex2f(0, y_end);
        glEnd();

        glBegin(GL_QUAD_STRIP);
            glColor3f(0.1f, 0.4f, 0.7f);
            glVertex2f(0, y_start);
            glVertex2f(N_WIDTH, y_start);
            glColor3f(0.2f, 0.6f, 0.9f);
            glVertex2f(0, y_end);
            glVertex2f(N_WIDTH, y_end);
        glEnd();

        glColor4f(0.95f, 0.98f, 1.0f, 0.8f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);

        for (int i = 0; i < N_WIDTH; i += 10) {
            float ripple_y_base = y_start + (y_end - y_start) * 0.85f;
            float ripple_amplitude = 8.0f;
            float ripple_frequency = 0.02f;

            glVertex2f(i, ripple_y_base + sin(i * ripple_frequency + N_riverWaveOffset * 1.5f) * ripple_amplitude);
            glVertex2f(i + 10, ripple_y_base + sin((i + 10) * ripple_frequency + N_riverWaveOffset * 1.5f) * ripple_amplitude);
        }
        for (int i = 0; i < N_WIDTH; i += 12) {
            float ripple_y_base = y_start + (y_end - y_start) * 0.65f;
            float ripple_amplitude = 10.0f;
            float ripple_frequency = 0.015f;

            glVertex2f(i, ripple_y_base + cos(i * ripple_frequency + N_riverWaveOffset * 1.2f) * ripple_amplitude);
            glVertex2f(i + 15, ripple_y_base + cos((i + 15) * ripple_frequency + N_riverWaveOffset * 1.2f) * ripple_amplitude);
        }
        for (int i = 0; i < N_WIDTH; i += 15) {
            float ripple_y_base = y_start + (y_end - y_start) * 0.45f;
            float ripple_amplitude = 12.0f;
            float ripple_frequency = 0.01f;

            glVertex2f(i, ripple_y_base + sin(i * ripple_frequency * 0.8f + N_riverWaveOffset * 0.7f) * ripple_amplitude);
            glVertex2f(i + 20, ripple_y_base + sin((i + 20) * ripple_frequency * 0.8f + N_riverWaveOffset * 0.7f) * ripple_amplitude);
        }
        for (int i = 0; i < N_WIDTH; i += 18) {
            float ripple_y_base = y_start + (y_end - y_start) * 0.25f;
            float ripple_amplitude = 7.0f;
            float ripple_frequency = 0.025f;

            glVertex2f(i, ripple_y_base + cos(i * ripple_frequency * 1.5f + N_riverWaveOffset * 2.0f) * ripple_amplitude);
            glVertex2f(i + 12, ripple_y_base + cos((i + 12) * ripple_frequency * 1.5f + N_riverWaveOffset * 2.0f) * ripple_amplitude);
        }
        glEnd();

        glLineWidth(1.0);
    }

    void drawBirdN(float x, float y, bool direction) {
        glColor3f(0.2f, 0.2f, 0.2f);

        glBegin(GL_TRIANGLES);
            glVertex2f(x + (direction ? 0 : 15), y);
            glVertex2f(x + (direction ? 15 : 0), y);
            glVertex2f(x + (direction ? 7.5 : 7.5), y + 7);
        glEnd();

        glPushMatrix();
        glTranslatef(x + (direction ? 7.5 : 7.5), y + 7, 0.0f);
        glRotatef(N_birdWingAngle * (direction ? 1 : -1), 0.0f, 0.0f, 1.0f);
        glTranslatef(-(x + (direction ? 7.5 : 7.5)), -(y + 7), 0.0f);

        glBegin(GL_TRIANGLES);
            glVertex2f(x + (direction ? 7.5 : 7.5), y + 7);
            glVertex2f(x + (direction ? 25 : -10), y + 18);
            glVertex2f(x + (direction ? 15 : 0), y + 7);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(x + (direction ? 7.5 : 7.5), y + 7, 0.0f);
        glRotatef(-N_birdWingAngle * (direction ? 1 : -1), 0.0f, 0.0f, 1.0f);
        glTranslatef(-(x + (direction ? 7.5 : 7.5)), -(y + 7), 0.0f);

        glBegin(GL_TRIANGLES);
            glVertex2f(x + (direction ? 7.5 : 7.5), y + 7);
            glVertex2f(x + (direction ? -10 : 25), y + 18);
            glVertex2f(x + (direction ? 0 : 15), y + 7);
        glEnd();
        glPopMatrix();
    }

    void drawFenceN(float y_offset, float height, float spacing) {
        glColor3f(0.5f, 0.3f, 0.1f);
        float post_width = 5.0f;
        for (float x = 10.0f; x < N_WIDTH - 10.0f; x += spacing) {
            glBegin(GL_POLYGON);
                glVertex2f(x, y_offset);
                glVertex2f(x + post_width, y_offset);
                glVertex2f(x + post_width, y_offset + height);
                glVertex2f(x, y_offset + height);
            glEnd();
        }

        glColor3f(0.6f, 0.35f, 0.15f);
        float rail_height = 5.0f;
        glBegin(GL_POLYGON);
            glVertex2f(0, y_offset + height * 0.2f);
            glVertex2f(N_WIDTH, y_offset + height * 0.2f);
            glVertex2f(N_WIDTH, y_offset + height * 0.2f + rail_height);
            glVertex2f(0, y_offset + height * 0.2f + rail_height);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2f(0, y_offset + height * 0.8f);
            glVertex2f(N_WIDTH, y_offset + height * 0.8f);
            glVertex2f(N_WIDTH, y_offset + height * 0.8f + rail_height);
            glVertex2f(0, y_offset + height * 0.8f + rail_height);
        glEnd();
    }

    // Main Display Function for Scene N
    void displayN() {
        glClear(GL_COLOR_BUFFER_BIT);

        float normalized_sun_y = (N_sunY - (-200.0f)) / (N_peakSunY - (-200.0f));
        if (normalized_sun_y < 0.0f) normalized_sun_y = 0.0f;
        if (normalized_sun_y > 1.0f) normalized_sun_y = 1.0f;

        drawSkyN();
        drawSunN(N_sunX, N_sunY, 50);
        drawHorizonHazeN();
        drawHillsN();
        drawCloudN(N_cloudPosition1, N_HEIGHT - 100);
        drawCloudN(N_cloudPosition2, N_HEIGHT - 50);
        drawCloudN(N_cloudPosition3, N_HEIGHT - 120);
        drawRiverN(0, N_HEIGHT * 0.4f);
        drawGroundN();
        drawFenceN(N_HEIGHT * 0.24f, 30.0f, 40.0f);
        drawRealisticTreeN(N_WIDTH * 0.15f, N_HEIGHT * 0.18f, 0.8f);
        drawRealisticTreeN(N_WIDTH * 0.05f, N_HEIGHT * 0.22f, 0.7f);
        drawRealisticTreeN(N_WIDTH * 0.25f, N_HEIGHT * 0.20f, 0.9f);
        drawRealisticTreeN(N_WIDTH * 0.45f, N_HEIGHT * 0.25f, 0.95f);
        drawRealisticTreeN(N_WIDTH * 0.35f, N_HEIGHT * 0.28f, 0.85f);
        drawRealisticTreeN(N_WIDTH * 0.55f, N_HEIGHT * 0.23f, 1.0f);
        drawRealisticTreeN(N_WIDTH * 0.75f, N_HEIGHT * 0.19f, 0.8f);
        drawRealisticTreeN(N_WIDTH * 0.85f, N_HEIGHT * 0.24f, 0.75f);
        drawRealisticTreeN(N_WIDTH * 0.65f, N_HEIGHT * 0.21f, 0.9f);
        drawHouseN(N_WIDTH * 0.08f, N_HEIGHT * 0.12f, 0.95f, normalized_sun_y);
        drawHouseN(N_WIDTH * 0.18f, N_HEIGHT * 0.15f, 1.0f, normalized_sun_y);
        drawHouseN(N_WIDTH * 0.02f, N_HEIGHT * 0.10f, 0.85f, normalized_sun_y);
        drawHouseN(N_WIDTH * 0.30f, N_HEIGHT * 0.18f, 1.1f, normalized_sun_y);
        drawHouseN(N_WIDTH * 0.45f, N_HEIGHT * 0.15f, 1.05f, normalized_sun_y);
        drawHouseN(N_WIDTH * 0.38f, N_HEIGHT * 0.16f, 0.9f, normalized_sun_y);
        drawHouseN(N_WIDTH * 0.60f, N_HEIGHT * 0.17f, 0.98f, normalized_sun_y);
        drawHouseN(N_WIDTH * 0.75f, N_HEIGHT * 0.18f, 0.88f, normalized_sun_y);
        drawHouseN(N_WIDTH * 0.88f, N_HEIGHT * 0.19f, 0.8f, normalized_sun_y);
        drawRoadN();
        drawDashedRoadLineN();
        drawCarN(N_carX, N_HEIGHT * 0.08f);
        drawBirdN(N_birdX, N_birdY, N_birdDirection);
        drawBirdN(N_birdX + 150, N_birdY - 50, N_birdDirection);
        drawBirdN(N_birdX + 300, N_birdY + 30, N_birdDirection);
        drawBirdN(N_birdX - 200, N_birdY + 100, !N_birdDirection);
        drawBirdN(N_birdX + 500, N_birdY - 20, !N_birdDirection);

        glutSwapBuffers();
    }

    // Animation Update Function for Scene N
    void updateN(int value) {
        if (currentScene != 0) { // Only update if this is the current scene
            glutTimerFunc(16, masterUpdate, 0);
            return;
        }

        N_cloudPosition1 += 0.5f;
        if (N_cloudPosition1 > N_WIDTH + 100) N_cloudPosition1 = -150;
        N_cloudPosition2 += 0.3f;
        if (N_cloudPosition2 > N_WIDTH + 100) N_cloudPosition2 = -150;
        N_cloudPosition3 += 0.4f;
        if (N_cloudPosition3 > N_WIDTH + 100) N_cloudPosition3 = -150;

        if (N_birdWingUp) {
            N_birdWingAngle += N_birdFlapSpeed;
            if (N_birdWingAngle > 30.0f) N_birdWingUp = false;
        } else {
            N_birdWingAngle -= N_birdFlapSpeed;
            if (N_birdWingAngle < -30.0f) N_birdWingUp = true;
        }

        if (N_birdDirection) {
            N_birdX += 1.5f;
            if (N_birdX > N_WIDTH + 100) {
                N_birdDirection = false;
                N_birdX = N_WIDTH + 50;
                N_birdY = (float)(rand() % (N_HEIGHT / 4)) + (N_HEIGHT * 0.6f);
                N_birdFlapSpeed = 0.2f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(0.3f)));
            }
        } else {
            N_birdX -= 1.5f;
            if (N_birdX < -150) {
                N_birdDirection = true;
                N_birdX = -100;
                N_birdY = (float)(rand() % (N_HEIGHT / 4)) + (N_HEIGHT * 0.6f);
                N_birdFlapSpeed = 0.2f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(0.3f)));
            }
        }

        if (N_sunRising && !N_sunHasRisen) {
            N_sunY += 1.984f;
            if (N_sunY >= N_peakSunY) {
                N_sunY = N_peakSunY;
                N_sunHasRisen = true;
            }
        }

        float sun_travel_range = N_peakSunY - (-200.0f);
        float sun_trigger_y = -200.0f + (sun_travel_range * 0.9f);

        if (!N_carMoving && N_sunY >= sun_trigger_y) {
            N_carMoving = true;
        }

        if (N_carMoving) {
            N_carX += N_carSpeed;
            if (N_carX > N_WIDTH + 150) {
                N_carMoving = false;
            }
        }
        N_riverWaveOffset += 0.05f;

        glutPostRedisplay();
        glutTimerFunc(16, masterUpdate, 0);
    }

    void resetN() {
        N_sunY = -200.0f;
        N_sunHasRisen = false;
        N_sunRising = true;
        N_carX = -120.0f;
        N_carMoving = false;
        N_birdX = 0.0f;
        N_birdY = 400.0f;
        N_birdDirection = true;
        N_birdWingAngle = 0.0f;
        N_birdWingUp = true;
        N_birdFlapSpeed = 0.2f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(0.3f)));
        N_cloudPosition1 = 0.0f;
        N_cloudPosition2 = 300.0f;
        N_cloudPosition3 = 600.0f;
        N_riverWaveOffset = 0.0f;
    }

    void keyboardN(unsigned char key, int x, int y) {
        if (currentScene != 0) return;
        switch (key) {
            case 'r':
            case 'R':
                resetN();
                break;
            case 27:
                exit(0);
                break;
        }
    }


    // Initialization for Scene N
    void initN() {
        glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, N_WIDTH, 0, N_HEIGHT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_POLYGON_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
        srand(time(NULL));
        resetN(); // Reset state every time the scene is initialized
    }
}

// =================================================================
// --- SCENE S (FROM main_s.cpp) --- This is now Scene 1
// =================================================================
namespace SceneS {
    // Define PI for calculations
    #define S_PI 3.14159265358979323846

    // --- Global Variables ---
    #define S_WIDTH 800
    #define S_HEIGHT 600

    float bladeAngle = 0.0f;
    float carPosition = -150.0f;

    struct Cloud {
        float x, y, speed;
        float alpha;
    };
    Cloud clouds[] = {
        {-50.0f, 450.0f, 0.3f, 0.8f},
        {150.0f, 500.0f, 0.2f, 0.9f},
        {350.0f, 480.0f, 0.4f, 0.75f},
        {550.0f, 520.0f, 0.35f, 0.85f},
        {700.0f, 460.0f, 0.25f, 0.95f}
    };
    const int numClouds = sizeof(clouds) / sizeof(clouds)[0];

    struct SmokeParticle {
        float x, y;
        float size;
        float alpha;
        float speedY;
        float speedX;
        float initialX;
        float life;
    };
    SmokeParticle smokeParticles[50];
    int numSmokeParticles = 0;
    const int MAX_SMOKE_PARTICLES = 50;

    const float S_FOG_R = 0.8f;
    const float S_FOG_G = 0.9f;
    const float S_FOG_B = 1.0f;

    void drawFilledEllipseS(float cx, float cy, float rx, float ry, float alpha, float r, float g, float b, int segments=36) {
        glColor4f(r, g, b, alpha);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= segments; i++) {
            float angle = i * 2 * S_PI / segments;
            glVertex2f(cx + rx * cos(angle), cy + ry * sin(angle));
        }
        glEnd();
    }

    void drawGradientRectangleS(float x1, float y1, float x2, float y2,
                               float r1, float g1, float b1,
                               float r2, float g2, float b2) {
        glBegin(GL_POLYGON);
            glColor3f(r2, g2, b2); glVertex2f(x1, y1);
            glColor3f(r2, g2, b2); glVertex2f(x2, y1);
            glColor3f(r1, g1, b1); glVertex2f(x2, y2);
            glColor3f(r1, g1, b1); glVertex2f(x1, y2);
        glEnd();
    }

    void drawWindTurbineS() {
        // Tower Base
        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_POLYGON);
            glVertex2f(S_WIDTH * 0.5f - 25, S_HEIGHT * 0.2f - 5);
            glVertex2f(S_WIDTH * 0.5f + 25, S_HEIGHT * 0.2f - 5);
            glVertex2f(S_WIDTH * 0.5f + 22, S_HEIGHT * 0.2f);
            glVertex2f(S_WIDTH * 0.5f - 22, S_HEIGHT * 0.2f);
        glEnd();

        float towerBaseW = 20.0f;
        float towerTopW = 12.0f;
        float towerHeight = S_HEIGHT * 0.6f;
        float towerCenterX = S_WIDTH * 0.5f;
        float towerBaseY = S_HEIGHT * 0.2f;

        glColor3f(0.6f, 0.6f, 0.6f);
        glBegin(GL_POLYGON);
            glVertex2f(towerCenterX - towerBaseW, towerBaseY);
            glVertex2f(towerCenterX - towerTopW, towerBaseY + towerHeight);
            glVertex2f(towerCenterX - towerTopW + 2, towerBaseY + towerHeight);
            glVertex2f(towerCenterX - towerBaseW + 2, towerBaseY);
        glEnd();

        glColor3f(0.85f, 0.85f, 0.85f);
        glBegin(GL_POLYGON);
            glVertex2f(towerCenterX - towerBaseW + 2, towerBaseY);
            glVertex2f(towerCenterX + towerBaseW - 2, towerBaseY);
            glVertex2f(towerCenterX + towerTopW - 2, towerBaseY + towerHeight);
            glVertex2f(towerCenterX - towerTopW + 2, towerBaseY + towerHeight);
        glEnd();

        glColor3f(0.55f, 0.55f, 0.55f);
        glBegin(GL_POLYGON);
            glVertex2f(towerCenterX + towerBaseW - 2, towerBaseY);
            glVertex2f(towerCenterX + towerBaseW, towerBaseY);
            glVertex2f(towerCenterX + towerTopW, towerBaseY + towerHeight);
            glVertex2f(towerCenterX + towerTopW - 2, towerBaseY + towerHeight);
        glEnd();

        float nacelleWidth = 35;
        float nacelleHeight = 20;
        float nacelleX = towerCenterX - (nacelleWidth / 2);
        float nacelleY = towerBaseY + towerHeight - 2;

        glColor3f(0.4f, 0.4f, 0.4f);
        glBegin(GL_POLYGON);
            glVertex2f(nacelleX, nacelleY);
            glVertex2f(nacelleX + nacelleWidth, nacelleY);
            glVertex2f(nacelleX + nacelleWidth, nacelleY + nacelleHeight);
            glVertex2f(nacelleX, nacelleY + nacelleHeight);
        glEnd();

        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_POLYGON);
            glVertex2f(nacelleX, nacelleY + nacelleHeight);
            glVertex2f(nacelleX + nacelleWidth, nacelleY + nacelleHeight);
            glVertex2f(nacelleX + nacelleWidth - 5, nacelleY + nacelleHeight + 5);
            glVertex2f(nacelleX + 5, nacelleY + nacelleHeight + 5);
        glEnd();

        float hubX = towerCenterX;
        float hubY = nacelleY + nacelleHeight / 2 + 3;

        drawFilledEllipseS(hubX, hubY, 12, 12, 1.0f, 0.35f, 0.35f, 0.35f);
        drawFilledEllipseS(hubX, hubY, 10, 10, 1.0f, 0.45f, 0.45f, 0.45f);

        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_POLYGON);
            glVertex2f(hubX, hubY - 5);
            glVertex2f(hubX + 25, hubY);
            glVertex2f(hubX, hubY + 5);
            glVertex2f(hubX - 10, hubY);
        glEnd();
        glColor3f(0.4f, 0.4f, 0.4f);
        glBegin(GL_TRIANGLES);
            glVertex2f(hubX, hubY - 5);
            glVertex2f(hubX, hubY + 5);
            glVertex2f(hubX + 25, hubY);
        glEnd();

        glPushMatrix();
        glTranslatef(hubX, hubY, 0);
        glRotatef(bladeAngle, 0, 0, 1);

        for (int i = 0; i < 3; ++i) {
            float angle_offset = i * 120.0f;
            float blade_length = 150.0f;

            glBegin(GL_POLYGON);
                glColor3f(0.45f, 0.45f, 0.45f);
                glVertex2f(cos( (angle_offset - 2) * S_PI / 180.0f) * 10, sin( (angle_offset - 2) * S_PI / 180.0f) * 10);
                glVertex2f(cos( (angle_offset - 2) * S_PI / 180.0f) * blade_length, sin( (angle_offset - 2) * S_PI / 180.0f) * blade_length);
                glVertex2f(cos( (angle_offset + 10) * S_PI / 180.0f) * blade_length, sin( (angle_offset + 10) * S_PI / 180.0f) * blade_length);
                glVertex2f(cos( (angle_offset + 10) * S_PI / 180.0f) * 10, sin( (angle_offset + 10) * S_PI / 180.0f) * 10);

                glColor3f(0.75f, 0.75f, 0.75f);
                glVertex2f(cos( (angle_offset + 5) * S_PI / 180.0f) * 10, sin( (angle_offset + 5) * S_PI / 180.0f) * 10);
                glVertex2f(cos( (angle_offset + 2) * S_PI / 180.0f) * blade_length, sin( (angle_offset + 2) * S_PI / 180.0f) * blade_length);
                glVertex2f(cos( (angle_offset - 2) * S_PI / 180.0f) * blade_length, sin( (angle_offset - 2) * S_PI / 180.0f) * blade_length);
                glVertex2f(cos( (angle_offset - 5) * S_PI / 180.0f) * 10, sin( (angle_offset - 5) * S_PI / 180.0f) * 10);
            glEnd();

            glColor3f(0.3f, 0.3f, 0.3f);
            glLineWidth(1.5);
            glBegin(GL_LINE_STRIP);
                glVertex2f(cos( (angle_offset + 5) * S_PI / 180.0f) * 10, sin( (angle_offset + 5) * S_PI / 180.0f) * 10);
                glVertex2f(cos( (angle_offset + 2) * S_PI / 180.0f) * blade_length, sin( (angle_offset + 2) * S_PI / 180.0f) * blade_length);
            glEnd();
            glLineWidth(1.0);
        }
        glPopMatrix();
    }

    void drawSunS(float x, float y, float baseRadius) {
        drawFilledEllipseS(x, y, baseRadius, baseRadius, 1.0f, 1.0f, 1.0f, 0.0f, 60);
        drawFilledEllipseS(x, y, baseRadius * 1.3, baseRadius * 1.3, 0.3f, 1.0f, 0.9f, 0.0f, 60);
        drawFilledEllipseS(x, y, baseRadius * 1.6, baseRadius * 1.6, 0.15f, 1.0f, 0.85f, 0.0f, 60);

        glColor4f(1.0f, 1.0f, 0.5f, 0.1f);
        for (int i = 0; i < 12; ++i) {
            float angle = i * (360.0f / 12) * S_PI / 180.0f;
            float start_x = x + baseRadius * cos(angle);
            float start_y = y + baseRadius * sin(angle);
            float end_x = x + baseRadius * 2.5 * cos(angle);
            float end_y = y + baseRadius * 2.5 * sin(angle);

            glBegin(GL_LINES);
                glVertex2f(start_x, start_y);
                glVertex2f(end_x, end_y);
            glEnd();
        }
    }

    void drawCloudS(float x, float y, float alpha) {
        drawFilledEllipseS(x + 40, y + 12, 60, 25, alpha * 0.8f, 0.9f, 0.92f, 0.95f, 30);
        drawFilledEllipseS(x + 15, y + 16, 45, 20, alpha * 0.85f, 0.92f, 0.94f, 0.97f, 30);
        drawFilledEllipseS(x + 75, y + 16, 55, 22, alpha * 0.8f, 0.9f, 0.92f, 0.95f, 30);
        drawFilledEllipseS(x + 30, y + 22, 40, 20, alpha * 0.9f, 0.95f, 0.97f, 1.0f, 30);
        drawFilledEllipseS(x + 65, y + 25, 45, 22, alpha * 0.92f, 0.96f, 0.98f, 1.0f, 30);
        drawFilledEllipseS(x + 50, y + 30, 35, 18, alpha * 0.95f, 0.98f, 0.99f, 1.0f, 30);
        drawFilledEllipseS(x + 40, y + 2, 60, 20, alpha * 0.6f, 0.85f, 0.87f, 0.9f, 30);
        drawFilledEllipseS(x + 25, y + 6, 30, 15, alpha * 0.55f, 0.83f, 0.85f, 0.88f, 30);
        drawFilledEllipseS(x + 55, y + 33, 20, 12, alpha * 0.98f, 1.0f, 1.0f, 1.0f, 30);
        drawFilledEllipseS(x + 20, y + 27, 18, 10, alpha * 0.95f, 1.0f, 1.0f, 1.0f, 30);
    }

    void drawDashedRoadLineS() {
        glColor3f(1.0f, 1.0f, 1.0f);
        glLineWidth(3.0);
        float roadCenterY = S_HEIGHT * 0.06f;
        float lineBottomY = roadCenterY - 2;
        float lineTopY = roadCenterY + 2;
        for (int i = 0; i < S_WIDTH; i += 60) {
            glBegin(GL_POLYGON);
                glVertex2f(i, lineBottomY);
                glVertex2f(i + 30, lineBottomY);
                glVertex2f(i + 30, lineTopY);
                glVertex2f(i, lineTopY);
            glEnd();
        }
        glLineWidth(1.0);
    }

    void drawRedCartoonCarS(float x, float y) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glVertex2f(x + 120, y);
            glVertex2f(x, y);
            glVertex2f(x, y + 20);
            glVertex2f(x + 20, y + 40);
            glVertex2f(x + 80, y + 40);
            glVertex2f(x + 100, y + 20);
            glVertex2f(x + 120, y + 20);
        glEnd();

        glColor3f(0.6f, 0.8f, 1.0f);
        glBegin(GL_POLYGON);
            glVertex2f(x + 12, y + 22);
            glVertex2f(x + 25, y + 38);
            glVertex2f(x + 55, y + 38);
            glVertex2f(x + 55, y + 22);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex2f(x + 60, y + 22);
            glVertex2f(x + 60, y + 38);
            glVertex2f(x + 82, y + 38);
            glVertex2f(x + 98, y + 22);
        glEnd();

        for (int i = 0; i < 2; i++) {
            float cx = x + 25 + i * 70;
            float cy = y - 2;
            float radiusOuter = 12;
            float radiusInner = 6;
            drawFilledEllipseS(cx, cy, radiusOuter, radiusOuter, 1.0f, 0.0f, 0.0f, 0.0f, 100);
            drawFilledEllipseS(cx, cy, radiusInner, radiusInner, 1.0f, 1.0f, 1.0f, 1.0f, 100);
        }
    }


    void drawFarmHouseS() {
		float fx = 200, fy = 120; // Base position

		// --- Foundation ---
		glColor3f(0.4f, 0.35f, 0.3f); // Stone-like dark grey-brown
		glBegin(GL_POLYGON);
			glVertex2f(fx - 5, fy - 5);
			glVertex2f(fx + 105, fy - 5);
			glVertex2f(fx + 100, fy);
			glVertex2f(fx, fy);
		glEnd();

		// --- Main House Body ---
		// Front Wall (subtle gradient, warmer tan)
		glBegin(GL_POLYGON);
			glColor3f(0.9f, 0.8f, 0.65f); glVertex2f(fx, fy + 100); // Top-left
			glColor3f(0.9f, 0.8f, 0.65f); glVertex2f(fx + 100, fy + 100); // Top-right
			glColor3f(0.8f, 0.7f, 0.55f); glVertex2f(fx + 100, fy); // Bottom-right
			glColor3f(0.8f, 0.7f, 0.55f); glVertex2f(fx, fy); // Bottom-left
		glEnd();

		// Side Wall (left) - darker for depth
		glBegin(GL_POLYGON);
			glColor3f(0.7f, 0.6f, 0.45f); glVertex2f(fx, fy); // Front-bottom-left
			glColor3f(0.6f, 0.5f, 0.35f); glVertex2f(fx - 30, fy + 10); // Back-bottom-left
			glColor3f(0.6f, 0.5f, 0.35f); glVertex2f(fx - 30, fy + 110); // Back-top-left
			glColor3f(0.7f, 0.6f, 0.45f); glVertex2f(fx, fy + 100); // Front-top-left
		glEnd();

		// --- Roof ---
		// Front Roof (triangle) - Dark grey-brown with subtle red/brown tint
		glBegin(GL_TRIANGLES);
			glColor3f(0.4f, 0.35f, 0.35f); glVertex2f(fx, fy + 100); // left front
			glColor3f(0.4f, 0.35f, 0.35f); glVertex2f(fx + 100, fy + 100); // right front
			glColor3f(0.3f, 0.25f, 0.25f); glVertex2f(fx + 50, fy + 150); // roof peak
		glEnd();

		// Side Roof (left side) - Even darker shade for shadow
		glBegin(GL_POLYGON);
			glColor3f(0.3f, 0.25f, 0.25f); glVertex2f(fx, fy + 100); // front-left roof edge
			glColor3f(0.2f, 0.15f, 0.15f); glVertex2f(fx - 30, fy + 110); // back-left roof edge
			glColor3f(0.2f, 0.15f, 0.15f); glVertex2f(fx + 20, fy + 160); // peak-back-left
			glColor3f(0.3f, 0.25f, 0.25f); glVertex2f(fx + 50, fy + 150); // peak-front
		glEnd();

		// --- Chimney ---
		glColor3f(0.6f, 0.5f, 0.4f); // Brick-like color for chimney
		glBegin(GL_POLYGON);
			glVertex2f(fx + 10, fy + 150); // Base on roof
			glVertex2f(fx + 25, fy + 150);
			glVertex2f(fx + 25, fy + 170);
			glVertex2f(fx + 10, fy + 170);
		glEnd();
		// Chimney top (darker)
		glColor3f(0.3f, 0.25f, 0.2f);
		glBegin(GL_POLYGON);
			glVertex2f(fx + 8, fy + 170);
			glVertex2f(fx + 27, fy + 170);
			glVertex2f(fx + 27, fy + 172);
			glVertex2f(fx + 8, fy + 172);
		glEnd();

		// Smoke emission logic
		if (rand() % 5 < 3 && numSmokeParticles < MAX_SMOKE_PARTICLES) {
			SmokeParticle newSmoke;
			newSmoke.initialX = fx + 17.5f + (rand() % 5 - 2);
			newSmoke.x = newSmoke.initialX;
			newSmoke.y = fy + 175;
			newSmoke.size = 5.0f + (rand() % 5);
			newSmoke.alpha = 0.6f;
			newSmoke.speedY = 0.5f + (rand() % 50) / 100.0f;
			newSmoke.speedX = (rand() % 50 - 25) / 100.0f;
			newSmoke.life = 0.0f;
			smokeParticles[numSmokeParticles++] = newSmoke;
		}

		// --- Door ---
		glColor3f(0.55f, 0.27f, 0.07f);
		glBegin(GL_POLYGON);
			glVertex2f(fx + 40, fy);
			glVertex2f(fx + 60, fy);
			glVertex2f(fx + 60, fy + 70);
			glVertex2f(fx + 40, fy + 70);
		glEnd();
		glColor3f(0.8f, 0.8f, 0.0f);
		drawFilledEllipseS(fx + 55, fy + 45, 2, 2, 1.0f, 0.8f, 0.8f, 0.0f);
		glColor3f(0.3f, 0.15f, 0.05f);
		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(fx + 40, fy);
			glVertex2f(fx + 60, fy);
			glVertex2f(fx + 60, fy + 70);
			glVertex2f(fx + 40, fy + 70);
		glEnd();
		glLineWidth(1.0);

		// --- Windows ---
		glColor4f(0.6f, 0.7f, 0.8f, 0.7f);
		glBegin(GL_POLYGON); // Left front window
			glVertex2f(fx + 10, fy + 55);
			glVertex2f(fx + 30, fy + 55);
			glVertex2f(fx + 30, fy + 85);
			glVertex2f(fx + 10, fy + 85);
		glEnd();
		glBegin(GL_POLYGON); // Right front window
			glVertex2f(fx + 70, fy + 55);
			glVertex2f(fx + 90, fy + 55);
			glVertex2f(fx + 90, fy + 85);
			glVertex2f(fx + 70, fy + 85);
		glEnd();
		glBegin(GL_POLYGON); // Side window (left)
			glVertex2f(fx - 20, fy + 63);
			glVertex2f(fx - 10, fy + 60);
			glVertex2f(fx - 10, fy + 90);
			glVertex2f(fx - 20, fy + 93);
		glEnd();

		glColor3f(0.3f, 0.15f, 0.05f);
		glLineWidth(1.5);
		glBegin(GL_LINE_LOOP); // Left front frame
			glVertex2f(fx + 10, fy + 55); glVertex2f(fx + 30, fy + 55);
			glVertex2f(fx + 30, fy + 85); glVertex2f(fx + 10, fy + 85);
		glEnd();
		glBegin(GL_LINES); // Left front panes
			glVertex2f(fx + 20, fy + 55); glVertex2f(fx + 20, fy + 85);
			glVertex2f(fx + 10, fy + 70); glVertex2f(fx + 30, fy + 70);
		glEnd();

		glBegin(GL_LINE_LOOP); // Right front frame
			glVertex2f(fx + 70, fy + 55); glVertex2f(fx + 90, fy + 55);
			glVertex2f(fx + 90, fy + 85); glVertex2f(fx + 70, fy + 85);
		glEnd();
		glBegin(GL_LINES); // Right front panes
			glVertex2f(fx + 80, fy + 55); glVertex2f(fx + 80, fy + 85);
			glVertex2f(fx + 70, fy + 70); glVertex2f(fx + 90, fy + 70);
		glEnd();

		glBegin(GL_LINE_LOOP); // Side window frame
			glVertex2f(fx - 20, fy + 63); glVertex2f(fx - 10, fy + 60);
			glVertex2f(fx - 10, fy + 90); glVertex2f(fx - 20, fy + 93);
		glEnd();
		glBegin(GL_LINES); // Side window panes
			glVertex2f(fx - 15, fy + 61.5f); glVertex2f(fx - 15, fy + 91.5f);
			glVertex2f(fx - 20, fy + 78); glVertex2f(fx - 10, fy + 75);
		glEnd();
		glLineWidth(1.0);
    }

    void drawBarnS() {
        float bx = 50, by = 120;

        glColor3f(0.4f, 0.35f, 0.3f);
        glBegin(GL_POLYGON);
            glVertex2f(bx - 5, by - 5);
            glVertex2f(bx + 105, by - 5);
            glVertex2f(bx + 100, by);
            glVertex2f(bx, by);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f(0.8f, 0.1f, 0.1f); glVertex2f(bx, by + 90);
            glColor3f(0.8f, 0.1f, 0.1f); glVertex2f(bx + 100, by + 90);
            glColor3f(0.7f, 0.08f, 0.08f); glVertex2f(bx + 100, by);
            glColor3f(0.7f, 0.08f, 0.08f); glVertex2f(bx, by);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f(0.6f, 0.08f, 0.08f); glVertex2f(bx, by);
            glColor3f(0.5f, 0.06f, 0.06f); glVertex2f(bx - 30, by + 10);
            glColor3f(0.5f, 0.06f, 0.06f); glVertex2f(bx - 30, by + 100);
            glColor3f(0.6f, 0.08f, 0.08f); glVertex2f(bx, by + 90);
        glEnd();

        glColor3f(0.6f, 0.05f, 0.05f);
        glLineWidth(1.0);
        glBegin(GL_LINES);
            for(int i = 0; i <= 10; ++i) {
                glVertex2f(bx + i * 10, by); glVertex2f(bx + i * 10, by + 90);
                glVertex2f(bx - 30 + i * 3, by + 10); glVertex2f(bx - 30 + i * 3, by + 100);
            }
        glEnd();
        glLineWidth(1.0);

        glBegin(GL_POLYGON);
            glColor3f(0.35f, 0.3f, 0.3f); glVertex2f(bx, by + 90);
            glColor3f(0.35f, 0.3f, 0.3f); glVertex2f(bx + 100, by + 90);
            glColor3f(0.25f, 0.2f, 0.2f); glVertex2f(bx + 50, by + 140);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f(0.25f, 0.2f, 0.2f); glVertex2f(bx, by + 90);
            glColor3f(0.15f, 0.1f, 0.1f); glVertex2f(bx - 30, by + 100);
            glColor3f(0.15f, 0.1f, 0.1f); glVertex2f(bx + 20, by + 150);
            glColor3f(0.25f, 0.2f, 0.2f); glVertex2f(bx + 50, by + 140);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f(0.55f, 0.27f, 0.07f); glVertex2f(bx + 5, by + 85);
            glColor3f(0.55f, 0.27f, 0.07f); glVertex2f(bx + 50, by + 85);
            glColor3f(0.45f, 0.2f, 0.05f); glVertex2f(bx + 50, by);
            glColor3f(0.45f, 0.2f, 0.05f); glVertex2f(bx + 5, by);
        glEnd();
        glBegin(GL_POLYGON);
            glColor3f(0.55f, 0.27f, 0.07f); glVertex2f(bx + 50, by + 85);
            glColor3f(0.55f, 0.27f, 0.07f); glVertex2f(bx + 95, by + 85);
            glColor3f(0.45f, 0.2f, 0.05f); glVertex2f(bx + 95, by);
            glColor3f(0.45f, 0.2f, 0.05f); glVertex2f(bx + 50, by);
        glEnd();

        glColor3f(0.3f, 0.15f, 0.05f);
        glLineWidth(3.0);
        glBegin(GL_LINES);
            glVertex2f(bx + 5, by); glVertex2f(bx + 50, by + 85);
            glVertex2f(bx + 50, by); glVertex2f(bx + 5, by + 85);
            glVertex2f(bx + 50, by); glVertex2f(bx + 95, by + 85);
            glVertex2f(bx + 95, by); glVertex2f(bx + 50, by + 85);
        glEnd();
        glLineWidth(1.0);
    }

    void drawTreeS(float x, float y, float scale) {
        float trunk_base_w = 15 * scale;
        float trunk_top_w = 8 * scale;
        float trunk_h = 80 * scale;
        float canopy_r_max = 60 * scale;

        glColor3f(0.45f, 0.22f, 0.05f);
        glBegin(GL_POLYGON);
            glVertex2f(x - trunk_base_w / 2, y);
            glVertex2f(x + trunk_base_w / 2, y);
            glVertex2f(x + trunk_top_w / 2 + 2 * scale, y + trunk_h * 0.4f);
            glVertex2f(x - trunk_top_w / 2 - 2 * scale, y + trunk_h * 0.4f);
        glEnd();

        glColor3f(0.55f, 0.27f, 0.07f);
        glBegin(GL_POLYGON);
            glVertex2f(x - trunk_top_w / 2 * 0.8f, y + trunk_h * 0.4f);
            glVertex2f(x + trunk_top_w / 2 * 0.8f, y + trunk_h * 0.4f);
            glVertex2f(x + trunk_top_w / 2 * 0.8f, y + trunk_h);
            glVertex2f(x - trunk_top_w / 2 * 0.8f, y + trunk_h);
        glEnd();

        glColor3f(0.4f, 0.2f, 0.05f);
        glLineWidth(2.0);
        glBegin(GL_POLYGON);
            glVertex2f(x - trunk_top_w / 2 * 0.8f, y + trunk_h * 0.7f);
            glVertex2f(x - trunk_top_w / 1.5f, y + trunk_h * 0.8f);
            glVertex2f(x - trunk_top_w * 2.5f, y + trunk_h * 1.1f);
            glVertex2f(x - trunk_top_w * 2, y + trunk_h * 1.0f);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2f(x + trunk_top_w / 2 * 0.8f, y + trunk_h * 0.6f);
            glVertex2f(x + trunk_top_w * 1.2f, y + trunk_h * 0.7f);
            glVertex2f(x + trunk_top_w * 2.0f, y + trunk_h * 0.9f);
            glVertex2f(x + trunk_top_w * 1.5f, y + trunk_h * 0.8f);
        glEnd();
        glLineWidth(1.0);

        drawFilledEllipseS(x + 5 * scale, y + trunk_h + 30 * scale, canopy_r_max * 0.8f, canopy_r_max * 0.7f, 0.8f, 0.05f, 0.4f, 0.05f, 24);
        drawFilledEllipseS(x + 10 * scale, y + trunk_h + 45 * scale, canopy_r_max, canopy_r_max * 0.9f, 0.85f, 0.1f, 0.6f, 0.1f, 28);
        drawFilledEllipseS(x - 15 * scale, y + trunk_h + 35 * scale, canopy_r_max * 0.7f, canopy_r_max * 0.8f, 0.88f, 0.15f, 0.65f, 0.15f, 26);
        drawFilledEllipseS(x + 25 * scale, y + trunk_h + 30 * scale, canopy_r_max * 0.6f, canopy_r_max * 0.65f, 0.87f, 0.12f, 0.62f, 0.12f, 25);
        drawFilledEllipseS(x + 20 * scale, y + trunk_h + 55 * scale, canopy_r_max * 0.7f, canopy_r_max * 0.65f, 0.9f, 0.2f, 0.7f, 0.2f, 24);
        drawFilledEllipseS(x - 5 * scale, y + trunk_h + 60 * scale, canopy_r_max * 0.5f, canopy_r_max * 0.55f, 0.9f, 0.25f, 0.75f, 0.25f, 22);
        drawFilledEllipseS(x + 30 * scale, y + trunk_h + 70 * scale, canopy_r_max * 0.3f, canopy_r_max * 0.28f, 0.95f, 0.4f, 0.85f, 0.4f, 18);
        drawFilledEllipseS(x + 5 * scale, y + trunk_h + 75 * scale, canopy_r_max * 0.35f, canopy_r_max * 0.32f, 0.95f, 0.45f, 0.9f, 0.45f, 19);
        drawFilledEllipseS(x - 20 * scale, y + trunk_h + 65 * scale, canopy_r_max * 0.25f, canopy_r_max * 0.22f, 0.95f, 0.4f, 0.88f, 0.4f, 17);
    }

    void drawHillsS() {
        glBegin(GL_POLYGON);
            glColor3f(S_FOG_R * 0.7f, S_FOG_G * 0.7f, S_FOG_B * 0.7f);
            glVertex2f(0, S_HEIGHT * 0.4f);
            glVertex2f(S_WIDTH * 0.2f, S_HEIGHT * 0.5f);
            glVertex2f(S_WIDTH * 0.4f, S_HEIGHT * 0.45f);
            glVertex2f(S_WIDTH * 0.6f, S_HEIGHT * 0.52f);
            glVertex2f(S_WIDTH * 0.8f, S_HEIGHT * 0.47f);
            glVertex2f(S_WIDTH, S_HEIGHT * 0.5f);
            glVertex2f(S_WIDTH, S_HEIGHT * 0.2f);
            glVertex2f(0, S_HEIGHT * 0.2f);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f(0.5f, 0.6f, 0.5f);
            glVertex2f(0, S_HEIGHT * 0.3f);
            glVertex2f(S_WIDTH * 0.1f, S_HEIGHT * 0.35f);
            glVertex2f(S_WIDTH * 0.3f, S_HEIGHT * 0.32f);
            glVertex2f(S_WIDTH * 0.5f, S_HEIGHT * 0.4f);
            glVertex2f(S_WIDTH * 0.7f, S_HEIGHT * 0.38f);
            glVertex2f(S_WIDTH * 0.9f, S_HEIGHT * 0.32f);
            glVertex2f(S_WIDTH, S_HEIGHT * 0.3f);
            glVertex2f(S_WIDTH, S_HEIGHT * 0.2f);
            glVertex2f(0, S_HEIGHT * 0.2f);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f(0.3f, 0.5f, 0.2f);
            glVertex2f(0, S_HEIGHT * 0.25f);
            glVertex2f(S_WIDTH * 0.15f, S_HEIGHT * 0.28f);
            glVertex2f(S_WIDTH * 0.35f, S_HEIGHT * 0.26f);
            glVertex2f(S_WIDTH * 0.55f, S_HEIGHT * 0.32f);
            glVertex2f(S_WIDTH * 0.75f, S_HEIGHT * 0.3f);
            glVertex2f(S_WIDTH, S_HEIGHT * 0.28f);
            glVertex2f(S_WIDTH, S_HEIGHT * 0.2f);
            glVertex2f(0, S_HEIGHT * 0.2f);
        glEnd();
    }

    void drawFenceS() {
        float fenceBaseY = S_HEIGHT * 0.12f;
        float postHeight = 30.0f;
        float postWidth = 5.0f;
        float postSpacing = 50.0f;

        glColor3f(0.6f, 0.4f, 0.2f);

        for (float x = 0; x < S_WIDTH; x += postSpacing) {
            glBegin(GL_POLYGON);
                glVertex2f(x, fenceBaseY);
                glVertex2f(x + postWidth, fenceBaseY);
                glVertex2f(x + postWidth * 0.8f, fenceBaseY + postHeight);
                glVertex2f(x + postWidth * 0.2f, fenceBaseY + postHeight);
            glEnd();
        }

        glColor3f(0.5f, 0.3f, 0.15f);
        glLineWidth(2.0);

        float railThickness = 5.0f;

        glBegin(GL_POLYGON);
            glVertex2f(0, fenceBaseY + postHeight * 0.7f - railThickness / 2);
            glVertex2f(S_WIDTH, fenceBaseY + postHeight * 0.7f - railThickness / 2);
            glVertex2f(S_WIDTH, fenceBaseY + postHeight * 0.7f + railThickness / 2);
            glVertex2f(0, fenceBaseY + postHeight * 0.7f + railThickness / 2);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex2f(0, fenceBaseY + postHeight * 0.3f - railThickness / 2);
            glVertex2f(S_WIDTH, fenceBaseY + postHeight * 0.3f - railThickness / 2);
            glVertex2f(S_WIDTH, fenceBaseY + postHeight * 0.3f + railThickness / 2);
            glVertex2f(0, fenceBaseY + postHeight * 0.3f + railThickness / 2);
        glEnd();

        glLineWidth(1.0);
    }

    void drawSmokeParticleS(float x, float y, float size, float alpha) {
        drawFilledEllipseS(x, y, size, size * 0.7f, alpha, 0.7f, 0.7f, 0.7f, 10);
    }


    void displayS() {
        glClear(GL_COLOR_BUFFER_BIT);

        drawGradientRectangleS(0, S_HEIGHT * 0.5f, S_WIDTH, S_HEIGHT,
                              0.6f, 0.8f, 1.0f,
                              0.8f, 0.9f, 1.0f);

        glColor4f(S_FOG_R, S_FOG_G, S_FOG_B, 0.5f);
        glBegin(GL_POLYGON);
            glVertex2f(0, S_HEIGHT * 0.2f);
            glVertex2f(S_WIDTH, S_HEIGHT * 0.2f);
            glVertex2f(S_WIDTH, S_HEIGHT * 0.25f);
            glVertex2f(0, S_HEIGHT * 0.25f);
        glEnd();

        drawHillsS();

        glBegin(GL_POLYGON);
            glColor3f(0.4f, 0.6f, 0.2f);
            glVertex2f(0, 0);
            glVertex2f(S_WIDTH, 0);
            glColor3f(0.45f, 0.65f, 0.25f);
            glVertex2f(S_WIDTH, S_HEIGHT * 0.2f);
            glVertex2f(0, S_HEIGHT * 0.2f);
        glEnd();

        srand(1);
        for(int i = 0; i < 50; ++i) {
            float grass_x = (float)(rand() % S_WIDTH);
            float grass_y = (float)(rand() % (int)(S_HEIGHT * 0.18)) + S_HEIGHT * 0.12f;
            float grass_r = 3 + (float)(rand() % 5);
            float grass_g = 0.35f + (float)(rand() % 20) / 100.0f;
            float grass_b = 0.55f + (float)(rand() % 15) / 100.0f;
            float grass_a = 0.9f + (float)(rand() % 10) / 100.0f;
            drawFilledEllipseS(grass_x, grass_y, grass_r, grass_r * 0.8f, grass_a, grass_g, grass_b, 0.2f, 12);
        }
        srand(time(NULL));

        drawSunS(S_WIDTH - 100, S_HEIGHT - 100, 50);

        for (int i = 0; i < numClouds; ++i) {
            drawCloudS(clouds[i].x, clouds[i].y, clouds[i].alpha);
        }

        drawBarnS();
        drawFarmHouseS();

        for (int i = 0; i < numSmokeParticles; ++i) {
            drawSmokeParticleS(smokeParticles[i].x, smokeParticles[i].y, smokeParticles[i].size, smokeParticles[i].alpha);
        }

        drawWindTurbineS();
        drawTreeS(S_WIDTH * 0.6f, S_HEIGHT * 0.15f, 1.2f);
        drawTreeS(S_WIDTH * 0.7f, S_HEIGHT * 0.12f, 1.0f);
        drawTreeS(S_WIDTH * 0.85f, S_HEIGHT * 0.1f, 0.9f);
        drawTreeS(S_WIDTH * 0.45f, S_HEIGHT * 0.18f, 1.1f);
        drawFenceS();

        glBegin(GL_POLYGON);
            glColor3f(0.2f, 0.2f, 0.2f); glVertex2f(0, 0);
            glColor3f(0.2f, 0.2f, 0.2f); glVertex2f(S_WIDTH, 0);
            glColor3f(0.3f, 0.3f, 0.3f); glVertex2f(S_WIDTH, S_HEIGHT * 0.12f);
            glColor3f(0.3f, 0.3f, 0.3f); glVertex2f(0, S_HEIGHT * 0.12f);
        glEnd();

        drawDashedRoadLineS();
        drawRedCartoonCarS(carPosition, S_HEIGHT * 0.08f);

        glutSwapBuffers();
    }

    void updateS(int value) {
        if (currentScene != 1) { // Only update if this is the current scene
            glutTimerFunc(16, masterUpdate, 0);
            return;
        }

        bladeAngle += 2.0f;
        if (bladeAngle > 360) bladeAngle -= 360;

        for (int i = 0; i < numClouds; ++i) {
            clouds[i].x -= clouds[i].speed;
            if (clouds[i].x < -150) {
                clouds[i].x = S_WIDTH + (rand() % 100);
                clouds[i].y = (float)(rand() % (S_HEIGHT / 4)) + (S_HEIGHT * 0.7f);
                clouds[i].speed = 0.2f + (float)(rand() % 50) / 100.0f;
                clouds[i].alpha = 0.8f + (float)(rand() % 20) / 100.0f;
            }
        }

        if (carPosition < S_WIDTH + 50) {
            carPosition += 3.0f;
        }

        int i = 0;
        while (i < numSmokeParticles) {
            smokeParticles[i].y += smokeParticles[i].speedY;
            smokeParticles[i].x += (rand() % 3 - 1.0f) * 0.5f;
            smokeParticles[i].alpha -= 0.01f;
            smokeParticles[i].size += 0.3f;
            smokeParticles[i].speedY *= 0.98f;
            if (smokeParticles[i].speedY < 0.1f) smokeParticles[i].speedY = 0.1f;
            smokeParticles[i].life += 0.015f;
            if (smokeParticles[i].alpha <= 0.0f || smokeParticles[i].y > S_HEIGHT + 100 || smokeParticles[i].life >= 1.0f) {
                smokeParticles[i] = smokeParticles[numSmokeParticles - 1];
                numSmokeParticles--;
            } else {
                ++i;
            }
        }

        glutPostRedisplay();
        glutTimerFunc(16, masterUpdate, 0);
    }

    void initS() {
        glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, S_WIDTH, 0, S_HEIGHT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_LINE_SMOOTH);
        srand(time(NULL));
    }
}

// =================================================================
// --- SCENE Z (FROM main_z.cpp) --- This is now Scene 3
// =================================================================
namespace SceneZ {
	const GLfloat PI_CONSTANT = static_cast<GLfloat>(M_PI);

	const int Z_WINDOW_WIDTH = 793;
	const int Z_WINDOW_HEIGHT = 556;

	// Layer Y-coordinates
	const GLfloat WATER_BOTTOM_Y = 0.0f;
	const GLfloat WATER_TOP_Y = 130.0f;
	const GLfloat BRIDGE_BOTTOM_Y = WATER_TOP_Y;
	const GLfloat BRIDGE_TOP_Y = BRIDGE_BOTTOM_Y + 80.0f;

	// Barrier properties
	const GLfloat BARRIER_COLOR_R = 228.0f / 255.0f;
	const GLfloat BARRIER_COLOR_G = 177.0f / 255.0f;
	const GLfloat BARRIER_COLOR_B = 93.0f / 255.0f;
	const GLfloat BARRIER_HEIGHT = 15.0f;
	const GLfloat BARRIER_LINE_THICKNESS = 2.0f;
	const GLfloat BARRIER_VERTICAL_LINE_WIDTH = 2.0f;
	const GLfloat BARRIER_VERTICAL_LINE_SPACING = 15.0f;

	const GLfloat ROAD_BOTTOM_Y = BRIDGE_TOP_Y;
	const GLfloat ROAD_TOP_Y = ROAD_BOTTOM_Y + 50.0f;
	const GLfloat SKY_BOTTOM_Y = ROAD_TOP_Y;
	const GLfloat SKY_TOP_Y = (GLfloat)Z_WINDOW_HEIGHT;

	// Arch properties
	const int NUM_ARCHES = 4;
	const GLfloat ARCH_RADIUS = 55.0f;
	const int ARCH_SEGMENTS = 50;
	const GLfloat ARCH_START_OFFSET = 80.0f;
	const GLfloat ARCH_DISTANCE = 200.0f;

	// Road stripe properties
	const GLfloat ROAD_STRIPE_LEN = 30.0f;
	const GLfloat ROAD_STRIPE_GAP = 20.0f;
	const GLfloat ROAD_STRIPE_WIDTH = 2.0f;

	// Water stripe properties
	const GLfloat WATER_STRIPE_MIN_LEN = 20.0f;
	const GLfloat WATER_STRIPE_MAX_LEN = 60.0f;
	const GLfloat WATER_STRIPE_MIN_GAP = 10.0f;
	const GLfloat WATER_STRIPE_MAX_GAP = 50.0f;
	const GLfloat WATER_STRIPE_WIDTH = 3.0f;
	const GLfloat WATER_STRIPE_VERT_SPACING = 15.0f;
	const GLfloat WATER_STRIPE_RANDOM_Y_MAX = 2.0f;
	const GLfloat WATER_STRIPE_DENSITY_FACTOR = 1.5f;
	GLfloat waterStripeAnimationX = 0.0f;
	const GLfloat WATER_STRIPE_FLOW_SPEED = 0.2f;

	// Foreground ground properties
	const GLfloat FG_GROUND_PEAK_HEIGHT = 50.0f;
	const GLfloat GROUND_SINK_OFFSET = 2.0f;

	// Tree/Bush properties
	const GLfloat TREE_TRUNK_W = 10.0f;
	const GLfloat TREE_TRUNK_H = 60.0f;
	const GLfloat TREE_LEAVES_R = 30.0f;
	const int TREE_LEAVES_SEG = 20;
	const GLfloat TREE1_X = Z_WINDOW_WIDTH * 0.55f;
	const GLfloat TREE2_X = Z_WINDOW_WIDTH * 0.62f;
	const GLfloat TREE3_X = Z_WINDOW_WIDTH * 0.70f;
	const GLfloat TREE4_X = Z_WINDOW_WIDTH * 0.78f;
	const GLfloat TREE5_X = Z_WINDOW_WIDTH * 0.86f;
	const GLfloat TREE6_X = Z_WINDOW_WIDTH * 0.94f;
	const GLfloat BUSH1_X = Z_WINDOW_WIDTH * 0.58f;
	const GLfloat BUSH1_W = 120.0f;
	const GLfloat BUSH1_H = 50.0f;
	const GLfloat BUSH2_X = Z_WINDOW_WIDTH * 0.75f;
	const GLfloat BUSH2_W = 100.0f;
	const GLfloat BUSH2_H = 40.0f;
	const GLfloat BUSH_COLOR_R = 5.0f / 255.0f;
	const GLfloat BUSH_COLOR_G = 46.0f / 255.0f;
	const GLfloat BUSH_COLOR_B = 32.0f / 255.0f;
	float leafOffset = 0.0f;

	// Bridge stripe colors and structure
	const GLfloat BRIDGE_STRIPE_COLOR1_R = 165.0f / 255.0f;
	const GLfloat BRIDGE_STRIPE_COLOR1_G = 117.0f / 255.0f;
	const GLfloat BRIDGE_STRIPE_COLOR1_B = 43.0f / 255.0f;
	const GLfloat BRIDGE_STRIPE_COLOR2_R = 215.0f / 255.0f;
	const GLfloat BRIDGE_STRIPE_COLOR2_G = 158.0f / 255.0f;
	const GLfloat BRIDGE_STRIPE_COLOR2_B = 54.0f / 255.0f;
	struct BridgeStripe {
		GLfloat x, y, length, width;
		GLfloat color_r, color_g, color_b;
	};
	const int NUM_STATIC_BRIDGE_STRIPES = 5;
	BridgeStripe staticBridgeStripes[NUM_STATIC_BRIDGE_STRIPES];

	// Car dimensions (original values for scaling reference)
	const GLfloat ORIGINAL_CAR_BODY_WIDTH = 120.0f;
	const GLfloat ORIGINAL_CAR_BODY_HEIGHT = 40.0f; // Used for scaling factor calculation
	const GLfloat ORIGINAL_CAR_WHEEL_OUTER_RADIUS = 12.0f;
	const GLfloat CAR_SCALE_FACTOR = (ROAD_TOP_Y - ROAD_BOTTOM_Y) / 3.0f / ORIGINAL_CAR_BODY_HEIGHT;
	const GLfloat SCALED_CAR_BODY_WIDTH = ORIGINAL_CAR_BODY_WIDTH * CAR_SCALE_FACTOR;
	const int MAX_CARS = 20;
	struct Car {
		GLfloat x, y, speed, wheelAngle;
		GLfloat carColorR, carColorG, carColorB;
		int direction; // 1 for L-R, -1 for R-L
	};
	Car cars[MAX_CARS];
	const GLfloat MIN_CAR_SPEED = 0.8f;
	const GLfloat MAX_CAR_SPEED = 3.0f;
	const GLfloat WHEEL_ROTATION_FACTOR = 0.5f;
	const int SPEED_CHANGE_INTERVAL = 300;
	int timerTickCount = 0;
	const GLfloat HEADLIGHT_ORIGINAL_OFFSET_X = 115.0f;
	const GLfloat HEADLIGHT_ORIGINAL_OFFSET_Y = 15.0f;
	const GLfloat HEADLIGHT_ORIGINAL_WIDTH = 8.0f;
	const GLfloat HEADLIGHT_ORIGINAL_HEIGHT = 5.0f;
	const GLfloat HEADLIGHT_COLOR_R = 1.0f;
	const GLfloat HEADLIGHT_COLOR_G = 1.0f;
	const GLfloat HEADLIGHT_COLOR_B = 0.8f;
	const GLfloat SHADOW_ORIGINAL_OFFSET_X = 10.0f;
	const GLfloat SHADOW_ORIGINAL_OFFSET_Y = -15.0f;
	const GLfloat SHADOW_ORIGINAL_WIDTH_FACTOR = 0.9f;
	const GLfloat SHADOW_ORIGINAL_HEIGHT = 5.0f;
	const GLfloat SHADOW_COLOR_A = 0.4f;

	// Cityscape colors
	const GLfloat CITYSCAPE_COLOR1_R = 85.0f / 255.0f, CITYSCAPE_COLOR1_G = 131.0f / 255.0f, CITYSCAPE_COLOR1_B = 129.0f / 255.0f;
	const GLfloat CITYSCAPE_COLOR2_R = 141.0f / 255.0f, CITYSCAPE_COLOR2_G = 171.0f / 255.0f, CITYSCAPE_COLOR2_B = 168.0f / 255.0f;
	const GLfloat CITYSCAPE_COLOR3_R = 177.0f / 255.0f, CITYSCAPE_COLOR3_G = 196.0f / 255.0f, CITYSCAPE_COLOR3_B = 196.0f / 255.0f;
	const GLfloat GILDED_COLOR_1_R = 155.0f / 255.0f, GILDED_COLOR_1_G = 115.0f / 255.0f, GILDED_COLOR_1_B = 56.0f / 255.0f;
	const GLfloat GILDED_COLOR_2_R = 203.0f / 255.0f, GILDED_COLOR_2_G = 171.0f / 255.0f, GILDED_COLOR_2_B = 120.0f / 255.0f;
	const GLfloat GILDED_COLOR_3_R = 243.0f / 255.0f, GILDED_COLOR_3_G = 226.0f / 255.0f, GILDED_COLOR_3_B = 206.0f / 255.0f;
	const GLfloat VICTORIAN_COLOR_1_R = 199.0f / 255.0f, VICTORIAN_COLOR_1_G = 170.0f / 255.0f, VICTORIAN_COLOR_1_B = 140.0f / 255.0f;
	const GLfloat VICTORIAN_COLOR_2_R = 181.0f / 255.0f, VICTORIAN_COLOR_2_G = 139.0f / 255.0f, VICTORIAN_COLOR_2_B = 78.0f / 255.0f;
	const GLfloat VICTORIAN_COLOR_3_R = 72.0f / 255.0f, VICTORIAN_COLOR_3_G = 48.0f / 255.0f, VICTORIAN_COLOR_3_B = 24.0f / 255.0f;
	const GLfloat VICTORIAN_COLOR_4_R = 147.0f / 255.0f, VICTORIAN_COLOR_4_G = 116.0f / 255.0f, VICTORIAN_COLOR_4_B = 91.0f / 255.0f;
	const GLfloat VICTORIAN_COLOR_5_R = 136.0f / 255.0f, VICTORIAN_COLOR_5_G = 107.0f / 255.0f, VICTORIAN_COLOR_5_B = 91.0f / 255.0f;

	// Building types
	const int BUILDING_TYPE_RECT = 0;
	const int BUILDING_TYPE_SETBACK = 1;
	const int BUILDING_TYPE_POINTED = 2;
	const int BUILDING_TYPE_GILDED = 3;
	const int BUILDING_TYPE_VICTORIAN = 4;
	struct Building {
		GLfloat x, y, width, height;
		GLfloat colorR, colorG, colorB;
		int type;
	};
	const int NUM_BUILDINGS = 40;
	Building buildings[NUM_BUILDINGS];

	// Cloud properties
	const int MAX_CLOUD_PACKS = 7;
	const int MAX_CLOUDS_PER_PACK_MAX = 4;
	const GLfloat CLOUD_PACK_SPEED_MIN = 0.3f;
	const GLfloat CLOUD_PACK_SPEED_MAX = 1.0f;
	struct CloudZ {
		GLfloat x_offset, y_offset, size;
		GLfloat r, g, b, a;
	};
	struct CloudPack {
		GLfloat base_x, base_y, speed;
		int numCloudsInPack;
		CloudZ individualClouds[MAX_CLOUDS_PER_PACK_MAX];
	};
	CloudPack cloudPacks[MAX_CLOUD_PACKS];


	const int MAX_BIRD_GROUPS = 5;
	const int MAX_BIRDS_PER_GROUP = 10;
	const GLfloat BIRD_GROUP_SPEED_MIN = 1.5f;
	const GLfloat BIRD_GROUP_SPEED_MAX = 4.0f;
	const GLfloat BIRD_SIZE = 5.0f;
	const GLfloat WING_FLAP_SPEED = 0.1f;
	struct BirdZ {
		GLfloat x_offset, y_offset, wing_angle;
	};
	struct BirdGroup {
		GLfloat base_x, base_y, speed;
		int direction, numBirdsInGroup;
		BirdZ individualBirds[MAX_BIRDS_PER_GROUP];
	};
	BirdGroup birdGroups[MAX_BIRD_GROUPS];


	const GLfloat SUNSET_HORIZON_R = 255.0f / 255.0f, SUNSET_HORIZON_G = 100.0f / 255.0f, SUNSET_HORIZON_B = 0.0f / 255.0f;
	const GLfloat SUNSET_TOP_R = 150.0f / 255.0f, SUNSET_TOP_G = 200.0f / 255.0f, SUNSET_TOP_B = 255.0f / 255.0f;
	const GLfloat CLOUD_COLOR_BASE_R = 0.95f, CLOUD_COLOR_BASE_G = 0.95f, CLOUD_COLOR_BASE_B = 0.95f;
	const GLfloat CLOUD_COLOR_SHADE_R = 0.8f, CLOUD_COLOR_SHADE_G = 0.8f, CLOUD_COLOR_SHADE_B = 0.8f;
	const GLfloat SUN_RADIUS = 40.0f;
	const GLfloat SUN_COLOR_R = 255.0f / 255.0f, SUN_COLOR_G = 100.0f / 255.0f, SUN_COLOR_B = 0.0f / 255.0f;


	void drawFilledArchZ(GLfloat centerX, GLfloat bottomY, GLfloat radius, int segments);
	void drawCloudZ(GLfloat x, GLfloat y, GLfloat size, GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void drawSunZ(GLfloat centerX, GLfloat centerY, GLfloat radius, int segments);
	void drawBirdZ(GLfloat x, GLfloat y, GLfloat wing_angle, int direction);
	GLfloat getGroundYAtX(GLfloat x_pos);


	GLfloat randomFloat(GLfloat min, GLfloat max) {
		return min + (static_cast<GLfloat>(rand()) / RAND_MAX) * (max - min);
	}


	void _drawCarShadowGeometryZ() {
		glColor4f(0.0f, 0.0f, 0.0f, SHADOW_COLOR_A);
		glBegin(GL_QUADS);
			glVertex2f(SHADOW_ORIGINAL_OFFSET_X * CAR_SCALE_FACTOR, SHADOW_ORIGINAL_OFFSET_Y * CAR_SCALE_FACTOR);
			glVertex2f((SHADOW_ORIGINAL_OFFSET_X + ORIGINAL_CAR_BODY_WIDTH * SHADOW_ORIGINAL_WIDTH_FACTOR) * CAR_SCALE_FACTOR, SHADOW_ORIGINAL_OFFSET_Y * CAR_SCALE_FACTOR);
			glVertex2f((SHADOW_ORIGINAL_OFFSET_X + ORIGINAL_CAR_BODY_WIDTH * SHADOW_ORIGINAL_WIDTH_FACTOR) * CAR_SCALE_FACTOR, (SHADOW_ORIGINAL_OFFSET_Y + SHADOW_ORIGINAL_HEIGHT) * CAR_SCALE_FACTOR);
			glVertex2f(SHADOW_ORIGINAL_OFFSET_X * CAR_SCALE_FACTOR, (SHADOW_ORIGINAL_OFFSET_Y + SHADOW_ORIGINAL_HEIGHT) * CAR_SCALE_FACTOR);
		glEnd();
	}


	void _drawCarHeadlightGeometryZ() {
		glColor3f(HEADLIGHT_COLOR_R, HEADLIGHT_COLOR_G, HEADLIGHT_COLOR_B);
		glBegin(GL_QUADS);
			glVertex2f(HEADLIGHT_ORIGINAL_OFFSET_X * CAR_SCALE_FACTOR, HEADLIGHT_ORIGINAL_OFFSET_Y * CAR_SCALE_FACTOR);
			glVertex2f((HEADLIGHT_ORIGINAL_OFFSET_X + HEADLIGHT_ORIGINAL_WIDTH) * CAR_SCALE_FACTOR, HEADLIGHT_ORIGINAL_OFFSET_Y * CAR_SCALE_FACTOR);
			glVertex2f((HEADLIGHT_ORIGINAL_OFFSET_X + HEADLIGHT_ORIGINAL_WIDTH) * CAR_SCALE_FACTOR, (HEADLIGHT_ORIGINAL_OFFSET_Y + HEADLIGHT_ORIGINAL_HEIGHT) * CAR_SCALE_FACTOR);
			glVertex2f(HEADLIGHT_ORIGINAL_OFFSET_X * CAR_SCALE_FACTOR, (HEADLIGHT_ORIGINAL_OFFSET_Y + HEADLIGHT_ORIGINAL_HEIGHT) * CAR_SCALE_FACTOR);
		glEnd();
	}


	void _drawCarBodyAndWheelsZ(float wheelAngle, GLfloat r, GLfloat g, GLfloat b) {
		glColor3f(r, g, b);
		glBegin(GL_POLYGON);
			glVertex2f(ORIGINAL_CAR_BODY_WIDTH * CAR_SCALE_FACTOR, 0);
			glVertex2f(0, 0);
			glVertex2f(0, 20 * CAR_SCALE_FACTOR);
			glVertex2f(20 * CAR_SCALE_FACTOR, 40 * CAR_SCALE_FACTOR);
			glVertex2f(80 * CAR_SCALE_FACTOR, 40 * CAR_SCALE_FACTOR);
			glVertex2f(100 * CAR_SCALE_FACTOR, 20 * CAR_SCALE_FACTOR);
			glVertex2f(ORIGINAL_CAR_BODY_WIDTH * CAR_SCALE_FACTOR, 20 * CAR_SCALE_FACTOR);
		glEnd();

		glColor3f(0.6f, 0.8f, 1.0f);
		glBegin(GL_POLYGON);
			glVertex2f(12 * CAR_SCALE_FACTOR, 22 * CAR_SCALE_FACTOR);
			glVertex2f(25 * CAR_SCALE_FACTOR, 38 * CAR_SCALE_FACTOR);
			glVertex2f(55 * CAR_SCALE_FACTOR, 38 * CAR_SCALE_FACTOR);
			glVertex2f(55 * CAR_SCALE_FACTOR, 22 * CAR_SCALE_FACTOR);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex2f(60 * CAR_SCALE_FACTOR, 22 * CAR_SCALE_FACTOR);
			glVertex2f(60 * CAR_SCALE_FACTOR, 38 * CAR_SCALE_FACTOR);
			glVertex2f(82 * CAR_SCALE_FACTOR, 38 * CAR_SCALE_FACTOR);
			glVertex2f(98 * CAR_SCALE_FACTOR, 22 * CAR_SCALE_FACTOR);
		glEnd();

		for (int i = 0; i < 2; i++) {

			float cx_original = (25.0f + i * 70.0f);
			float cy_original = -2.0f;
			float cx_scaled = cx_original * CAR_SCALE_FACTOR;
			float cy_scaled = cy_original * CAR_SCALE_FACTOR;
			float radiusOuter_scaled = ORIGINAL_CAR_WHEEL_OUTER_RADIUS * CAR_SCALE_FACTOR;
			float radiusInner_scaled = 6.0f * CAR_SCALE_FACTOR;
			glPushMatrix();
			glTranslatef(cx_scaled, cy_scaled, 0.0f);
			glRotatef(wheelAngle, 0.0f, 0.0f, 1.0f);

			glColor3f(0.0f, 0.0f, 0.0f);
			glBegin(GL_TRIANGLE_FAN);
				glVertex2f(0.0f, 0.0f);
				for (int j = 0; j <= 100; ++j) {
					float angle = 2.0f * PI_CONSTANT * j / 100.0f;
					glVertex2f(cos(angle) * radiusOuter_scaled, sin(angle) * radiusOuter_scaled);
				}
			glEnd();

			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_TRIANGLE_FAN);
				glVertex2f(0.0f, 0.0f);
				for (int j = 0; j <= 100; ++j) {
					float angle = 2.0f * PI_CONSTANT * j / 100.0f;
					glVertex2f(cos(angle) * radiusInner_scaled, sin(angle) * radiusInner_scaled);
				}
			glEnd();
			glPopMatrix();
		}
	}


	void drawAnimatedCarZ(float x, float y, float wheelAngle, GLfloat r, GLfloat g, GLfloat b, int direction) {
		glPushMatrix();
		glTranslatef(x, y, 0.0f);
		if (direction == -1) {
			glScalef(-1.0f, 1.0f, 1.0f);
			glTranslatef(-SCALED_CAR_BODY_WIDTH, 0.0f, 0.0f);
		}
		_drawCarShadowGeometryZ();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(x, y, 0.0f);
		if (direction == -1) {
			glScalef(-1.0f, 1.0f, 1.0f);
			glTranslatef(-SCALED_CAR_BODY_WIDTH, 0.0f, 0.0f);
		}
		_drawCarBodyAndWheelsZ(wheelAngle, r, g, b);
		_drawCarHeadlightGeometryZ();
		glPopMatrix();
	}


	void drawFilledArchZ(GLfloat centerX, GLfloat bottomY, GLfloat radius, int segments) {
		glBegin(GL_TRIANGLE_FAN);
			glVertex2f(centerX, bottomY);
			for (int i = 0; i <= segments; ++i) {
				float angle = PI_CONSTANT * i / segments;
				glVertex2f(centerX + radius * cos(angle), bottomY + radius * sin(angle));
			}
		glEnd();
	}

	void drawBuildingZ(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat r, GLfloat g, GLfloat b, int type) {
		glColor3f(r, g, b);
		if (type == BUILDING_TYPE_RECT) {
			glBegin(GL_QUADS);
				glVertex2f(x, y); glVertex2f(x + width, y);
				glVertex2f(x + width, y + height); glVertex2f(x, y + height);
			glEnd();
		} else if (type == BUILDING_TYPE_SETBACK) {
			GLfloat base_h = height * 0.7f, top_w = width * 0.7f, top_h = height * 0.3f, top_x_off = (width - top_w) / 2.0f;
			glBegin(GL_QUADS);
				glVertex2f(x, y); glVertex2f(x + width, y);
				glVertex2f(x + width, y + base_h); glVertex2f(x, y + base_h);
			glEnd();
			glBegin(GL_QUADS);
				glVertex2f(x + top_x_off, y + base_h); glVertex2f(x + top_x_off + top_w, y + base_h);
				glVertex2f(x + top_x_off + top_w, y + base_h + top_h); glVertex2f(x + top_x_off, y + base_h + top_h);
			glEnd();
		} else if (type == BUILDING_TYPE_POINTED) {
			GLfloat base_h = height * 0.85f, peak_h = height * 0.15f;
			glBegin(GL_QUADS);
				glVertex2f(x, y); glVertex2f(x + width, y);
				glVertex2f(x + width, y + base_h); glVertex2f(x, y + base_h);
			glEnd();
			glBegin(GL_TRIANGLES);
				glVertex2f(x, y + base_h); glVertex2f(x + width, y + base_h);
				glVertex2f(x + width / 2.0f, y + base_h + peak_h);
			glEnd();
		} else if (type == BUILDING_TYPE_GILDED) {
			glBegin(GL_QUADS);
				glVertex2f(x, y); glVertex2f(x + width, y);
				glVertex2f(x + width, y + height); glVertex2f(x, y + height);
			glEnd();
			GLfloat cornice_h = height * 0.08f, cornice_inset = width * 0.05f;
			glColor3f(r * 0.9f, g * 0.9f, b * 0.9f);
			glBegin(GL_QUADS);
				glVertex2f(x - cornice_inset, y + height - cornice_h); glVertex2f(x + width + cornice_inset, y + height - cornice_h);
				glVertex2f(x + width + cornice_inset, y + height); glVertex2f(x - cornice_inset, y + height);
			glEnd();
			GLfloat dome_r = width * 0.2f, dome_cx = x + width / 2.0f, dome_cy = y + height;
			glColor3f(r * 0.7f, g * 0.7f, b * 0.7f);
			drawFilledArchZ(dome_cx, dome_cy, dome_r, 20);
			glBegin(GL_QUADS);
				glVertex2f(dome_cx - dome_r, dome_cy); glVertex2f(dome_cx + dome_r, dome_cy);
				glVertex2f(dome_cx + dome_r, dome_cy + dome_r * 0.2f); glVertex2f(dome_cx - dome_r, dome_cy + dome_r * 0.2f);
			glEnd();
		} else if (type == BUILDING_TYPE_VICTORIAN) {
			glBegin(GL_QUADS);
				glVertex2f(x, y); glVertex2f(x + width, y);
				glVertex2f(x + width, y + height * 0.7f); glVertex2f(x, y + height * 0.7f);
			glEnd();
			glColor3f(r * 0.8f, g * 0.8f, b * 0.8f);
			glBegin(GL_TRIANGLES);
				glVertex2f(x, y + height * 0.7f); glVertex2f(x + width, y + height * 0.7f);
				glVertex2f(x + width / 2.0f, y + height);
			glEnd();
			GLfloat turret_w = width * 0.25f, turret_h = height * 0.3f, turret_x = x + width * 0.7f, turret_y = y + height * 0.5f;
			glColor3f(r * 0.95f, g * 0.95f, b * 0.95f);
			glBegin(GL_QUADS);
				glVertex2f(turret_x, turret_y); glVertex2f(turret_x + turret_w, turret_y);
				glVertex2f(turret_x + turret_w, turret_y + turret_h); glVertex2f(turret_x, turret_y + turret_h);
			glEnd();
			glColor3f(r * 0.7f, g * 0.7f, b * 0.7f);
			glBegin(GL_TRIANGLES);
				glVertex2f(turret_x, turret_y + turret_h); glVertex2f(turret_x + turret_w, turret_y + turret_h);
				glVertex2f(turret_x + turret_w / 2.0f, turret_y + turret_h + height * 0.1f);
			glEnd();
			GLfloat bay_w = width * 0.3f, bay_h = height * 0.2f, bay_x = x + width * 0.1f, bay_y = y + height * 0.1f;
			glColor3f(r * 0.9f, g * 0.9f, b * 0.9f);
			glBegin(GL_QUADS);
				glVertex2f(bay_x, bay_y); glVertex2f(bay_x + bay_w, bay_y);
				glVertex2f(bay_x + bay_w, bay_y + bay_h); glVertex2f(bay_x, bay_y + bay_h);
			glEnd();
		}

		glColor3f(r * 0.8f, g * 0.8f, b * 0.8f);
		GLfloat win_w = width * 0.1f, win_h = height * 0.07f, h_gap = width * 0.05f, v_gap = height * 0.05f;
		GLfloat win_top_bound = y + height;
		if (type == BUILDING_TYPE_SETBACK) win_top_bound = y + height * 0.7f;
		if (type == BUILDING_TYPE_POINTED) win_top_bound = y + height * 0.85f;
		if (type == BUILDING_TYPE_GILDED) win_top_bound = y + height - (height * 0.1f);
		if (type == BUILDING_TYPE_VICTORIAN) win_top_bound = y + height * 0.7f - v_gap;

		for (GLfloat cy = y + v_gap; cy < win_top_bound - win_h; cy += (win_h + v_gap)) {
			for (GLfloat cx = x + h_gap; cx < x + width - win_w; cx += (win_w + h_gap)) {
				if (type == BUILDING_TYPE_GILDED && (cy + win_h > y + height - (height * 0.1f))) continue;
				if (type == BUILDING_TYPE_VICTORIAN && (cy + win_h > y + height * 0.7f)) continue;
				glBegin(GL_QUADS);
					glVertex2f(cx, cy); glVertex2f(cx + win_w, cy);
					glVertex2f(cx + win_w, cy + win_h); glVertex2f(cx, cy + win_h);
				glEnd();
			}
		}
	}

	void drawTreeZ(GLfloat x, GLfloat y, bool isYellow) {
		glColor3f(139.0f / 255.0f, 69.0f / 255.0f, 19.0f / 255.0f);
		glBegin(GL_QUADS);
			glVertex2f(x - TREE_TRUNK_W / 2.0f, y); glVertex2f(x + TREE_TRUNK_W / 2.0f, y);
			glVertex2f(x + TREE_TRUNK_W / 2.0f, y + TREE_TRUNK_H); glVertex2f(x - TREE_TRUNK_W / 2.0f, y + TREE_TRUNK_H);
		glEnd();

		if (isYellow) glColor3f(255.0f / 255.0f, 165.0f / 255.0f, 0.0f / 255.0f);
		else glColor3f(210.0f / 255.0f, 105.0f / 255.0f, 30.0f / 255.0f);

		GLfloat base_leaves_y = y + TREE_TRUNK_H;

		auto drawLeafCircle = [&](GLfloat cx_offset, GLfloat cy_offset, GLfloat radius_scale) {
			glBegin(GL_TRIANGLE_FAN);
			glVertex2f(x + leafOffset + cx_offset, base_leaves_y + cy_offset);
			for (int i = 0; i <= TREE_LEAVES_SEG; ++i) {
				float angle = 2.0f * PI_CONSTANT * i / TREE_LEAVES_SEG;
				glVertex2f(x + leafOffset + cx_offset + TREE_LEAVES_R * radius_scale * cos(angle),
						   base_leaves_y + cy_offset + TREE_LEAVES_R * radius_scale * sin(angle));
			}
			glEnd();
		};
		drawLeafCircle(0.0f, TREE_LEAVES_R * 0.5f, 1.0f);
		drawLeafCircle(TREE_LEAVES_R * 0.3f, TREE_LEAVES_R * 0.8f, 0.8f);
		drawLeafCircle(-TREE_LEAVES_R * 0.3f, TREE_LEAVES_R * 0.8f, 0.8f);
		drawLeafCircle(0.0f, TREE_LEAVES_R * 1.5f, 0.6f);
	}

	void drawBushZ(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
		glColor3f(BUSH_COLOR_R, BUSH_COLOR_G, BUSH_COLOR_B);
		glBegin(GL_POLYGON);
			glVertex2f(x, y); glVertex2f(x + width, y);
			int segments = 20;
			for (int i = segments; i >= 0; --i) {
				float t = (float)i / segments;
				float current_x = x + width * t;
				float curve_y_offset = height * (1.0f - (t - 0.5f) * (t - 0.5f) * 4.0f);
				glVertex2f(current_x, y + curve_y_offset);
			}
		glEnd();
	}

	void drawForegroundGroundZ() {
		glColor4f(50.0f / 255.0f, 100.0f / 255.0f, 50.0f / 255.0f, 1.0f);
		glBegin(GL_POLYGON);
			glVertex2f(0.0f, WATER_BOTTOM_Y); glVertex2f((GLfloat)Z_WINDOW_WIDTH, WATER_BOTTOM_Y);
			int segments = 100;
			for (int i = segments; i >= 0; --i) {
				float t = (float)i / segments;
				float x_pos = (GLfloat)Z_WINDOW_WIDTH * t;
				float y_offset = FG_GROUND_PEAK_HEIGHT * (0.5f + 0.5f * sin(t * PI_CONSTANT * 3.0f));
				glVertex2f(x_pos, WATER_BOTTOM_Y + y_offset);
			}
		glEnd();
	}

	GLfloat getGroundYAtX(GLfloat x_pos) {
		GLfloat normalized_t = x_pos / (GLfloat)Z_WINDOW_WIDTH;
		if (normalized_t < 0.0f) normalized_t = 0.0f;
		if (normalized_t > 1.0f) normalized_t = 1.0f;
		float y_offset = FG_GROUND_PEAK_HEIGHT * (0.5f + 0.5f * sin(normalized_t * PI_CONSTANT * 3.0f));
		return WATER_BOTTOM_Y + y_offset;
	}

	void drawCloudZ(GLfloat x, GLfloat y, GLfloat size, GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
		glColor4f(r, g, b, a);
		glPushMatrix();
		glTranslatef(x, y, 0);
		drawFilledArchZ(0, 0, 12 * size, 20);
		drawFilledArchZ(15 * size, 0, 17 * size, 20);
		drawFilledArchZ(7 * size, 10 * size, 15 * size, 20);
		glPopMatrix();
	}

	void drawSunZ(GLfloat centerX, GLfloat centerY, GLfloat radius, int segments) {
		glColor3f(SUN_COLOR_R, SUN_COLOR_G, SUN_COLOR_B);
		glBegin(GL_TRIANGLE_FAN);
			glVertex2f(centerX, centerY);
			for (int i = 0; i <= segments; ++i) {
				float angle = 2 * PI_CONSTANT * i / segments;
				glVertex2f(centerX + radius * cos(angle), centerY + radius * sin(angle));
			}
		glEnd();
	}

	void drawBirdZ(GLfloat x, GLfloat y, GLfloat wing_angle, int direction) {
		glColor3f(0.0f, 0.0f, 0.0f);
		glPushMatrix();
		glTranslatef(x, y, 0.0f);
		if (direction == -1) glScalef(-1.0f, 1.0f, 1.0f);
		glRotatef(wing_angle, 0.0f, 0.0f, 1.0f);
		glBegin(GL_LINES);
			glVertex2f(-BIRD_SIZE, 0.0f); glVertex2f(0.0f, BIRD_SIZE);
			glVertex2f(0.0f, BIRD_SIZE); glVertex2f(BIRD_SIZE, 0.0f);
		glEnd();
		glPopMatrix();
	}

	void initZ() {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, Z_WINDOW_WIDTH, 0, Z_WINDOW_HEIGHT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		for (int i = 0; i < NUM_STATIC_BRIDGE_STRIPES; ++i) {
			staticBridgeStripes[i].y = randomFloat(BRIDGE_BOTTOM_Y + 5.0f, BRIDGE_TOP_Y - 5.0f);
			staticBridgeStripes[i].length = randomFloat(30.0f, 100.0f);
			staticBridgeStripes[i].x = randomFloat(0.0f, (GLfloat)Z_WINDOW_WIDTH - staticBridgeStripes[i].length);
			if (i % 3 == 0) staticBridgeStripes[i].width = 5.0f;
			else if (i % 3 == 1) staticBridgeStripes[i].width = 10.0f;
			else staticBridgeStripes[i].width = 15.0f;
			if (i % 2 == 0) {
				staticBridgeStripes[i].color_r = BRIDGE_STRIPE_COLOR1_R; staticBridgeStripes[i].color_g = BRIDGE_STRIPE_COLOR1_G; staticBridgeStripes[i].color_b = BRIDGE_STRIPE_COLOR1_B;
			} else {
				staticBridgeStripes[i].color_r = BRIDGE_STRIPE_COLOR2_R; staticBridgeStripes[i].color_g = BRIDGE_STRIPE_COLOR2_G; staticBridgeStripes[i].color_b = BRIDGE_STRIPE_COLOR2_B;
			}
		}

		GLfloat road_half_height = (ROAD_TOP_Y - ROAD_BOTTOM_Y) / 2.0f;
		GLfloat lower_lane_y_center = ROAD_BOTTOM_Y + road_half_height * 0.5f;
		GLfloat upper_lane_y_center = ROAD_BOTTOM_Y + road_half_height * 1.5f;
		GLfloat scaled_car_actual_height = ORIGINAL_CAR_BODY_HEIGHT * CAR_SCALE_FACTOR;

		for (int i = 0; i < MAX_CARS; ++i) {
			cars[i].speed = randomFloat(MIN_CAR_SPEED, MAX_CAR_SPEED);
			cars[i].wheelAngle = 0.0f;
			cars[i].carColorR = randomFloat(0.3f, 1.0f);
			cars[i].carColorG = randomFloat(0.3f, 1.0f);
			cars[i].carColorB = randomFloat(0.3f, 1.0f);

			if (i % 2 == 0) {
				cars[i].direction = 1;
				cars[i].y = upper_lane_y_center - (scaled_car_actual_height / 2.0f);
				cars[i].x = -randomFloat(0.0f, Z_WINDOW_WIDTH) - (i * (SCALED_CAR_BODY_WIDTH + 50.0f));
			} else {
				cars[i].direction = -1;
				cars[i].y = lower_lane_y_center - (scaled_car_actual_height / 2.0f);
				cars[i].x = Z_WINDOW_WIDTH + randomFloat(0.0f, Z_WINDOW_WIDTH) + (i * (SCALED_CAR_BODY_WIDTH + 50.0f));
			}
		}

		const GLfloat MAX_BUILDING_HEIGHT = (SKY_TOP_Y - SKY_BOTTOM_Y) / 2.0f;
		GLfloat current_city_x = 0.0f;
		for (int i = 0; i < NUM_BUILDINGS; ++i) {
			buildings[i].width = randomFloat(50.0f, 120.0f);
			buildings[i].height = randomFloat(50.0f, MAX_BUILDING_HEIGHT);
			buildings[i].x = current_city_x;
			buildings[i].y = SKY_BOTTOM_Y;
			int type_choice = rand() % 10;
			if (type_choice < 2) buildings[i].type = BUILDING_TYPE_RECT;
			else if (type_choice < 4) buildings[i].type = BUILDING_TYPE_SETBACK;
			else if (type_choice < 6) buildings[i].type = BUILDING_TYPE_POINTED;
			else if (type_choice < 8) buildings[i].type = BUILDING_TYPE_GILDED;
			else buildings[i].type = BUILDING_TYPE_VICTORIAN;

			if (buildings[i].type == BUILDING_TYPE_GILDED) {
				int c = rand() % 3; if(c==0){buildings[i].colorR=GILDED_COLOR_1_R;buildings[i].colorG=GILDED_COLOR_1_G;buildings[i].colorB=GILDED_COLOR_1_B;} else if(c==1){buildings[i].colorR=GILDED_COLOR_2_R;buildings[i].colorG=GILDED_COLOR_2_G;buildings[i].colorB=GILDED_COLOR_2_B;} else{buildings[i].colorR=GILDED_COLOR_3_R;buildings[i].colorG=GILDED_COLOR_3_G;buildings[i].colorB=GILDED_COLOR_3_B;}
			} else if (buildings[i].type == BUILDING_TYPE_VICTORIAN) {
				int c = rand() % 5; if(c==0){buildings[i].colorR=VICTORIAN_COLOR_1_R;buildings[i].colorG=VICTORIAN_COLOR_1_G;buildings[i].colorB=VICTORIAN_COLOR_1_B;} else if(c==1){buildings[i].colorR=VICTORIAN_COLOR_2_R;buildings[i].colorG=VICTORIAN_COLOR_2_G;buildings[i].colorB=VICTORIAN_COLOR_2_B;} else if(c==2){buildings[i].colorR=VICTORIAN_COLOR_3_R;buildings[i].colorG=VICTORIAN_COLOR_3_G;buildings[i].colorB=VICTORIAN_COLOR_3_B;} else if(c==3){buildings[i].colorR=VICTORIAN_COLOR_4_R;buildings[i].colorG=VICTORIAN_COLOR_4_G;buildings[i].colorB=VICTORIAN_COLOR_4_B;} else{buildings[i].colorR=VICTORIAN_COLOR_5_R;buildings[i].colorG=VICTORIAN_COLOR_5_G;buildings[i].colorB=VICTORIAN_COLOR_5_B;}
			} else {
				int c = rand() % 3; if(c==0){buildings[i].colorR=CITYSCAPE_COLOR1_R;buildings[i].colorG=CITYSCAPE_COLOR1_G;buildings[i].colorB=CITYSCAPE_COLOR1_B;} else if(c==1){buildings[i].colorR=CITYSCAPE_COLOR2_R;buildings[i].colorG=CITYSCAPE_COLOR2_G;buildings[i].colorB=CITYSCAPE_COLOR2_B;} else{buildings[i].colorR=CITYSCAPE_COLOR3_R;buildings[i].colorG=CITYSCAPE_COLOR3_G;buildings[i].colorB=CITYSCAPE_COLOR3_B;}
			}
			current_city_x += randomFloat(buildings[i].width * 0.3f, buildings[i].width * 0.8f);
			if (current_city_x > Z_WINDOW_WIDTH) current_city_x = 0.0f;
		}

		for (int i = 0; i < MAX_CLOUD_PACKS; ++i) {
			cloudPacks[i].base_x = randomFloat(0, Z_WINDOW_WIDTH);
			cloudPacks[i].base_y = randomFloat(SKY_BOTTOM_Y + 50.0f, SKY_TOP_Y - 50.0f);
			cloudPacks[i].speed = randomFloat(CLOUD_PACK_SPEED_MIN, CLOUD_PACK_SPEED_MAX);
			cloudPacks[i].numCloudsInPack = rand() % (MAX_CLOUDS_PER_PACK_MAX - 1) + 2;
			for (int j = 0; j < cloudPacks[i].numCloudsInPack; ++j) {
				cloudPacks[i].individualClouds[j].x_offset = randomFloat(-50.0f, 50.0f);
				cloudPacks[i].individualClouds[j].y_offset = randomFloat(-20.0f, 20.0f);
				cloudPacks[i].individualClouds[j].size = randomFloat(0.2f, 0.5f);
				cloudPacks[i].individualClouds[j].r = randomFloat(CLOUD_COLOR_SHADE_R, CLOUD_COLOR_BASE_R);
				cloudPacks[i].individualClouds[j].g = randomFloat(CLOUD_COLOR_SHADE_G, CLOUD_COLOR_BASE_G);
				cloudPacks[i].individualClouds[j].b = randomFloat(CLOUD_COLOR_SHADE_B, CLOUD_COLOR_BASE_B);
				cloudPacks[i].individualClouds[j].a = randomFloat(0.9f, 1.0f);
			}
		}

		for (int i = 0; i < MAX_BIRD_GROUPS; ++i) {
			birdGroups[i].speed = randomFloat(BIRD_GROUP_SPEED_MIN, BIRD_GROUP_SPEED_MAX);
			birdGroups[i].direction = (rand() % 2 == 0) ? 1 : -1;
			birdGroups[i].numBirdsInGroup = rand() % (MAX_BIRDS_PER_GROUP - 1) + 2;
			if (birdGroups[i].direction == 1) birdGroups[i].base_x = -randomFloat(50.0f, 200.0f);
			else birdGroups[i].base_x = Z_WINDOW_WIDTH + randomFloat(50.0f, 200.0f);
			birdGroups[i].base_y = randomFloat(SKY_BOTTOM_Y + 10.0f, SKY_TOP_Y - 10.0f);
			for (int j = 0; j < birdGroups[i].numBirdsInGroup; ++j) {
				birdGroups[i].individualBirds[j].x_offset = randomFloat(-20.0f, 20.0f);
				birdGroups[i].individualBirds[j].y_offset = randomFloat(-10.0f, 10.0f);
				birdGroups[i].individualBirds[j].wing_angle = 0.0f;
			}
		}
	}

	void updateZ(int value) {
        if (currentScene != 3) { // Only update if this is the current scene
            glutTimerFunc(30, masterUpdate, value + 1);
            return;
        }

		leafOffset = 5.0f * sin(value * 0.02f);
		timerTickCount++;
		for (int i = 0; i < MAX_CARS; ++i) {
			cars[i].x += cars[i].speed * cars[i].direction;
			cars[i].wheelAngle -= cars[i].speed * WHEEL_ROTATION_FACTOR * cars[i].direction;
			if (cars[i].direction == 1 && cars[i].x > Z_WINDOW_WIDTH) {
				cars[i].x = -SCALED_CAR_BODY_WIDTH; cars[i].speed = randomFloat(MIN_CAR_SPEED, MAX_CAR_SPEED);
			} else if (cars[i].direction == -1 && cars[i].x < -SCALED_CAR_BODY_WIDTH) {
				cars[i].x = Z_WINDOW_WIDTH; cars[i].speed = randomFloat(MIN_CAR_SPEED, MAX_CAR_SPEED);
			}
			if (timerTickCount % SPEED_CHANGE_INTERVAL == 0) {
				cars[i].speed = randomFloat(MIN_CAR_SPEED, MAX_CAR_SPEED);
			}
		}

		for (int i = 0; i < MAX_CLOUD_PACKS; ++i) {
			cloudPacks[i].base_x += cloudPacks[i].speed;
			GLfloat max_pack_width = 0.0f;
			for(int j = 0; j < cloudPacks[i].numCloudsInPack; ++j) {
				GLfloat cloud_right_edge = cloudPacks[i].individualClouds[j].x_offset + 35.0f * cloudPacks[i].individualClouds[j].size;
				if (cloud_right_edge > max_pack_width) max_pack_width = cloud_right_edge;
			}
			if (cloudPacks[i].base_x > Z_WINDOW_WIDTH + max_pack_width) {
				cloudPacks[i].base_x = -max_pack_width - randomFloat(50.0f, 150.0f);
				cloudPacks[i].base_y = randomFloat(SKY_BOTTOM_Y + 50.0f, SKY_TOP_Y - 50.0f);
				cloudPacks[i].speed = randomFloat(CLOUD_PACK_SPEED_MIN, CLOUD_PACK_SPEED_MAX);
				cloudPacks[i].numCloudsInPack = rand() % (MAX_CLOUDS_PER_PACK_MAX - 1) + 2;
				for (int j = 0; j < cloudPacks[i].numCloudsInPack; ++j) {
					cloudPacks[i].individualClouds[j].x_offset = randomFloat(-50.0f, 50.0f); cloudPacks[i].individualClouds[j].y_offset = randomFloat(-20.0f, 20.0f); cloudPacks[i].individualClouds[j].size = randomFloat(0.2f, 0.5f); cloudPacks[i].individualClouds[j].r = randomFloat(CLOUD_COLOR_SHADE_R, CLOUD_COLOR_BASE_R); cloudPacks[i].individualClouds[j].g = randomFloat(CLOUD_COLOR_SHADE_G, CLOUD_COLOR_BASE_G); cloudPacks[i].individualClouds[j].b = randomFloat(CLOUD_COLOR_SHADE_B, CLOUD_COLOR_BASE_B); cloudPacks[i].individualClouds[j].a = randomFloat(0.9f, 1.0f);
				}
			}
		}

		for (int i = 0; i < MAX_BIRD_GROUPS; ++i) {
			birdGroups[i].base_x += birdGroups[i].speed * birdGroups[i].direction;
			for (int j = 0; j < birdGroups[i].numBirdsInGroup; ++j) {
				birdGroups[i].individualBirds[j].wing_angle = 15.0f * sin(value * WING_FLAP_SPEED + j * 0.5f);
			}
			if ((birdGroups[i].direction == 1 && birdGroups[i].base_x > Z_WINDOW_WIDTH + 100) ||
				(birdGroups[i].direction == -1 && birdGroups[i].base_x < -100)) {
				if (birdGroups[i].direction == 1) birdGroups[i].base_x = -100.0f - randomFloat(0.0f, 100.0f);
				else birdGroups[i].base_x = Z_WINDOW_WIDTH + 100.0f + randomFloat(0.0f, 100.0f);
				birdGroups[i].base_y = randomFloat(SKY_BOTTOM_Y + 10.0f, SKY_TOP_Y - 10.0f);
				birdGroups[i].speed = randomFloat(BIRD_GROUP_SPEED_MIN, BIRD_GROUP_SPEED_MAX);
				birdGroups[i].numBirdsInGroup = rand() % (MAX_BIRDS_PER_GROUP - 1) + 2;
			}
		}

		waterStripeAnimationX -= WATER_STRIPE_FLOW_SPEED;
		if (waterStripeAnimationX < -(WATER_STRIPE_MAX_LEN + WATER_STRIPE_MAX_GAP)) {
			waterStripeAnimationX += (WATER_STRIPE_MAX_LEN + WATER_STRIPE_MAX_GAP);
		}

		glutPostRedisplay();
		glutTimerFunc(30, masterUpdate, value + 1);
	}

	void displayZ() {
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_QUADS);
			glColor3f(SUNSET_TOP_R, SUNSET_TOP_G, SUNSET_TOP_B);
			glVertex2f(0.0f, SKY_TOP_Y); glVertex2f((GLfloat)Z_WINDOW_WIDTH, SKY_TOP_Y);
			glColor3f(SUNSET_HORIZON_R, SUNSET_HORIZON_G, SUNSET_HORIZON_B);
			glVertex2f((GLfloat)Z_WINDOW_WIDTH, SKY_BOTTOM_Y); glVertex2f(0.0f, SKY_BOTTOM_Y);
		glEnd();

		drawSunZ(Z_WINDOW_WIDTH * 0.8f, SKY_TOP_Y * 0.7f, SUN_RADIUS, 50);

		for (int i = 0; i < MAX_CLOUD_PACKS; ++i) {
			for (int j = 0; j < cloudPacks[i].numCloudsInPack; ++j) {
				CloudZ c = cloudPacks[i].individualClouds[j];
				drawCloudZ(cloudPacks[i].base_x + c.x_offset, cloudPacks[i].base_y + c.y_offset, c.size, c.r, c.g, c.b, c.a);
			}
		}

		for (int i = 0; i < MAX_BIRD_GROUPS; ++i) {
			for (int j = 0; j < birdGroups[i].numBirdsInGroup; ++j) {
				BirdZ b = birdGroups[i].individualBirds[j];
				drawBirdZ(birdGroups[i].base_x + b.x_offset, birdGroups[i].base_y + b.y_offset, b.wing_angle, birdGroups[i].direction);
			}
		}

		glColor4f(107.0f / 255.0f, 182.0f / 255.0f, 205.0f / 255.0f, 1.0f);
		glBegin(GL_QUADS);
			glVertex2f(0.0f, WATER_BOTTOM_Y); glVertex2f((GLfloat)Z_WINDOW_WIDTH, WATER_BOTTOM_Y);
			glVertex2f((GLfloat)Z_WINDOW_WIDTH, WATER_TOP_Y); glVertex2f(0.0f, WATER_TOP_Y);
		glEnd();

		glColor4f(187.0f / 255.0f, 138.0f / 255.0f, 45.0f / 255.0f, 1.0f);
		glBegin(GL_QUADS);
			glVertex2f(0.0f, BRIDGE_BOTTOM_Y); glVertex2f((GLfloat)Z_WINDOW_WIDTH, BRIDGE_BOTTOM_Y);
			glVertex2f((GLfloat)Z_WINDOW_WIDTH, BRIDGE_TOP_Y); glVertex2f(0.0f, BRIDGE_TOP_Y);
		glEnd();

		for (int i = 0; i < NUM_STATIC_BRIDGE_STRIPES; ++i) {
			BridgeStripe s = staticBridgeStripes[i];
			glColor4f(s.color_r, s.color_g, s.color_b, 1.0f);
			glLineWidth(s.width);
			glBegin(GL_LINES); glVertex2f(s.x, s.y); glVertex2f(s.x + s.length, s.y); glEnd();
		}

		glColor4f(86.0f / 255.0f, 99.0f / 255.0f, 115.0f / 255.0f, 1.0f);
		glBegin(GL_QUADS);
			glVertex2f(0.0f, ROAD_BOTTOM_Y); glVertex2f((GLfloat)Z_WINDOW_WIDTH, ROAD_BOTTOM_Y);
			glVertex2f((GLfloat)Z_WINDOW_WIDTH, ROAD_TOP_Y); glVertex2f(0.0f, ROAD_TOP_Y);
		glEnd();

		glColor4f(55.0f / 255.0f, 35.0f / 255.0f, 21.0f / 255.0f, 1.0f); glLineWidth(6.0f);
		glBegin(GL_LINES); glVertex2f(0.0f, ROAD_TOP_Y); glVertex2f((GLfloat)Z_WINDOW_WIDTH, ROAD_TOP_Y); glEnd();
		glBegin(GL_LINES); glVertex2f(0.0f, ROAD_BOTTOM_Y); glVertex2f((GLfloat)Z_WINDOW_WIDTH, ROAD_BOTTOM_Y); glEnd();

		glColor4f(133.0f / 255.0f, 152.0f / 255.0f, 166.0f / 255.0f, 1.0f); glLineWidth(ROAD_STRIPE_WIDTH);
		GLfloat road_middle_y = (ROAD_BOTTOM_Y + ROAD_TOP_Y) / 2.0f;
		for (GLfloat cx = 0.0f; cx < Z_WINDOW_WIDTH; cx += (ROAD_STRIPE_LEN + ROAD_STRIPE_GAP)) {
			glBegin(GL_LINES); glVertex2f(cx, road_middle_y); glVertex2f(cx + ROAD_STRIPE_LEN, road_middle_y); glEnd();
		}

		for (int i = 0; i < MAX_CARS; ++i) {
			drawAnimatedCarZ(cars[i].x, cars[i].y, cars[i].wheelAngle, cars[i].carColorR, cars[i].carColorG, cars[i].carColorB, cars[i].direction);
		}

		glColor4f(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, 1.0f);
		glLineWidth(BARRIER_LINE_THICKNESS);
		glBegin(GL_LINES); glVertex2f(0.0f, BRIDGE_TOP_Y + BARRIER_HEIGHT); glVertex2f((GLfloat)Z_WINDOW_WIDTH, BRIDGE_TOP_Y + BARRIER_HEIGHT); glEnd();
		glBegin(GL_LINES); glVertex2f(0.0f, BRIDGE_TOP_Y); glVertex2f((GLfloat)Z_WINDOW_WIDTH, BRIDGE_TOP_Y); glEnd();
		glLineWidth(BARRIER_VERTICAL_LINE_WIDTH);
		for (GLfloat x_barrier = BARRIER_VERTICAL_LINE_SPACING / 2.0f; x_barrier < Z_WINDOW_WIDTH; x_barrier += BARRIER_VERTICAL_LINE_SPACING) {
			glBegin(GL_LINES); glVertex2f(x_barrier, BRIDGE_TOP_Y); glVertex2f(x_barrier, BRIDGE_TOP_Y + BARRIER_HEIGHT); glEnd();
		}

		for (int i = 0; i < NUM_BUILDINGS; ++i) {
			Building bld = buildings[i];
			drawBuildingZ(bld.x, bld.y, bld.width, bld.height, bld.colorR, bld.colorG, bld.colorB, bld.type);
		}

		glColor4f(36.0f / 255.0f, 23.0f / 255.0f, 14.0f / 255.0f, 1.0f);
		for (int i = 0; i < NUM_ARCHES; ++i) {
			drawFilledArchZ(ARCH_START_OFFSET + (i * ARCH_DISTANCE), BRIDGE_BOTTOM_Y, ARCH_RADIUS, ARCH_SEGMENTS);
		}

		glColor4f(171.0f / 255.0f, 225.0f / 255.0f, 236.0f / 255.0f, 1.0f); glLineWidth(WATER_STRIPE_WIDTH);
		for (GLfloat y_stripe = WATER_BOTTOM_Y + WATER_STRIPE_VERT_SPACING / 2.0f; y_stripe < WATER_TOP_Y; y_stripe += (WATER_STRIPE_VERT_SPACING * WATER_STRIPE_DENSITY_FACTOR)) {
			GLfloat current_x_water_stripe = (fmod(y_stripe / (WATER_STRIPE_VERT_SPACING * WATER_STRIPE_DENSITY_FACTOR), 2.0f) < 1.0f) ? 0.0f : -(WATER_STRIPE_MAX_LEN / 2.0f + WATER_STRIPE_MAX_GAP / 2.0f);
			GLfloat randomized_y = y_stripe + randomFloat(-WATER_STRIPE_RANDOM_Y_MAX, WATER_STRIPE_RANDOM_Y_MAX);
			GLfloat loop_start_x = current_x_water_stripe + waterStripeAnimationX;
			while (loop_start_x < Z_WINDOW_WIDTH) {
				GLfloat stripe_length = randomFloat(WATER_STRIPE_MIN_LEN, WATER_STRIPE_MAX_LEN);
				GLfloat stripe_gap = randomFloat(WATER_STRIPE_MIN_GAP, WATER_STRIPE_MAX_GAP);
				glBegin(GL_LINES);
					glVertex2f(loop_start_x, randomized_y); glVertex2f(loop_start_x + stripe_length, randomized_y);
				glEnd();
				loop_start_x += (stripe_length + stripe_gap);
			}
		}

		drawForegroundGroundZ();

		drawTreeZ(TREE1_X, getGroundYAtX(TREE1_X) - GROUND_SINK_OFFSET, false);
		drawTreeZ(TREE2_X, getGroundYAtX(TREE2_X) - GROUND_SINK_OFFSET, true);
		drawTreeZ(TREE3_X, getGroundYAtX(TREE3_X) - GROUND_SINK_OFFSET, false);
		drawTreeZ(TREE4_X, getGroundYAtX(TREE4_X) - GROUND_SINK_OFFSET, true);
		drawTreeZ(TREE5_X, getGroundYAtX(TREE5_X) - GROUND_SINK_OFFSET, false);
		drawTreeZ(TREE6_X, getGroundYAtX(TREE6_X) - GROUND_SINK_OFFSET, true);

		drawBushZ(BUSH1_X, getGroundYAtX(BUSH1_X) - GROUND_SINK_OFFSET, BUSH1_W, BUSH1_H);
		drawBushZ(BUSH2_X, getGroundYAtX(BUSH2_X) - GROUND_SINK_OFFSET, BUSH2_W, BUSH2_H);

		glFlush(); // Note: Original used glFlush, but glutSwapBuffers is used in main for double buffering
	}
}


// =================================================================
// --- MASTER CONTROL FUNCTIONS ---
// =================================================================

void masterDisplay() {
    switch (currentScene) {
        case 0: SceneN::displayN(); break;       // Rural Scene
        case 1: SceneS::displayS(); break;       // Wind Turbine Scene
        case 2: SceneA::displayA(); break;       // Ocean Scene
        case 3:                                  // City Scene
            SceneZ::displayZ();
            glutSwapBuffers();
            break;
    }
}

void masterUpdate(int value) {
    switch (currentScene) {
        case 0: SceneN::updateN(value); break;
        case 1: SceneS::updateS(value); break;
        case 2: SceneA::updateA(value); break;
        case 3: SceneZ::updateZ(value); break;
    }
}

void masterKeyboard(unsigned char key, int x, int y) {
    // Keyboard handler for Rural Scene (now Scene 0)
    if (currentScene == 0) {
        SceneN::keyboardN(key, x, y);
    }
    // Allow ESC to quit from any scene
    if (key == 27) {
        exit(0);
    }
}

void masterReshape(int w, int h) {
    glViewport(0, 0, w, h);
    // Initialize the scene based on the new order
    switch (currentScene) {
        case 0: SceneN::initN(); break;
        case 1: SceneS::initS(); break;
        case 2: SceneA::initA(); break;
        case 3: SceneZ::initZ(); break;
    }
}

void sceneChangeTimer(int value) {
    currentScene++; // Move to the next scene index

    // Check if we have shown all scenes. If so, exit.
    if (currentScene >= NUM_SCENES) {
        std::cout << "All scenes displayed. Exiting." << std::endl;
        exit(0);
        return;
    }

    std::cout << "Switching to Scene " << currentScene << std::endl;
    PlaySound(NULL, 0, 0); // Stop any currently playing sound

    // Initialize the next scene
    switch (currentScene) {
        case 1: // Wind Turbine Scene (S)
            glutReshapeWindow(800, 600);
            SceneS::initS();
            PlaySound(TEXT("car_horn.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            break;
        case 2: // Ocean Scene (A)
            glutReshapeWindow(800, 500);
            SceneA::initA();
            PlaySound(TEXT("sound.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            break;
        case 3: // City Scene (Z)
            glutReshapeWindow(793, 556);
            SceneZ::initZ();
            PlaySound(TEXT("traffic_audio.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            break;
    }
    glutPostRedisplay();
    // Set the timer for the next change
    glutTimerFunc(10000, sceneChangeTimer, 0);
}

// --- Main Function ---
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);

    // Initialize with the first scene in the new order: Rural Scene (N)
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Final Sequence");

    // Initialize Scene N and its sound
    SceneN::initN();
    // NOTE: For this to work, a file named "sound.wav" must be present.
    // The original rural scene triggered sound on an event, this plays it immediately.
    PlaySound(TEXT("sound.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    // Register callback functions
    glutDisplayFunc(masterDisplay);
    glutReshapeFunc(masterReshape);
    glutKeyboardFunc(masterKeyboard);

    // Start the animation and the first scene-switching timer
    glutTimerFunc(16, masterUpdate, 0);
    glutTimerFunc(10000, sceneChangeTimer, 0);

    glutMainLoop();
    return 0;
}
