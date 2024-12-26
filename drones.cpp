#include "lab_m1/DroneMiniGames/drones.h"

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <random>
#include <utility>



using namespace std;
using namespace m1;


float random(glm::vec2 st) {
    return glm::fract(glm::sin(glm::dot(st, glm::vec2(12.9898f, 78.233f))) * 43758.5453123f);
}

float noise(glm::vec2 st) {
    glm::vec2 i = glm::floor(st);
    glm::vec2 f = glm::fract(st);
    float a = random(i);
    float b = random(i + glm::vec2(1.0f, 0.0f));
    float c = random(i + glm::vec2(0.0f, 1.0f));
    float d = random(i + glm::vec2(1.0f, 1.0f));
    glm::vec2 u = f * f * (3.0f - 2.0f * f);
    return glm::mix(a, b, u.x) + (c - a) * u.y * (1.0f - u.x) + (d - b) * u.x * u.y;
}

float getHeightAtPoint(float x, float z, float frequency) {
    glm::vec2 position = glm::vec2(x, z) * frequency;
    float noiseValue = noise(position);
    return noiseValue * 2;
}

Mesh* CreateDrone(const std::string& name, glm::vec3 color) {
    vector<VertexFormat> vertices =
    {   //first parallelepiped
        VertexFormat(glm::vec3(20, -2, 2), color),
        VertexFormat(glm::vec3(20, 2, 2), color),
        VertexFormat(glm::vec3(-20, 2, 2), color),
        VertexFormat(glm::vec3(-20, -2, 2), color),
        VertexFormat(glm::vec3(20, -2, -2), color),
        VertexFormat(glm::vec3(20, 2, -2), color),
        VertexFormat(glm::vec3(-20, 2, -2),color),
        VertexFormat(glm::vec3(-20, -2, -2), color),
        //second parallelepiped
        VertexFormat(glm::vec3(-2, -2, 20), color),
        VertexFormat(glm::vec3(2, -2, 20),color),
        VertexFormat(glm::vec3(2, 2, 20),color),
        VertexFormat(glm::vec3(-2, 2, 20),color),
        VertexFormat(glm::vec3(-2, -2, -20),color),
        VertexFormat(glm::vec3(2, -2, -20), color),
        VertexFormat(glm::vec3(2, 2, -20), color),
        VertexFormat(glm::vec3(-2,  2, -20), color),

        //cube 1
        VertexFormat(glm::vec3(20, 2, -2), color), //16
        VertexFormat(glm::vec3(20, 2, 2), color), //17
        VertexFormat(glm::vec3(16, 2, 2), color), // 18
        VertexFormat(glm::vec3(16, 2, -2), color), //19
        VertexFormat(glm::vec3(20, 6, -2), color), //20
        VertexFormat(glm::vec3(20, 6, 2), color), //21
        VertexFormat(glm::vec3(16, 6, 2), color), //22
        VertexFormat(glm::vec3(16, 6, -2), color), //23

        //cube 2
        VertexFormat(glm::vec3(-16, 2, -2), color), //24
        VertexFormat(glm::vec3(-16, 2, 2), color), // 25
        VertexFormat(glm::vec3(-20, 2, 2), color), //26
        VertexFormat(glm::vec3(-20, 2, -2), color),//27
        VertexFormat(glm::vec3(-16, 6, -2), color), //28
        VertexFormat(glm::vec3(-16, 6, 2), color), //29
        VertexFormat(glm::vec3(-20, 6, 2), color), //30
        VertexFormat(glm::vec3(-20, 6, -2), color), //31

        //cube 3
        VertexFormat(glm::vec3(2, 2, 16),color), // 32
        VertexFormat(glm::vec3(2, 2, 20),color), //33
        VertexFormat(glm::vec3(-2, 2, 20),color), //34
        VertexFormat(glm::vec3(-2, 2, 16),color), //35
        VertexFormat(glm::vec3(2, 6,  16),color), //36
        VertexFormat(glm::vec3(2, 6,  20),color), //37
        VertexFormat(glm::vec3(-2, 6, 20), color), //38
        VertexFormat(glm::vec3(-2, 6,  16),color), //39

        //cube 4
        VertexFormat(glm::vec3(2, 2, -20),color), //40
        VertexFormat(glm::vec3(2, 2, -16),color), //41
        VertexFormat(glm::vec3(-2, 2, -20),color), //42
        VertexFormat(glm::vec3(-2, 2, -16),color), //43
        VertexFormat(glm::vec3(2, 6, -20),color), //44
        VertexFormat(glm::vec3(2, 6, -16),color), //45
        VertexFormat(glm::vec3(-2, 6, -20),color), //46
        VertexFormat(glm::vec3(-2, 6, -16),color) //47
    };
    Mesh* drone = new Mesh(name);
    vector<unsigned int> indices = {
        //first parallelepiped
        0, 3, 1,
        3, 2, 1,
        1, 2, 6,
        1, 6, 5,
        5, 6, 7,
        5, 7, 4,
        4, 7, 3,
        4, 3, 0,
        3, 7, 6,
        3, 6, 2,
        0, 4, 5,
        0, 5, 1,
        //second parallelepiped
        8, 11, 9,
        11, 10, 9,
        9, 10, 14,
        9, 14, 13,
        13, 14, 15,
        13, 15, 12,
        12, 15, 11,
        12, 11, 8,
        11, 15, 14,
        11, 14, 10,
        8, 12, 13,
        8, 13, 9,
        //cube 1
        20, 16, 17,
        20, 17, 21,

        16, 19, 18,
        16, 17, 17,
        
        17, 18, 22,
        17, 22, 21,

        19, 23, 22,
        19, 22, 18,
        
        23, 20, 21,
        23, 21, 22,
        
        20, 23, 19,
        20, 19, 16,
        //cube 2
        28, 24, 25,
        28, 25, 29,

        24, 27, 26,
        24, 25, 25,

        25, 26, 30,
        25, 30, 29,

        27, 31, 30,
        27, 30, 26,

        31, 28, 29,
        31, 29, 30,

        28, 31, 27,
        28, 27, 24,
        //cube3
        36, 32, 33,
        36, 33, 37,

        32, 35, 34,
        32, 33, 33,

        33, 34, 38,
        33, 38, 37,

        35, 39, 38,
        35, 38, 34,

        39, 36, 37,
        39, 37, 38,

        36, 39, 35,
        36, 35, 32,
        //cube4
        44, 40, 41,
        44, 41, 45,

        40, 43, 42,
        40, 41, 41,

        41, 42, 46,
        41, 46, 45,

        43, 47, 46,
        43, 46, 42,

        47, 44, 45,
        47, 45, 46,

        44, 47, 43,
        44, 43, 40
    };
    drone->InitFromData(vertices, indices);
    return drone;
}

