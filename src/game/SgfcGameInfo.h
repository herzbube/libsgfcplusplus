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
#include "../../include/ISgfcGameInfo.h"
#include "../../include/ISgfcNode.h"

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGameInfo class provides an implementation of the
  /// ISgfcGameInfo interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup game-tree
  class SgfcGameInfo : virtual public ISgfcGameInfo
  {
  public:
    /// @brief Initializes a newly constructed SgfcGameInfo object with
    /// default values.
    SgfcGameInfo();

    /// @brief Initializes a newly constructed SgfcGameInfo object with values
    /// taken from the properties in root node @a rootNode. All values that
    /// would normally be taken from the properties in the game info node have
    /// default values.
    ///
    /// @exception std::invalid_argument Is thrown if @a rootNode is @e nullptr.
    SgfcGameInfo(std::shared_ptr<ISgfcNode> rootNode);

    /// @brief Initializes a newly constructed SgfcGameInfo object with values
    /// taken from the properties in root node @a rootNode and from game info
    /// node @a gameInfoNode.
    ///
    /// @exception std::invalid_argument Is thrown if @a rootNode is @e nullptr
    /// or if @a gameInfoNode is @e nullptr.
    SgfcGameInfo(std::shared_ptr<ISgfcNode> rootNode, std::shared_ptr<ISgfcNode> gameInfoNode);

    /// @brief Destroys and cleans up the SgfcGameInfo object.
    virtual ~SgfcGameInfo();

    virtual SgfcGameType GetGameType() const override;
    virtual SgfcNumber GetGameTypeAsNumber() override;
    virtual SgfcBoardSize GetBoardSize() const override;

    virtual SgfcSimpleText GetRecorderName() const override;
    virtual void SetRecorderName(const SgfcSimpleText& recorderName) override;
    virtual SgfcSimpleText GetSourceName() const override;
    virtual void SetSourceName(const SgfcSimpleText& sourceName) override;
    virtual SgfcSimpleText GetAnnotationAuthor() const override;
    virtual void SetAnnotationAuthor(const SgfcSimpleText& annotationAuthor) override;
    virtual SgfcSimpleText GetCopyrightInformation() const override;
    virtual void SetCopyrightInformation(const SgfcSimpleText& copyrightInformation) override;

    virtual SgfcSimpleText GetGameName() const override;
    virtual void SetGameName(const SgfcSimpleText& gameName) override;
    virtual SgfcText GetGameInformation() const override;
    virtual void SetGameInformation(const SgfcText& gameInformation) override;
    virtual std::vector<SgfcDate> GetGameDates() const override;
    virtual void SetGameDates(const std::vector<SgfcDate>& gameDates) override;
    virtual SgfcSimpleText GetRawGameDates() const override;
    virtual SgfcSimpleText GetRulesName() const override;
    virtual void SetRulesName(const SgfcSimpleText& rulesName) override;
    virtual SgfcGameResult GetGameResult() const override;
    virtual void SetGameResult(SgfcGameResult gameResult) override;
    virtual SgfcSimpleText GetRawGameResult() const override;

    virtual SgfcReal GetTimeLimitInSeconds() const override;
    virtual void SetTimeLimitInSeconds(SgfcReal timeLimitInSeconds) override;
    virtual SgfcSimpleText GetOvertimeInformation() const override;
    virtual void SetOvertimeInformation(const SgfcSimpleText& overtimeInformation) override;
    virtual SgfcSimpleText GetOpeningInformation() const override;
    virtual void SetOpeningInformation(const SgfcSimpleText& openingInformation) override;

    virtual SgfcSimpleText GetBlackPlayerName() const override;
    virtual void SetBlackPlayerName(const SgfcSimpleText& blackPlayerName) override;
    virtual SgfcSimpleText GetBlackPlayerRank() const override;
    virtual void SetBlackPlayerRank(const SgfcSimpleText& blackPlayerRank) override;
    virtual SgfcSimpleText GetBlackPlayerTeamName() const override;
    virtual void SetBlackPlayerTeamName(const SgfcSimpleText& blackPlayerTeamName) override;
    virtual SgfcSimpleText GetWhitePlayerName() const override;
    virtual void SetWhitePlayerName(const SgfcSimpleText& whitePlayerName) override;
    virtual SgfcSimpleText GetWhitePlayerRank() const override;
    virtual void SetWhitePlayerRank(const SgfcSimpleText& whitePlayerRank) override;
    virtual SgfcSimpleText GetWhitePlayerTeamName() const override;
    virtual void SetWhitePlayerTeamName(const SgfcSimpleText& whitePlayerTeamName) override;

    virtual SgfcSimpleText GetGameLocation() const override;
    virtual void SetGameLocation(const SgfcSimpleText& gameLocation) override;
    virtual SgfcSimpleText GetEventName() const override;
    virtual void SetEventName(const SgfcSimpleText& eventName) override;
    virtual SgfcRoundInformation GetRoundInformation() const override;
    virtual void SetRoundInformation(const SgfcRoundInformation& roundInformation) override;
    virtual SgfcSimpleText GetRawRoundInformation() const override;

    virtual const ISgfcGoGameInfo* ToGoGameInfo() const override;

    /// @brief Writes all root property values in the ISgfcGameInfo object
    /// to the corresponding properties in @a rootNode.
    ///
    /// @exception std::invalid_argument Is thrown if @a rootNode is
    /// @e nullptr.
    virtual void WriteToRootNode(std::shared_ptr<ISgfcNode> rootNode);

    /// @brief Writes all game info property values in the ISgfcGameInfo object
    /// to the corresponding properties in @a gameInfoNode.
    ///
    /// @exception std::invalid_argument Is thrown if @a gameInfoNode is
    /// @e nullptr.
    virtual void WriteToGameInfoNode(std::shared_ptr<ISgfcNode> gameInfoNode);

  protected:
    SgfcNumber GetNumberPropertyValue(std::shared_ptr<ISgfcProperty> property);
    SgfcReal GetRealPropertyValue(std::shared_ptr<ISgfcProperty> property);
    SgfcSimpleText GetSimpleTextPropertyValue(std::shared_ptr<ISgfcProperty> property);
    SgfcText GetTextPropertyValue(std::shared_ptr<ISgfcProperty> property);

  private:
    SgfcGameType gameType;
    SgfcNumber gameTypeAsNumber;
    SgfcBoardSize boardSize;

    SgfcSimpleText recorderName;
    SgfcSimpleText sourceName;
    SgfcSimpleText annotationAuthor;
    SgfcSimpleText copyrightInformation;

    SgfcSimpleText gameName;
    SgfcText gameInformation;
    std::vector<SgfcDate> gameDates;
    SgfcSimpleText rawGameDates;
    SgfcSimpleText rulesName;
    SgfcGameResult gameResult;
    SgfcSimpleText rawGameResult;

    SgfcReal timeLimitInSeconds;
    SgfcSimpleText overtimeInformation;
    SgfcSimpleText openingInformation;

    SgfcSimpleText blackPlayerName;
    SgfcSimpleText blackPlayerRank;
    SgfcSimpleText blackPlayerTeamName;
    SgfcSimpleText whitePlayerName;
    SgfcSimpleText whitePlayerRank;
    SgfcSimpleText whitePlayerTeamName;

    SgfcSimpleText gameLocation;
    SgfcSimpleText eventName;
    SgfcRoundInformation roundInformation;
    SgfcSimpleText rawRoundInformation;

    void ReadFromRootNode(std::shared_ptr<ISgfcNode> rootNode);
    void ReadFromGameInfoNode(std::shared_ptr<ISgfcNode> gameInfoNode);
  };
}
