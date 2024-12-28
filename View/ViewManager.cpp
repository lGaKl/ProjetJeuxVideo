#include "ViewManager.h"

ViewManager::ViewManager()
    : window(sf::VideoMode(800, 600), "View Manager") {}

void ViewManager::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (!views.empty()) {
            window.clear(sf::Color::Black);

            // Appeler la vue active avec la fenêtre et le gestionnaire
            views.top()(window, *this);

            window.display();
        } else {
            // Si aucune vue, fermer la fenêtre
            window.close();
        }
    }
}

void ViewManager::pushView(const std::function<void(sf::RenderWindow&, ViewManager&)>& view) {
    views.push(view);
}

void ViewManager::popView() {
    if (!views.empty()) {
        views.pop();
    }
}

void ViewManager::clearViews() {
    while (!views.empty()) {
        views.pop();
    }
}