Mesh* CreatePropeller(const std::string& name, glm::vec3 color) {
    vector<VertexFormat> vertices = {
        VertexFormat(glm::vec3(-1, 0, 7), glm::vec3(0,0,0)),
        VertexFormat(glm::vec3(1, 0, 7), glm::vec3(0,0,0)),
        VertexFormat(glm::vec3(1, 0, -7), glm::vec3(0,0,0)),
        VertexFormat(glm::vec3(-1, 0, -7), glm::vec3(0,0,0)),
        VertexFormat(glm::vec3(-1, 0.5, 7), glm::vec3(0,0,0)),
        VertexFormat(glm::vec3(1, 0.5, 7), glm::vec3(0,0,0)),
        VertexFormat(glm::vec3(1, 0.5, -7), glm::vec3(0,0,0)),
        VertexFormat(glm::vec3(-1, 0.5, -7), glm::vec3(0,0,0)),
    };

    Mesh* propeller = new Mesh(name);
    vector<unsigned int> indices = {
        0, 1, 2,
        0, 3, 2,
        4, 7, 3,
        4, 3, 0, 
        4, 0, 1, 
        4, 1, 5,
        1, 2, 6, 
        1, 6, 5,
        3, 7, 6,
        3, 6, 2,
        4, 7, 6,
        4, 6, 5
    };
    propeller->InitFromData(vertices, indices);
    return propeller;
}

Mesh* CreateArrow(const std::string& name, glm::vec3 color) {
    vector<VertexFormat> vertices = {
        VertexFormat(glm::vec3(0, 0, -20), color),
        VertexFormat(glm::vec3(0, 0, 0), color),
        VertexFormat(glm::vec3(-2, 0, -2), color),
        VertexFormat(glm::vec3(2, 0, -2), color)
    };
    Mesh* arrow = new Mesh(name);
    vector<unsigned int> indices = {
        0, 1, 2,
        0, 3, 1
    };
    arrow->InitFromData(vertices, indices);
    return arrow;
}

