from BidirectionalCategoryEnum import BidirectionalCategoryEnum
from CharacterDecompositionMappingEnum import CharacterDecompositionMappingEnum
from GeneralCategoryEnum import GeneralCategoryEnum


class HPPGenerator:

    def __init__(self, output, datas, specialCasing):

        self.__output = output
        self.__datas = datas
        self.__specialCasing = specialCasing

    def generate(self):

        with open(self.__output + ".hpp", "w") as ofile:

            self.__writeHeaderGuard(ofile)
            self.__writeIncludes(ofile)
            self.__writeClass(ofile)
            self.__writeFooterGuard(ofile)

    def __writeHeaderGuard(self, ofile):

        ofile.write("#ifndef __" + self.__output.upper() + "_HPP__\n")
        ofile.write("#define __" + self.__output.upper() + "_HPP__\n\n")

    def __writeIncludes(self, ofile):

        ofile.write("#include <array>\n")
        ofile.write("#include <utility>\n\n")

    def __writeClass(self, ofile):

        ofile.write("class " + self.__output + "\n")
        ofile.write("{\n")

        self.__writeUsing(ofile)
        self.__writePublic(ofile)
        self.__writePrivate(ofile)

        ofile.write("};\n")

    def __writeFooterGuard(self, ofile):

        ofile.write("\n#endif // __" + self.__output.upper() + "_HPP__\n")

    def __writeUsing(self, ofile):

        ofile.write("\tpublic:\n\n")

        ofile.write("\t\tusing Unicode = uint64_t;\n\n")

    def __writeEnum(self, ofile, enum):

        enumerationName = str(enum)[7:-2].replace("Enum", "")
        ofile.write("\t\tenum class " + enumerationName + "\n")
        ofile.write("\t\t{\n")
        for member in enum.__members__:
            ofile.write("\t\t\t" + member + ",\n")
        ofile.write("\t\t};\n\n")

    def __writePublic(self, ofile):


        for enum in [BidirectionalCategoryEnum, GeneralCategoryEnum]:
            self.__writeEnum(ofile, enum)

        ofile.write("\t\tstatic BidirectionalCategory bidirectional_category(Unicode character);\n\n")
        ofile.write("\t\tstatic unsigned char canonical_combining_classes(Unicode character);\n\n")
        #ofile.write("\t\tstatic CharacterDecompositionMapping character_decomposition_mapping(Unicode character);\n\n")
        ofile.write("\t\tstatic GeneralCategory general_category(Unicode character);\n\n")
        ofile.write("\t\tstatic Unicode lowercase_mapping(Unicode character);\n\n")
        ofile.write("\t\tstatic bool mirrored(Unicode character);\n\n")
        ofile.write("\t\tstatic Unicode titlecase_mapping(Unicode character);\n\n")
        ofile.write("\t\tstatic Unicode uppercase_mapping(Unicode character);\n\n")

        if self.__specialCasing is not None:

            ofile.write("\t\tstatic std::array<Unicode, 3> special_lowercase_mapping(Unicode character);\n\n")
            ofile.write("\t\tstatic std::array<Unicode, 3> special_titlecase_mapping(Unicode character);\n\n")
            ofile.write("\t\tstatic std::array<Unicode, 3> special_uppercase_mapping(Unicode character);\n\n")

    def __writePrivate(self, ofile):

        ofile.write("\tprivate:\n\n")

        numberBidirectional = str(self.__datas[0])
        numberCategory = str(self.__datas[1])
        numberCombining = str(self.__datas[2])
        #numberDecomposition = str(self.__datas[3])
        numberLowers = str(self.__datas[3])
        numberMirror = str(self.__datas[4])
        numberTitles = str(self.__datas[5])
        numberUppers = str(self.__datas[6])

        ofile.write("\t\tstatic std::array<std::pair<Unicode, BidirectionalCategory>, " + numberBidirectional + "> m_bidirectionals;\n")
        ofile.write("\t\tstatic std::array<std::pair<Unicode, GeneralCategory>, " + numberCategory + "> m_categories;\n")
        ofile.write("\t\tstatic std::array<std::pair<Unicode, unsigned char>, " + numberCombining + "> m_combinings;\n")
        #ofile.write("\t\tstatic std::array<std::pair<Unicode, CharacterDecompositionMapping>, " + numberDecomposition + "> m_decompositions;\n")
        ofile.write("\t\tstatic std::array<std::pair<Unicode, Unicode>, " + numberLowers + "> m_lowers;\n")
        ofile.write("\t\tstatic std::array<std::pair<Unicode, bool>, " + numberMirror + "> m_mirrors;\n")
        ofile.write("\t\tstatic std::array<std::pair<Unicode, Unicode>, " + numberTitles + "> m_titles;\n")
        ofile.write("\t\tstatic std::array<std::pair<Unicode, Unicode>, " + numberUppers + "> m_uppers;\n")

        if self.__specialCasing is not None:
            numberSpecialLowers = str(self.__specialCasing[0])
            numberSpecialTitles = str(self.__specialCasing[1])
            numberSpecialUppers = str(self.__specialCasing[2])
            ofile.write("\t\tstatic std::array<std::pair<Unicode, std::array<Unicode, 3>>, " + numberSpecialLowers + "> m_specialLowers;\n")
            ofile.write("\t\tstatic std::array<std::pair<Unicode, std::array<Unicode, 3>>, " + numberSpecialTitles + "> m_specialTitles;\n")
            ofile.write("\t\tstatic std::array<std::pair<Unicode, std::array<Unicode, 3>>, " + numberSpecialUppers + "> m_specialUppers;\n")