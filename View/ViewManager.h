#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <stack>

class ViewManager {
private:
    sf::RenderWindow window;
    std::stack<std::function<void(sf::RenderWindow&, ViewManager&)>> views;

public:
    ViewManager();
    void run();
    void pushView(const std::function<void(sf::RenderWindow&, ViewManager&)>& view);
    void popView();
    void clearViews();
};

#endif // VIEWMANAGER_H
