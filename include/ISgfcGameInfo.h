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
#include "SgfcBoardSize.h"
#include "SgfcDate.h"
#include "SgfcGameResult.h"
#include "SgfcGameType.h"
#include "SgfcRoundInformation.h"
#include "SgfcTypedefs.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <string>
#include <vector>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcGoGameInfo;

  /// @brief The ISgfcGameInfo interface ia a collection of meta data that
  /// describes one SGF game. For instance, the meta data includes information
  /// such as the name of the game, when and where it was played, by whom, etc.
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  /// @ingroup game
  ///
  /// ISgfcGame or ISgfcNode can be queried to provide an ISgfcGameInfo object.
  /// The object is newly created and contains a snapshot of the property values
  /// of a few root properties (SgfcPropertyCategory::Root) and all game info
  /// properties (SgfcPropertyCategory::GameInfo) found in the root node and the
  /// game info node, respectively, at the time the query is made.
  ///
  /// Alternatively a new but empty ISgfcGameInfo object can be created via
  /// SgfcPlusPlusFactory and then populated with data as the library client
  /// sees fit.
  ///
  /// The values that an ISgfcGameInfo object holds can be written to an
  /// ISgfcGame or ISgfcNode. The values are converted to properties and
  /// property values that are then stored in the root node and the game info
  /// node, respectively. Properties and property values that already exist at
  /// that time are overwritten.
  ///
  /// Root property values are read-only - they must be provided at the time the
  /// ISgfcGameInfo object is constructed and cannot be changed later on. The
  /// reason is that changing these values in an ISgfcGameInfo object that was
  /// captured from a game tree and then later writing the ISgfcGameInfo object
  /// data back to the game tree would likely invalidate most if not all of the
  /// game tree's data.
  class SGFCPLUSPLUS_EXPORT ISgfcGameInfo
  {
  public:
    /// @brief Initializes a newly constructed ISgfcGameInfo object.
    ISgfcGameInfo();

    /// @brief Destroys and cleans up the ISgfcGameInfo object.
    virtual ~ISgfcGameInfo();

    /// @name Root properties (read only)
    //@{
    /// @brief Returns the game type. The default value is
    /// SgfcConstants::DefaultGameType.
    ///
    /// Returns #SgfcGameType::Unknown if the Number value of the GM property is
    /// not in the list of valid games defined in the SGF standard.
    ///
    /// @see SgfcPropertyType::GM
    virtual SgfcGameType GetGameType() const = 0;

    /// @brief Returns the game type as an SgfcNumber value. The default value
    /// is the SgfcNumber value that corresponds to
    /// SgfcConstants::DefaultGameType.
    ///
    /// This is useful if GetGameType() returns SgfcGameType::Unknown because
    /// the Number value of the GM property is not in the list of valid games
    /// defined in the SGF standard.
    ///
    /// @see SgfcPropertyType::GM
    virtual SgfcNumber GetGameTypeAsNumber() = 0;

    /// @brief Returns the size of the board on which the game was played. The
    /// default value is the default board size for
    /// SgfcConstants::DefaultGameType.
    ///
    /// Returns SgfcConstants::BoardSizeNone or SgfcConstants::BoardSizeInvalid
    /// if there is a problem with determining a valid board size from the SZ
    /// property. See ISgfcGame::GetBoardSize() for details.
    ///
    /// @see SgfcPropertyType::SZ
    virtual SgfcBoardSize GetBoardSize() const = 0;
    //@}

    /// @name Game data information
    //@{
    /// @brief Returns the name of the user (or program) who recorded or
    /// entered the game data. The default value is
    /// SgfcConstants::NoneValueString.
    ///
    /// @see SgfcPropertyType::US
    virtual SgfcSimpleText GetRecorderName() const = 0;
    /// @brief Sets the name of the user (or program) who recorded or entered
    /// the game data.
    ///
    /// @see SgfcPropertyType::US
    virtual void SetRecorderName(const SgfcSimpleText& recorderName) = 0;

    /// @brief Returns the name of the source of the game data (e.g. book,
    /// journal, etc.). The default value is SgfcConstants::NoneValueString.
    ///
    /// @see SgfcPropertyType::SO
    virtual SgfcSimpleText GetSourceName() const = 0;
    /// @brief Sets the name of the source of the game data (e.g. book,
    /// journal, etc.).
    ///
    /// @see SgfcPropertyType::SO
    virtual void SetSourceName(const SgfcSimpleText& sourceName) = 0;

    /// @brief Returns the name of the person who made the annotations to the
    /// game. The default value is SgfcConstants::NoneValueString.
    ///
    /// @see SgfcPropertyType::AN
    virtual SgfcSimpleText GetAnnotationAuthor() const = 0;
    /// @brief Sets the name of the person who made the annotations to the
    /// game.
    ///
    /// @see SgfcPropertyType::AN
    virtual void SetAnnotationAuthor(const SgfcSimpleText& annotationAuthor) = 0;

    /// @brief Returns the copyright information for the game data (including
    /// the annotations). The default value is SgfcConstants::NoneValueString.
    ///
    /// @see SgfcPropertyType::CP
    virtual SgfcSimpleText GetCopyrightInformation() const = 0;
    /// @brief Sets the copyright information for the game data (including
    /// the annotations).
    ///
    /// @see SgfcPropertyType::CP
    virtual void SetCopyrightInformation(const SgfcSimpleText& copyrightInformation) = 0;
    //@}

    /// @name Basic game information
    //@{
    /// @brief Returns the name of the game (e.g. for easily finding the game
    /// again within a collection). The default value is
    /// SgfcConstants::NoneValueString.
    ///
    /// @see SgfcPropertyType::GN
    virtual SgfcSimpleText GetGameName() const = 0;
    /// @brief Sets the name of the game (e.g. for easily finding the game
    /// again within a collection).
    ///
    /// @see SgfcPropertyType::GN
    virtual void SetGameName(const SgfcSimpleText& gameName) = 0;

    /// @brief Returns information about the game (e.g. background information,
    /// a game summary, etc.). The default value is
    /// SgfcConstants::NoneValueString.
    ///
    /// @see SgfcPropertyType::GC
    virtual SgfcText GetGameInformation() const = 0;
    /// @brief Sets information about the game (e.g. background information,
    /// a game summary, etc.).
    ///
    /// @see SgfcPropertyType::GC
    virtual void SetGameInformation(const SgfcText& gameInformation) = 0;

    /// @brief Returns the dates when the game was played, decomposed into
    /// years, optional months and optional days. Several non-consecutive dates
    /// are possible. The default value is an empty collection of dates.
    ///
    /// The returned collection is also empty if there is a problem with
    /// decomposing the raw property value. See SgfcDate::FromPropertyValue()
    /// for details. An indicator that this happened is if GetRawGameDates()
    /// returns a value that is not equal to SgfcConstants::NoneValueString.
    ///
    /// @see SgfcPropertyType::DT
    virtual std::vector<SgfcDate> GetGameDates() const = 0;
    /// @brief Sets the dates when the game was played, decomposed into
    /// years, optional months and optional days. Several non-consecutive dates
    /// are possible.
    ///
    /// Invoking this setter also changes the information returned by
    /// GetRawGameDates().
    ///
    /// @see SgfcPropertyType::DT
    virtual void SetGameDates(const std::vector<SgfcDate>& gameDates) = 0;
    /// @brief Returns the dates when the game was played. Several
    /// non-consecutive dates are possible. The default value is
    /// SgfcConstants::NoneValueString.
    ///
    /// This is useful if the raw game dates cannot be decomposed into years,
    /// optional months and optional days, as is required by the SGF standard
    /// for SgfcPropertyType::DT.
    ///
    /// @note There is no setter for the raw game dates value because the
    /// SGF standard @b requires a certain format in the raw property value,
    /// and that can be guaranteed only by forcing the library client to set
    /// the game dates via structured SgfcDate values.
    ///
    /// @see SgfcPropertyType::DT
    virtual SgfcSimpleText GetRawGameDates() const = 0;

    /// @brief Returns the name of the rules used for the game. The default
    /// value is SgfcConstants::NoneValueString.
    ///
    /// @see SgfcPropertyType::RU
    virtual SgfcSimpleText GetRulesName() const = 0;
    /// @brief Sets the name of the rules used for the game.
    ///
    /// @see SgfcPropertyType::RU
    virtual void SetRulesName(const SgfcSimpleText& rulesName) = 0;

    /// @brief Returns the result of the game, decomposed into an outcome and
    /// an optional score. The default value is an SgfcGameResult object which
    /// has the @e IsValid property set to false.
    ///
    /// The returned SgfcGameResult also has the @e IsValid property set to
    /// false if there is a problem with decomposing the raw property value.
    /// See SgfcGameResult::FromPropertyValue() for details. An indicator that
    /// this happened is if GetRawGameResult() returns a value that is not equal
    /// to SgfcConstants::NoneValueString.
    ///
    /// @see SgfcPropertyType::RE
    virtual SgfcGameResult GetGameResult() const = 0;
    /// @brief Sets the result of the game, decomposed into an outcome and
    /// an optional score.
    ///
    /// Invoking this setter also changes the information returned by
    /// GetRawGameResult().
    ///
    /// @see SgfcPropertyType::RE
    virtual void SetGameResult(SgfcGameResult gameResult) = 0;
    /// @brief Returns the result of the game. The default value is
    /// SgfcConstants::NoneValueString.
    ///
    /// This is useful if the raw game result cannot be decomposed into an
    /// outcome and an optional score as is required by the SGF standard for
    /// SgfcPropertyType::RE.
    ///
    /// @note There is no setter for the raw game result value because the
    /// SGF standard @b requires a certain format in the raw property value,
    /// and that can be guaranteed only by forcing the library client to set
    /// the game result via a structured SgfcGameResult value.
    ///
    /// @see SgfcPropertyType::RE
    virtual SgfcSimpleText GetRawGameResult() const = 0;
    //@}

    /// @name Extra game information
    //@{
    /// @brief Returns the time limit of the game in seconds. The default value
    /// is 0.0.
    ///
    /// @see SgfcPropertyType::TM
    virtual SgfcReal GetTimeLimitInSeconds() const = 0;
    /// @brief Sets the time limit of the game in seconds.
    ///
    /// @see SgfcPropertyType::TM
    virtual void SetTimeLimitInSeconds(SgfcReal timeLimitInSeconds) = 0;

    /// @brief Returns the description of the method used for overtime
    /// (byo-yomi). The default value is SgfcConstants::NoneValueString.
    ///
    /// @see SgfcPropertyType::OT
    virtual SgfcSimpleText GetOvertimeInformation() const = 0;
    /// @brief Sets the description of the method used for overtime
    /// (byo-yomi).
    ///
    /// @see SgfcPropertyType::OT
    virtual void SetOvertimeInformation(const SgfcSimpleText& overtimeInformation) = 0;

    /// @brief Returns information about the opening played. The default value
    /// is SgfcConstants::NoneValueString.
    ///
    /// @see SgfcPropertyType::ON
    virtual SgfcSimpleText GetOpeningInformation() const = 0;
    /// @brief Sets the information about the opening played.
    ///
    /// @see SgfcPropertyType::ON
    virtual void SetOpeningInformation(const SgfcSimpleText& openingInformation) = 0;
    //@}

    /// @name Player information
    //@{
    /// @brief Returns the name of the black player. The default value is an
    /// empty string.
    ///
    /// @see SgfcPropertyType::PB
    virtual SgfcSimpleText GetBlackPlayerName() const = 0;
    /// @brief Sets the name of the black player.
    ///
    /// @see SgfcPropertyType::PB
    virtual void SetBlackPlayerName(const SgfcSimpleText& blackPlayerName) = 0;

    /// @brief Returns the rank of the black player. The default value is an
    /// empty string.
    ///
    /// @see SgfcPropertyType::BR
    virtual SgfcSimpleText GetBlackPlayerRank() const = 0;
    /// @brief Sets the rank of the black player.
    ///
    /// @see SgfcPropertyType::BR
    virtual void SetBlackPlayerRank(const SgfcSimpleText& blackPlayerRank) = 0;

    /// @brief Returns the name of the black player's team. The default value
    /// is SgfcConstants::NoneValueString.
    ///
    /// @see SgfcPropertyType::BT
    virtual SgfcSimpleText GetBlackPlayerTeamName() const = 0;
    /// @brief Sets the name of the black player's team.
    ///
    /// @see SgfcPropertyType::BT
    virtual void SetBlackPlayerTeamName(const SgfcSimpleText& blackPlayerTeamName) = 0;

    /// @brief Returns the name of the white player. The default value is an
    /// empty string.
    ///
    /// @see SgfcPropertyType::PW
    virtual SgfcSimpleText GetWhitePlayerName() const = 0;
    /// @brief Sets the name of the white player.
    ///
    /// @see SgfcPropertyType::PW
    virtual void SetWhitePlayerName(const SgfcSimpleText& whitePlayerName) = 0;

    /// @brief Returns the rank of the white player. The default value is an
    /// empty string.
    ///
    /// @see SgfcPropertyType::WR
    virtual SgfcSimpleText GetWhitePlayerRank() const = 0;
    /// @brief Sets the rank of the white player.
    ///
    /// @see SgfcPropertyType::WR
    virtual void SetWhitePlayerRank(const SgfcSimpleText& whitePlayerRank) = 0;

    /// @brief Returns the name of the white player's team. The default value
    /// is SgfcConstants::NoneValueString.
    ///
    /// @see SgfcPropertyType::WT
    virtual SgfcSimpleText GetWhitePlayerTeamName() const = 0;
    /// @brief Sets the name of the white player's team.
    ///
    /// @see SgfcPropertyType::WT
    virtual void SetWhitePlayerTeamName(const SgfcSimpleText& whitePlayerTeamName) = 0;
    //@}

    /// @name Context in which the game was played
    //@{
    /// @brief Returns the name or description of the location where the game
    /// was played. The default value is SgfcConstants::NoneValueString.
    ///
    /// @see SgfcPropertyType::PC
    virtual SgfcSimpleText GetGameLocation() const = 0;
    /// @brief Sets the name or description of the location where the game
    /// was played.
    ///
    /// @see SgfcPropertyType::PC
    virtual void SetGameLocation(const SgfcSimpleText& gameLocation) = 0;

    /// @brief Returns the name of the event (e.g. tournament) where the game
    /// was played. The default value is SgfcConstants::NoneValueString.
    ///
    /// @see SgfcPropertyType::EV
    virtual SgfcSimpleText GetEventName() const = 0;
    /// @brief Sets the name of the event (e.g. tournament) where the game
    /// was played.
    ///
    /// @see SgfcPropertyType::EV
    virtual void SetEventName(const SgfcSimpleText& eventName) = 0;

    /// @brief Returns the information that describes the round in which the
    /// game was played, decomposed into round number and type of round.
    /// The default value is an SgfcRoundInformation object which has the
    /// @e IsValid property set to false.
    ///
    /// The returned SgfcRoundInformation also has the @e IsValid property set
    /// to false if there is a problem with decomposing the raw property value.
    /// See SgfcRoundInformation::FromPropertyValue() for details. An indicator
    /// that this happened is if GetRawRoundInformation() returns a value that
    /// is not equal to SgfcConstants::NoneValueString.
    ///
    /// @see SgfcPropertyType::RO
    virtual SgfcRoundInformation GetRoundInformation() const = 0;
    /// @brief Sets the information that describes the round in which the
    /// game was played, decomposed into round number and type of round.
    ///
    /// Invoking this setter also changes the information returned by
    /// GetRawRoundInformation().
    ///
    /// @see SgfcPropertyType::RO
    virtual void SetRoundInformation(const SgfcRoundInformation& roundInformation) = 0;
    /// @brief Returns the information that describes the round in which the
    /// game was played. The default value is SgfcConstants::NoneValueString.
    ///
    /// This is useful if the raw round information cannot be decomposed into
    /// round number and type of round as recommended by the SGF standard for
    /// SgfcPropertyType::RO.
    ///
    /// @note There is no setter for the raw round information value because the
    /// SGF standard @b requires a certain format in the raw property value,
    /// and that can be guaranteed only by forcing the library client to set
    /// the round information via a structured SgfcRoundInformation value.
    ///
    /// @see SgfcPropertyType::RO
    virtual SgfcSimpleText GetRawRoundInformation() const = 0;
    //@}

    /// @brief Returns an ISgfcGoGameInfo object if the ISgfcGameInfo object
    /// was created specifically for SgfcGameType::Go. Returns @e nullptr
    /// otherwise. The caller is not the owner of the returned object.
    virtual const ISgfcGoGameInfo* ToGoGameInfo() const = 0;
  };
}
