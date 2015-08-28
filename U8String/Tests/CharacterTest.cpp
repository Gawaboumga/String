#include <catch.hpp>
#include <Character.hpp>

#include <iostream>

SCENARIO("Character", "[CORE]")
{

	using Character = U8::Character;

	GIVEN("No character.")
	{

		WHEN("We test for constructors.")
		{

			THEN("Nothing should be wrong.")
			{

				{
					Character charA('a');
					REQUIRE(charA == 'a');
					REQUIRE(charA.number_byte() == 1);
				}

				{
					Character charUTF8(u8"à");
					REQUIRE(charUTF8 == u8"à");
					REQUIRE(charUTF8.number_byte() == 2);
				}

				{
					Character charUTF8(u8"a");
					charUTF8 = charUTF8.toupper(std::locale("en_US.utf8"));
					CHECK(charUTF8 == u8"A");
					CHECK(charUTF8 == "A");
					CHECK(charUTF8 == 'A');

				}

				{

					Character tmp;
					REQUIRE_THROWS(tmp = u8"ab");

				}

			}


		}

	}

	GIVEN("One empty character")
	{

		WHEN("We test assignation.")
		{

			Character charA;

			THEN("Nothing should be wrong.")
			{

				charA = 'A';
				CHECK(charA == u8"A");
				CHECK(charA == "A");
				CHECK(charA == 'A');

				charA = u8"à";
				CHECK(charA == u8"à");
				CHECK(charA == "à");

				charA = Character(u8"é");
				CHECK(charA == u8"é");
				CHECK(charA == "é");

			}

		}

	}

	GIVEN("Two accentuated characters")
	{

		WHEN("We test comparison")
		{

			THEN("These are expected")
			{

				Character American(u8"ä");
				Character Swedish(u8"å");

				REQUIRE(American.compare(Swedish, std::locale("C")) < 0);
				REQUIRE(American.compare(Swedish, std::locale("en_US.utf8")) > 0);

			}

		}

	}

	GIVEN("Character sigma")
	{

		WHEN("We do upper and lower")
		{

			THEN("Greek letters are funny")
			{

				Character upperSigma(u8"Σ");
				REQUIRE(u8"σ" == upperSigma.tolower(std::locale("en_US.utf8")));

				Character lowerSigma(u8"σ");
				REQUIRE(u8"Σ" == lowerSigma.toupper(std::locale("en_US.utf8")));

			}


		}

	}

	GIVEN("The Character I")
	{

		Character capitalI(u8"I");

		WHEN("We use azeri or turk")
		{

			THEN("The lower case is")
			{

				REQUIRE(capitalI.tolower(std::locale("tr_TR.utf8")) == u8"\u0131");

			}

			AND_THEN("The upper case")
			{

				REQUIRE(Character(u8"i").toupper(std::locale("tr_TR.utf8")) == u8"\u0130");

			}

		}

		WHEN("We use others than azeri or turk")
		{

			THEN("The lower case is")
			{

				REQUIRE(capitalI.tolower(std::locale("en_US.utf8")) == u8"i");

			}

			AND_THEN("The upper case")
			{

				REQUIRE(Character(u8"i").toupper(std::locale("en_US.utf8")) == u8"I");

			}

		}

	}

	GIVEN("The character E acute")
	{

		Character e(u8"é");

		WHEN("We have different unicode")
		{

			THEN("They must be equal to utf8")
			{

				REQUIRE(e == Character::fromUTF16(u"é"));
				REQUIRE(e == Character::fromUTF32(U"é"));
				//REQUIRE(e == Character::fromWide(L"é"));

				Character Gclef(u8"\U0001D11E");
				REQUIRE(Gclef == Character::fromUTF16(u"\U0001D11E"));
				REQUIRE(Gclef == Character::fromUTF32(U"\U0001D11E"));
				//REQUIRE(Gclef == Character::fromWide(L"\U0001D11E"));

			}

		}

		WHEN("We convert to different unicode")
		{

			THEN("They must be equal to utf8")
			{

				std::u16string tmp16;
				e.toUTF16(std::back_inserter(tmp16));
				REQUIRE(tmp16 == u"é");
				std::u32string tmp32;
				e.toUTF32(std::back_inserter(tmp32));
				REQUIRE(tmp32 == U"é");
				/*std::wstring tmpW;
				e.toWide(std::back_inserter(tmpW));
				REQUIRE(tmpW == L"é");*/

				Character Gclef(u8"\U0001D11E");
				tmp16.clear();
				Gclef.toUTF16(std::back_inserter(tmp16));
				REQUIRE(tmp16 == u"\U0001D11E");
				tmp32.clear();
				Gclef.toUTF32(std::back_inserter(tmp32));
				REQUIRE(tmp32 == U"\U0001D11E");
				/*tmpW.clear();
				Gclef.toWide(std::back_inserter(tmpW));
				REQUIRE(tmpW == L"\U0001D11E");*/

			}

		}

		WHEN("We ask for character information")
		{

			THEN("Unicode defines these properties")
			{

				REQUIRE(e.category() == UnicodeData::GeneralCategory::Ll);
				REQUIRE(e.combining_class() == 0);
				REQUIRE(e.direction() == UnicodeData::BidirectionalCategory::L);
				REQUIRE(e.has_mirrored() == false);
				REQUIRE(e.totitlecase() == u8"É");
				REQUIRE(e.toupper() == u8"É");

			}

		}

	}

}
