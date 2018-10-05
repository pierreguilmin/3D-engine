#include "general.hpp"
#include "geometry.hpp"
#include "mouse.hpp"

#define FPS 60
#define LOOP_TIME (1000.0 / FPS)


int main()
{
    sf::Clock loop_timer;
    sf::Clock current_time;

	srand(time(NULL));


    // setup window
    sf::ContextSettings window_settings;
    window_settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT), "3D-engine", sf::Style::Close | sf::Style::Resize, window_settings);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    Mouse::setPosition(sf::Vector2i(INITIAL_WINDOW_WIDTH / 2, INITIAL_WINDOW_HEIGHT / 2), window);


    // create solid: colorful plane
    Solid3d colorful_plane;
    colorful_plane.add_segment(Segment3d(Vector3d(-120, 0, -120, sf::Color::Cyan ),
                                         Vector3d(120 , 0, -120, sf::Color::Blue )));
    colorful_plane.add_segment(Segment3d(Vector3d(120 , 0, -120, sf::Color::Blue ),
                                         Vector3d(120 , 0, 120 , sf::Color::Red  )));
    colorful_plane.add_segment(Segment3d(Vector3d(120 , 0, 120 , sf::Color::Red  ),
                                         Vector3d(-120, 0, 120 , sf::Color::Green)));
    colorful_plane.add_segment(Segment3d(Vector3d(-120, 0, 120 , sf::Color::Green),
                                         Vector3d(-120, 0, -120, sf::Color::Cyan )));


    // create solid: cube inside cube
    Solid3d cube(Solid3d::SOLID_TYPE::CUBE, "50");
    cube.set_center(Vector3d(-60-50, -50, -50));
    Solid3d smaller_cube(Solid3d::SOLID_TYPE::CUBE, "25");
    smaller_cube.set_center(Vector3d(-60-25, -25, -25));


    // create solid: rotating sphere
    Solid3d rotating_sphere(Solid3d::SOLID_TYPE::SPHERE, "40:20:50");
    rotating_sphere.set_center(Vector3d(60, 0, 0));


    // create camera
    Camera3d camera(Vector3d(0, -120, -230), -30, 0, 0);


    loop_timer.restart();
    current_time.restart();

    while (window.isOpen())
    {
        sf::Event event;

        // handle events
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
            if (event.type == sf::Event::Resized) {
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                Parameters::update_window_size(event.size.width, event.size.height);
                cout << "Window resized: "
                     << event.size.width
                     << " x "
                     << event.size.height << std::endl;
                camera.reload_frustrum();
            }
        }

        // rotate camera
        camera.rotate(Mouse::get_move_x(window), Mouse::get_move_y(window));

        // move camera
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            camera.move(Camera3d::DIRECTION::FRONT);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            camera.move(Camera3d::DIRECTION::BEHIND);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            camera.move(Camera3d::DIRECTION::RIGHT);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            camera.move(Camera3d::DIRECTION::LEFT);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            camera.move(Camera3d::DIRECTION::UP);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            camera.move(Camera3d::DIRECTION::DOWN);

        // rendering
        window.clear();

        colorful_plane.render_solid(window, camera);

        cube.render_solid(window, camera);
        smaller_cube.render_solid(window, camera);

        rotating_sphere.rotate(Vector3d(), Vector3d(1, 1, 0), 3, true);
        rotating_sphere.render_solid(window, camera);

        window.display();

        // other
        Parameters::print_mean_CPU_usage(cout, loop_timer.getElapsedTime().asMilliseconds(), LOOP_TIME);

        sf::sleep(sf::milliseconds(LOOP_TIME - loop_timer.getElapsedTime().asMilliseconds()));
        loop_timer.restart();
    }

    cout << endl;
    
	return 0;
}
