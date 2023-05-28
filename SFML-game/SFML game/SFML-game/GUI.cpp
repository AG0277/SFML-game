#include "GUI.h"

GUI::GUI(sf::Window* window)
{
    this->window = window;
    char test[24] = "Enter your username";
    char test1[24] = "Enter your password";
    for (int i = 0; i < 24; i++)
    {
        ubuf[i] = test[i];
        pbuf[i] = test1[i];
    }
    size = 10;


};
void GUI::loginmenu()
{

    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoBackground;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    ImGui::Begin("##LogIn",0,window_flags);
    int windowx = ImGui::GetWindowWidth();
    int windowy = ImGui::GetWindowHeight();
    ImVec2 middle(windowx / 3, windowy / 2);



    // username
    ImGui::SetCursorPos(middle);
    ImGui::LabelText("", "username");
    ImGui::SetCursorPosX(middle.x);
    ImGui::PushItemWidth(20*size);
    ImGui::SetItemAllowOverlap();
    ImGui::InputText("##username", ubuf, IM_ARRAYSIZE(ubuf), ImGuiInputTextFlags_AutoSelectAll);
    //ImGui::SetCursorPosX(middle.x);
    // ImGui::SetCursorPosY(middle.y+ImGui::CalcTextSize("username").y*0.8+ ImGui::CalcTextSize("##username").y);
    //if (ImGui::Button("##Username", buttonSize))
    //    for (int i = 0; i < 22; i++)
    //        ubuf[i] = '\0';
    



    //password
    ImGui::SetCursorPosX(middle.x);
    ImGui::LabelText("", "password");
    ImGui::SetCursorPosX(middle.x);
    ImGui::PushItemWidth(20 * size);
    ImGui::InputText("##password", pbuf, IM_ARRAYSIZE(pbuf), ImGuiInputTextFlags_AutoSelectAll);

    //log in button
    ImGui::SetCursorPosX(middle.x);
    ImVec2 tempbuttonSize(20 * size,2*size);
    ImGui::Button("LogIn",tempbuttonSize);
    ImGui::End();
    


    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    //ImVec4* colors = ImGui::GetStyle().Colors;
    //{
    //    colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);

    //    colors[ImGuiCol_FrameBg] = ImColor(11, 11, 11, 255);
    //    colors[ImGuiCol_FrameBgHovered] = ImColor(11, 11, 11, 255);

    //    colors[ImGuiCol_Button] = ImColor(255, 0, 46, 255);
    //    colors[ImGuiCol_ButtonActive] = ImColor(255, 0, 46, 255);
    //    colors[ImGuiCol_ButtonHovered] = ImColor(255, 0, 46, 255);

    //    colors[ImGuiCol_TextDisabled] = ImVec4(0.37f, 0.37f, 0.37f, 1.00f);
    //}

    //ImGuiStyle* style = &ImGui::GetStyle();
    //{
    //    style->WindowPadding = ImVec2(4, 4);
    //    style->WindowBorderSize = 0.f;

    //    style->FramePadding = ImVec2(8, 6);
    //    style->FrameRounding = 3.f;
    //    style->FrameBorderSize = 1.f;
    //}


    //bool acti = true;
    //bool* active = &acti;
    //bool acti1 = false;
    //bool* active1 = &acti1;

    //char user_name[255] = "Enter your username";
    //char pass_word[255] = "Enter your password";

    //char invite_key[255] = "Enter your invite key";

    //int button_opacity = 255;
    //bool doOnce = false;

    //bool show_login = true;
    //bool show_register = false;
    //// ImGui::SetNextWindowSize(iw.window_size);
    //const char* window_title = "Loader";
    //    ImGui::Begin(window_title, active);
    //    {
    //        ImGui::SetCursorPos(ImVec2(726, 5));
    //        ImGui::TextDisabled("X");
    //        if (ImGui::IsItemClicked())
    //        {
    //            active = active1;
    //        }

    //        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.054, 0.054, 0.054, 255));
    //        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.082, 0.078, 0.078, 255));
    //        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 3.f);
    //        {
    //            ImGui::SetCursorPos(ImVec2(222, 83));
    //            ImGui::BeginChild("##MainPanel", ImVec2(300, 276), true);
    //            {
    //                if (show_login)
    //                {
    //                    ImGui::SetCursorPos(ImVec2(118, 20));
    //                    ImGui::TextDisabled("Welcome Back");

    //                    ImGui::SetCursorPos(ImVec2(97, 35));
    //                    ImGui::Text("Log into your account");

    //                    ImGui::PushItemWidth(260.f);
    //                    {
    //                        ImGui::SetCursorPos(ImVec2(22, 79));
    //                        ImGui::TextDisabled("Username");

    //                        ImGui::SetCursorPos(ImVec2(20, 95));
    //                        ImGui::InputText("##Username", user_name, IM_ARRAYSIZE(user_name));
    //                    }
    //                    ImGui::PopItemWidth();

    //                    ImGui::PushItemWidth(260.f);
    //                    {
    //                        ImGui::SetCursorPos(ImVec2(22, 130));
    //                        ImGui::TextDisabled("Password");

    //                        ImGui::SetCursorPos(ImVec2(188, 130));
    //                        ImGui::TextDisabled("Forgot password?");

    //                        ImGui::SetCursorPos(ImVec2(20, 146));
    //                        ImGui::InputText("##Passowrd", pass_word, IM_ARRAYSIZE(pass_word));
    //                    }
    //                    ImGui::PopItemWidth();

    //                    ImGui::SetCursorPos(ImVec2(22, 190));
    //                    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.f);
    //                    if (ImGui::Button("Login", ImVec2(260.f, 30.f)))
    //                    {
    //                        show_login = false;
    //                        show_register = true;
    //                    }
    //                    ImGui::PopStyleVar();

    //                    ImGui::SetCursorPos(ImVec2(22, 240));
    //                    ImGui::TextDisabled("Don't have an account? Sign up!");
    //                }


    //                if (show_register)
    //                {
    //                    ImGui::SetCursorPos(ImVec2(118, 20));
    //                    ImGui::TextDisabled("Welcome Back");

    //                    ImGui::SetCursorPos(ImVec2(95, 35));
    //                    ImGui::Text("Register For An Account");

    //                    ImGui::PushItemWidth(260.f);
    //                    {
    //                        ImGui::SetCursorPos(ImVec2(22, 79));
    //                        ImGui::TextDisabled("Username");

    //                        ImGui::SetCursorPos(ImVec2(20, 95));
    //                        ImGui::InputText("##Username",user_name, IM_ARRAYSIZE(user_name));
    //                    }
    //                    ImGui::PopItemWidth();

    //                    ImGui::PushItemWidth(260.f);
    //                    {
    //                        ImGui::SetCursorPos(ImVec2(22, 130));
    //                        ImGui::TextDisabled("Invite Key");

    //                        ImGui::SetCursorPos(ImVec2(20, 146));
    //                        ImGui::InputText("##InviteKey", invite_key, IM_ARRAYSIZE(invite_key));
    //                    }
    //                    ImGui::PopItemWidth();

    //                    ImGui::SetCursorPos(ImVec2(22, 190));
    //                    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.f);
    //                    if (ImGui::Button("Register", ImVec2(260.f, 30.f)))
    //                    {
    //                        show_login = true;
    //                        show_register = false;
    //                    }
    //                    ImGui::PopStyleVar();

    //                    ImGui::SetCursorPos(ImVec2(22, 240));
    //                    ImGui::TextDisabled("Already have an account? Sign in now!");
    //                }

    //            }
    //            ImGui::EndChild();
    //        }
    //        ImGui::PopStyleColor(2);
    //        ImGui::PopStyleVar(1);

    //        ImGui::SetCursorPos(ImVec2(5, 445));
    //        ImGui::TextDisabled("Loader base, made with <3 by booget#0001");
    //    }
    //    ImGui::End();
  
}
bool GUI::createButton(const char* text, float x, float y, float posx, float posy)
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

    ImGui::Begin("Button", 0, window_flags);
    ImGui::SetCursorPos(buttonPos2);
    if (ImGui::Button(text, buttonSize))
    {
        ImGui::End();
        return true;
    }
    ImGui::End();
    return false;
}