// Library includes
#include <sgfc/message/SgfcMessage.h>
#include <SgfcPrivateConstants.h>

// Unit test library includes
#include <catch2/catch.hpp>

using namespace LibSgfcPlusPlus;

TEST_CASE( "SgfcMessage default values", "[message]" )
{
  SgfcMessage message;
  REQUIRE( message.GetMessageID() == SgfcPrivateConstants::DefaultMessageID );
}
