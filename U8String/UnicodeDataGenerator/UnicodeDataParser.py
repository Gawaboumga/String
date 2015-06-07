import UnicodeData
import re


class UnicodeDataParser():

    def __init__(self):
        pass

    def parse(self, fileName):

        UnicodeDatas = []

        with open(fileName, "r") as ifile:

            for line in ifile:
                line = line.rstrip()
                tokens = line.split(";")

                p = re.compile(r"<.*,.*>")
                if p.match(tokens[1]):
                    line = next(ifile)
                    endRange = int(line.split(";")[0], 16)

                    for i in range(int(tokens[0], 16), endRange):
                        tokens[0] = "{0:x}".format(i)
                        UnicodeDatas.append(UnicodeData.UnicodeData(tokens))

                else:
                    UnicodeDatas.append(UnicodeData.UnicodeData(tokens))

        return UnicodeDatas
