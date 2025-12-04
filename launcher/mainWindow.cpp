// ===================== begin_copyright_notice ============================
//
// Copyright (C) 2023-2025 Intel Corporation
//
// SPDX-License-Identifier: MIT
//
// ===================== end_copyright_notice ==============================

#include "mainWindow.h"
#include "context.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include "imgui.h"
#include "imGuiHelper.h"

namespace gits::gui {
#ifdef _WIN32
GUIController::GUIController(HWND hwnd) : m_Handle(hwnd), m_CleanUpAfterRecording(true) {
  // nothing to do here
}
#else
GUIController::GUIController() : m_CleanUpAfterRecording(true) {
  // nothing to do here
}
#endif
void GUIController::DrawGui() {
  const auto& io = ImGui::GetIO();
  ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSize(io.DisplaySize);

  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 4.0f);
  ImGui::Begin("Full Window", nullptr,
               ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize);
  RenderUI();
  ImGui::End();
  ImGui::PopStyleVar();
}

void GUIController::Resized() {
  #ifdef _WIN32
  RECT rect;
  GetWindowRect(m_Handle, &rect);
  ImVec2 size = ImVec2(static_cast<float>(rect.right - rect.left),
                       static_cast<float>(rect.bottom - rect.top));
  m_LauncherConfig.WindowSize = size;
  #endif
}

void GUIController::Positioned() {
  #ifdef _WIN32
  RECT rect;
  GetWindowRect(m_Handle, &rect);
  ImVec2 position = ImVec2(static_cast<float>(rect.left), static_cast<float>(rect.top));
  m_LauncherConfig.WindowPos = position;
  #endif
}
} // namespace gits::gui