Mesh* CreateTree(const std::string& name) {
    glm::vec3 brown = glm::vec3(0.6f, 0.3f, 0.1f);
    glm::vec3 green = glm::vec3(0, 0.7f, 0);
    vector<unsigned int> indices;
    vector<VertexFormat> vertices = {
        VertexFormat(glm::vec3(0, -10, 0), brown) // 0
    };
    float angleStep = 2.0f * M_PI / 200;
    for (int i = 0; i <= 200; ++i) {
        float angle = i * angleStep;
        vertices.push_back(VertexFormat(
            glm::vec3(5 * cos(angle),-15,  5 * sin(angle)),
            brown
        ));

        if (i < 200) {
            indices.push_back(0);
            indices.push_back(i + 1);
            indices.push_back(i + 2);
        }
    } // 1 -> 201

    int baseIndex = vertices.size();
    vertices.push_back(VertexFormat(glm::vec3(0, 7, 0), brown)); // 202
    for (int i = 0; i <= 200; ++i) {
        float angle = i * angleStep;
        vertices.push_back(VertexFormat(
            glm::vec3(5 * cos(angle), 7, 5 * sin(angle)),
            brown
        )); // 203 - 403

        if (i < 200) {
            indices.push_back(baseIndex);
            indices.push_back(baseIndex + i + 1);
            indices.push_back(baseIndex + i + 2);
        }
    }
    baseIndex = vertices.size();
    for (int i = 0; i <= 200; i++) {
        indices.push_back(i + 201);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
        indices.push_back(i + 201);
        indices.push_back(i + 2);
        indices.push_back(i + 202);
    }

    vertices.push_back(VertexFormat(glm::vec3(0, 7, 0), green)); // 404
    for (int i = 0; i <= 200; ++i) {
        float angle = i * angleStep;
        vertices.push_back(VertexFormat(
            glm::vec3(15 * cos(angle), 7, 15 * sin(angle)),
            green
        )); // 404 - 604

        if (i < 200) {
            indices.push_back(404);
            indices.push_back(404 + i + 1);
            indices.push_back(404 + i + 2);
        }
    }
    int coneTipIndex = vertices.size(); 
    vertices.push_back(VertexFormat(glm::vec3(0, 42, 0), green)); // 606
    for (int i = 0; i < 200; i++) {
        indices.push_back(606);
        indices.push_back(i + 404 + 1);
        indices.push_back(i + 404 + 2);
    }
    indices.push_back(606);
    indices.push_back(605);
    indices.push_back(404);
    vertices.push_back(VertexFormat(glm::vec3(0, 30, 0), green)); // 607
    for (int i = 0; i <= 200; ++i) {
        float angle = i * angleStep;
        vertices.push_back(VertexFormat(
            glm::vec3(10 * cos(angle), 30, 10 * sin(angle)),
            green
        )); // 608 - 808

        if (i < 200) {
            indices.push_back(607);
            indices.push_back(607 + i + 1);
            indices.push_back(607 + i + 2);
        }
    }
    vertices.push_back(VertexFormat(glm::vec3(0, 55, 0), green)); // 809

    for (int i = 0; i < 200; i++) {
        indices.push_back(809);
        indices.push_back(607 + i + 1);
        indices.push_back(607 + i + 2);
    }
    Mesh* tree = new Mesh(name);
    tree->InitFromData(vertices, indices);
    return tree;
}

