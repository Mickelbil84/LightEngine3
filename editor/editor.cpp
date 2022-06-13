#include <le3_application.h>
#include <le3_shader.h>
#include <le3_mesh.h>
#include <le3_primitives.h>
#include <le3_camera.h>
#include <le3_texture.h>
#include <le3_material.h>
#include <le3_scene_root.h>
#include <le3_static_mesh.h>
#include <le3_asset_manager.h>

#include <map>
#include <vector>
#include <glm/gtx/transform.hpp>

#include <Qt>
#include <QApplication>
#include <QPushButton>
#include <QOpenGLWidget>
#include <QSurfaceFormat>
#include <QKeyEvent>


#ifndef __APPLE__
const std::string resource_prefix = std::string("../../");
#else
const std::string resource_prefix = std::string("../../../../");
#endif

class LE3EditorOpenGL : public QOpenGLWidget
{
public:
    double runTime = 0.0;

    LE3SceneRoot root;
    LE3AssetManager assets;

    LE3Object car;
    LE3Object wheelsFront, wheelsBack;
    LE3StaticMesh carBodyMesh;
    LE3StaticMesh wheel1, wheel2, wheel3, wheel4;

    LE3FreeCamera camera;

    std::map<Qt::Key, bool> keymap;

protected:
    void keyPressEvent(QKeyEvent* event) override
    {
        keymap[(Qt::Key)event->key()] = true;
        std::cout << "hi :)" << std::endl;
    }
    void keyReleaseEvent(QKeyEvent* event) override
    {
        keymap[(Qt::Key)event->key()] = false;
    }

    void initializeGL() override
    {
        glewInit();
        glEnable(GL_DEPTH_TEST);

        // Reset keys
        keymap[Qt::Key_W] = false;
        keymap[Qt::Key_A] = false;
        keymap[Qt::Key_S] = false;
        keymap[Qt::Key_D] = false;
        keymap[Qt::Key_E] = false;
        keymap[Qt::Key_Q] = false;

        // ---------------------------
        //   Load Assets
        // ---------------------------
        assets.LoadShader("basic", 
            resource_prefix + "resources/shaders/basic/basic.vs", 
            resource_prefix + "resources/shaders/basic/basic.fs");

        std::vector<LE3Vertex> box;
        AddBox(box, 0.f, 0.f, 0.f, .5f, .5f, .3f);
        assets.LoadMesh("wheel", resource_prefix + "resources/models/cars/Audi R8 Wheel.fbx");
        assets.LoadMesh("carBody", resource_prefix + "resources/models/cars/Audi R8 Body.fbx");

        assets.CreateMaterial("red", "basic");
        assets.GetMaterial("red")->diffuseColor = glm::vec4(1.f, 0.f, 0.f, 1.f);
        assets.CreateMaterial("green", "basic");
        assets.GetMaterial("green")->diffuseColor = glm::vec4(0.f, 1.f, 0.f, 1.f);
        assets.CreateMaterial("blue", "basic");
        assets.GetMaterial("blue")->diffuseColor = glm::vec4(0.f, 0.f, 1.f, 1.f);
        assets.CreateMaterial("yellow", "basic");
        assets.GetMaterial("yellow")->diffuseColor = glm::vec4(1.f, 1.f, 0.f, 1.f);

        assets.CreateMaterial("carBody", "basic");
        assets.LoadTexture("wood", resource_prefix + "resources/textures/woodparquet_59-2K/woodparquet_59_basecolor-2K-2K.png");
        assets.GetMaterial("carBody")->diffuseTexture = assets.GetTexture("wood");
        assets.GetMaterial("carBody")->bUseDiffuseTexture = false;
        
        // ---------------------s------
        //   Create game objects
        // ---------------------------
        root.AppendChild(&camera);

        root.AppendChild(&car);
        // car.AddRotationY(-3.14159265f);
        car.SetPosition(glm::vec3(0.f, 0.f, 2.f));

        carBodyMesh.SetMesh(assets.GetMesh("carBody"));
        carBodyMesh.SetMaterial(assets.GetMaterial("carBody"));
        carBodyMesh.SetScale(0.3f);
        carBodyMesh.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f));
        car.AppendChild(&carBodyMesh);

        wheelsFront.SetPosition(glm::vec3(-.705f, 0.175f, 0.f));
        car.AppendChild(&wheelsFront);
        wheelsBack.SetPosition(glm::vec3(.935f, 0.175f, 0.f));
        car.AppendChild(&wheelsBack);

        wheel1.SetMesh(assets.GetMesh("wheel"));
        wheel1.SetMaterial(assets.GetMaterial("red"));
        wheel1.SetPosition(glm::vec3(0.f, 0.f, -.5f));
        wheel1.SetScale(0.33f);
        wheel1.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f));
        wheelsFront.AppendChild(&wheel1);

        wheel2.SetMesh(assets.GetMesh("wheel"));
        wheel2.SetMaterial(assets.GetMaterial("green"));
        wheel2.SetPosition(glm::vec3(0.f, 0.f, .5f));
        wheel2.SetScale(0.33f);
        wheel2.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, 3.14159265f / 2.f));
        wheelsFront.AppendChild(&wheel2);

        wheel3.SetMesh(assets.GetMesh("wheel"));
        wheel3.SetMaterial(assets.GetMaterial("blue"));
        wheel3.SetPosition(glm::vec3(0.f, 0.f, -.5f));
        wheel3.SetScale(0.33f);
        wheel3.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f));
        wheelsBack.AppendChild(&wheel3);

        wheel4.SetMesh(assets.GetMesh("wheel"));
        wheel4.SetMaterial(assets.GetMaterial("yellow"));
        wheel4.SetPosition(glm::vec3(0.f, 0.f, .55f));
        wheel4.SetScale(0.33f);
        wheel4.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, 3.14159265f / 2.f));
        wheelsBack.AppendChild(&wheel4);


        // ---------------------------
        //   Misc
        // ---------------------------
        
        camera.SetPosition(glm::vec3(0.f, 1.f, 5.f));
    }

    void resizeGL(int w, int h) override
    {
    }

    void paintGL() override
    {
        glClearColor(
            100.f/255.f, 
            149.f/255.f, 
            237.f/255.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ////////////////////////
        // Camera Movement
        ////////////////////////
        if (keymap[Qt::Key_W])
            camera.SetMoveVelocityY(1.f);
        else if (keymap[Qt::Key_S])
            camera.SetMoveVelocityY(-1.f);
        else
            camera.SetMoveVelocityY(0.f);

        if (keymap[Qt::Key_D])
            camera.SetMoveVelocityX(1.f);
        else if (keymap[Qt::Key_A])
            camera.SetMoveVelocityX(-1.f);
        else
            camera.SetMoveVelocityX(0.f);

        if (keymap[Qt::Key_E])
            camera.SetMoveVelocityZ(1.f);
        else if (keymap[Qt::Key_Q])
            camera.SetMoveVelocityZ(-1.f);
        else
            camera.SetMoveVelocityZ(0.f);

        root.Update(0.01);

        assets.GetShader("basic")->Use();
        assets.GetShader("basic")->Uniform("view", camera.GetViewMatrix());
        assets.GetShader("basic")->Uniform("projection", camera.GetProjectionMatrix(800.f / 600.f));
        root.Draw();

        update();
    }
};

int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    
    // Set correct OpenGL version
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(4, 1);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    QSurfaceFormat::setDefaultFormat(format);

    LE3EditorOpenGL screen;
    screen.setMinimumSize(800, 600);
    
    screen.show();

    return app.exec();
}