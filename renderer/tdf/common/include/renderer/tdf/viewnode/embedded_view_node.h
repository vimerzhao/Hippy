/**
 * Tencent is pleased to support the open source community by making
 * Hippy available.
 *
 * Copyright (C) 2022 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "renderer/tdf/viewnode/view_node.h"

namespace tdfrender {

class EmbeddedViewNode : public ViewNode {
 public:
  ~EmbeddedViewNode() override = default;
  using ViewNode::ViewNode;
  EmbeddedViewNode(RenderInfo render_info, const std::string &view_type);

 protected:
  void HandleStyleUpdate(const DomStyleMap &dom_style) override;

 private:
  std::shared_ptr<tdfcore::View> CreateView() override;

  std::map<std::string, std::string> property_;
  std::string native_view_type_;
};

}  // namespace tdfrender
