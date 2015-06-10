from os.path import isfile
import sys

import CPPGenerator
import HPPGenerator
import UnicodeDataParser

def main(argv):

    if len(argv) != 3:
        print("Use python3 " + argv[0] + " UnicodeData.txt filesNameOutput")
        return

    inputFile = argv[1]
    output = argv[2]

    if not isfile(inputFile):
        print("The inputFile: " + inputFile + " is not a valid path.")

    unicodeDataParser = UnicodeDataParser.UnicodeDataParser()

    datas = None
    #try:
    datas = unicodeDataParser.parse(inputFile)
    """except Exception as e:
        print(e)
        return"""

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

    it = 0
    for data in datas:

        i = hex(it)

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

        it += 1

    numbers = [len(listBidi), len(listCate), len(listCombi), len(listLower), len(listMirror), len(listTitle), len(listUpper)]

    generatorHPP = HPPGenerator.HPPGenerator(output, numbers)
    generatorHPP.generate()

    ranges = [listBidi, listCate, listCombi, listLower, listMirror, listTitle, listUpper]

    generatorCPP = CPPGenerator.CPPGenerator(output, ranges)
    generatorCPP.generate()


if __name__ == "__main__":

    main(sys.argv)
