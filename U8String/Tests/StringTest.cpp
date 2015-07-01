#include <catch.hpp>
#include <String.hpp>

#include <forward_list>
#include <regex>

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
					REQUIRE(emptyString.empty());
					REQUIRE(emptyString.capacity() == 0);
					REQUIRE(emptyString.size() == 0);
				}

				{
					String sizeTwoCapacityFour(u8"éà");
					REQUIRE(sizeTwoCapacityFour.capacity() >= 4);
					REQUIRE(sizeTwoCapacityFour.size() == 2);
					REQUIRE(sizeTwoCapacityFour == u8"éà");
				}

				{
					String oneChar('a');
					REQUIRE(oneChar.capacity() >= 1);
					REQUIRE(oneChar.size() == 1);
					REQUIRE(oneChar == u8"a");
				}

				{
					String oneChar(Character(u8"à"));
					REQUIRE(oneChar.capacity() >= 2);
					REQUIRE(oneChar.size() == 1);
					REQUIRE(oneChar == u8"à");
				}

				{
					String threeChar(3, 'a');
					REQUIRE(threeChar.capacity() >= 3);
					REQUIRE(threeChar.size() == 3);
					REQUIRE(threeChar == u8"aaa");
				}

				{
					String threeChar(3, Character(u8"à"));
					REQUIRE(threeChar.capacity() >= 6);
					REQUIRE(threeChar.size() == 3);
					REQUIRE(threeChar == u8"ààà");
				}

				{
					String sizeThreeCapacityFour(u8"Téste", 1, 3);
					REQUIRE(sizeThreeCapacityFour.capacity() >= 4);
					REQUIRE(sizeThreeCapacityFour.size() == 3);
					REQUIRE(sizeThreeCapacityFour == u8"ést");
				}


				{
					String sizeThreeCapacityFour(u8"Tést", 1, String::npos);
					REQUIRE(sizeThreeCapacityFour.capacity() >= 4);
					REQUIRE(sizeThreeCapacityFour.size() == 3);
					REQUIRE(sizeThreeCapacityFour == u8"ést");
				}

				{
					String sizeFourCapacityFour("Test");
					REQUIRE(sizeFourCapacityFour.capacity() >= 4);
					REQUIRE(sizeFourCapacityFour.size() == 4);
					REQUIRE(sizeFourCapacityFour == u8"Test");
				}

				{
					String sizeThreeCapacityFour("Tça");
					REQUIRE(sizeThreeCapacityFour.capacity() >= 4);
					REQUIRE(sizeThreeCapacityFour.size() == 3);
					REQUIRE(sizeThreeCapacityFour == u8"Tça");
				}

				{
					std::string tmp("abc");
					String sizeThreeCapacityThree(tmp.begin(), tmp.end());
					REQUIRE(sizeThreeCapacityThree.capacity() >= 3);
					REQUIRE(sizeThreeCapacityThree.size() == 3);
					REQUIRE(sizeThreeCapacityThree == u8"abc");
				}

				{
					std::forward_list<Character> flist{ u8"é", u8"t", u8"à" };
					String sizeThreeCapacityFive(flist.begin(), flist.end());
					REQUIRE(sizeThreeCapacityFive.capacity() >= 5);
					REQUIRE(sizeThreeCapacityFive.size() == 3);
					REQUIRE(sizeThreeCapacityFive == u8"étà");
				}

				{
					String sizeThreeCapacityThree(std::string("abc"));
					REQUIRE(sizeThreeCapacityThree.capacity() >= 3);
					REQUIRE(sizeThreeCapacityThree.size() == 3);
					REQUIRE(sizeThreeCapacityThree == u8"abc");
				}

				{
					String sizeFourCapacityFive(String(u8"aébc"));
					REQUIRE(sizeFourCapacityFive.capacity() >= 5);
					REQUIRE(sizeFourCapacityFive.size() == 4);
					REQUIRE(sizeFourCapacityFive == u8"aébc");
				}

				{
					String tmp(u8"aébc");
					String sizeFourCapacityFive(std::move(tmp));
					REQUIRE(sizeFourCapacityFive.capacity() >= 5);
					REQUIRE(sizeFourCapacityFive.size() == 4);
					REQUIRE(sizeFourCapacityFive == u8"aébc");
					REQUIRE(tmp.capacity() == 0);
					REQUIRE(tmp.size() == 0);
				}

				{
					String sizeThreeCapacityThree({'a', 'b', 'c'});
					REQUIRE(sizeThreeCapacityThree.capacity() >= 3);
					REQUIRE(sizeThreeCapacityThree.size() == 3);
					REQUIRE(sizeThreeCapacityThree == u8"abc");
				}

				{
					String sizeThreeCapacityThree({u8"à", u8"b", u8"c"});
					REQUIRE(sizeThreeCapacityThree.capacity() >= 4);
					REQUIRE(sizeThreeCapacityThree.size() == 3);
					REQUIRE(sizeThreeCapacityThree == u8"àbc");
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

				emptyString = Character(u8"à");
				REQUIRE(emptyString.capacity() >= 5);
				REQUIRE(emptyString.size() == 1);

				emptyString = {'c', 'a'};
				REQUIRE(emptyString.capacity() >= 5);
				REQUIRE(emptyString.size() == 2);

				emptyString = {u8"ç", u8"à", u8"v", u8"a"};
				REQUIRE(emptyString.capacity() >= 6);
				REQUIRE(emptyString.size() == 4);

				emptyString = u8"étà";
				emptyString.assign(emptyString.begin(), emptyString.end());
				REQUIRE(emptyString.capacity() >= 5);
				REQUIRE(emptyString.size() == 3);
				REQUIRE(emptyString == u8"étà");

			}

		}

	}

	GIVEN("Two strings")
	{

		String stringOne(u8"stringOne");
		String stringTwo(u8"stringTwo");

		WHEN("We swap")
		{

			String oldStringOne(u8"stringOne");
			String oldStringTwo(u8"stringTwo");

			THEN("Value was swapped")
			{
				std::swap(stringOne, stringTwo);

				REQUIRE(stringOne == oldStringTwo);
				REQUIRE(stringTwo == oldStringOne);

				stringOne.swap(stringTwo);

				REQUIRE(stringOne == oldStringOne);
				REQUIRE(stringTwo == oldStringTwo);

			}

			THEN("We move")
			{

				String stringThree(std::move(stringTwo));
				REQUIRE(stringThree == oldStringTwo);
				REQUIRE(stringTwo == "");

				String tmp(u8"tmp");
				tmp = std::move(stringThree);
				REQUIRE(tmp == oldStringTwo);

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
				REQUIRE(u8"Tél" != randomString);
				REQUIRE(randomString != u8"Telt");
				REQUIRE(randomString == u8"Télt");
				REQUIRE(randomString != u8"Tél");
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
				abe.front() = u8"b";
				REQUIRE(abe == u8"bbé");
				REQUIRE(abe.back() == u8"é");
				abe.back() = u8"t";
				REQUIRE(abe == u8"bbt");

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

			THEN("We try to empty it")
			{

				abe = "";
				abe.shrink_to_fit();
				REQUIRE(abe == "");
				REQUIRE(abe.capacity() == 0);
				REQUIRE(abe.size() == 0);

			}

			THEN("We resize (5) and (3), we come back to origin")
			{

				abe.resize(5, Character('a'));
				REQUIRE(abe == u8"àbéaa");
				abe.resize(3);
				REQUIRE(abe == u8"àbé");

			}

		}

	}

	GIVEN("One empty string")
	{

		String emptyString;

		WHEN("We insert")
		{

			THEN("Insert with index ")
			{

				emptyString.insert(0, u8"léa");

				REQUIRE(emptyString == u8"léa");
				REQUIRE(emptyString.capacity() >= 4);
				REQUIRE(emptyString.size() == 3);

				emptyString.insert(1, u8"çà");

				REQUIRE(emptyString == u8"lçàéa");
				REQUIRE(emptyString.capacity() >= 8);
				REQUIRE(emptyString.size() == 5);

				emptyString.insert(emptyString.size(), 3, Character(u8"o"));

				REQUIRE(emptyString == u8"lçàéaooo");
				REQUIRE(emptyString.capacity() >= 11);
				REQUIRE(emptyString.size() == 8);

			}

			THEN("Insert with iterator")
			{

				auto it = emptyString.insert(emptyString.begin(), { u8"ç", u8"a", u8"é" });

				REQUIRE(it == emptyString.begin());
				REQUIRE(emptyString == u8"çaé");
				REQUIRE(emptyString.capacity() >= 5);
				REQUIRE(emptyString.size() == 3);

				it = emptyString.begin();
				std::advance(it, 3);
				auto tmp = emptyString.insert(it, 3, u8"!");

				it = emptyString.begin();
				std::advance(it, 3);
				REQUIRE(it == tmp);
				REQUIRE(emptyString == u8"çaé!!!");
				REQUIRE(emptyString.capacity() >= 8);
				REQUIRE(emptyString.size() == 6);

				it = --emptyString.end();
				tmp = emptyString.insert(it, 5, Character(u8"u"));
				REQUIRE(emptyString.capacity() >= 13);
				REQUIRE(emptyString.size() == 11);
				REQUIRE(emptyString == u8"çaé!!uuuuu!");

				std::forward_list<Character> flist({ u8"b", "ô" });
				emptyString.insert(--emptyString.end(), flist.begin(), flist.end());
				REQUIRE(emptyString.capacity() >= 16);
				REQUIRE(emptyString.size() == 13);
				REQUIRE(emptyString == u8"çaé!!uuuuubô!");

			}

		}

	}

	GIVEN("One string with characters")
	{

		String randomString(u8"hélto");

		WHEN("We erase")
		{

			THEN("This is expected with index")
			{

				randomString.erase(4).erase(3);
				REQUIRE(randomString == u8"hél");
				REQUIRE(randomString.size() == 3);

				randomString.erase(1);
				REQUIRE(randomString == u8"h");
				REQUIRE(randomString.size() == 1);

				randomString = u8"hélto";
				randomString.erase(1, 3);
				REQUIRE(randomString == u8"ho");
				REQUIRE(randomString.size() == 2);

			}

			THEN("This is expected with iterator")
			{

				auto it = randomString.erase(--randomString.end());
				REQUIRE(randomString == u8"hélt");
				REQUIRE(randomString.size() == 4);
				REQUIRE(it == randomString.end());

				auto itBegin = randomString.begin();
				std::advance(itBegin, 1);
				auto itEnd = randomString.begin();
				std::advance(itEnd, 3);

				it = randomString.erase(itBegin, itEnd);
				REQUIRE(it == --randomString.end());
				REQUIRE(randomString == u8"ht");
				REQUIRE(randomString.size() == 2);

			}

			THEN("With mixed")
			{

				String str(u8"This is an example sentence.");
				str.erase(10, 8);
				REQUIRE(str == u8"This is an sentence.");
				auto it = str.begin();
				std::advance(it, 9);
				str.erase(it);
				REQUIRE(str == u8"This is a sentence.");
				auto itFirst = str.begin();
				auto itEnd = str.begin();
				std::advance(itFirst, 5);
				std::advance(itEnd, str.size() - 9);
				str.erase(itFirst, itEnd);
				REQUIRE(str == u8"This sentence.");

			}

		}

	}

	GIVEN("One string with some character")
	{

		String randomString(u8"Héllo");

		WHEN("We push, pop and append")
		{

			THEN("This is expected")
			{

				randomString.push_back(u8"à");
				REQUIRE(randomString == u8"Hélloà");
				REQUIRE(randomString.capacity() >= 8);
				REQUIRE(randomString.size() == 6);

				randomString.pop_back();
				REQUIRE(randomString == u8"Héllo");
				REQUIRE(randomString.capacity() >= 8);
				REQUIRE(randomString.size() == 5);

				randomString.append(u8"à");
				REQUIRE(randomString == u8"Hélloà");
				REQUIRE(randomString.capacity() >= 8);
				REQUIRE(randomString.size() == 6);

				randomString.append(u8"blabla");
				REQUIRE(randomString == u8"Hélloàblabla");
				REQUIRE(randomString.capacity() >= 14);
				REQUIRE(randomString.size() == 12);

				randomString.append(String(u8"Test"));
				REQUIRE(randomString == u8"HélloàblablaTest");
				REQUIRE(randomString.capacity() >= 18);
				REQUIRE(randomString.size() == 16);

			}

		}

	}

	GIVEN("One random string")
	{

		String randomString(u8" éà à etc ...");

		WHEN("We try to find something")
		{

			THEN("These results are expected for front to back")
			{

				auto pos = randomString.find(u8"à");
				REQUIRE(pos == 2);
				pos = randomString.find(u8"à", pos + 1);
				REQUIRE(pos == 4);

				pos = randomString.find(String(u8"etc"));
				REQUIRE(pos == 6);

				pos = randomString.find(Character(u8"à"));
				REQUIRE(pos == 2);

				pos = randomString.find_first_of(String(u8"abcde"));
				REQUIRE(pos == 6);

				pos = randomString.find_first_not_of(String(u8" éà à "));
				REQUIRE(pos == 6);

				pos = randomString.find_last_of(String(u8"abcde"), 10);
				REQUIRE(pos == 8);

				pos = randomString.find_last_not_of(String(u8" ..."));
				REQUIRE(pos == 8);

			}

			AND_THEN("These are for back to front")
			{

				auto pos = randomString.rfind(u8"à");
				REQUIRE(pos == 4);
				pos = randomString.rfind(u8"à", pos - 1);
				REQUIRE(pos == 2);

				pos = randomString.rfind(String(u8"etc"));
				REQUIRE(pos == 6);

				pos = randomString.rfind(Character(u8"à"));
				REQUIRE(pos == 4);

			}

		}

		WHEN("We use std::find")
		{

			THEN("This should work")
			{

				auto it = std::find(randomString.begin(), randomString.end(), u8"à");
				REQUIRE(it == ++(++randomString.begin()));

				auto rit = std::find(randomString.rbegin(), randomString.rend(), u8"é");
				REQUIRE(rit == --(--randomString.rend()));

			}

		}

		WHEN("We take examples from cplusplus.com")
		{

			THEN("These should work for find_first_of")
			{

				String str = u8"Please, replace the vowels in this sentence by asterisks.";
				String::size_type found = str.find_first_of(u8"aeiouy");
				while(found != String::npos)
				{
					str[found] = '*';
					found = str.find_first_of(u8"aeiouy", found + 1);
				}

				REQUIRE(str == u8"Pl**s*, r*pl*c* th* v*w*ls *n th*s s*nt*nc* b* *st*r*sks.");

			}

			THEN("These should work for find_first_not_of")
			{

				String str = u8"look for non-alphabetic characters...";
				String::size_type found = str.find_first_not_of(u8"abcdefghijklmnopqrstiuvwxyz ");

				REQUIRE(str[found] == u8"-");
				REQUIRE(found == 12);

			}

			THEN("These should work for find_last_of")
			{

				String str1 = u8"/usr/bin/man";
				String str2 = u8"c:\\windows\\winhelp.exe";
				String::size_type found1 = str1.find_last_of(u8"/\\");
				String::size_type found2 = str2.find_last_of(u8"/\\");

				REQUIRE(str1.substr(0, found1) == u8"/usr/bin");
				REQUIRE(str1.substr(found1 + 1) == u8"man");

				REQUIRE(str2.substr(0, found2) == u8"c:\\windows");
				REQUIRE(str2.substr(found2 + 1) == u8"winhelp.exe");

			}

			THEN("These should work for find_last_not_of")
			{

				String str = u8"Please, erase trailing white-spaces   \n";
				String whitespaces = u8" \t\f\v\n\r";

				String::size_type found = str.find_last_not_of(whitespaces);
				str.erase(found + 1);

				REQUIRE(str == u8"Please, erase trailing white-spaces");

			}

		}

	}

	GIVEN("One random string")
	{

		String randomString(u8"hello ");

		WHEN("We try to do operator+=")
		{

			THEN("These results are expected")
			{

				randomString += randomString;
				REQUIRE(randomString == u8"hello hello ");

				String helloWorld = String("hello") + String(" ") + String("world");
				REQUIRE(helloWorld == "hello world");

			}

		}

	}

	GIVEN("Two string")
	{

		WHEN("We test operator of comparison")
		{

			THEN("These are expected")
			{

				{

					String American(u8"hrnec");
					String Czech(u8"chrt");

					REQUIRE(American.compare(Czech, std::locale("en_US.utf8")) > 0);
					REQUIRE(American.compare(Czech, std::locale("cs_CZ.utf8")) < 0); // sudo locale-gen cs_CZ.utf8 or comment it :)

				}

				{

					String American(u8"ängel");
					String Swedish(u8"år");

					REQUIRE(American.compare(Swedish, std::locale("en_US.utf8")) < 0);
					REQUIRE(American.compare(Swedish, std::locale("sv_SE.utf8")) > 0); // sudo locale-gen sv_SE.utf8 or comment it :)

				}

				{

					String A(u8"à");
					String E(u8"é");
					REQUIRE(A < E);

				}

				{

					std::vector<String> v { u8"жил", u8"был", u8"кот" };
					std::sort(v.begin(), v.end(), [](const String& lhs, const String& rhs) { return lhs < rhs; });
					REQUIRE(v[0] == u8"был");
					REQUIRE(v[1] == u8"жил");
					REQUIRE(v[2] == u8"кот");

				}


			}


		}

	}

	GIVEN("One randomString")
	{

		String randomString(u8"hello world à tous");

		WHEN("We use substr")
		{

			THEN("This is expected")
			{

				String sub = randomString.substr(12);
				REQUIRE(sub == u8"à tous");

				String sub2 = randomString.substr(12, 3);
				REQUIRE(sub2 == u8"à t");

			}

		}

	}

	GIVEN("One random string")
	{

		String randomString(u8"hello world à tous et à toutes");

		WHEN("We use STL count and erase/remove_if")
		{

			THEN("It should behave normally")
			{

				REQUIRE(std::count(randomString.begin(), randomString.end(), u8"à") == 2);

				randomString.erase(std::remove_if(randomString.begin(), randomString.end(), [](const Character& x) {
					return x == 'o';
				}), randomString.end());

				REQUIRE(randomString == u8"hell wrld à tus et à tutes");

				randomString.erase(std::remove_if(randomString.begin(), randomString.end(), [](const Character& x) {
					return x == u8"à";
				}), randomString.end());

				REQUIRE(randomString == u8"hell wrld  tus et  tutes");

			}

		}

	}

	GIVEN("One string")
	{

		String foo(u8"quùùux");
		char bar[9] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
		foo.copy(bar, sizeof(bar));
		REQUIRE(bar[7] == 'x');
		REQUIRE(bar[8] == 'i');
		bar[8] = '\0';
		String tmp(bar);
		REQUIRE(tmp == u8"quùùux");

	}

	GIVEN("Two strings containing the lowers")
	{

		String toTransform(u8"a \u00DF ça và ?");

		WHEN("We use transform")
		{

			std::transform(toTransform.begin(), toTransform.end(), toTransform.begin(), [](const Character& chr) { return chr.toupper(); });

			THEN("No conversion to multi is done.")
			{

				REQUIRE(toTransform == u8"A \u00DF ÇA VÀ ?");

			}

		}

		WHEN("We use toupper")
		{

			toTransform = toTransform.toupper();

			THEN("Conversion to multi is done.")
			{

				REQUIRE(toTransform == u8"A SS ÇA VÀ ?");

			}

		}


	}

	GIVEN("One empty string")
	{

		String emptyString;

		WHEN("We reserve and append characters")
		{
			emptyString.reserve(2);
			emptyString.push_back(u8"ç");
			emptyString.push_back(u8"a");

			THEN("Nothing should fail")
			{

				REQUIRE(emptyString == u8"ça");

			}

		}

	}

}
