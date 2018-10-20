#include "utils/mouse.hpp"
#include "utils/parameters.hpp"
#include "geometry/camera3d.hpp"
#include "geometry/solid3d.hpp"
#include "geometry/geometry.hpp"

using std::cout;
using std::endl;


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
    colorful_plane.add_segment(Segment3d(Vector3d(-150, 0, -150, sf::Color::Cyan ),
                                         Vector3d(150 , 0, -150, sf::Color::Blue )));
    colorful_plane.add_segment(Segment3d(Vector3d(150 , 0, -150, sf::Color::Blue ),
                                         Vector3d(150 , 0, 150 , sf::Color::Red  )));
    colorful_plane.add_segment(Segment3d(Vector3d(150 , 0, 150 , sf::Color::Red  ),
                                         Vector3d(-150, 0, 150 , sf::Color::Green)));
    colorful_plane.add_segment(Segment3d(Vector3d(-150, 0, 150 , sf::Color::Green),
                                         Vector3d(-150, 0, -150, sf::Color::Cyan )));

    // create solid: cube inside cube
    Cube3d big_cube(Vector3d(100, 0, 0), 50);
    Cube3d small_cube(Vector3d(100, 0, 0), 25);

    // create solid: rotating sphere
    Sphere3d sphere(Vector3d(-90, 0, 0), 40, 30, 50);

    // create camera
    Camera3d camera(Vector3d(0, -120, -230), -30, 0, 0, Parameters::window_width, Parameters::window_height);


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
                     << event.size.height << endl;
                camera.reload_frustrum(Parameters::window_width, Parameters::window_height);
            }
        }

        // rotate camera
        camera.rotate(Mouse::get_move_x(window), Mouse::get_move_y(window));

        // move camera
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            camera.move(Camera3d::DIRECTION::FRONT);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            camera.move(Camera3d::DIRECTION::BACK);
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

        colorful_plane.render_solid(window, Parameters::window_width, Parameters::window_height, camera);

        small_cube.rotate(Vector3d(50, 0, 0), Vector3d(0, 1, 0), 1, false);
        big_cube.rotate(Vector3d(50, 0, 0), Vector3d(0, 1, 0), 1, false);

        small_cube.rotate(Vector3d(), Vector3d(1, 1, 0), 2, true);
        big_cube.render_solid(window, Parameters::window_width, Parameters::window_height, camera);
        small_cube.render_solid(window, Parameters::window_width, Parameters::window_height, camera);

        sphere.rotate(Vector3d(), Vector3d(0, 1, 1), 3, true);
        sphere.render_solid(window, Parameters::window_width, Parameters::window_height, camera);

        window.display();

        // other
        Parameters::print_mean_CPU_usage(cout, loop_timer.getElapsedTime().asMilliseconds());

        sf::sleep(sf::milliseconds(MAX_MAIN_LOOP_DURATION - loop_timer.getElapsedTime().asMilliseconds()));
        loop_timer.restart();
    }

    cout << endl;
    
	return 0;
}
