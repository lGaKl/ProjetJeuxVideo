#include "MenuView.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// Constructor for MenuView: Initializes the menu window and its graphical elements.
MenuView::MenuView(sf::RenderWindow& window) : window(window), isHovered(false) {
    // Create the menu window with desktop screen dimensions.
    window.create(sf::VideoMode::getDesktopMode(), "Menu", sf::Style::Default);

    // Load the background image.
    if (!backgroundTexture.loadFromFile("Image/GoldoCPC_Title_Overscan.png")) {
        std::cerr << "Error: Unable to load the background image!\n";
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Scale the background image to fit the window size.
    float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    // Load the font for the menu text.
    if (!font.loadFromFile("retro-land-mayhem.ttf")) {
        std::cerr << "Error: Unable to load the font!\n";
    }

    // Configure the start button's rectangle.
    startButtonRect.setSize(sf::Vector2f(750.f, 150.f)); // Set the button's dimensions.
    startButtonRect.setFillColor(sf::Color(0, 0, 255));  // Initial fill color (blue).
    startButtonRect.setOutlineColor(sf::Color::White);   // Outline color.
    startButtonRect.setOutlineThickness(4.f);           // Outline thickness.
    startButtonRect.setPosition(
        (window.getSize().x - startButtonRect.getSize().x) / 2, // Center horizontally.
        (window.getSize().y - startButtonRect.getSize().y) / 2  // Center vertically.
    );

    // Configure the start button's text.
    startButtonText.setFont(font);                           // Set the font.
    startButtonText.setString("Start Game");                 // Set the text string.
    startButtonText.setCharacterSize(80);                    // Set the font size.
    startButtonText.setFillColor(sf::Color::White);          // Set the text color.
    startButtonText.setPosition(
        startButtonRect.getPosition().x +
        (startButtonRect.getSize().x - startButtonText.getLocalBounds().width) / 2,  // Center text horizontally within the button.
        startButtonRect.getPosition().y +
        (startButtonRect.getSize().y - startButtonText.getLocalBounds().height) / 2 - 10 // Center text vertically within the button.
    );
}

// Updates the hover state of the start button based on the mouse position.
void MenuView::updateHoverState(const sf::Vector2i& mousePosition) {
    // Get the bounding box of the start button.
    sf::FloatRect buttonBounds = startButtonRect.getGlobalBounds();

    // Check if the mouse is hovering over the button.
    if (buttonBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if (!isHovered) {
            // Change the button's style to indicate hover state.
            startButtonRect.setFillColor(sf::Color(255, 0, 0));    // Change fill color to red.
            startButtonRect.setOutlineColor(sf::Color::Yellow);    // Change outline color to yellow.
            startButtonText.setFillColor(sf::Color::Yellow);       // Change text color to yellow.
            isHovered = true;
        }
    } else {
        if (isHovered) {
            // Revert the button's style to its default state.
            startButtonRect.setFillColor(sf::Color(0, 0, 255));    // Default fill color (blue).
            startButtonRect.setOutlineColor(sf::Color::White);     // Default outline color (white).
            startButtonText.setFillColor(sf::Color::White);        // Default text color (white).
            isHovered = false;
        }
    }
}

// Renders the menu by drawing the background, button, and button text.
void MenuView::render() {
    window.clear();                       // Clear the window for a new frame.
    window.draw(backgroundSprite);        // Draw the background.
    window.draw(startButtonRect);         // Draw the start button.
    window.draw(startButtonText);         // Draw the text on the button.
    window.display();                     // Display the rendered frame.
}

// Checks if the start button was clicked based on the mouse position.
bool MenuView::isStartButtonClicked(const sf::Vector2i& mousePosition) {
    // Get the bounding box of the start button.
    sf::FloatRect buttonBounds = startButtonRect.getGlobalBounds();

    // Return true if the mouse position is within the button's bounds.
    return buttonBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
}
