#include <catch.hpp>
#include <Character.hpp>

#include <iostream>

SCENARIO("Character", "[CORE]")
{

	using Character = U8::Character;

	GIVEN("One character.")
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
					// Because locale works perfectly as I want !
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

		WHEN("We test comparison")
		{

			THEN("These are expected")
			{

				Character American(u8"ä");
				Character Swedish(u8"å");

				REQUIRE(American.compare(Swedish, std::locale("C")) < 0);
				REQUIRE(American.compare(Swedish, std::locale("sv_SE.utf8")) > 0); // sudo locale-gen sv_SE.utf8 or comment it :)

			}

		}

		WHEN("We do upper and lower")
		{

			THEN("Griek letters are funny")
			{

				Character upperSigma(u8"Σ");
				REQUIRE(u8"σ" == upperSigma.tolower(std::locale("en_US.utf8")));

				Character lowerSigma(u8"σ");
				REQUIRE(u8"Σ" == lowerSigma.toupper(std::locale("en_US.utf8")));

			}


		}

		WHEN("We have different unicode")
		{

			THEN("They must be equal to utf8")
			{

				Character e(u8"é");
				/*REQUIRE(e == Character::fromUTF16(u"é"));
				REQUIRE(e == Character::fromUTF32(U"é"));
				REQUIRE(e == Character::fromWide(L"é"));*/

			}

		}

	}

}
