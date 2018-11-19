/*
 * Copyright (c) 2018 Isetta
 */
#pragma once

#include <list>
#include <string>
#include "Core/Config/CVar.h"
#include "GLFW/glfw3.h"
#include "Horde3D/Horde3D.h"

namespace Isetta {
class ISETTA_API_DECLARE RenderModule {
 public:
  struct RenderConfig {
    CVar<int> hordeLoadTextures{"horde_load_textures", 1};
    CVar<int> hordeTexCompression{"horde_tex_compression", 0};
    CVar<int> hordeMaxAnisotropy{"horde_max_abusotropy", 4};
    CVar<int> hordeShadowmapSize{"horde_shadowmap_size", 2048};
    CVar<int> hordeFastAnimation{"horde_fast_animation", 1};
    CVar<int> hordeSampleCount{"horde_sample_count", 0};
    CVar<int> hordeDumpFailedShaders{"horde_dump_failed_shaders", 1};
    CVarString hordePipeline{"horde_pipeline",
                             "pipelines/forward.pipeline.xml"};
  };

  static void LoadResourceFromDisk(H3DRes resource, std::string errorMessage);

  /**
   * \brief The array of animation nodes
   */
  std::list<class AnimationComponent*> animationComponents;
  std::list<class MeshComponent*> meshComponents;
  std::list<class LightComponent*> lightComponents;
  std::list<class CameraComponent*> cameraComponents;
  std::list<class ParticleSystemComponent*> particleSystemComponents;

 private:
  RenderModule() = default;
  ~RenderModule() = default;

  void StartUp(GLFWwindow* win);
  void Update(float deltaTime);
  void ShutDown();

  int renderInterface;
  static std::string resourcePath;

  void InitRenderConfig();
  void InitHordeConfig();
  void InitH3D();
  void InitResources();

  // Engine objects
  int curPipeline;

  H3DRes pipelineRes;
  GLFWwindow* winHandle;

  friend class CameraComponent;
  friend class EngineLoop;
};
}  // namespace Isetta
