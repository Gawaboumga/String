from BidirectionalCategoryEnum import BidirectionalCategoryEnum
from CharacterDecompositionMappingEnum import CharacterDecompositionMappingEnum
from GeneralCategoryEnum import GeneralCategoryEnum


class CPPGenerator:

    def __init__(self, output, datas):

        self.__output = output
        self.__datas = datas

    def generate(self):

        with open(self.__output + ".cpp", "w") as ofile:

            self.__writeIncludes(ofile)
            self.__writeFunctions(ofile)
            self.__writeDatas(ofile)

    def __writeIncludes(self, ofile):

        ofile.write("#include \"" + self.__output + ".hpp" + "\"\n\n")
        ofile.write("#include <algorithm>\n\n")

    def __writeFunctions(self, ofile):

        self.__writeBidiCategory(ofile)
        self.__writeCombining(ofile)
        #self.__writeDecomposition(ofile)
        self.__writeCategory(ofile)
        self.__writeLower(ofile)
        self.__writeMirror(ofile)
        self.__writeTitle(ofile)
        self.__writeUpper(ofile)

    def __writeBidiCategory(self, ofile):

        ofile.write(self.__output + "::BidirectionalCategory " + self.__output + "::bidirectional_category(Unicode character)\n")
        self.__writeFunctionRanges(ofile, "m_bidirectionals", "BidirectionalCategory")

    def __writeCombining(self, ofile):

        ofile.write("unsigned char " + self.__output + "::canonical_combining_classes(Unicode character)\n")
        self.__writeFunctionRanges(ofile, "m_combinings", "unsigned char")

    def __writeDecomposition(self, ofile):

        ofile.write(self.__output + "::CharacterDecompositionMapping " + self.__output + "::character_decomposition_mapping(Unicode character)\n")
        self.__writeFunctionRanges(ofile, "m_decompositions", "CharacterDecompositionMapping")

    def __writeCategory(self, ofile):
        ofile.write(self.__output + "::GeneralCategory " + self.__output + "::general_category(Unicode character)\n")
        self.__writeFunctionRanges(ofile, "m_categories", "GeneralCategory")

    def __writeLower(self, ofile):
        ofile.write(self.__output + "::Unicode " + self.__output + "::lowercase_mapping(Unicode character)\n")
        self.__writeFunctionFind(ofile, "m_lowers", "Unicode")

    def __writeMirror(self, ofile):
        ofile.write("bool " + self.__output + "::mirrored(Unicode character)\n")
        self.__writeFunctionRanges(ofile, "m_mirrors", "bool")

    def __writeTitle(self, ofile):
        ofile.write(self.__output + "::Unicode " + self.__output + "::titlecase_mapping(Unicode character)\n")
        self.__writeFunctionFind(ofile, "m_titles", "Unicode")

    def __writeUpper(self, ofile):
        ofile.write(self.__output + "::Unicode " + self.__output + "::uppercase_mapping(Unicode character)\n")
        self.__writeFunctionFind(ofile, "m_uppers", "Unicode")

    def __writeFunctionRanges(self, ofile, container, type):

        ofile.write("{\n")
        ofile.write("\tauto it = std::upper_bound(" + container + ".begin(), " + container + ".end(), character, [](Unicode characterIt, const std::pair<Unicode, " + type + ">& itPair) {\n")
        ofile.write("\t\treturn itPair.first > characterIt;\n")
        ofile.write("\t});\n\n")

        ofile.write("\tif (it == " + container + ".end())\n")
        ofile.write("\t\tthrow std::runtime_error(\"Character \" + std::to_string(character) + \" is not handled.\");\n")
        ofile.write("\telse\n")
        ofile.write("\t\treturn it->second;\n")
        ofile.write("}\n\n")

    def __writeFunctionFind(self, ofile, container, type):

        ofile.write("{\n")
        ofile.write("\tauto it = std::lower_bound(" + container + ".begin(), " + container + ".end(), character, [](const std::pair<Unicode, " + type + ">& itPair, Unicode characterIt) {\n")
        ofile.write("\t\treturn itPair.first < characterIt;\n")
        ofile.write("\t});\n\n")

        ofile.write("\tif (it == " + container + ".end())\n")
        ofile.write("\t\tthrow std::runtime_error(\"Character \" + std::to_string(character) + \" is not handled.\");\n")
        ofile.write("\telse\n")
        ofile.write("\t{\n")
        ofile.write("\t\tif (it->first != character)\n")
        ofile.write("\t\t\treturn character;\n")
        ofile.write("\t\telse\n")
        ofile.write("\t\t\treturn it->second;\n")
        ofile.write("\t}\n")
        ofile.write("}\n\n")

    def __writeDatas(self, ofile):

        self.__writeStatic(ofile, self.__datas[0], "m_bidirectionals", "BidirectionalCategory", True)
        self.__writeStatic(ofile, self.__datas[1], "m_categories", "GeneralCategory", True)
        self.__writeStatic(ofile, self.__datas[2], "m_combinings", "unsigned char")
        self.__writeStatic(ofile, self.__datas[3], "m_lowers", "Unicode", True)
        self.__writeStatic(ofile, self.__datas[4], "m_mirrors", "bool")
        self.__writeStatic(ofile, self.__datas[5], "m_titles", "Unicode", True)
        self.__writeStatic(ofile, self.__datas[6], "m_uppers", "Unicode", True)


    def __writeStatic(self, ofile, data, container, type, scopedType = False):

        if scopedType:
            ofile.write("std::array<std::pair<" + self.__output + "::Unicode, " + self.__output + "::" + type + ">, " + str(len(data)) + "> " + self.__output + "::" + container + " { {\n")
        else:
            ofile.write("std::array<std::pair<" + self.__output + "::Unicode, " + type + ">, " + str(len(data)) + "> " + self.__output + "::" + container + " { {\n")
        if type != "Unicode":
            if type == "bool":
                for tupleData in data:
                    ofile.write("\t{" + str(tupleData[0]) + ", " + str(tupleData[1]).lower() + "},\n")
            else:
                for tupleData in data:
                    ofile.write("\t{" + str(tupleData[0]) + ", " + str(tupleData[1]) + "},\n")
        else:
            for tupleData in data:
                ofile.write("\t{" + str(tupleData[0]) + ", 0x" + str(tupleData[1]) + "},\n")
        ofile.write("} };\n\n")
