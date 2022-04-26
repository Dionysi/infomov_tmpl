#include "tmpl/App.h"
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

class DemoApp : public App {

public:
	DemoApp(uint width, uint height) : App(width, height) { }

protected:
	void Tick(float dt) override {

	}
	void Draw(float dt) override {

	}
	void RenderGUI(float dt) override {
		// feed inputs to dear imgui, start new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		const static char* windowTitle = "Debug";
		static bool display = true;
		ImGui::Begin(windowTitle, &display, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::SetWindowFontScale(1.5f);
		ImGui::Text("Frame-time: %.1f", dt * 1000.0f);
		ImGui::End();

		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
};

int main() {
	DemoApp* app = new DemoApp(1080, 720);
	app->Run();

	return 0;
}