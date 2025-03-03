#include "demo_layer.hpp"

#include "sampo/input/input.hpp"
#include "sampo/input/keyboard.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

#if SAMPO_PLATFORM_WINDOWS
	#include "platform/opengl/opengl_shader.hpp"
#endif 

DemoLayer::DemoLayer()
	: Sampo::Layer("DemoLayer")
	, m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	, m_Keyboard(nullptr)
{
}

void DemoLayer::OnAttach()
{
	Sampo::Application& application = Sampo::Application::GetInstance();
	Sampo::Input& input = application.GetPlatform()->GetInput();
	if (const unsigned int index = input.GetFirstInputDeviceIndexByType(Sampo::InputType::kKeyboard) != -1)
		m_Keyboard = static_cast<const Sampo::Keyboard*>(input.GetInputDevice(index));

	m_SquareVA = Sampo::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		 -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
	};

	std::shared_ptr<Sampo::VertexBuffer> squareVB = Sampo::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({ 
		{ Sampo::ShaderDataType::Float3, "aPosition" },
		{ Sampo::ShaderDataType::Float2, "aTextureCoord" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32 squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	std::shared_ptr<Sampo::IndexBuffer> squareIB = Sampo::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32));
	m_SquareVA->SetIndexBuffer(squareIB);

	const std::string vertexSquareSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 aPosition;

			uniform mat4 uViewProjection;
			uniform mat4 uTransform;

			out vec3 vPosition;

			void main()
			{
				vPosition = aPosition;
				gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
			}
		)";

	const std::string fragmentSquareSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 colorOut;

			in vec3 vPosition;

			uniform vec3 uColor;

			void main()
			{
				colorOut = vec4(uColor, 1.0);
			}
		)";

	m_SquareShader = Sampo::Shader::Create(vertexSquareSource, fragmentSquareSource);

	m_TextureShader = Sampo::Shader::Create("../../../../../demo/data/assets/shaders/texture.glsl");

	m_Texture = Sampo::Texture2D::Create("../../../../../demo/data/assets/textures/checkerboard.png");
	m_TransparentTexture = Sampo::Texture2D::Create("../../../../../demo/data/assets/textures/transparent_test.png");

	std::shared_ptr<Sampo::OpenGLShader> texture = std::dynamic_pointer_cast<Sampo::OpenGLShader>(m_TextureShader);
	texture->Bind();
	texture->UploadUniformInt("uTexture", 0);
}

void DemoLayer::OnUpdate(Sampo::Timestep aDeltaTime)
{
	if (m_Keyboard->GetIsButtonPressed(Sampo::KeyboardButton::kLEFT))
		m_CameraPosition.x -= m_CameraMoveSpeed * aDeltaTime;
	if (m_Keyboard->GetIsButtonPressed(Sampo::KeyboardButton::kRIGHT))
		m_CameraPosition.x += m_CameraMoveSpeed * aDeltaTime;
	if (m_Keyboard->GetIsButtonPressed(Sampo::KeyboardButton::kDOWN))
		m_CameraPosition.y -= m_CameraMoveSpeed * aDeltaTime;
	if (m_Keyboard->GetIsButtonPressed(Sampo::KeyboardButton::kUP))
		m_CameraPosition.y += m_CameraMoveSpeed * aDeltaTime;

	if (m_Keyboard->GetIsButtonPressed(Sampo::KeyboardButton::kA))
		m_CameraRotation += m_CameraRotationSpeed * aDeltaTime;
	if (m_Keyboard->GetIsButtonPressed(Sampo::KeyboardButton::kD))
		m_CameraRotation -= m_CameraRotationSpeed * aDeltaTime;

	m_Camera.SetPosition(m_CameraPosition);
	m_Camera.SetRotation(m_CameraRotation);

	Sampo::RenderCommand::Clear();

	Sampo::Renderer::BeginScene(m_Camera);

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	glm::vec4 redColor(0.75f, 0.25f, 0.35f, 1.0f);
	glm::vec4 blueColor(0.25f, 0.35f, 0.75f, 1.0f);

	std::shared_ptr<Sampo::OpenGLShader> squareShader = std::dynamic_pointer_cast<Sampo::OpenGLShader>(m_SquareShader);
	squareShader->Bind();
	squareShader->UploadUniformFloat3("uColor", m_SquareColor);

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 position(x * 0.175f, y * 0.175f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;
			Sampo::Renderer::Submit(m_SquareShader, m_SquareVA, transform);
		}
	}

	m_Texture->Bind();
	Sampo::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.50f)));

	m_TransparentTexture->Bind();
	Sampo::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.50f)));

	Sampo::Renderer::EndScene();
}

void DemoLayer::OnImGuiRender()
{
	ImGui::Begin("DemoSettings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}
