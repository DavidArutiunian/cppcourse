void init(sf::ConvexShape &pointer);

float toDegrees(float radians);

float toRadians(float degrees);

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition);

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition);

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer);

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer);