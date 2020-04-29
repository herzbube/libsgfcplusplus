#pragma once

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

namespace LibSgfcPlusPlus
{
  /// @brief SgfcPropertyType enumerates all property types defined by the SGF
  /// standard, plus a small number of non-standard property types that are
  /// specially handled by SGFC. The enum value SgfcPropertyType::Unknown is
  /// used for all other non-standard properties.
  enum class SGFCPLUSPLUS_EXPORT SgfcPropertyType
  {
    // ----------------------------------------------------------------------
    // Standard properties from FF4
    // ----------------------------------------------------------------------

    /// @brief Execute black move. Property value type: Move.
    ///
    /// This is a move property.
    B,
    /// @brief Execute a black or white move within the same node even if it is
    /// illegal. The property is illegal if there isn't a black or white move
    /// within the same node. Property value type: None.
    ///
    /// This is a move property.
    KO,
    /// @brief Set the move number of a move specified in the same node as this
    /// property to the given value. Property value type: Number.
    ///
    /// This is a move property.
    MN,
    /// @brief Execute white move. Property value type: Move.
    ///
    /// This is a move property.
    W,

    /// @brief Add black stones to the board. Property value type: List
    /// of Stone.
    ///
    /// This is a board setup property.
    AB,
    /// @brief Clear the given points on the board. Property value type: List
    /// of Point.
    ///
    /// This is a board setup property.
    AE,
    /// @brief Add white stones to the board. Property value type: List
    /// of Stone.
    ///
    /// This is a board setup property.
    AW,
    /// @brief Set the player whose turn it is. Property value type: Color.
    ///
    /// This is a board setup property.
    PL,

    /// @brief Provide a comment text for the node. Property value type: Text.
    ///
    /// This is a node annotation property.
    C,
    /// @brief Specify that the position is even. Property value type: Double.
    ///
    /// The property must not be mixed with UC, GB or GW within a node.
    ///
    /// This is a node annotation property.
    DM,
    /// @brief The node contains something that is good for black. Property
    /// value type: Double.
    ///
    /// The property must not be mixed with GW, DM or UC within a node.
    ///
    /// This is a node annotation property.
    GB,
    /// @brief The node contains something that is good for white. Property
    /// value type: Double.
    ///
    /// The property must not be mixed with GB, DM or UC within a node.
    ///
    /// This is a node annotation property.
    GW,
    /// @brief The node contains a "hotspot", i.e. something interesting such
    /// as a game-deciding move. Property value type: Double.
    ///
    /// This is a node annotation property.
    HO,
    /// @brief Provide a name text for the node. Property value
    /// type: SimpleText.
    ///
    /// This is a node annotation property.
    N,
    /// @brief The node contains a position that is unclear. Property
    /// value type: Double.
    ///
    /// The property must not be mixed with DM, GB or GW within a node.
    ///
    /// This is a node annotation property.
    UC,
    /// @brief Define a value for the node. Positive values are good for black,
    /// negative values are good for white. Property value type: Real.
    ///
    /// The interpretation of particular values is game-specific. In Go, this
    /// is the estimated score.
    ///
    /// This is a node annotation property.
    V,

    /// @brief The move played in this node is a bad move. Property value
    /// type: Double.
    ///
    /// The property must not be mixed with TE, DO or IT within a node.
    ///
    /// This is a move annotation property.
    BM,
    /// @brief The move played in this node is doubtful. Property value
    /// type: None.
    ///
    /// The property must not be mixed with BM, TE, or IT within a node.
    ///
    /// This is a move annotation property.
    DO,
    /// @brief The move played in this node is interesting. Property value
    /// type: None.
    ///
    /// The property must not be mixed with BM, TE, or DO within a node.
    ///
    /// This is a move annotation property.
    IT,
    /// @brief The move played in this node is tesuji (good move). Property
    /// value type: Double.
    ///
    /// The property must not be mixed with BM, TE, or IT within a node.
    ///
    /// This is a move annotation property.
    TE,

    /// @brief For each property value, draw an arrow from the first point to
    /// the second point. Property value type: List of composed Point/Point
    /// (i.e. "Point:Point").
    ///
    /// No two property values must specify the same arrow twice. A property
    /// value must specify two different points.
    ///
    /// This is a markup property.
    AR,
    /// @brief Mark the given points with a circle. Property value type: List of
    /// Point.
    ///
    /// Property values must be unique.
    ///
    /// Within the same node the points specified must not also be specified by
    /// one of the other properties MA, SL, SQ or TR.
    ///
    /// This is a markup property.
    CR,
    /// @brief Dim (grey out) the given points. Property value type: Elist of
    /// Point.
    ///
    /// Elist means that the property value can be either a list of Point, or
    /// None.
    ///
    /// Property values must be unique (not specified in the SGF standard).
    ///
    /// An "inherits" property. Specifying a None value clears any inherited
    /// values, i.e. "undims" everyting.
    ///
    /// This is a markup property.
    DD,
    /// @brief Write the given labels on the board, centered around the given
    /// points. Property value type: List of composed Point/SimpleText (i.e.
    /// "Point:SimpleText").
    ///
    /// Property values must be unique.
    ///
    /// This is a markup property.
    LB,
    /// @brief For each property value, draw a line from the first point to
    /// the second point. Property value type: List of composed Point/Point
    /// (i.e. "Point:Point").
    ///
    /// No two property values must specify the same arrow twice. A property
    /// value must specify two different points.
    ///
    /// Within the same node the point pairs specified must not also be
    /// specified by the AR properties (restriction is not in the SGF standard).
    ///
    /// This is a markup property.
    LN,
    /// @brief Mark the given points with an "X". Property value type: List of
    /// Point.
    ///
    /// Property values must be unique.
    ///
    /// Within the same node the points specified must not also be specified by
    /// one of the other properties CR, SL, SQ or TR.
    ///
    /// This is a markup property.
    MA,
    /// @brief Draw the given points as "selected". Property value type: List of
    /// Point.
    ///
    /// Property values must be unique.
    ///
    /// Within the same node the points specified must not also be specified by
    /// one of the other properties CR, MA, SQ or TR.
    ///
    /// This is a markup property.
    SL,
    /// @brief Mark the given points with a square. Property value type: List of
    /// Point.
    ///
    /// Property values must be unique.
    ///
    /// Within the same node the points specified must not also be specified by
    /// one of the other properties CR, MA, SL or TR.
    ///
    /// This is a markup property.
    SQ,
    /// @brief Mark the given points with a triangle. Property value type: List
    /// of Point.
    ///
    /// Property values must be unique.
    ///
    /// Within the same node the points specified must not also be specified by
    /// one of the other properties CR, MA, SL or SQ.
    ///
    /// This is a markup property.
    TR,

    /// @brief Name and version number of the application used to create the
    /// game tree. Property value type: Composed SimpleText/SimpleText (i.e.
    /// "SimpleText:SimpleText").
    ///
    /// This is a root property.
    AP,
    /// @brief The encoding (aka "character set) used for SimpleText and Text
    /// type property values in the game tree. Property value type: SimpleText.
    ///
    /// The default value is "ISO-8859-1" aka "Latin1". Only character set
    /// names (or their aliases) as specified in RFC 1345 (or updates thereof)
    /// are allowed.
    ///
    /// This is a root property.
    CA,
    /// @brief The file format used in the game tree. Property value
    /// type: Number.
    ///
    /// Allowed values are 1, 3 and 4. The default value is 1.
    ///
    /// This is a root property.
    ///
    /// @todo Since SGFC converts to FF4 automatically, and writes FF4 only,
    /// libsgfc++ should only ever allow 4.
    FF,
    /// @brief The type of game that is stored in the game tree. Property
    /// value type: Number.
    ///
    /// Allowed values are 1-16. The default value is 1 (Go).
    ///
    /// This is a root property.
    ///
    /// @see SgfcGameType.
    GM,
    /// @brief Define how variations should be shown. Property value
    /// type: Number.
    ///
    /// This is a root property.
    ///
    /// @todo Grok the meaning of this property type.
    ST,
    /// @brief Define the board size. Property value type: Either a single
    /// Number, or a composed Number/Number (i.e. "Number:Number").
    ///
    /// A single number means the board is square. Two numbers means the board
    /// is rectangular. If two numbers are specified they must be different.
    /// The first number specifies the number of columns, the second number
    /// specifies the number of rows.
    ///
    /// Allowed values are numbers >= 1. For games of type Go the maximum
    /// value is 52. The default value for games of type Go is 19, for games
    /// of type Chess it is 8.
    ///
    /// This is a root property.
    SZ,

    AN,
    BR,
    BT,
    CP,
    DT,
    EV,
    GN,
    GC,
    ON,
    OT,
    PB,
    PC,
    PW,
    RE,
    RO,
    RU,
    SO,
    TM,
    US,
    WR,
    WT,

    BL,
    OB,
    OW,
    WL,

    FG,
    PM,
    VW,

    // ----------------------------------------------------------------------
    // Standard properties from FF1-3
    // ----------------------------------------------------------------------
    BS,
    CH,
    EL,
    EX,
    ID,
    L,
    LT,
    M,
    OM,
    OP,
    OV,
    RG,
    SC,
    SE,
    SI,
    TC,
    WS,

    // ----------------------------------------------------------------------
    // Standard properties from FF4 for the game of Go (GM[1])
    // ----------------------------------------------------------------------

    /// @brief Defines the number of handicap stones. This is a game-specific
    /// property for the game of Go. Property value type: Number.
    ///
    /// Property value must be >= 2.
    ///
    /// When this property appears, the handicap stones should be set up with
    /// an AB property within the same node.
    ///
    /// This is a game info property.
    HA,
    /// @brief Defines the komi value. This is a game-specific property for the
    /// game of Go. Property value type: Real.
    ///
    /// This is a game info property.
    KM,
    TB,
    TW,

    // ----------------------------------------------------------------------
    // Standard properties from FF4 for the game of Backgammon (GM[6])
    // ----------------------------------------------------------------------
    CO,
    CV,
    DI,
    MI,

    // ----------------------------------------------------------------------
    // Standard properties from FF4 for the game of Lines of Action (GM[9])
    // ----------------------------------------------------------------------
    IY,
    SU,

    // ----------------------------------------------------------------------
    // Standard properties from FF4 for the game of Hex (GM[11])
    // ----------------------------------------------------------------------
    IS,

    // ----------------------------------------------------------------------
    // Standard properties from FF4 for the game of Amazons (GM[18])
    // ----------------------------------------------------------------------
    AA,

    // ----------------------------------------------------------------------
    // Standard properties from FF4 for the game of Octi (GM[19])
    // ----------------------------------------------------------------------
    BO,
    WO,
    NP,
    NR,
    NS,
    CS,
    MS,
    SS,
    TS,
    RP,

    // ----------------------------------------------------------------------
    // Standard properties from FF4 for more than one game
    // ----------------------------------------------------------------------
    // Lines of Action (GM[9]) and Octi (GM[19])
    AS,
    // Lines of Action (GM[9]) and Hex (GM[11])
    IP,

    // ----------------------------------------------------------------------
    // Non-standard properties
    // ----------------------------------------------------------------------

    /// @brief A private property of the "Smart Game Board" application (SGB),
    /// meaning "integer komi". SGFC converts this to the regular KM property.
    /// Property value type: Number.
    ///
    /// @todo Do we ever get to see this property? If not then we can safely
    /// remove this enumeration value. If yes, then maybe we should still
    /// remove this enumeration value - after all we want to be conforming to
    /// a standard.
    KI,

    /// @brief The property type is unknown, i.e. the property is a custom
    /// property not defined by the SGF standard.
    Unknown,
  };
}
