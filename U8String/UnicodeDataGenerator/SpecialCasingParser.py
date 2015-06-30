import re


class SpecialCasingParser():

    def __init__(self, fileName):

        self.__fileName = fileName

    def parse(self):

        with open(self.__fileName) as ifile:

            lower = dict({})
            title = dict({})
            upper = dict({})

            for line in ifile:

                line = line.strip()

                reg = re.compile("[0-9A-F]+;( [0-9A-F]+)+;( [0-9A-F]+)+;( [0-9A-F]+)+")

                if reg.match(line):
                    tokens = line.split(";")
                    if len(tokens[1].split()) >= 2:
                        lower[tokens[2].strip()] = tokens[1].strip().split()
                    else:
                        title[tokens[1].strip()] = tokens[2].strip().split()
                        upper[tokens[1].strip()] = tokens[3].strip().split()

            sortedLower = []
            for key in sorted(lower.keys()):
                sortedLower.append((key, lower[key]))

            sortedTitle = []
            for key in sorted(title.keys()):
                sortedTitle.append((key, title[key]))

            sortedUpper = []
            for key in sorted(upper.keys()):
                sortedUpper.append((key, upper[key]))


            return [sortedLower, sortedTitle, sortedUpper]