Mesh* CreateTerrain(const std::string& name, glm::vec3 color) {
    vector<VertexFormat> vertices;
    vector<unsigned int> indices;

    int gridSize = 100;
    float squareSize = 0.5f;
    for (int z = 0; z <= gridSize; ++z) {
        for (int x = 0; x <= gridSize; ++x) {
            vertices.emplace_back(glm::vec3(x * squareSize, 0, z * squareSize), color);
        }
    }
    for (int z = 0; z < gridSize; ++z) {
        for (int x = 0; x < gridSize; ++x) {
            int topLeft = z * (gridSize + 1) + x;
            int topRight = topLeft + 1;
            int bottomLeft = topLeft + (gridSize + 1);
            int bottomRight = bottomLeft + 1;
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }

    Mesh* terrain = new Mesh(name);
    terrain->InitFromData(vertices, indices);
    return terrain;
}

Mesh* CreateDropZone(const std::string& name, glm::vec3 color) {
    std::vector<unsigned int> indices;
    std::vector<VertexFormat> vertices;
    const float angleStep = 2.0f * M_PI / 200;
    const float radius = 5.0f;
    const float height = 20.0f;
    for (int i = 0; i <= 200; ++i) {
        float angle = i * angleStep;
        vertices.push_back(VertexFormat(glm::vec3(radius * cos(angle), 0.0f, radius * sin(angle)), color));
    }
    for (int i = 0; i <= 200; ++i) {
        float angle = i * angleStep;
        vertices.push_back(VertexFormat(glm::vec3(radius * cos(angle), height, radius * sin(angle)), color));
    }
    for (int i = 0; i < 200; ++i) {
        indices.push_back(i);
        indices.push_back(i + 201);
        indices.push_back(i + 202);

        indices.push_back(i);
        indices.push_back(i + 202);
        indices.push_back(i + 1);
    }
    indices.push_back(200);
    indices.push_back(401);
    indices.push_back(201);
    indices.push_back(200);
    indices.push_back(201);
    indices.push_back(0);
    Mesh* dropZone = new Mesh(name);
    dropZone->InitFromData(vertices, indices);
    return dropZone;
}



DronesGame::DronesGame()
{
}


DronesGame::~DronesGame()
{
}

float getRandomNumber(float i, float j) {
    random_device rd;
    mt19937 generator(rd());
    uniform_real_distribution<float> distribution(i, j);
    return distribution(generator);
}

void DronesGame::Init()
{
    renderCameraTarget = false;
    fov = RADIANS(60);
    aspect = window->props.aspectRatio;
    zNear = 0.01f;
    zFar = 200.0f;
    left = -10;
    right = 10;
    top = -10;
    bottom = 10;
    angle_offset = 0;
    drone_rotation_angle = 0;
    tilt_forward = 0;
    tilt_right = 0;
    once_generated = false;
    acceleration = 200;
    float verticalSpeed = 0;
    stabilize = false;
    picked = false;
    inDropZone = false;

    camera = new implemented::DroneCamera();
    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    camera_above = new implemented::DroneCamera();
    camera_above->Set(glm::vec3(0, 62, 3.5f), glm::vec3(0, 2, 3.5f), glm::vec3(0, 0, -1));

    {
        Shader* shader = new Shader("Shader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "DroneMiniGames", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "DroneMiniGames", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("tree");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "pom.fbx");
        meshes[mesh->GetMeshID()] = mesh;
    }
    Mesh* drone = CreateDrone("drone", glm::vec3(0.5f, 0.5f, 0.5f));
    meshes[drone->GetMeshID()] = drone;
    Mesh* propeller = CreatePropeller("propeller", glm::vec3(0, 0, 0));
    meshes[propeller->GetMeshID()] = propeller;
    Mesh* arrow = CreateArrow("arrow", glm::vec3(0, 0, 1));
    meshes[arrow->GetMeshID()] = arrow;
    Mesh* terrain = CreateTerrain("terrain", glm::vec3(0, 0.1, 0));
    meshes[terrain->GetMeshID()] = terrain;
    Mesh* tree = CreateTree("tree1");
    meshes[tree->GetMeshID()] = tree;
    Mesh* dropZone = CreateDropZone("dropZone", glm::vec3(1, 1, 1));
    meshes[dropZone->GetMeshID()] = dropZone;

    // TODO(student): After you implement the changing of the projection
    // parameters, remove hardcodings of these parameters
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
   
    projectionMatrix_1 = glm::ortho(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);
    
    for (float i = -25; i < 25; i += 10) {
        for (float j = -25; j < 25; j += 10) {
            float i_barrier = i + 9;
            float j_barrier = j + 9;
            trees.push_back(make_pair(getRandomNumber(i, i_barrier), getRandomNumber(j, j_barrier)));
            centers.push_back(make_pair(i + 5, j + 5));
        }
    }
    srand(time(0));
    random1 = rand() % (trees.size());
    random2 = std::rand() % (trees.size());
    /*cout << trees[random2].first << " " << trees[random2].second << "\n";
    cout << centers[random2].first << " " << centers[random2].second << "\n";*/
}

void DronesGame::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.537f, 0.812f, 0.941f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void DronesGame::generate_trees() {
    for (int i = 0; i < trees.size(); i++) {
        auto it = trees[i], it_2 = centers[i];
        if (i == random1 ) {
            if (!picked) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(it.first, 2, it.second));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(1));
                RenderMesh(meshes["box"], shaders["VertexColor"], modelMatrix);
            }
            continue;
        }   
        if (i == random2) {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(it_2.first, 0, it_2.second));
            RenderMesh(meshes["dropZone"], shaders["VertexColor"], modelMatrix);
            if (inDropZone) {
                modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 3, 0));
                RenderMesh(meshes["box"], shaders["VertexColor"], modelMatrix);
            }
            continue;
        }
        glm::mat4 modelMatrix = glm::mat4(1);
        float height = getHeightAtPoint(it.first, it.second, 0.1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(it.first, 1, it.second));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1));
        RenderMesh(meshes["tree1"], shaders["VertexColor"], modelMatrix);
    }
}


