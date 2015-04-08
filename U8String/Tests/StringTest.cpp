#include <catch.hpp>
#include <String.hpp>

SCENARIO("String", "[CORE]")
{

	using Character = U8::Character;
	using String = U8::String;

	GIVEN("Differents string.")
	{

		WHEN("We test constructors.")
		{

			THEN("Those results are expected.")
			{

				{
					String emptyString;
					REQUIRE(emptyString.capacity() == 0);
					REQUIRE(emptyString.size() == 0);
				}

				{
					String sizeTwoCapacityFour(u8"éà");
					REQUIRE(sizeTwoCapacityFour.capacity() >= 4);
					REQUIRE(sizeTwoCapacityFour.size() == 2);
				}

				{
					String oneChar('a');
					REQUIRE(oneChar.capacity() >= 1);
					REQUIRE(oneChar.size() == 1);
				}

				{
					String sizeTwoCapacityThree(u8"Téste", 1, 3);
					REQUIRE(sizeTwoCapacityThree.capacity() >= 3);
					REQUIRE(sizeTwoCapacityThree.size() == 2);
				}


				{
					String sizeThreeCapacityFour(u8"Tést", 1, String::npos);
					REQUIRE(sizeThreeCapacityFour.capacity() >= 4);
					REQUIRE(sizeThreeCapacityFour.size() == 3);
				}

				{
					String sizeFourCapacityFour("Test");
					REQUIRE(sizeFourCapacityFour.capacity() >= 4);
					REQUIRE(sizeFourCapacityFour.size() == 4);
				}

				{
					String sizeThreeCapacityFour("Tça");
					REQUIRE(sizeThreeCapacityFour.capacity() >= 4);
					REQUIRE(sizeThreeCapacityFour.size() == 3);
				}

				{
					std::string tmp("abc");
					String sizeThreeCapacityThree(tmp.begin(), tmp.end());
					REQUIRE(sizeThreeCapacityThree.capacity() >= 3);
					REQUIRE(sizeThreeCapacityThree.size() == 3);
				}

				{
					String sizeThreeCapacityThree(std::string("abc"));
					REQUIRE(sizeThreeCapacityThree.capacity() >= 3);
					REQUIRE(sizeThreeCapacityThree.size() == 3);
				}

				{
					String sizeFourCapacityFive(String(u8"aébc"));
					REQUIRE(sizeFourCapacityFive.capacity() >= 5);
					REQUIRE(sizeFourCapacityFive.size() == 4);
				}

				{
					String tmp(u8"aébc");
					String sizeFourCapacityFive(std::move(tmp));
					REQUIRE(sizeFourCapacityFive.capacity() >= 5);
					REQUIRE(sizeFourCapacityFive.size() == 4);
					REQUIRE(tmp.capacity() == 0);
					REQUIRE(tmp.size() == 0);
				}

				{
					String sizeThreeCapacityThree({'a', 'b', 'c'});
					REQUIRE(sizeThreeCapacityThree.capacity() >= 3);
					REQUIRE(sizeThreeCapacityThree.size() == 3);
				}

			}

		}

	}

	GIVEN("One empty string.")
	{

		String emptyString;

		WHEN("We test assignation (operator=).")
		{

			THEN("Capacity must always be superior or equal to the size.")
			{

				emptyString = u8"éà";
				REQUIRE(emptyString.capacity() >= 4);
				REQUIRE(emptyString.size() == 2);

				emptyString = u8"ç";
				REQUIRE(emptyString.capacity() >= 4);
				REQUIRE(emptyString.size() == 1);

				emptyString = String(u8"çdvta");
				REQUIRE(emptyString.capacity() >= 6);
				REQUIRE(emptyString.size() == 5);

				String tmp(u8"çdva");
				emptyString = std::move(tmp);
				REQUIRE(emptyString.capacity() >= 5);
				REQUIRE(emptyString.size() == 4);

				emptyString = "cava";
				REQUIRE(emptyString.capacity() >= 5);
				REQUIRE(emptyString.size() == 4);

				emptyString = 'c';
				REQUIRE(emptyString.capacity() >= 5);
				REQUIRE(emptyString.size() == 1);

				emptyString = {'c', 'a'};
				REQUIRE(emptyString.capacity() >= 5);
				REQUIRE(emptyString.size() == 2);

			}

		}

	}

	GIVEN("One string")
	{

		String randomString(u8"Télt");

		WHEN("We try operator==")
		{

			THEN("This is expected")
			{
				REQUIRE(randomString != u8"Tél");
				REQUIRE(randomString != std::string(u8"Telt"));
				REQUIRE(randomString == std::string(u8"Télt"));
				REQUIRE(randomString != std::string(u8"Tél"));
				REQUIRE(randomString == randomString);

			}

		}

	}

	GIVEN("One random string.")
	{

		String randomString(u8"I love éçà");

		WHEN("We ask for characters.")
		{

			THEN("These results are expected.")
			{

				REQUIRE(randomString.at(2) == u8"l");
				REQUIRE(randomString.at(7) == u8"é");
				REQUIRE(randomString.at(9) == u8"à");

			}

		}

		const String constString(u8"I love éçà");
		REQUIRE(randomString.at(2) == u8"l");
		REQUIRE(randomString.at(7) == u8"é");
		REQUIRE(randomString.at(9) == u8"à");

	}

	GIVEN("One string test")
	{

		String randomString(u8"Tést");

		WHEN("We assign the letter.")
		{

			randomString.at(2) = u8"l";

			THEN("This is expected with the same size")
			{

				REQUIRE(randomString.at(2) == u8"l");

			}

			REQUIRE(randomString == u8"Télt");

			randomString.at(1) = u8"j";

			THEN("This is expected with smaller size")
			{

				REQUIRE(randomString.at(1) == u8"j");

			}

			REQUIRE(randomString == u8"Tjlt");

			randomString.at(1) = u8"é";

			THEN("This is expected with bigger size")
			{

				REQUIRE(randomString.at(1) == u8"é");

			}

			REQUIRE(randomString == u8"Télt");

		}

	}

	GIVEN("Replace")
	{

		String randomString(u8"Tést");

		WHEN("We replace the é by two a")
		{

			auto oldCapacity = randomString.capacity();
			auto oldSize = randomString.size();

			randomString.replace(1, 2, Character(u8"a"));

			THEN("Should be good")
			{

				REQUIRE(randomString == u8"Taast");
				REQUIRE(randomString.capacity() == oldCapacity);
				REQUIRE(randomString.size() == 5);

			}

			randomString.at(3) = u8"見";

			THEN("Replace the s by a japanese character")
			{

				REQUIRE(randomString == u8"Taa見t");
				REQUIRE(randomString.capacity() >= 7);
				REQUIRE(randomString.size() == 5);

			}

			randomString.replace(3, 2, Character('s'));

			THEN("Replace the japanese one by two s")
			{

				REQUIRE(randomString == u8"Taasst");
				REQUIRE(randomString.capacity() >= 7);
				REQUIRE(randomString.size() == 6);

			}

		}

		WHEN("We replace the T by 5 u")
		{
			randomString = u8"Tést";

			randomString.replace(0, 5, Character('u'));
			THEN("Should be good")
			{

				REQUIRE(randomString.capacity() >= 10);
				REQUIRE(randomString.size() == 8);
				REQUIRE(randomString == u8"uuuuuést");

			}

		}

	}

	GIVEN("One string àbé")
	{

		String abe(u8"àbé");

		WHEN("We test front and back")
		{

			THEN("We get à and é")
			{

				REQUIRE(abe.front() == u8"à");
				REQUIRE(abe.back() == u8"é");

			}

		}

		WHEN("We shrink to fit")
		{

			REQUIRE(abe.capacity() >= 5);

			THEN("We replace the é by one a and we shrink to fit")
			{

				auto oldCapacity = abe.capacity();
				abe.replace(2, 1, Character(u8"a"));
				abe.shrink_to_fit();
				REQUIRE(abe.capacity() >= 4);
				REQUIRE(abe.capacity() < oldCapacity);
				REQUIRE(abe == u8"àba");

			}

		}

	}

}