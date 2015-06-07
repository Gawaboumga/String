from BidirectionalCategoryEnum import BidirectionalCategoryEnum
from CharacterDecompositionMappingEnum import CharacterDecompositionMappingEnum
from GeneralCategoryEnum import GeneralCategoryEnum


class UnicodeData():

    def __init__(self, tokens):

        self.__codeValue = tokens[0]
        self.__characterName = tokens[1]
        self.__generalCategory = self.__convertStringToGeneralCategory(tokens[2])
        self.__canonicalCombiningClasses = self.__convertStringToCanonicalCombiningClasses(tokens[3])
        self.__bidirectionalCategory = self.__convertStringToBidirectionalCategory(tokens[4])
        self.__characterDecompositionMapping = self.__convertStringToCharacterDecompositionMapping(tokens[5])
        self.__mirrored = self.__convertStringToMirror(tokens[9])

        self.__uppercaseMapping = tokens[12]
        self.__lowercaseMapping = tokens[13]
        self.__titlecaseMapping = tokens[14]

    def __convertStringToCodeValue(self, token):

        return int(token)

    def __convertStringToGeneralCategory(self, token):

        return GeneralCategoryEnum[token]

    def __convertStringToCanonicalCombiningClasses(self, token):

        return int(token)

    def __convertStringToBidirectionalCategory(self, token):

        return BidirectionalCategoryEnum[token]

    def __convertStringToCharacterDecompositionMapping(self, token):

        if token in CharacterDecompositionMappingEnum.__members__:
            return CharacterDecompositionMappingEnum[token]
        else:
            return CharacterDecompositionMappingEnum.Canonical

    def __convertStringToMirror(self, token):

        if token == "Y":
            return True
        elif token == "N":
            return False
        else:
            raise Exception

    def getLower(self):

        if len(self.__lowercaseMapping) == 0:
            return None

        return self.__lowercaseMapping

    def getTitle(self):

        if len(self.__titlecaseMapping) == 0:
            return None

        return self.__titlecaseMapping

    def getUpper(self):

        if len(self.__uppercaseMapping) == 0:
            return None

        return self.__uppercaseMapping

    def getCategory(self):

        return self.__generalCategory

    def getCombine(self):

        return self.__canonicalCombiningClasses

    def getBidi(self):

        return self.__bidirectionalCategory

    def getDecomposition(self):

        return self.__characterDecompositionMapping

    def getMirror(self):

        return self.__mirrored

    def __str__(self):

        return self.__codeValue