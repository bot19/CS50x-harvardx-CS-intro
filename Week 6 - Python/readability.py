from cs50 import get_string

# adapt my readability C program into Python
# task: https:#cs50.harvard.edu/x/2025/psets/6/readability/

# get text
text = get_string("Text: ")

# calc letters, words, sentences
letters = 0
words = 1  # accommodates last sentence not counted in logic
sentences = 0

for i in range(len(text)):
    currentChar = text[i]

    # (1) get letters count
    # only count letters
    if currentChar.isalpha():
        # printf("%c\n", currentChar);
        letters += 1

    # (2) get words count; increment for each space character
    if currentChar == " ":
        words += 1

    # (3) get sentences count
    if currentChar == '.' or currentChar == '!' or currentChar == '?':
        sentences += 1

# get ratios per 100 words
wordRatio = 100 / words
letterRatio = letters * wordRatio
sentencesRatio = sentences * wordRatio

# work out grade
index = 0.0588 * letterRatio - 0.296 * sentencesRatio - 15.8

# print(f"L {letters} / W {words} / S {sentences} / RW {wordRatio} / G {index}")

# print grade logic
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")
