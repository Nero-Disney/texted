#include "TextViewContent.h"

TextViewContent::TextViewContent() {
    this->fontSize = 20;
    this->font.loadFromFile("FreeMono.ttf");
}

// TODO: Reemplazar fontSize por fontHeight especifica para cada tipo de font.
void TextViewContent::drawLines(sf::RenderWindow &window, TextDocument &document) {
    sf::Vector2u windowSize = window.getSize();

    for (int i = 0; i < document.getLineCount(); i++) {

        sf::Text textLine;
        textLine.setFont(font);

        // Estoy leyendo la misma string muchas veces, contando conversiones y todo..
        // Quiza me convenga usar sf::string[wide] desde el principio
        textLine.setString(this->toUtf32(document.getLine(i)));

        textLine.setCharacterSize(this->fontSize);
        textLine.setPosition(0, i * this->fontSize);

        // window.draw(line, 2, sf::Lines);
        window.draw(textLine);
    }
}

// [start, end] is inclusive
void TextViewContent::selectText(int start, int end) {
    this->selections.addSelection(start, end);
}

void TextViewContent::setFontSize(int fontSize) {
    this->fontSize = fontSize;
}

sf::String TextViewContent::toUtf32(const std::string& inString) {
    sf::String outString = "";
    auto iterEnd = inString.cend();

    // Decode avanza el iterador
    for (auto iter = inString.cbegin(); iter != iterEnd; ) {
        sf::Uint32 out;
        iter = sf::Utf8::decode(iter, iterEnd, out);
        outString += out;
    }

    return outString;
}

