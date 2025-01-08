#include "EndView.h"
#include <iostream>

// Constructor for EndView: Initializes the end screen with a background image and a button to return to the menu.
EndView::EndView(sf::RenderWindow& window, const std::string& backgroundImagePath) : window(window), isHovered(false) {
    // Create the window with desktop dimensions
    window.create(sf::VideoMode::getDesktopMode(), "End Screen", sf::Style::Default);

    // Load the background image
    if (!backgroundTexture.loadFromFile(backgroundImagePath)) {
        std::cerr << "Error: Unable to load background image!\n";
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Scale the background image to fit the window size
    float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    // Load the font for UI elements
    if (!font.loadFromFile("retro-land-mayhem.ttf")) {
        std::cerr << "Error: Unable to load font!\n";
    }

    // Configure the "Go to Menu" button rectangle
    menuButtonRect.setSize(sf::Vector2f(400.f, 100.f));
    menuButtonRect.setFillColor(sf::Color(0, 0, 255)); // Default color
    menuButtonRect.setOutlineColor(sf::Color::White); // Outline color
    menuButtonRect.setOutlineThickness(4.f);
    menuButtonRect.setPosition(
        window.getSize().x - menuButtonRect.getSize().x - 50.f, // Margin from right edge
        window.getSize().y - menuButtonRect.getSize().y - 50.f  // Margin from bottom edge
    );

    // Configure the "Go to Menu" button text
    menuButtonText.setFont(font);
    menuButtonText.setString("Go to Menu");
    menuButtonText.setCharacterSize(40);
    menuButtonText.setFillColor(sf::Color::White);
    menuButtonText.setPosition(
        menuButtonRect.getPosition().x + (menuButtonRect.getSize().x - menuButtonText.getLocalBounds().width) / 2,
        menuButtonRect.getPosition().y + (menuButtonRect.getSize().y - menuButtonText.getLocalBounds().height) / 2 - 10
    );
}

// Update the hover state of the "Go to Menu" button based on the mouse position.
void EndView::updateHoverState(const sf::Vector2i& mousePosition) {
    sf::FloatRect buttonBounds = menuButtonRect.getGlobalBounds();
    if (buttonBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if (!isHovered) {
            menuButtonRect.setFillColor(sf::Color(255, 0, 0)); // Highlight color on hover
            menuButtonRect.setOutlineColor(sf::Color::Yellow);
            menuButtonText.setFillColor(sf::Color::Yellow);
            isHovered = true;
        }
    } else {
        if (isHovered) {
            menuButtonRect.setFillColor(sf::Color(0, 0, 255)); // Default color
            menuButtonRect.setOutlineColor(sf::Color::White);
            menuButtonText.setFillColor(sf::Color::White);
            isHovered = false;
        }
    }
}

// Check if the "Go to Menu" button was clicked.
bool EndView::isMenuButtonClicked(const sf::Vector2i& mousePosition) {
    sf::FloatRect buttonBounds = menuButtonRect.getGlobalBounds();
    return buttonBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
}

// Render the end screen, including the background and button.
void EndView::render() {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(menuButtonRect);
    window.draw(menuButtonText);
    window.display();
}
