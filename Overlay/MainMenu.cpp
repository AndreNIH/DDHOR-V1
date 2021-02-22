#include "MainMenu.h"
#include "ImGUIPlus/Tabs.h"
#include "ImGUIPlus/StringAlignment.h"
#include <imgui-ext/ImGuiFileDialog.h>
char macroFolderPath[_MAX_PATH] = {0};
bool openDirSuccess;

void populateHomeTab() {
    const char* ddhorLogo =
        "d8888b. d8888b. db   db  .d88b.  d8888b. \n"
        "88  `8D 88  `8D 88   88 .8P  Y8. 88  `8D \n"
        "88   88 88   88 88ooo88 88    88 88oobY' \n"
        "88   88 88   88 88~~~88 88    88 88`8b   \n"
        "88  .8D 88  .8D 88   88 `8b  d8' 88 `88. \n"
        "Y8888D' Y8888D' YP   YP  `Y88P'  88   YD ";

    ImGUIPlus::String::centerText(ddhorLogo);
    ImGui::Spacing();
    ImGui::Text("Version: 1.0.7");
    
    ImGui::Text("Macros Folder:");
    ImGui::SameLine();
    ImGui::PushID(1);
    ImGui::InputText("", macroFolderPath, _MAX_PATH);
    ImGui::PopID();
    ImGui::SameLine();
    
    if (ImGui::Button("..."))
        ImGuiFileDialog::Instance()->OpenDialog(
            "ChooseDirDlgKey",
            "Choose a Macro Directory",
            nullptr,
            "");
    if (ImGuiFileDialog::Instance()->Display("ChooseDirDlgKey")) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            strcpy_s(macroFolderPath, filePathName.c_str());
        }
        ImGuiFileDialog::Instance()->Close();
    }
    ImGui::Dummy({ 0,20 });
    
    if(ImGui::Button("Open Hacks Menu   ")){}
    if(ImGui::Button("Open Settings Menu")) {}
    
}

void populatePlayTab() {

}

void populateRecordTab() {

}


void MainMenu::createMenu(){
    ImGui::Begin("DDHORBot Menu");
    ImGUIPlus::Tabs menuTab("MenuTabs");
    menuTab.populate("Home", populateHomeTab);
    menuTab.populate("Play", populatePlayTab);
    menuTab.populate("Record", populateRecordTab);
    menuTab.finalize();
    ImGui::End();

}
