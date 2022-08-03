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

#include "core/tdfi/view/refresh_header.h"
#include "renderer/tdf/viewnode/list_view_node.h"

namespace tdfrender {

inline namespace refreshwrapper {
constexpr const char kRefreshWrapper[] = "RefreshWrapper";
constexpr const char kBounceTime[] = "bounceTime";                    // int
constexpr const char kOnScrollEnable[] = "onScrollEnable";            // boolean
constexpr const char kScrollEventThrottle[] = "scrollEventThrottle";  // int
constexpr const char kRefreshComplected[] = "refreshComplected";
}  // namespace refreshwrapper

class HippyRefreshHeader : public tdfcore::RefreshHeader {
 public:
  explicit HippyRefreshHeader(std::shared_ptr<tdfcore::View> content_view)
      : tdfcore::RefreshHeader(), content_view_(std::move(content_view)) {}

  std::shared_ptr<tdfcore::View> GetView() override { return content_view_; }

  void Init() override;

 private:
  std::shared_ptr<tdfcore::View> content_view_;
};

class RefreshWrapperItemNode : public ViewNode {
 public:
  using ViewNode::ViewNode;

  /**
   * @brief make CreateView public,because it's call by RefreshWrapperNode
   */
  std::shared_ptr<tdfcore::View> CreateView() override;

  void HandleLayoutUpdate(hippy::LayoutResult layout_result) override;
};

class RefreshWrapperNode : public ViewNode {
 public:
  using ViewNode::ViewNode;
  static node_creator GetCreator();

  void OnChildAdd(const std::shared_ptr<ViewNode>& child, int64_t index) override;
  void OnChildRemove(const std::shared_ptr<ViewNode>& child) override;

 protected:
  void CallFunction(const std::string& name, const DomArgument& param, const uint32_t call_back_id) override;

 private:
  std::shared_ptr<tdfcore::View> CreateView() override;
  void HandleOffsetListener(int32_t position, double offset);
  std::shared_ptr<RefreshWrapperItemNode> item_node_;
  std::shared_ptr<HippyRefreshHeader> refresh_header_;
  uint32_t refresh_header_node_id_;
  std::shared_ptr<ListViewNode> list_node_;
};

}  // namespace tdfrender
