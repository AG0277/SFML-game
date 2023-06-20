#include "pch.h"
#include "GUI.h"



bool GUI::createButton(const char* text, int x, int y, int posx, int posy,std::vector<float> color, std::vector<float> textColor)
{
    buttonSize.x = x;
    buttonSize.y = y;
    ImVec2 buttonPos2(posx, posy);
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoBackground;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    window_flags |= ImGuiWindowFlags_NoScrollbar;

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(color.at(0), color.at(1), color.at(2), color.at(3)));
    ImGui::Begin("Button", 0, window_flags);
    ImGui::SetCursorPos(buttonPos2);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(textColor.at(0), textColor.at(1), textColor.at(2), textColor.at(3)));
    if (ImGui::Button(text,buttonSize))
    {
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::End();
        return true;
    }
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    ImGui::End();

    return false;
}

sf::Text GUI::createText(const std::string& inputtext, const sf::Font& font, unsigned int charsize, float posY, float posX )
{
    sf::Text text;
    text.setString(inputtext);
    text.setFont(font);
    text.setCharacterSize(charsize);
    if (posX == 0)
        text.setPosition((float)this->window->getSize().x / 2 - text.getGlobalBounds().width / 2, posY);
    else
        text.setPosition(posX, posY);

    return text;
}
