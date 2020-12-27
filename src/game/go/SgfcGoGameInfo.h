// -----------------------------------------------------------------------------
// Copyright 2020 Patrick Näf (herzbube@herzbube.ch)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// -----------------------------------------------------------------------------

#pragma once

// Project includes
#include "../../../include/ISgfcGoGameInfo.h"
#include "../SgfcGameInfo.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGoGameInfo class provides an implementation of the
  /// ISgfcGoGameInfo interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup game-tree
  class SgfcGoGameInfo : public SgfcGameInfo, public ISgfcGoGameInfo
  {
  public:
    /// @brief Initializes a newly constructed SgfcGoGameInfo object.
    SgfcGoGameInfo();

    /// @brief Initializes a newly constructed SgfcGoGameInfo object with values
    /// taken from the properties in root node @a rootNode. All values that
    /// would normally be taken from the properties in the game info node have
    /// default values.
    ///
    /// @exception std::invalid_argument Is thrown if @a rootNode is @e nullptr.
    SgfcGoGameInfo(std::shared_ptr<ISgfcNode> rootNode);

    /// @brief Initializes a newly constructed SgfcGoGameInfo object with values
    /// taken from the properties in root node @a rootNode and from game info
    /// node @a gameInfoNode.
    ///
    /// @exception std::invalid_argument Is thrown if @a rootNode is @e nullptr
    /// or if @a gameInfoNode is @e nullptr.
    SgfcGoGameInfo(std::shared_ptr<ISgfcNode> rootNode, std::shared_ptr<ISgfcNode> gameInfoNode);

    /// @brief Destroys and cleans up the SgfcGoGameInfo object.
    virtual ~SgfcGoGameInfo();

    virtual SgfcNumber GetNumberOfHandicapStones() const override;
    virtual void SetNumberOfHandicapStones(SgfcNumber numberOfHandicapStones) override;
    virtual SgfcReal GetKomi() const override;
    virtual void SetKomi(SgfcReal komi) override;
    virtual SgfcGoRuleset GetGoRuleset() const override;
    virtual void SetRuleset(SgfcGoRuleset goRuleset) override;
    virtual void SetRulesName(const SgfcSimpleText& rulesName) override;

    virtual SgfcGoPlayerRank GetGoBlackPlayerRank() const override;
    virtual void SetBlackPlayerRank(SgfcGoPlayerRank goBlackPlayerRank) override;
    virtual void SetBlackPlayerRank(const SgfcSimpleText& blackPlayerRank) override;
    virtual SgfcGoPlayerRank GetGoWhitePlayerRank() const override;
    virtual void SetWhitePlayerRank(SgfcGoPlayerRank goWhitePlayerRank) override;
    virtual void SetWhitePlayerRank(const SgfcSimpleText& whitePlayerRank) override;

    virtual const ISgfcGoGameInfo* ToGoGameInfo() const override;

    virtual void WriteToGameInfoNode(std::shared_ptr<ISgfcNode> gameInfoNode) override;

  private:
    SgfcNumber numberOfHandicapStones;
    SgfcReal komi;
    SgfcGoRuleset goRuleset;
    SgfcGoPlayerRank goBlackPlayerRank;
    SgfcGoPlayerRank goWhitePlayerRank;

    void ReadFromRootNode(std::shared_ptr<ISgfcNode> rootNode);
    void ReadFromGameInfoNode(std::shared_ptr<ISgfcNode> gameInfoNode);
  };
}
