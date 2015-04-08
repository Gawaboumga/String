#include <catch.hpp>
#include <Character.hpp>

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
					charUTF8 = std::toupper(std::string(charUTF8)[0], std::locale("en_US.utf8"));
					CHECK(charUTF8 == u8"A");
					CHECK(charUTF8 == "A");
					CHECK(charUTF8 == 'A');

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


	}

}
