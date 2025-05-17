#include "ShaderWidget.h"

#include "GraphicsEngine/IEngine.h"

ShaderWidget::ShaderWidget (GLFWwindow* spWindow, graphics_engine::IEnginePtr spEngine)
	: Widget(spWindow, spEngine)
{
}

auto ShaderWidget::Iterate (bool* pShow) -> void
{
	ImGui::Begin ("Shader", pShow, ImGuiWindowFlags_AlwaysAutoResize);
	auto oldDisabledAlpha = ImGui::GetStyle ().DisabledAlpha;
	ImGui::GetStyle ().DisabledAlpha = 1.f;

	auto pShader = GetEngine ()->GetShaderManager ()->GetCurrentShader ();
	
	int shaderId = pShader->ID;
	ImGui::BeginDisabled ();
	ImGui::DragInt ("Shader Id", &shaderId);

	int id = 0;
	auto DisplayMat4 = [&id] (const glm::mat4& mat)
		{
			std::array<float, 4> row0 = { mat[0][0], mat[1][0], mat[2][0], mat[3][0] };
			std::array<float, 4> row1 = { mat[0][1], mat[1][1], mat[2][1], mat[3][1] };
			std::array<float, 4> row2 = { mat[0][2], mat[1][2], mat[2][2], mat[3][2] };
			std::array<float, 4> row3 = { mat[0][3], mat[1][3], mat[2][3], mat[3][3] };
			ImGui::PushID (id); ImGui::InputFloat4 ("##", row0.data ()); ImGui::PopID (); ++id;
			ImGui::PushID (id); ImGui::InputFloat4 ("##", row1.data ()); ImGui::PopID (); ++id;
			ImGui::PushID (id); ImGui::InputFloat4 ("##", row2.data ()); ImGui::PopID (); ++id;
			ImGui::PushID (id); ImGui::InputFloat4 ("##", row3.data ()); ImGui::PopID (); ++id;
		};

	if (auto oMat = pShader->GetUniformData ("model"))
	{
		if (std::holds_alternative<glm::mat4> (*oMat))
		{
			ImGui::Text ("model");
			DisplayMat4 (std::get<glm::mat4> (*oMat));
		}
	}
	if (auto oMat = pShader->GetUniformData ("projection"))
	{
		if (std::holds_alternative<glm::mat4> (*oMat))
		{
			ImGui::Text ("projection");
			DisplayMat4 (std::get<glm::mat4>(*oMat));
		}
	}
	if (auto oMat = pShader->GetUniformData ("transformationMatrix"))
	{
		if (std::holds_alternative<glm::mat4> (*oMat))
		{
			ImGui::Text ("transformationMatrix");
			DisplayMat4 (std::get<glm::mat4> (*oMat));
		}
	}
	if (auto oMat = pShader->GetUniformData ("view"))
	{
		if (std::holds_alternative<glm::mat4> (*oMat))
		{
			ImGui::Text ("view");
			DisplayMat4 (std::get<glm::mat4> (*oMat));
		}
	}

	ImGui::EndDisabled ();

	ImGui::GetStyle ().DisabledAlpha = oldDisabledAlpha;
	ImGui::End ();
}

auto CreateShaderWidget (GLFWwindow* pWindow, graphics_engine::IEnginePtr spEngine) -> ShaderWidgetPtr
{
	return std::make_shared<ShaderWidget> (pWindow, spEngine);
}