void DronesGame::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
    RenderDrone();
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-25, 0, -25));
    RenderMesh(meshes["terrain"], shaders["Shader"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.05f));
    generate_trees();
    
    /*DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);*/
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);
    glClear(GL_DEPTH_BUFFER_BIT);
    projectionMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.01f, 200.0f);
    camera_above->position.x = camera->GetTargetPosition().x;
    camera_above->position.y = camera->GetTargetPosition().y ;
    camera_above->position.z = camera->GetTargetPosition().z;
    //RenderArrow();
    DrawCoordinateSystem(camera_above->GetViewMatrix(), projectionMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-25, 0, -25));
    RenderMesh(meshes["terrain"], shaders["Shader"], modelMatrix);
    cout << camera->GetTargetPosition().y << "\n";
}

void DronesGame::RenderArrow() {
    camera_above->GetTargetPosition();
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
    RenderMesh(meshes["arrow"], shaders["VertexColor"], modelMatrix);
}

void DronesGame::FrameEnd()
{
}


void DronesGame::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));


    mesh->Render();
}

bool DronesGame::CheckCollision() {
    glm::vec3 position = camera->GetTargetPosition();
    glm::vec3 size = glm::vec3(40, 6, 40);

    for (int i = 0; i < trees.size(); i++) {
        if (i == random1 && i == random2) {
            continue;
        }
        if (position.y < 7) {
            if (glm::distance(position, glm::vec3(trees[i].first, 0, trees[i].second)) < 1.18) {
                return true;
            }
        }
       /* if (position.y >= 7 && position.y < 42) {
            if (glm::distance(position, glm::vec3(trees[i].first, 0, trees[i].second)) < 2) {
                return true;
            }
        }*/
    }
    return false;
}



void DronesGame::RenderDrone() {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01f));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f) + RADIANS(drone_rotation_angle), glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(tilt_forward), glm::vec3(1, 0, 1));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f) , glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(tilt_right), glm::vec3(1, 0, 0));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(-45.0f), glm::vec3(0, 1, 0));
    RenderMesh(meshes["drone"], shaders["VertexColor"], modelMatrix);
    angle_offset += 20;
    RenderPropeller(0, modelMatrix);
    RenderPropeller(90, modelMatrix);
    RenderPropeller(180, modelMatrix);
    RenderPropeller(270, modelMatrix);
    if (picked && !inDropZone) {
        RenderPackage(modelMatrix);
    }
}
void DronesGame::RenderPackage(glm::mat4 modelMatrix) {
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -40, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(60));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 0));
    RenderMesh(meshes["box"], shaders["VertexColor"], modelMatrix);
}

void DronesGame::RenderTree(float x, float y, float z) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y, z));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(270), glm::vec3(1, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(.7f));

}

void DronesGame::RenderPropeller(float angle, glm::mat4 modelMatrix) {
    modelMatrix = glm::rotate(modelMatrix, RADIANS(angle), glm::vec3(0, 1, 0));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(18, 6, 0));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(angle_offset), glm::vec3(0, 1, 0));
    RenderMesh(meshes["propeller"], shaders["VertexColor"], modelMatrix);
}

