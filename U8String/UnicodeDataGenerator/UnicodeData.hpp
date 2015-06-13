#ifndef __UNICODEDATA_HPP__
#define __UNICODEDATA_HPP__

#include <array>
#include <utility>

class UnicodeData
{
	public:

		using Unicode = unsigned int;

		enum class BidirectionalCategory
		{
			AL,
			AN,
			B,
			BN,
			CS,
			EN,
			ES,
			ET,
			FSI,
			L,
			LRE,
			LRI,
			LRO,
			NSM,
			ON,
			PDF,
			PDI,
			R,
			RLE,
			RLI,
			RLO,
			S,
			WS,
		};

		enum class GeneralCategory
		{
			Cc,
			Cf,
			Cn,
			Co,
			Cs,
			Ll,
			Lt,
			Lu,
			Mc,
			Me,
			Mn,
			Nd,
			Nl,
			No,
			Zl,
			Zp,
			Zs,
			Lm,
			Lo,
			Pc,
			Pd,
			Pe,
			Pf,
			Pi,
			Po,
			Ps,
			Sc,
			Sm,
			Sk,
			So,
		};

		static BidirectionalCategory bidirectional_category(Unicode character);

		static unsigned char canonical_combining_classes(Unicode character);

		static GeneralCategory general_category(Unicode character);

		static Unicode lowercase_mapping(Unicode character);

		static bool mirrored(Unicode character);

		static Unicode titlecase_mapping(Unicode character);

		static Unicode uppercase_mapping(Unicode character);

	private:

		static std::array<std::pair<Unicode, BidirectionalCategory>, 801> m_bidirectionals;
		static std::array<std::pair<Unicode, GeneralCategory>, 2587> m_categories;
		static std::array<std::pair<Unicode, unsigned char>, 461> m_combinings;
		static std::array<std::pair<Unicode, Unicode>, 1092> m_lowers;
		static std::array<std::pair<Unicode, bool>, 222> m_mirrors;
		static std::array<std::pair<Unicode, Unicode>, 1104> m_titles;
		static std::array<std::pair<Unicode, Unicode>, 1100> m_uppers;
};

#endif // __UNICODEDATA_HPP__
