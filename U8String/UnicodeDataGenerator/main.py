from os.path import isfile
import sys

import CPPGenerator
import HPPGenerator
import SpecialCasingParser
import UnicodeDataParser

def main(argv):

    if len(argv) != 3 and len(argv) != 4:
        print("Use python3 " + argv[0] + " (SpecialCasing.txt) UnicodeData.txt filesNameOutput")
        return

    multicase = None

    if len(argv) == 3:
        inputFile = argv[1]
        output = argv[2]
    else:
        if not isfile(argv[1]):
            print("The inputFile: " + argv[1] + " is not a valid path.")
            return
        multicase = argv[1]
        inputFile = argv[2]
        output = argv[3]

    if not isfile(inputFile):
        print("The inputFile: " + inputFile + " is not a valid path.")
        return

    unicodeDataParser = UnicodeDataParser.UnicodeDataParser()

    datas = None
    datas = unicodeDataParser.parse(inputFile)

    oldBidi = datas[0].getBidi()
    oldCategory = datas[0].getCategory()
    oldCombine = datas[0].getCombine()
    #oldDecomp = datas[0].getDecom()
    oldMirror = datas[0].getMirror()

    listBidi = []
    listCate = []
    listCombi = []
    listDecomp = []
    listLower = []
    listMirror = []
    listTitle = []
    listUpper = []

    for data in datas:

        i = "0x" + data.getCodeValue()

        if oldBidi != data.getBidi():
            listBidi.append((i, str(oldBidi).replace("BidirectionalCategoryEnum.", "")))
            oldBidi = data.getBidi()

        if oldCategory != data.getCategory():
            listCate.append((i, str(oldCategory).replace("GeneralCategoryEnum.","")))
            oldCategory = data.getCategory()

        if oldCombine != data.getCombine():
            listCombi.append((i, oldCombine))
            oldCombine = data.getCombine()

        """if oldDecomp != data.getDecomposition():
            listDecomp.append((i, oldDecomp))
            oldDecomp = data.getDecomposition()"""

        if data.getLower() is not None:
            listLower.append((i, data.getLower()))

        if oldMirror != data.getMirror():
            listMirror.append((i, oldMirror))
            oldMirror = data.getMirror()

        if data.getTitle() is not None:
            listTitle.append((i, data.getTitle()))

        if data.getUpper() is not None:
            listUpper.append((i, data.getUpper()))

    numbers = [len(listBidi), len(listCate), len(listCombi), len(listLower), len(listMirror), len(listTitle), len(listUpper)]

    numbersSpecialCasing = None
    specialCasing = None
    if multicase is not None:
        specialCasingParser = SpecialCasingParser.SpecialCasingParser(multicase)
        specialCasing = specialCasingParser.parse()
        numbersSpecialCasing = [len(specialCasing[0]), len(specialCasing[1]), len(specialCasing[2])]

    generatorHPP = HPPGenerator.HPPGenerator(output, numbers, numbersSpecialCasing)
    generatorHPP.generate()

    ranges = [listBidi, listCate, listCombi, listLower, listMirror, listTitle, listUpper]

    generatorCPP = CPPGenerator.CPPGenerator(output, ranges, specialCasing)
    generatorCPP.generate()


if __name__ == "__main__":

    main(sys.argv)