void DronesGame::OnInputUpdate(float deltaTime, int mods)
{
        float cameraSpeed = 2.0f;
        if (window->KeyHold(GLFW_KEY_W))
        {
            //camera_above->MoveForward(0.01 * (cameraSpeed + (deltaTime * acceleration)) / miniViewportArea.y * window->GetResolution().y );
                camera->MoveForward(0.01 * cameraSpeed);
            if (CheckCollision())
                camera->MoveForward(-0.01 * cameraSpeed);
                if (tilt_forward > -40)
                    tilt_forward -= 0.5;
            // TODO(student): Translate the camera forward
        }

        if (window->KeyHold(GLFW_KEY_A)) {
                camera->TranslateRight(-0.01 * cameraSpeed);
                if (CheckCollision())
                    camera->TranslateRight(0.01 * cameraSpeed);
                if (tilt_right > -40)
                    tilt_right -= 0.5;
            // TODO(student): Translate the camera to the left
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            // TODO(student): Translate the camera backward
                camera->MoveForward(-0.01 * cameraSpeed);
                if (CheckCollision())
                    camera->MoveForward(0.01 * cameraSpeed);
                if (tilt_forward < 40)
                    tilt_forward += 0.5;
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            // TODO(student): Translate the camera to the right
                camera->TranslateRight(0.01 * cameraSpeed);
                if (CheckCollision())
                    camera->TranslateRight(-0.01 * cameraSpeed);
                if (tilt_right < 40)
                    tilt_right += 0.5;
        }


        if (window->KeyHold(GLFW_KEY_SPACE)) {
        //    // TODO(student): Translate the camera downward
            camera->TranslateUpward(0.01 * cameraSpeed);

        }
        else {
            if (camera->GetTargetPosition().y > 1 && !stabilize)
                camera->TranslateUpward(-0.01 * cameraSpeed);
        }


        if (window->KeyHold(GLFW_KEY_Q)) {
            // TODO(student): Translate the camera downward
            camera->TranslateUpward(0.01 * cameraSpeed);

        }
        if (window->KeyHold(GLFW_KEY_E)) {
            // TODO(student): Translate the camera upward
            if (camera->GetTargetPosition().y > 0.01)
                camera->TranslateUpward(-0.01 * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_RIGHT)) {
            drone_rotation_angle -= 2.5;
            camera->RotateThirdPerson_OY(RADIANS(-2.5));
        }

        if (window->KeyHold(GLFW_KEY_LEFT)) {
            drone_rotation_angle += 2.5;
            camera->RotateThirdPerson_OY(RADIANS(2.5));
        }
        if (!window->KeyHold(GLFW_KEY_D && !window->KeyHold(GLFW_KEY_A) && !window->KeyHold(GLFW_KEY_S) && !window->KeyHold(GLFW_KEY_W))) {
            if (tilt_right > 0 && !window->KeyHold(GLFW_KEY_D)) {
                tilt_right -= 0.5;
            }
            if (tilt_right < 0 && !window->KeyHold(GLFW_KEY_A)) {
                tilt_right += 0.5;
            }
            if (tilt_forward < 0 && !window->KeyHold(GLFW_KEY_W)) {
                tilt_forward += 0.5;
            }
            if (tilt_forward > 0 && !window->KeyHold(GLFW_KEY_S)) {
                tilt_forward -= 0.5;
            }
        }
    //}

    // TODO(student): Change projection parameters. Declare any extra
    // variables you might need in the class header. Inspect this file
    // for any hardcoded projection arguments (can you find any?) and
    // replace them with those extra variables.

}


void DronesGame::OnKeyPress(int key, int mods)
{
    // TODO(student): Switch projections
    if (key == GLFW_KEY_M) {
        stabilize = !stabilize;
    }
    if (key == GLFW_KEY_P) {
        float x = trees[random1].first;
        float y = 4;
        float z = trees[random1].second;
        float my_x = camera->GetTargetPosition().x;
        float my_y = camera->GetTargetPosition().y;
        float my_z = camera->GetTargetPosition().z;
        float distance = std::sqrt(std::pow(my_x - x, 2) + std::pow(my_y - y, 2) + std::pow(my_z - z, 2));
        cout << distance << "\n";
        if (distance <= 2) {
            picked = true;
        }
    }

    if (key == GLFW_KEY_R) {
        float x = centers[random2].first;
        float y = 4;
        float z = centers[random2].second;
        float my_x = camera->GetTargetPosition().x;
        float my_y = camera->GetTargetPosition().y;
        float my_z = camera->GetTargetPosition().z;
        float distance = std::sqrt(std::pow(my_x - x, 2) + std::pow(my_y - y, 2) + std::pow(my_z - z, 2));
        if (distance <= 2) {
            inDropZone = true;
        }
    }


}


void DronesGame::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void DronesGame::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void DronesGame::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void DronesGame::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void DronesGame::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void DronesGame::OnWindowResize(int width, int height)
{
}
