#include <String.hpp>
#include <catch.hpp>

SCENARIO("StringIterator", "[CORE]")
{

	using String = U8::String;

	GIVEN("One random string.")
	{

		String randomString(u8"aébà");
		REQUIRE(randomString.size() == 4);
		REQUIRE(randomString.capacity() >= 6);

		WHEN("We test for iterators.")
		{

			THEN("These results are expected.")
			{

				auto it = randomString.begin();
				REQUIRE(*it == u8"a");
				REQUIRE(randomString[0] == u8"a");
				REQUIRE(*(++it) == u8"é");
				REQUIRE(randomString[1] == u8"é");
				REQUIRE(*(++it) == u8"b");
				REQUIRE(randomString[2] == u8"b");
				REQUIRE(*(++it) == u8"à");
				REQUIRE(randomString[3] == u8"à");
				REQUIRE((++it) == randomString.end());

			}

			THEN("In the two directions")
			{

				String oppositeString(u8"àbéa");

				auto itR = oppositeString.rbegin();
				REQUIRE(*itR == u8"a");
				REQUIRE(oppositeString[3] == u8"a");
				REQUIRE(*(++itR) == u8"é");
				REQUIRE(oppositeString[2] == u8"é");
				REQUIRE(*(++itR) == u8"b");
				REQUIRE(oppositeString[1] == u8"b");
				REQUIRE(*(++itR) == u8"à");
				REQUIRE(oppositeString[0] == u8"à");
				assert((++itR) == oppositeString.rend());

				auto it = randomString.begin();
				for (auto itReverse = oppositeString.rbegin(); itReverse != oppositeString.rend(); ++itReverse, ++it)
				{
					REQUIRE(*it == *itReverse);
				}

			}

			THEN("Post increment and decrement")
			{

				auto it = randomString.begin();
				REQUIRE(*(it++) == u8"a");
				REQUIRE(*(it--) == u8"é");

			}

		}

		WHEN("We ask for logic of iterators")
		{

			THEN("Nothing should fail.")
			{

				REQUIRE(randomString.begin() == randomString.begin());
				REQUIRE(randomString.end() == randomString.end());
				REQUIRE(randomString.rbegin() == --randomString.end());
				assert(randomString.rend() == --randomString.begin());
				//REQUIRE(randomString.rend() == --randomString.begin());
				REQUIRE(randomString.cbegin() == randomString.begin());
				REQUIRE(randomString.cend() == randomString.cend());
				REQUIRE(randomString.crbegin() == --randomString.end());
				assert(randomString.crend() == --randomString.begin());
				//REQUIRE(randomString.crend() == --randomString.begin());

			}

		}

	}

}
